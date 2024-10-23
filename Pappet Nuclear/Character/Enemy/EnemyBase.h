#pragma once
#include "Character/CharacterBase.h"

class Player;
class SearchObject;
class AttackObject;

/// <summary>
/// �G�l�~�[�̃x�[�X�N���X
/// </summary>
class EnemyBase : public CharacterBase
{

public:
	//�R���X�g���N�^
	EnemyBase(Priority priority);
	//�f�X�g���N�^
	virtual ~EnemyBase();

	//virtual�Ōp������Ăяo��
	//����������
	virtual void Init(std::shared_ptr<MyLibrary::Physics> physics);
	//�X�V����
	virtual void Update(MyLibrary::LibVec3 playerPos, bool isChase) {};
	//�`�揈��
	virtual void Draw() {};
	//�I������
	virtual void End(std::shared_ptr<MyLibrary::Physics> physics);
	//�_���[�W���󂯂����ǂ������擾
	bool GetIsHit();
protected:
	//�ق��̃I�u�W�F�N�g�Ɖ����o����������铖���蔻����쐬
	void InitCollision(MyLibrary::LibVec3 vec, float len, float radius);
	//���f����ǂݍ���
	void LoadModel(std::string name);
	//�����N���X�̏�����
	void InitRigidbody(bool isUseGravity = true);
	//���f���̒��S���W���v�Z
	void CenterPos(float modeldefaultSize, float modelSize);
	//���f�����W��ݒ�
	void SetModelPos(float offset);
	//���G��������铖���蔻����쐬
	void InitSearch(float radius);
	//�U����������铖���蔻����쐬
	void InitAttack(float radius, MyLibrary::LibVec3 pos);
	//�_���[�W���󂯂���
	void OnDamage(float damage);
	//���S������
	void Death();

protected:
	std::shared_ptr<SearchObject> m_pSearch;        //���G��������铖���蔻��
	std::shared_ptr<AttackObject> m_pAttack;        //�U����������铖���蔻��

	bool m_enemySearchFlag[ENEMY_NOW];  //�G�̍��G�t���O
	bool m_enemyWait[ENEMY_NOW];    //�G����苗����ۂt���O
	bool m_enemyDeath;              //�G�����񂾔���
	int m_randomAction[ENEMY_NOW];    //�G�̃����_���s���𔻒f����ϐ�
	int m_animLeftWalking;   //�G�̍�����̃��[�V�����i�[�ϐ�
	int m_animRightWalking;   //�G�̉E����̃��[�V�����i�[�ϐ�
	int m_weakEnemyAnimation[ANIMATION][ENEMY_NOW];      //�G�̃A�j���[�V����
	bool m_weakAnimOne[ANIMATION][ENEMY_NOW];            //�G�̃A�j���[�V��������񂾂����s
	float m_weakAnimBlend[ENEMY_NOW];                    //�G�̃A�j���[�V�����u�����h��
	int m_core;               //�|�����Ƃ��ɂ��炦��R�A
	int m_allCore;            //�R�A���܂Ƃ߂�ϐ�
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
	int m_bossAnimTurnRight;      //�{�X�̉�]�A�j���[�V�����i�[�ϐ�
	int m_bossAnimTurnLeft;      //�{�X�̉�]�A�j���[�V�����i�[�ϐ�
	int m_bossAnimAttack1;   //�{�X�̍U���A�j���[�V�����i�[�ϐ�
	int m_bossAnimAttack2;   //�{�X�̍U���A�j���[�V�����i�[�ϐ�
	int m_bossAnimAttack3;   //�{�X�̍U���A�j���[�V�����i�[�ϐ�
	int m_bossAnimation[ANIMATION];  //�{�X�̃A�j���[�V�����i�[�ϐ�
	float m_bossTotalAnimTime[ANIMATION];  //�{�X�̃A�j���[�V�����Đ�����
	bool m_bossAnimOne[ANIMATION];      //�{�X�̃A�j���[�V��������񂾂����s
	SphereCol m_bossColDistance;        //��苗����ۂX�t�B�A�^�̓����蔻��
};

