#include "SceneGame.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "Character/Player/Item/ItemManager.h"
#include "Character/Effect/Effect.h"

namespace
{
	int seSize;      //seの音量
	int a;         //ブレンド率

	std::shared_ptr<ItemManager> item = std::make_shared<ItemManager>();

	//シングルトン
	auto& effect = Effect::GetInstance();
}

/// <summary>
/// コンストラクタ
/// </summary>
SceneGame::SceneGame():
	m_one(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
SceneGame::~SceneGame()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void SceneGame::Init()
{

	for (int i = 0; i < ENEMY_NOW; i++)
	{
		enemy->Init(i);
	}
	enemy->BossInit();
	camera->Init();
	map->Init();
	player->Init();
	ui->Init(*player, *enemy);
	setting->Init();
	bgmse->GameInit();
	bgmse->GameBGM();
	equipment->Init();

	a = 0;
}

/// <summary>
/// 更新処理
/// </summary>
/// <returns>シーンを返す</returns>
std::shared_ptr<SceneBase> SceneGame::Update()
{
	item->Update();
	player->SetCameraAngle(camera->GetAngleY());
	player->Update();
	player->WeaponUpdate(*equipment);
	player->PlaySE(setting->GetVolume());
	camera->Update(*player);
	map->Update();
	player->HitObj(*map, *item);
	enemy->MapHitBoss(*map);
	enemy->BossUpdate(*player, *map, setting->GetVolume());
	camera->HitObj(*map);

	enemy->isSphereBossHit(player->GetSphereCol(), player->GetDamage());
	enemy->isBossPlayerHit(player->GetCapsuleCol(), player->GetBounceMove(), player->GetBounceDis());
	enemy->isBossDistanceHit(player->GetCapsuleCol());
	map->CapsuleIsHit(player->GetCapsuleCol());
	map->CapsuleSaveHit(player->GetCapsuleCol());

	for (int i = 0; i < ITEM_NUMBER; i++)
	{
		map->CapsuleItemHit(player->GetCapsuleCol(), i);
	}

	for (int i = 0; i < ENEMY_NOW; i++)
	{
		player->OtherInfluence(enemy->GetOutPush(), enemy->GetWeakOutPush(i));
		enemy->Update(*player, *map, i, setting->GetVolume());
		enemy->isSeachHit(player->GetCapsuleCol(), i);
		enemy->isDistanceHit(player->GetCapsuleCol(), i);
		camera->LockUpdate(*player, *enemy, i);
		enemy->isSphereHit(player->GetSphereCol(), player->GetDamage(), i);
		enemy->MapHitWenemy(*map, i);
		player->IsCapsuleHit(enemy->GetCol(i), enemy->GetBossCol());
		
		//ボス部屋に入ってないとき
		if (map->GetRoomEntered() == false)
		{
			//盾の方が近かったら実行
			if (enemy->GetPlayerHit(i) == false)
			{
				player->isShieldHit(enemy->GetAttackCol(i), enemy->GetDamage());
			}
			player->isSphereHit(enemy->GetAttackCol(i), enemy->GetDamage());
		}
		
		enemy->isWeakPlayerHit(player->GetCapsuleCol(), player->GetBounceMove(), player->GetSpeed(), i);
		player->isTargetHit(enemy->GetCol(i), i);
	}

	//休息する場合
	if (player->GetRest() == true)
	{
		for (int i = 0; i < ENEMY_NOW; i++)
		{
			enemy->Init(i);
		}
		enemy->BossInit();
		player->Init();
		map->Init();

		player->SetRest(false);
	}
	//プレイヤーが死んだ場合
	if (player->GetDeath() == true)
	{
		a++;

		if (a > 300)
		{
			for (int i = 0; i < ENEMY_NOW; i++)
			{
				enemy->Init(i);
			}

			StopSoundMem(bgmse->GetBossBGM());  //サウンドを止める

			enemy->BossInit();
			map->Init();
			bgmse->GameBGM();
			player->Init();

			m_one = false;

			a = 0;
		}

	}

	//ボス部屋に入ったら
	if (map->GetRoomEntered() == true && m_one == false)
	{
		bgmse->BossBGM();

		m_one = true;
	}

	if (map->GetRoomEntered() == true)
	{
		//盾の方が近かったら実行
		if (enemy->GetBossPlayerHit() == false)
		{
			player->isBossShieldHit(enemy->GetBossAttackCol1(), enemy->GetBossAttackCol2(), enemy->GetBossAttackCol3(), enemy->BossGetDamage());
		}
		player->isBossSphereHit(enemy->GetBossAttackCol1(), enemy->GetBossAttackCol2(), enemy->GetBossAttackCol3(), enemy->BossGetDamage());
	}


	//ボスを倒したらゲームクリア
	if (enemy->GameClear() == true)
	{
		return std::make_shared<SceneClear>();
	}
	//タイトルに戻る
	if (setting->GetTitle() == true)
	{
		return std::make_shared<SceneTitle>();
	}

	//メニューを開く
	if (player->GetMenu() == true && setting->GetEquipment() == false)
	{
		setting->MenuUpdate();

		player->SetMenu(setting->GetReturn());
	}
	//メニューを開けるようにする
	else
	{
		setting->SetReturn(true);
	}
	//装備メニューを開く
	if (setting->GetEquipment() == true && equipment->GetRightEquipment() == false && equipment->GetLeftEquipment() == false)
	{
		equipment->Update();
	}
	//右手装備欄
	if (equipment->GetRightEquipment() == true && equipment->GetLeftEquipment() == false)
	{
		equipment->RightUpdate();
	}
	//左手装備欄
	if (equipment->GetLeftEquipment() == true && equipment->GetRightEquipment() == false)
	{
		equipment->LeftUpdate();
	}

	//コア取得
	player->SetCore(enemy->GetCore());

	bgmse->Update(setting->GetVolume());

	//エフェクトの更新
	Effect::GetInstance().Update();

	return shared_from_this();  //自身のポインタを返す
}

/// <summary>
/// 描画処理
/// </summary>
void SceneGame::Draw()
{

	map->Draw();
	camera->Draw();

	//エフェクト描画
	Effect::GetInstance().Draw();

	for (int i = 0; i < ENEMY_NOW; i++)
	{
		enemy->Draw(i);
	}

	enemy->BossDraw();
	
	//ロックオン表示
	if (player->GetLock() == true)
	{
		//DrawCircle(320, 200, 5, 0xffffff, true);

		DrawCircle(800, 200 * 2, 10, 0xffffff, true);
	}

	player->Draw();
	player->WeaponDraw(*equipment);
	ui->Draw(*player, *enemy, *equipment, *map, *item);

	//プレイヤーが死んだ場合
	if (player->GetDeath() == true)
	{

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		DrawBox(0, 170 * 2, 640 * 3, 260 * 2, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		ui->DiedDraw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}

	//メニューを開く
	if (player->GetMenu() == true && setting->GetEquipment() == false)
	{
		setting->MenuDraw();

		player->SetMenu(setting->GetReturn());
	}
	//装備メニューを開く
	if (setting->GetEquipment() == true && equipment->GetRightEquipment() == false && equipment->GetLeftEquipment() == false)
	{
		equipment->Draw();

		setting->SetEquipment(equipment->GetEquipment());
	}
	//右手の装備メニュー
	if (equipment->GetRightEquipment() == true && equipment->GetLeftEquipment() == false)
	{
		equipment->RightDraw();
	}
	//左手の装備メニュー
	if (equipment->GetLeftEquipment() == true && equipment->GetRightEquipment() == false)
	{
		equipment->LeftDraw();
	}

	setting->SettingDraw(setting->GetVolume());

	item->Draw();
}

/// <summary>
/// 終了処理
/// </summary>
void SceneGame::End()
{
	player->End();
	enemy->End(ENEMY_NOW);
	camera->End();
	map->End();
	equipment->End();
	setting->End();
	bgmse->End();
}
