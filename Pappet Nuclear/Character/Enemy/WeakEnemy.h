#pragma once
#include "EnemyBase.h"


/// <summary>
/// �G���G���Ǘ�����N���X
/// </summary>
class WeakEnemy : public EnemyBase
{
public:
	//�R���X�g���N�^
	WeakEnemy();
	//�f�X�g���N�^
	virtual ~WeakEnemy();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="max">�G�̍ő吔</param>
	void Init(int max);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="player">�v���C���[�Ăяo��</param>
	/// <param name="max">�G�̍ő吔</param>
	/// <param name="volume">����</param>
	void Update(Player& player, int max, int volume);

	/// <summary>
	/// �G�̍s���������܂Ƃ߂�
	/// </summary>
	/// <param name="player">�v���C���[�Ăяo��</param>
	/// <param name="max">�G�̍ő吔</param>
	void Action(Player& player, int max);

	/// <summary>
	/// �G�̃A�j���[�V�����֘A���܂Ƃ߂�
	/// </summary>
	/// <param name="time">�A�j���[�V�����Đ�����</param>
	/// <param name="max">�G�̍ő吔</param>
	void Animation(float& time, int max);

	/// <summary>
	/// �G�̃A�j���[�V�������u�����h����֐�
	/// </summary>
	/// <param name="time">�A�j���[�V�����Đ�����</param>
	/// <param name="max">�G�̍ő吔</param>
	/// <param name="blendNumber">�u�����h�������A�j���[�V�����i�[�ԍ�</param>
	/// <param name="DNumber">�u�����h�ŊO�������A�j���[�V�����i�[�ԍ�</param>
	void BlendAnimation(float& time, int max, int blendNumber, int DNumber);

	/// <summary>
	/// �}�b�v�Ƃ̓����蔻��
	/// </summary>
	/// <param name="map">�}�b�v�̌Ăяo��</param>
	/// <param name="max">�G�̍ő吔</param>
	void HitMap(Map& map, int max);

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="max">�G�̍ő吔</param>
	void Draw(int max);

	/// <summary>
	/// �I������
	/// </summary>
	/// <param name="max">�G�̍ő吔</param>
	void End(int max);

	//�U���̓����蔻��
	bool isSphereHit(const SphereCol& col, float damage,int max);
	//���G�͈͂̓����蔻��
	bool isSeachHit(const CapsuleCol& col,int max);
	//�v���C���[�Ƃ̓����蔻��
	bool isPlayerHit(const CapsuleCol& col,VECTOR& vec, float speed, int max);
	//������ۂ����蔻��
	bool isDistanceHit(const CapsuleCol& col,int max);

	VECTOR GetPos(int max) { return m_weakEnemyPos[max]; }              //�G�l�~�[�̃|�W�V��������
	float GetPosX(int max) { return m_weakEnemyPos[max].x; }            //�G�l�~�[�̃|�W�V��������X���W
	float GetPosY(int max) { return m_weakEnemyPos[max].y; }            //�G�l�~�[�̃|�W�V��������Y���W
	float GetPosZ(int max) { return m_weakEnemyPos[max].z; }            //�G�l�~�[�̃|�W�V��������Z���W
	float GetDamage() { return m_status.s_attack; }                     //�G�l�~�[�̍U���͏���
	float GetWeakHp(int max) { return m_weakEnemyHp[max]; }             //�G�l�~�[��HP����
	VECTOR GetOutPush(int max) { return m_outPush[max]; }               //�v���C���[�������o���x�N�^�[
	const CapsuleCol GetCol(int max) { return m_weakCapsuleCol[max]; }  //�G�l�~�[�̃J�v�Z������
	const SphereCol GetAttackCol(int max) { return m_colAttack[max]; }  //�G�l�~�[�̋��̏���
	bool GetPlayerHit(int max) { return m_playerHit[max]; }             //�v���C���[�ɍU����������������

	//�R�A����
	int GetCore() { return m_core; }


private:
	unsigned int m_color = 0xffffff;
	unsigned int m_seachColor = 0xffffff;
	unsigned int m_distanceColor = 0xffffff;

	//�z�񉻂��邽�߂̕ϐ�
	int m_weakEnemyHandle[ENEMY_NOW];                    //�G�̃n���h��
	float m_weakEnemyHp[ENEMY_NOW];                      //�G��HP
	VECTOR m_weakEnemyPos[ENEMY_NOW];                    //�G�̃|�W�V����
	VECTOR m_weakDrawPos[ENEMY_NOW];                     //�G��Draw�|�W�V����
	VECTOR m_weakEnemyMove[ENEMY_NOW];                   //�G�̈ړ��x�N�g��
	bool m_weakEnemyMoveAttack[ENEMY_NOW];               //�G�̍U������
	float m_weakEnemyAngle[ENEMY_NOW];                   //�G�̃A���O��
	Pos3 m_weakColPos[ENEMY_NOW];                        //�G�̓����蔻��|�W�V����
	CapsuleCol m_weakCapsuleCol[ENEMY_NOW];              //�G�̓����蔻��J�v�Z��
	float m_bounceX[ENEMY_NOW];                          //X�������Z�o
	float m_bounceZ[ENEMY_NOW];                          //Z�������Z�o
	float m_bounceAngle[ENEMY_NOW];                      //�����o���A���O��
	VECTOR m_outPush[ENEMY_NOW];                         //�����o���x�N�g��
	bool m_playerHit[ENEMY_NOW];                         //�v���C���[�ɓ����锻��
	bool m_death[ENEMY_NOW];                             //���񂾔���

	//�A�j���[�V�����֌W
	float m_weakPlayTime[ENEMY_NOW];                     //�G�̃A�j���[�V��������
	bool m_weakAnimBlendOne[ENEMY_NOW];                       //�G�̃u�����h��0�ɂ��锻��

	//SE����ϐ�
	int m_hitSE[ENEMY_NOW];
	int m_attackSE[ENEMY_NOW];
	int m_walkSE[ENEMY_NOW];
	int m_diedSE[ENEMY_NOW];

	//�G�t�F�N�g�ϐ�
	int m_effectWeakHit[ENEMY_NOW];                          //�U���������������̃G�t�F�N�g
};

