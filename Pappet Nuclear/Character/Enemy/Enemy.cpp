#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(int max)
{
	for (int i = 0; i < max; i++)
	{
		enemy->Init(i);
	}
	

	boss->Init();
}

void Enemy::Update(Player& player, Map& map, int max)
{
	enemy->Update(player, max);
	
	boss->Update(player, map);
}

void Enemy::Draw(int max)
{
	enemy->Draw(max);

	boss->Draw();
}

void Enemy::End(int max)
{
	for (int i = 0; i < max; i++)
	{
		enemy->End(i);
	}
	

	boss->End();
}
