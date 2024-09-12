#pragma once
#include "DxLib.h"

class WeaponSummary
{
public:
	WeaponSummary();
	virtual ~WeaponSummary();

	void Init();
	void Update(MATRIX mat);
	void Draw(VECTOR& vector);
	void End();

private:
	int m_weaponHandle;   //����̕ۑ��ϐ�
	float m_weaponSize;     //����̃T�C�Y�ύX
	int m_weaponFrameIndex;      //���f���̃C���f�b�N�X
	VECTOR m_weaponPos;        //���f���̃|�W�V�����ݒ�
	VECTOR m_weaponFramePosition;      //�A�^�b�`���郂�f���̃t���[�����W
	VECTOR m_weaponPosition;           //���f���̃|�W�V����
	MATRIX m_transMatrix;
	MATRIX m_weaponMatrixY;    //����̍s��Y
	MATRIX m_weaponMatrixZ;    //����̍s��Z
	MATRIX m_mixMatrix;      //�s�񍇐�
};

