#pragma once
#include "EnemyBase.h"
#include "WeakEnemy.h"
#include "BossEnemy.h"

/// <summary>
/// 敵の挙動や仕様をまとめる関数
/// </summary>
class Enemy : public EnemyBase
{
public:
	//コンストラクタ
	Enemy();
	//デストラクタ
	virtual ~Enemy();

	//初期化処理
	void Init(int max);
	//ボスの初期化処理
	void BossInit();
	//更新処理
	void Update(Player& player, Map& map, int max, int volume);
	//ボスの更新処理
	void BossUpdate(Player& player, Map& map, int volume);
	//マップとの判定更新
	void MapHitWenemy(Map& map, int max);
	//ボスのマップとの判定更新
	void MapHitBoss(Map& map);
	//描画処理
	void Draw(int max);
	//ボスの描画処理
	void BossDraw();
	//終了処理
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
	bool GetBossPlayerHit() { return boss->GetPlayerHit(); }

	//敵の取得変数
	VECTOR GetPos(int max) { return enemy->GetPos(max); }
	float GetPosX(int max) { return enemy->GetPosX(max); }
	float GetPosY(int max) { return enemy->GetPosY(max); }
	float GetPosZ(int max) { return enemy->GetPosZ(max); }
	float GetDamage() { return enemy->GetDamage(); }
	float GetWeakHp(int max) { return enemy->GetWeakHp(max); }
	VECTOR GetWeakOutPush(int max) { return enemy->GetOutPush(max); }
	CapsuleCol GetCol(int max) const { return enemy->GetCol(max); }
	SphereCol GetAttackCol(int max);
	bool isSphereHit(SphereCol col, float damage, int max) { return enemy->isSphereHit(col, damage, max); }
	bool isSeachHit(CapsuleCol col, int max) { return enemy->isSeachHit(col,max); }
	bool isDistanceHit(CapsuleCol col, int max) { return enemy->isDistanceHit(col,max); }
	bool isWeakPlayerHit(CapsuleCol col, VECTOR vec, float speed, int max) { return enemy->isPlayerHit(col, vec, speed, max); }
	bool GetPlayerHit(int max) { return enemy->GetPlayerHit(max); }

	//コアの所得変数
	int GetCore() { return m_baseCore + enemy->GetCore() + boss->GetCore(); }

private:
	//スマートポインタ
	std::shared_ptr<WeakEnemy> enemy = std::make_shared<WeakEnemy>();
	std::shared_ptr<BossEnemy> boss = std::make_shared<BossEnemy>();
};

