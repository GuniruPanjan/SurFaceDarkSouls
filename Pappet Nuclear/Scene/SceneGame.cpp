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
	enemy->Init();
	camera->Init();
	map->Init();
	player->Init();
	ui->Init(*player, *enemy);
}

std::shared_ptr<SceneBase> SceneGame::Update()
{
	player->SetCameraAngle(camera->GetAngleY());
	player->Update();
	player->OtherInfluence(enemy->GetOutPush());
	enemy->Update(*player, *map);
	camera->Update(*player, *enemy);
	map->Update(*player);
	player->HitObj(*map);
	//camera->HitObj(*map);

	player->IsCapsuleHit(enemy->GetCol(), enemy->GetBossCol());
	//player->isSphereHit(enemy->GetAttackCol(), enemy->GetBossAttackCol1(), enemy->GetBossAttackCol2(), enemy->GetBossAttackCol3(), enemy->GetDamage(), enemy->BossGetDamage());
	enemy->isSphereHit(player->GetSphereCol(), player->GetDamage());
	enemy->isSphereBossHit(player->GetSphereCol(), player->GetDamage());
	enemy->isSeachHit(player->GetCapsuleCol());
	enemy->isDistanceHit(player->GetCapsuleCol());
	enemy->isBossPlayerHit(player->GetCapsuleCol(), player->GetBounceMove(), player->GetBounceDis());
	enemy->isBossDistanceHit(player->GetCapsuleCol());
	map->CapsuleIsHit(player->GetCapsuleCol());
	map->CapsuleSaveHit(player->GetCapsuleCol());

	//休息する場合
	if (player->GetRest() == true)
	{
		enemy->Init();
		player->Init();
		map->Init();

		player->SetRest(false);
	}
	//プレイヤーが死んだ場合
	if (player->GetDeath() == true)
	{
		enemy->Init();
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
	enemy->Draw();
	ui->Draw(*player, *enemy);
}

void SceneGame::End()
{
	player->End();
	enemy->End();
	camera->End();
	map->End();
}
