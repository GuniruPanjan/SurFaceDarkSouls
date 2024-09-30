#pragma once
#include "Character/CharacterBase.h"

class Player;

class EnemyBase : public CharacterBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	//virtual�Ōp������Ăяo��
	void Init() {};
	void Update() {};
	void Draw() {};
	virtual void End();
	
protected:
	bool m_enemySearchFlag[ENEMY_NOW];  //�G�̍��G�t���O
	bool m_enemyWait[ENEMY_NOW];    //�G����苗����ۂt���O
	int m_randomAction[ENEMY_NOW];    //�G�̃����_���s���𔻒f����ϐ�
	int m_animLeftWalking;   //�G�̍�����̃��[�V�����i�[�ϐ�
	int m_animRightWalking;   //�G�̉E����̃��[�V�����i�[�ϐ�
	int m_weakEnemyAnimation[ANIMATION][ENEMY_NOW];      //�G�̃A�j���[�V����
	int m_core;               //�|�����Ƃ��ɂ��炦��R�A
	float m_weakEnemyTotalAnimationTime[ANIMATION][ENEMY_NOW];    //�G�̃A�j���[�V�����̑�����
	float m_searchRadius;  //�~�̓����蔻��
	float m_distanceRadius;  //�~�̔��a
	float m_attackRadius;   //�U�����a
	float m_moveTurning[ENEMY_NOW];   //���v���ɐ��񂷂邽�߂̖@���x�N�g��
	float m_moveReverseTurning[ENEMY_NOW];  //�����v����ɐ��񂷂邽�߂̖@���x�N�g��
	float m_randomNextActionTime[ENEMY_NOW];   //���Ƀ����_���s�����邽�߂̎���
	Pos3 m_colSearchPos[ENEMY_NOW];  //���G�͈͂̓����蔻��
	Pos3 m_colDistancePos[ENEMY_NOW];   //��苗����ۂ��߂̔���
	Pos3 m_colAttackPos[ENEMY_NOW];    //�U���̓����蔻��
	SphereCol m_colSearch[ENEMY_NOW];  //�X�t�B�A�^�̓����蔻��
	SphereCol m_colDistance[ENEMY_NOW];  //��苗����ۂX�t�B�A�^�̓����蔻��
	SphereCol m_colAttack[ENEMY_NOW];   //�U���̓����蔻��

	//�{�X�����̕ϐ�
	int m_bossModelHandle;   //�{�X�̃��f���n���h��
	float m_bossSize;        //�{�X�̃��f���T�C�Y�ϐ�
	int m_bossAnimStand;     //�{�X�̗����A�j���[�V�����i�[�ϐ�
	int m_bossAnimDeath;     //�{�X�̎��S�A�j���[�V�����i�[�ϐ�
	int m_bossAnimWalk;      //�{�X�̕����A�j���[�V�����i�[�ϐ�
	int m_bossAnimAttack1;   //�{�X�̍U���A�j���[�V�����i�[�ϐ�
	int m_bossAnimAttack2;   //�{�X�̍U���A�j���[�V�����i�[�ϐ�
	int m_bossAnimAttack3;   //�{�X�̍U���A�j���[�V�����i�[�ϐ�
	int m_bossAnimation[ANIMATION];  //�{�X�̃A�j���[�V�����i�[�ϐ�
	float m_bossTotalAnimTime[ANIMATION];  //�{�X�̃A�j���[�V�����Đ�����
	SphereCol m_bossColDistance;        //��苗����ۂX�t�B�A�^�̓����蔻��
};

