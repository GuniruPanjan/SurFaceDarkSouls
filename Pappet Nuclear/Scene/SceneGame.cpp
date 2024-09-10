#include "SceneGame.h"
#include "SceneClear.h"

namespace
{
	int seSize;      //seの音量
	int a;         //ブレンド率
}

SceneGame::SceneGame():
	m_one(false)
{
}

SceneGame::~SceneGame()
{
}

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

	a = 0;
}

std::shared_ptr<SceneBase> SceneGame::Update()
{
	player->SetCameraAngle(camera->GetAngleY());
	player->Update();
	player->PlaySE(setting->GetVolume());
	camera->Update(*player);
	map->Update(*player);
	player->HitObj(*map);
	enemy->MapHitBoss(*map);
	enemy->BossUpdate(*player, *map, setting->GetVolume());
	camera->HitObj(*map);

	enemy->isSphereBossHit(player->GetSphereCol(), player->GetDamage());
	enemy->isBossPlayerHit(player->GetCapsuleCol(), player->GetBounceMove(), player->GetBounceDis());
	enemy->isBossDistanceHit(player->GetCapsuleCol());
	map->CapsuleIsHit(player->GetCapsuleCol());
	map->CapsuleSaveHit(player->GetCapsuleCol());

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
		//雑魚敵のアタックコルが問題
		player->isSphereHit(enemy->GetAttackCol(i), enemy->GetBossAttackCol1(), enemy->GetBossAttackCol2(), enemy->GetBossAttackCol3(), enemy->GetDamage(), enemy->BossGetDamage());
		enemy->isWeakPlayerHit(player->GetCapsuleCol(), player->GetBounceMove(), player->GetSpeed(), i);
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


	//ボスを倒したらゲームクリア
	if (enemy->GameClear() == true)
	{
		return std::make_shared<SceneClear>();
	}

	bgmse->Update(setting->GetVolume());

	return shared_from_this();  //自身のポインタを返す
}

void SceneGame::Draw()
{
	map->Draw();
	camera->Draw();
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
	ui->Draw(*player, *enemy);

	//プレイヤーが死んだ場合
	if (player->GetDeath() == true)
	{
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		//DrawBox(0, 170, 640, 260, 0x000000, true);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		//ui->DiedDraw();
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		DrawBox(0, 170 * 2, 640 * 3, 260 * 2, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		ui->DiedDraw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}

	setting->SettingDraw();
}

void SceneGame::End()
{
	player->End();
	enemy->End(ENEMY_NOW);
	camera->End();
	map->End();

	setting->End();
	bgmse->End();
}
