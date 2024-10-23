#pragma once
#include "DxLib.h"
#include "Library/MyLibrary.h"
#include "Character/CharacterBase.h"
#include "Character/Player/Equipment/Equipment.h"
#include "Character/Player/WeaponSummary.h"
#include <list>
#include <memory>

class NewPlayer : public CharacterBase
{
public:
	//���x���֌W�̍\����
	struct LevelUpStatus
	{
		int sl_hp;         //�̗�
		int sl_stamina;    //�X�^�~�i
		int sl_muscle;     //�ؗ�
		int sl_skill;      //�Z��
		int sl_all;        //���ׂẴ��x��

	}m_levelStatus;

	NewPlayer();
	virtual ~NewPlayer();

	void Init(std::shared_ptr<MyLibrary::Physics> physics);
	void Finalize();
	void Update(std::shared_ptr<Equipment> eq);
	void Animation();
	void Draw(std::shared_ptr<Equipment> eq);

	//�Փ˂�����
	void OnCollideEnter(const std::shared_ptr<Collidable>& collidable) override;
	void OnTriggerEnter(const std::shared_ptr<Collidable>& collidable) override;

	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

	const MyLibrary::LibVec3 GetPos() const { return rigidbody.GetPos(); }



private:
	void SetModelPos();
private:
	XINPUT_STATE m_xpad;  //�p�b�h����
	float m_cameraAngle;  //�J�������
	float m_lockAngle;    //���b�N�I���������̃A���O�� 
	int m_recoveryNumber;     //�񕜂ł���񐔕ϐ�
	float m_heel;             //hp�ɑ����񕜗�
	bool m_recoberyAction;    //�񕜒��̔���
	bool m_lockonTarget;  //�^�[�Q�b�g���b�N�I������
	int m_moveAnimFrameIndex;  //�t���[������������
	int m_moveAnimFrameRight;   //�E��̃t���[������������
	VECTOR m_moveAnimFrameRigthPosition;  //�E��̃t���[���̃|�W�V����
	int m_moveAnimShieldFrameIndex;  //�K�[�h����Ƃ��̃t���[������
	int m_moveAnimShieldFrameHandIndex;     //�K�[�h����Ƃ��̑̂̃t���[������
	VECTOR m_moveAnimFrameLeftPosition;   //����̃t���[���̃|�W�V����
	MATRIX m_moveWeaponFrameMatrix;   //������A�^�b�`����t���[���̃��[�J�����W
	MATRIX m_moveShieldFrameMatrix;   //�����A�^�b�`����t���[���̃��[�J�����W
	bool m_oneAvoidance;   //��񂾂�����̕����𔻒肷��
	bool m_nextAttack1;  //���̍U������
	bool m_nextAttack2;  //���̍U������
	bool m_avoidanceNow;   //����ł���t���[���������f����ϐ�
	bool m_restAction;    //�񕜂��ł���悤�ɂȂ锻��
	bool m_dashMove;     //�_�b�V�����Ă锻�f�p�ϐ�
	bool m_staminaBroke;   //�X�^�~�i�؂ꔻ��
	bool m_menuOpen;      //���j���[���J��
	bool m_notWeapon;     //����������ĂȂ����
	bool m_notShield;     //���������ĂȂ����
	bool m_fistCol;       //���̓����蔻�菉����
	bool m_swordCol;      //���̓����蔻�菉��������
	VECTOR m_nowPos;   //���݂̃t���[���̍��W���擾����

	//�X�}�[�g�|�C���^
	std::shared_ptr<WeaponSummary> weapon = std::make_shared<WeaponSummary>();
};

