#pragma once
#include "EnemyBase.h"



class WeakEnemy : public EnemyBase
{
public:
	WeakEnemy();
	virtual ~WeakEnemy();

	void Init(int max);
	void Update(Player& player, int max, int volume);
	void Action(Player& player, int max);
	void Animation(float& time, int max);
	void HitMap(Map& map, int max);
	void Draw(int max);
	void End(int max);

	bool isSphereHit(const SphereCol& col, float damage,int max);
	bool isSeachHit(const CapsuleCol& col,int max);
	bool isPlayerHit(const CapsuleCol& col,VECTOR& vec, float speed, int max);
	bool isDistanceHit(const CapsuleCol& col,int max);

	VECTOR GetPos(int max) { return m_weakEnemyPos[max]; }
	float GetPosX(int max) { return m_weakEnemyPos[max].x; }
	float GetPosY(int max) { return m_weakEnemyPos[max].y; }
	float GetPosZ(int max) { return m_weakEnemyPos[max].z; }
	float GetDamage() { return m_attack; }
	float GetWeakHp(int max) { return m_weakEnemyHp[max]; }
	VECTOR GetOutPush(int max) { return m_outPush[max]; }
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
	VECTOR m_weakDrawPos[ENEMY_NOW];                     //敵のDrawポジション
	float m_weakPlayTime[ENEMY_NOW];                     //敵のアニメーション時間
	VECTOR m_weakEnemyMove[ENEMY_NOW];                   //敵の移動ベクトル
	bool m_weakEnemyMoveAttack[ENEMY_NOW];               //敵の攻撃判定
	float m_weakEnemyAngle[ENEMY_NOW];                   //敵のアングル
	Pos3 m_weakColPos[ENEMY_NOW];                        //敵の当たり判定ポジション
	CapsuleCol m_weakCapsuleCol[ENEMY_NOW];              //敵の当たり判定カプセル
	float m_bounceX[ENEMY_NOW];                          //X軸方向算出
	float m_bounceZ[ENEMY_NOW];                          //Z軸方向算出
	float m_bounceAngle[ENEMY_NOW];                      //押し出すアングル
	VECTOR m_outPush[ENEMY_NOW];                         //押し出すベクトル

	//SE代入変数
	int m_hitSE[ENEMY_NOW];
	int m_attackSE[ENEMY_NOW];
	int m_walkSE[ENEMY_NOW];
	int m_diedSE[ENEMY_NOW];
};

