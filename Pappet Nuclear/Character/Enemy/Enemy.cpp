#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(int max)
{
	enemy->Init(max);	
}

void Enemy::BossInit()
{
	boss->Init();
}

void Enemy::Update(Player& player, Map& map, int max, int volume)
{
	enemy->Update(player, max, volume);
}

void Enemy::BossUpdate(Player& player, Map& map, int volume)
{
	boss->Update(player, map, volume);
}

void Enemy::MapHitWenemy(Map& map, int max)
{
	enemy->HitMap(map, max);
}

void Enemy::MapHitBoss(Map& map)
{
	boss->MapHit(map);
}

void Enemy::Draw(int max)
{
	enemy->Draw(max);
}

void Enemy::BossDraw()
{
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

SphereCol Enemy::GetAttackCol(int max)
{
	return enemy->GetAttackCol(max);
	
}
