#pragma once
#include "EnemyBase.h"

class BossEnemy : public EnemyBase
{
public:
	BossEnemy();
	virtual ~BossEnemy();

	void Init();
	void Update(Player& player, Map& map, int volume);
	void Action(Player& player);
	void Animation(float& time);
	void MapHit(Map& map);
	void Draw();
	void End();

	bool isSphereHit(const SphereCol& col, float damage);
	bool isPlayerHit(const CapsuleCol& col, VECTOR vec,float bounce);
	bool isCapsuleHit(const CapsuleCol& col);

	float GetDamage() { return m_attack; }
	bool GameClear() { return m_gameClear; }
	bool GetBattle() { return m_bossBattle; }
	bool GetPlayerHit() { return m_playerHit; }
	VECTOR GetPos() { return m_pos; }
	float GetPosX() { return m_pos.x; }
	float GetPosY() { return m_pos.y; }
	float GetPosZ() { return m_pos.z; }
	VECTOR GetOutPush() { return m_outPush; }
	float GetHp() { return m_hp; }

	CapsuleCol GetCol() const { return m_capsuleCol; }
	SphereCol GetAttackCol1() { return m_colBossAttackSphere1; }
	SphereCol GetAttackCol2() { return m_colBossAttackSphere2; }
	SphereCol GetAttackCol3() { return m_colBossAttackSphere3; }

	//コア所得
	int GetCore() { return m_baseCore; }


private:
	bool m_gameClear;        //ボスを倒したらゲームクリア
	bool m_bossDistance;     //ボスが離れていたときの判断
	bool m_bossBattle;       //ボスの臨戦態勢判定
	bool m_bossMoveAttack;   //ボスの攻撃行動判定
	bool m_bossMoveAttackPattern;    //ボスのパターン2の攻撃判定
	bool m_bossAttack1;           //ボスの攻撃1の判断
	bool m_bossAttack2;           //ボスの攻撃2の判断
	bool m_bossAttack3;           //ボスの攻撃3の判断
	bool m_playerHit;             //プレイヤーに攻撃を当てられる判定
	bool m_turnRight;             //右に回転する判定
	bool m_turnLeft;              //左に回転する判定
	int m_bossAttack;     //ボスの攻撃パターン
	bool m_one;           //一回だけ初期化する
	unsigned int m_color = 0xffffff;
	unsigned int m_seachColor = 0xffffff;
	unsigned int m_distanceColor = 0xffffff;
	Pos3 m_colBossAttackPos1;     //攻撃の当たり判定1
	Pos3 m_colBossAttackPos2;     //攻撃の当たり判定2
	Pos3 m_colBossAttackPos3;     //攻撃の当たり判定3
	float m_bossAttackRadius1;     //攻撃の当たり判定半径1
	float m_bossAttackRadius2;     //攻撃の当たり判定半径2
	float m_bossAttackRadius3;     //攻撃の当たり判定半径3
	SphereCol m_colBossAttackSphere1;    //攻撃の当たり判定Col1
	SphereCol m_colBossAttackSphere2;    //攻撃の当たり判定Col2  
	SphereCol m_colBossAttackSphere3;    //攻撃の当たり判定Col3
	float m_bounceAngle;      //押し出すアングル
	VECTOR m_outPush;        //押し出す方向ベクトル


	//std::shared_ptr<Effect> effect = std::make_shared<Effect>();
	BlendAnimation *pAnim;
	//std::shared_ptr<BlendAnimation> pAnim = std::make_shared<BlendAnimation>();
};

