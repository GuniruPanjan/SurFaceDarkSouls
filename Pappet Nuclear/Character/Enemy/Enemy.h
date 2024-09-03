#pragma once
#include "EnemyBase.h"
#include "WeakEnemy.h"
#include "BossEnemy.h"

/// <summary>
/// 敵の挙動や仕様
/// </summary>
class Enemy : public EnemyBase
{
public:
	Enemy();
	virtual ~Enemy();

	void Init();
	void Update(Player& player, Map& map);
	void Draw();
	void End();

	VECTOR GetPos() { return enemy->GetPos(); }
	float GetPosX() { return enemy->GetPosX(); }
	float GetPosY() { return enemy->GetPosY(); }
	float GetPosZ() { return enemy->GetPosZ(); }
	float GetDamage() { return enemy->GetDamage(); }
	float BossGetDamage() { return boss->GetDamage(); }
	CapsuleCol GetCol() const { return enemy->GetCol(); }
	CapsuleCol GetBossCol() const { return boss->GetCol(); }
	SphereCol GetAttackCol() const { return enemy->GetAttackCol(); }
	SphereCol GetBossAttackCol1() const { return boss->GetAttackCol1(); }
	SphereCol GetBossAttackCol2() const { return boss->GetAttackCol2(); }
	SphereCol GetBossAttackCol3() const { return boss->GetAttackCol3(); }
	bool isSphereHit(SphereCol col, float damage) { return enemy->isSphereHit(col, damage); }
	bool isSphereBossHit(SphereCol col, float damage) { return boss->isSphereHit(col, damage); }
	bool isSeachHit(CapsuleCol col) { return enemy->isSeachHit(col); }
	bool isDistanceHit(CapsuleCol col) { return enemy->isDistanceHit(col); }
	bool isBossDistanceHit(CapsuleCol col) { return boss->isCapsuleHit(col); }
	bool GameClear() { return boss->GameClear(); }

private:
	//敵の構造体を配列で読み込み
	std::shared_ptr<WeakEnemy> enemy = std::make_shared<WeakEnemy>();
	std::shared_ptr<BossEnemy> boss = std::make_shared<BossEnemy>();
};

