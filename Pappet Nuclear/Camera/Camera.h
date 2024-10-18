#pragma once
#include "Character/Player/Player.h"
#include "Character/Enemy/Enemy.h"
#include <cmath>

class Map;

/// <summary>
/// �J�������Ǘ�����N���X
/// </summary>
class Camera
{
public:
	//�R���X�g���N�^
	Camera();
	//�f�X�g���N�^
	virtual ~Camera();

	//����������
	void Init();
	//�X�V����
	void Update(Player& player);
	//���b�N�I������
	void LockUpdate(Player& player, Enemy& enemy, int max);
	//�G���G�̃��b�N�I������
	void WeakLockUpdate(Player& player, Enemy& enemy, int weak);
	//�J�����̃}�b�v�����蔻��
	void HitObj(Map& map);
	//�`�揈��
	void Draw();
	//�I������
	void End();

	float GetAngleX() { return m_cameraAngle.x; }       //�J�����̃A���O���擾X���W
	float GetAngleY() { return m_cameraAngle.y; }       //�J�����̃A���O���擾Y���W
	float GetAngleZ() { return m_cameraAngle.z; }       //�J�����̃A���O���擾Z���W
	VECTOR GetAngle() { return m_cameraAngle; }         //�J�����̃A���O������

private:
	DINPUT_JOYSTATE input;

	//�J�����̃|�W�V����
	VECTOR m_cameraPos = VGet(0.0f, 0.0f, 0.0f);

	//�J�����̃^�[�Q�b�g
	VECTOR m_cameraTarget = VGet(0.0f, 0.0f, 0.0f);

	//�J�����̃A���O��
	VECTOR m_cameraAngle = VGet(0.0f, 0.0f, 0.0f);

	float m_x, m_z;
	float m_radius;

	//�}�b�v�Ƃ̓����蔻��
	bool m_HitFlag;              //�|���S���ɓ����������ǂ������L�����Ă����̂Ɏg���ϐ�
	int m_WallNum;               //�ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
	int m_FloorNum;              //���|���S���Ɣ��f���ꂽ�|���S���̐�
	MV1_COLL_RESULT_POLY_DIM HitDim;      //�L�����̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
	int m_HitDimNum;        //HitDim�̗L���Ȕz��v�f��
	MV1_COLL_RESULT_POLY* m_Wall[PLAYER_MAX_HITCOLL];     //�ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* m_Floor[PLAYER_MAX_HITCOLL];    //���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* m_Poly;  //�|���S���̍\���̂ɃA�N�Z�X���邽�߂ɂ��悤����|�C���^
};

