#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	enemy->Init();
	boss->Init();
}

void Enemy::Update(Player& player, Map& map)
{
	enemy->Update(player);
	boss->Update(player, map);
}

void Enemy::Draw()
{
	enemy->Draw();
	boss->Draw();
}

void Enemy::End()
{
	enemy->End();
	boss->End();
}
