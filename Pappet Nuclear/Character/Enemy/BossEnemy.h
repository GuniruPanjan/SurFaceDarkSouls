#pragma once
#include "EnemyBase.h"

/// <summary>
/// �{�X���Ǘ�����N���X
/// </summary>
class BossEnemy : public EnemyBase
{
public:
	//�R���X�g���N�^
	BossEnemy();
	//�f�X�g���N�^
	virtual ~BossEnemy();

	//����������
	void Init();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="player">�v���C���[�Ăяo��</param>
	/// <param name="map">�}�b�v�Ăяo��</param>
	/// <param name="volume">����</param>
	void Update(Player& player, Map& map, int volume);

	/// <summary>
	/// �{�X�̍s������
	/// </summary>
	/// <param name="player">�v���C���[�Ăяo��</param>
	void Action(Player& player);

	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="time">�Đ�����</param>
	void Animation(float& time);

	/// <summary>
	/// �}�b�v�̔���
	/// </summary>
	/// <param name="map">�}�b�v�Ăяo��</param>
	void MapHit(Map& map);

	//�`�揈��
	void Draw();

	//�I������
	void End();

	/// <summary>
	/// �U����������������
	/// </summary>
	/// <param name="col">�v���C���[�̃J�v�Z��</param>
	/// <param name="damage">�_���[�W</param>
	/// <returns></returns>
	bool isSphereHit(const SphereCol& col, float damage);

	/// <summary>
	/// �J�v�Z�����m�̓����蔻��
	/// </summary>
	/// <param name="col">�J�v�Z��</param>
	/// <param name="vec">�x�N�^�[</param>
	/// <param name="bounce">�����o������</param>
	/// <returns></returns>
	bool isPlayerHit(const CapsuleCol& col, VECTOR vec,float bounce);

	/// <summary>
	/// �ԍ�������
	/// </summary>
	/// <param name="col">�J�v�Z��</param>
	/// <returns></returns>
	bool isCapsuleHit(const CapsuleCol& col);

	float GetDamage() { return m_status.s_attack; }
	bool GameClear() { return m_gameClear; }
	bool GetBattle() { return m_bossBattle; }
	bool GetPlayerHit() { return m_playerHit; }
	VECTOR GetPos() { return m_pos; }
	float GetPosX() { return m_pos.x; }
	float GetPosY() { return m_pos.y; }
	float GetPosZ() { return m_pos.z; }
	VECTOR GetOutPush() { return m_outPush; }
	float GetHp() { return m_status.s_hp; }

	CapsuleCol GetCol() const { return m_capsuleCol; }
	SphereCol GetAttackCol1() { return m_colBossAttackSphere1; }
	SphereCol GetAttackCol2() { return m_colBossAttackSphere2; }
	SphereCol GetAttackCol3() { return m_colBossAttackSphere3; }

	//�R�A����
	int GetCore() { return m_core; }


private:
	bool m_gameClear;        //�{�X��|������Q�[���N���A
	bool m_bossDistance;     //�{�X������Ă����Ƃ��̔��f
	bool m_bossBattle;       //�{�X�̗Ր�Ԑ�����
	bool m_bossMoveAttack;   //�{�X�̍U���s������
	bool m_bossMoveAttackPattern;    //�{�X�̃p�^�[��2�̍U������
	bool m_bossAttack1;           //�{�X�̍U��1�̔��f
	bool m_bossAttack2;           //�{�X�̍U��2�̔��f
	bool m_bossAttack3;           //�{�X�̍U��3�̔��f
	bool m_playerHit;             //�v���C���[�ɍU���𓖂Ă��锻��
	bool m_turnRight;             //�E�ɉ�]���锻��
	bool m_turnLeft;              //���ɉ�]���锻��
	int m_bossAttack;     //�{�X�̍U���p�^�[��
	bool m_one;           //��񂾂�����������
	unsigned int m_color = 0xffffff;
	unsigned int m_seachColor = 0xffffff;
	unsigned int m_distanceColor = 0xffffff;
	Pos3 m_colBossAttackPos1;     //�U���̓����蔻��1
	Pos3 m_colBossAttackPos2;     //�U���̓����蔻��2
	Pos3 m_colBossAttackPos3;     //�U���̓����蔻��3
	float m_bossAttackRadius1;     //�U���̓����蔻�蔼�a1
	float m_bossAttackRadius2;     //�U���̓����蔻�蔼�a2
	float m_bossAttackRadius3;     //�U���̓����蔻�蔼�a3
	SphereCol m_colBossAttackSphere1;    //�U���̓����蔻��Col1
	SphereCol m_colBossAttackSphere2;    //�U���̓����蔻��Col2  
	SphereCol m_colBossAttackSphere3;    //�U���̓����蔻��Col3
	float m_bounceAngle;      //�����o���A���O��
	VECTOR m_outPush;        //�����o�������x�N�g��


	BlendAnimation *pAnim;
};

