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

	void Init(int max);
	void BossInit();
	void Update(Player& player, Map& map, int max, int volume);
	void BossUpdate(Player& player, Map& map, int volume);
	void MapHitWenemy(Map& map, int max);
	void MapHitBoss(Map& map);
	void Draw(int max);
	void BossDraw();
	void End(int max);

	//ボスの取得変数
	VECTOR GetBossPos() { return boss->GetPos(); }
	float GetBossPosX() { return boss->GetPosX(); }
	float GetBossPosY() { return boss->GetPosY(); }
	float GetBossPosZ() { return boss->GetPosZ(); }
	float GetBossHp() { return boss->GetHp(); }
	float BossGetDamage() { return boss->GetDamage(); }
	CapsuleCol GetBossCol() const { return boss->GetCol(); }
	SphereCol GetBossAttackCol1() const { return boss->GetAttackCol1(); }
	SphereCol GetBossAttackCol2() const { return boss->GetAttackCol2(); }
	SphereCol GetBossAttackCol3() const { return boss->GetAttackCol3(); }
	VECTOR GetOutPush() { return boss->GetOutPush(); }
	bool isSphereBossHit(SphereCol col, float damage) { return boss->isSphereHit(col, damage); }
	bool isBossPlayerHit(CapsuleCol col, VECTOR vec, float bounce) { return boss->isPlayerHit(col, vec, bounce); }
	bool isBossDistanceHit(CapsuleCol col) { return boss->isCapsuleHit(col); }
	bool GameClear() { return boss->GameClear(); }
	bool GetBattale() { return boss->GetBattle(); }

	//敵の取得変数
	VECTOR GetPos(int max) { return enemy->GetPos(max); }
	float GetPosX(int max) { return enemy->GetPosX(max); }
	float GetPosY(int max) { return enemy->GetPosY(max); }
	float GetPosZ(int max) { return enemy->GetPosZ(max); }
	float GetDamage() { return enemy->GetDamage(); }
	VECTOR GetWeakOutPush(int max) { return enemy->GetOutPush(max); }
	CapsuleCol GetCol(int max) const { return enemy->GetCol(max); }
	SphereCol GetAttackCol(int max);
	bool isSphereHit(SphereCol col, float damage, int max) { return enemy->isSphereHit(col, damage,max); }
	bool isSeachHit(CapsuleCol col, int max) { return enemy->isSeachHit(col,max); }
	bool isDistanceHit(CapsuleCol col, int max) { return enemy->isDistanceHit(col,max); }
	bool isWeakPlayerHit(CapsuleCol col, VECTOR vec, float speed, int max) { return enemy->isPlayerHit(col, vec, speed, max); }

	//VECTOR GetPos() { return weakenemy[4]->GetPos(); }
	//float GetPosX() { return weakenemy[4]->GetPosX(); }
	//float GetPosY() { return weakenemy[4]->GetPosY(); }
	//float GetPosZ() { return weakenemy[4]->GetPosZ(); }
	//float GetDamage() { return weakenemy[4]->GetDamage(); }
	//CapsuleCol GetCol() const { return weakenemy[4]->GetCol(); }
	//SphereCol GetAttackCol() const { return weakenemy[4]->GetAttackCol(); }
	//bool isSphereHit(SphereCol col, float damage) { return weakenemy[4]->isSphereHit(col, damage); }
	//bool isSeachHit(CapsuleCol col) { return weakenemy[4]->isSeachHit(col); }
	//bool isDistanceHit(CapsuleCol col) { return weakenemy[4]->isDistanceHit(col); }

private:
	//敵の構造体を配列で読み込み
	std::shared_ptr<WeakEnemy> enemy = std::make_shared<WeakEnemy>();
	std::shared_ptr<BossEnemy> boss = std::make_shared<BossEnemy>();
};

