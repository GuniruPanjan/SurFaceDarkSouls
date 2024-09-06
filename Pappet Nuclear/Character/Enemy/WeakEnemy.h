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

	//�z�񉻂��邽�߂̕ϐ�
	int m_weakEnemyHandle[ENEMY_NOW];                    //�G�̃n���h��
	float m_weakEnemyHp[ENEMY_NOW];                      //�G��HP
	VECTOR m_weakEnemyPos[ENEMY_NOW];                    //�G�̃|�W�V����
	float m_weakPlayTime[ENEMY_NOW];                     //�G�̃A�j���[�V��������
	VECTOR m_weakEnemyMove[ENEMY_NOW];                   //�G�̈ړ��x�N�g��
	bool m_weakEnemyMoveAttack[ENEMY_NOW];               //�G�̍U������
	float m_weakEnemyAngle[ENEMY_NOW];                   //�G�̃A���O��
	Pos3 m_weakColPos[ENEMY_NOW];                        //�G�̓����蔻��|�W�V����
	CapsuleCol m_weakCapsuleCol[ENEMY_NOW];              //�G�̓����蔻��J�v�Z��
};

