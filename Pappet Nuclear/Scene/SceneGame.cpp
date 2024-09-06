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
}

std::shared_ptr<SceneBase> SceneGame::Update()
{
	player->SetCameraAngle(camera->GetAngleY());
	player->Update();
	player->OtherInfluence(enemy->GetOutPush());
	enemy->Update(*player, *map, ENEMY_NOW);
	camera->Update(*player, *enemy, ENEMY_NOW);
	map->Update(*player);
	player->HitObj(*map);
	//camera->HitObj(*map);

	player->IsCapsuleHit(enemy->GetCol(ENEMY_NOW), enemy->GetBossCol());
	//player->isSphereHit(enemy->GetAttackCol(), enemy->GetBossAttackCol1(), enemy->GetBossAttackCol2(), enemy->GetBossAttackCol3(), enemy->GetDamage(), enemy->BossGetDamage());
	enemy->isSphereHit(player->GetSphereCol(), player->GetDamage(), ENEMY_NOW);
	enemy->isSphereBossHit(player->GetSphereCol(), player->GetDamage());
	enemy->isSeachHit(player->GetCapsuleCol(), ENEMY_NOW);
	enemy->isDistanceHit(player->GetCapsuleCol(), ENEMY_NOW);
	enemy->isBossPlayerHit(player->GetCapsuleCol(), player->GetBounceMove(), player->GetBounceDis());
	enemy->isBossDistanceHit(player->GetCapsuleCol());
	map->CapsuleIsHit(player->GetCapsuleCol());
	map->CapsuleSaveHit(player->GetCapsuleCol());

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
	enemy->Draw(ENEMY_NOW);
	ui->Draw(*player, *enemy);
}

void SceneGame::End()
{
	player->End();
	enemy->End(ENEMY_NOW);
	camera->End();
	map->End();
}
