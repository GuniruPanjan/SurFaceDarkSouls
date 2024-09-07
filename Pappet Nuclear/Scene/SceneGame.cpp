#include "SceneGame.h"
#include "SceneClear.h"

SceneGame::SceneGame()
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	enemy->Init(ENEMY_NOW);
	camera->Init();
	map->Init();
	player->Init();
	ui->Init(*player, *enemy);
	setting->Init();
}

std::shared_ptr<SceneBase> SceneGame::Update()
{
	player->SetCameraAngle(camera->GetAngleY());
	player->Update();
	player->OtherInfluence(enemy->GetOutPush());
	camera->Update(*player);
	map->Update(*player);
	player->HitObj(*map);
	enemy->BossUpdate(*player, *map);
	//camera->HitObj(*map);

	//player->isSphereHit(enemy->GetAttackCol(), enemy->GetBossAttackCol1(), enemy->GetBossAttackCol2(), enemy->GetBossAttackCol3(), enemy->GetDamage(), enemy->BossGetDamage());
	enemy->isSphereBossHit(player->GetSphereCol(), player->GetDamage());
	enemy->isBossPlayerHit(player->GetCapsuleCol(), player->GetBounceMove(), player->GetBounceDis());
	enemy->isBossDistanceHit(player->GetCapsuleCol());
	map->CapsuleIsHit(player->GetCapsuleCol());
	map->CapsuleSaveHit(player->GetCapsuleCol());

	for (int i = 0; i < ENEMY_NOW; i++)
	{
		enemy->Update(*player, *map, i);
		enemy->isSeachHit(player->GetCapsuleCol(), i);
		enemy->isDistanceHit(player->GetCapsuleCol(), i);
		player->IsCapsuleHit(enemy->GetCol(i), enemy->GetBossCol());
		camera->LockUpdate(*player, *enemy, i);
		enemy->isSphereHit(player->GetSphereCol(), player->GetDamage(), i);
	}

	//休息する場合
	if (player->GetRest() == true)
	{
		enemy->Init(ENEMY_NOW);
		
		player->Init();
		map->Init();

		player->SetRest(false);
	}
	//プレイヤーが死んだ場合
	if (player->GetDeath() == true)
	{
		enemy->Init(ENEMY_NOW);
		player->Init();
		map->Init();
	}


	//ボスを倒したらゲームクリア
	if (enemy->GameClear() == true)
	{
		return std::make_shared<SceneClear>();
	}

	return shared_from_this();  //自身のポインタを返す
}

void SceneGame::Draw()
{
	map->Draw();
	camera->Draw();
	player->Draw();
	for (int i = 0; i < ENEMY_NOW; i++)
	{
		enemy->Draw(i);
	}

	enemy->BossDraw();
	
	ui->Draw(*player, *enemy);

	setting->SettingDraw();
}

void SceneGame::End()
{
	player->End();
	enemy->End(ENEMY_NOW);
	camera->End();
	map->End();
}
