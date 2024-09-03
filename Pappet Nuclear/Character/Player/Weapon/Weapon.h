#pragma once
#include "DxLib.h"

class Weapon
{
public:
	Weapon();
	virtual ~Weapon();

	void Init();
	void Update(MATRIX& matrix);
	void Draw(VECTOR& vector);
	void End();

private:
	int m_weaponHandle;   //����̕ۑ��ϐ�
	float m_weaponSize;     //����̃T�C�Y�ύX
	int m_weaponFrameIndex;      //���f���̃C���f�b�N�X
	VECTOR m_weaponPos;        //���f���̃|�W�V�����ݒ�
	VECTOR m_weaponFramePosition;      //�A�^�b�`���郂�f���̃t���[�����W
	MATRIX m_transMatrix;
	MATRIX m_mixMatrix;      //�s�񍇐�
};

