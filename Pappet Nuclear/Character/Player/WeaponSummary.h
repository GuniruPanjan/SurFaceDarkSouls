#pragma once
#include "DxLib.h"
#include<memory>

/// <summary>
/// ������Ǘ�����N���X
/// </summary>
class WeaponSummary
{
public:
	//�R���X�g���N�^
	WeaponSummary();
	//�f�X�g���N�^
	virtual ~WeaponSummary();

	//����������
	void Init();

	//�E��̑����X�V����
	void RightUpdate(MATRIX mat);

	//����̑����X�V����
	void LeftUpdate(MATRIX mat);

	//�E��̑����̕`�揈��
	void RightDraw();

	//����̑����̕`�揈��
	void LeftDraw();

	//�I������
	void End();

private:
	int m_weaponHandle;   //����̕ۑ��ϐ�
	float m_weaponSize;     //����̃T�C�Y�ύX
	int m_weaponFrameIndex;      //���f���̃C���f�b�N�X
	VECTOR m_weaponFramePosition;      //�A�^�b�`���郂�f���̃t���[�����W
	VECTOR m_weaponPosition;           //���f���̃|�W�V����
	MATRIX m_transMatrix;
	MATRIX m_weaponMatrixY;    //����̍s��Y
	MATRIX m_weaponMatrixZ;    //����̍s��Z
	MATRIX m_mixMatrix;      //�s�񍇐�

	//���̍\����
	struct WeaponShield
	{
		int m_shieldHandle;    //���̕ۑ��ϐ�
		float m_shieldSize;    //����̃T�C�Y�ύX
		int m_shieldFrameIndex;     //���f���̃C���f�b�N�X
		VECTOR m_shieldPos;     //���f���̃|�W�V�����ݒ�
		VECTOR m_shieldFramePosition;    //�A�^�b�`���郂�f���̃t���[�����W
		MATRIX m_transMatrix;
		MATRIX m_weaponMatrixY;    //����̍s��Y
		MATRIX m_weaponMatrixZ;    //����̍s��Z
		MATRIX m_mixMatrix;        //�s�񍇐�
	};

	//�X�}�[�g�|�C���^
	std::shared_ptr<WeaponShield> pshield = std::make_shared<WeaponShield>();
};

