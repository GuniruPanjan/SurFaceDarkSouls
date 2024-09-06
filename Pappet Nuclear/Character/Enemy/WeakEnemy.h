#pragma once
#include "EnemyBase.h"



class WeakEnemy : public EnemyBase
{
public:
	WeakEnemy();
	virtual ~WeakEnemy();

	void Init(int max);
	void Update(Player& player, int max);
	void Action(Player& player, int max);
	void Animation(float& time, int max);
	void Draw(int max);
	void End(int max);

	bool isSphereHit(const SphereCol& col, float damage,int max);
	bool isSeachHit(const CapsuleCol& col,int max);
	bool isDistanceHit(const CapsuleCol& col,int max);

	VECTOR GetPos(int max) { return m_weakEnemyPos[max]; }
	float GetPosX(int max) { return m_weakEnemyPos[max].x; }
	float GetPosY(int max) { return m_weakEnemyPos[max].y; }
	float GetPosZ(int max) { return m_weakEnemyPos[max].z; }
	float GetDamage() { return m_attack; }
	const CapsuleCol GetCol(int max) { return m_weakCapsuleCol[max]; }
	const SphereCol GetAttackCol(int max) { return m_colAttack[max]; }


private:
	unsigned int m_color = 0xffffff;
	unsigned int m_seachColor = 0xffffff;
	unsigned int m_distanceColor = 0xffffff;

	//配列化するための変数
	int m_weakEnemyHandle[ENEMY_NOW];                    //敵のハンドル
	float m_weakEnemyHp[ENEMY_NOW];                      //敵のHP
	VECTOR m_weakEnemyPos[ENEMY_NOW];                    //敵のポジション
	float m_weakPlayTime[ENEMY_NOW];                     //敵のアニメーション時間
	VECTOR m_weakEnemyMove[ENEMY_NOW];                   //敵の移動ベクトル
	bool m_weakEnemyMoveAttack[ENEMY_NOW];               //敵の攻撃判定
	float m_weakEnemyAngle[ENEMY_NOW];                   //敵のアングル
	Pos3 m_weakColPos[ENEMY_NOW];                        //敵の当たり判定ポジション
	CapsuleCol m_weakCapsuleCol[ENEMY_NOW];              //敵の当たり判定カプセル
};

