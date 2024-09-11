#include "WeaponSummary.h"

namespace
{
	int a;
	MATRIX temp;
	MATRIX mat;
}

WeaponSummary::WeaponSummary():
	m_weaponHandle(-1),
	m_weaponSize(0.0f),
	m_weaponFrameIndex(0),
	m_weaponPos(VGet(0.0f, 10.0f, 0.0f)),
	m_weaponFramePosition(VGet(0.0f, 0.0f, 0.0f))
{
	m_transMatrix = MV1GetFrameLocalWorldMatrix(0, 0);
	m_mixMatrix = MV1GetFrameLocalWorldMatrix(0, 0);
}

WeaponSummary::~WeaponSummary()
{
	//���������
	MV1DeleteModel(m_weaponHandle);
}

void WeaponSummary::Init()
{
	m_weaponSize = 0.5f;

	m_weaponHandle = MV1LoadModel("Data/Weapon/Sword.mv1");

	//�T�C�Y�ύX
	MV1SetScale(m_weaponHandle, VGet(m_weaponSize, m_weaponSize, m_weaponSize));
}

void WeaponSummary::Update(int handle, int frame)
{
	//�t���[��������
	m_weaponFrameIndex = MV1SearchFrame(m_weaponHandle, "2:Sphere");

	//�A�^�b�`���郂�f���̃t���[���̍��W���擾����
	m_weaponFramePosition = MV1GetFramePosition(handle, frame);
	auto mt = MV1GetFrameLocalWorldMatrix(m_weaponHandle, m_weaponFrameIndex);
	auto rotation = MGetRotY(DX_PI_F);
	temp = MMult(rotation, mt);
	auto scaleMat = MGetScale(VGet(0.5f, 0.5f, 0.5f));
	mat = MMult(scaleMat, temp);

	////�A�^�b�`���郂�f�����t���[���̍��W�����_�ɂ��邽�߂̕��s�ړ��s����쐬
	//m_transMatrix = MGetTranslate(VScale(m_weaponFramePosition, -1.0f));

	//m_mixMatrix = MMult(m_transMatrix, matrix);

	//�A�^�b�`���郂�f����MV1SetMatrix�̐ݒ�𖳌�������
	//MV1SetMatrix(m_weaponHandle, mat);
}

void WeaponSummary::Draw(VECTOR& vector)
{
	//���������s����A�^�b�`���郂�f���ɃZ�b�g
	//MV1SetMatrix(m_weaponHandle, m_mixMatrix);

	//�x�N�g�����s��ŕϊ�
	//m_weaponPos = VTransform(m_weaponPos, m_mixMatrix);

	//vector = VAdd(vector, m_weaponPos);

	//���f���̍��W�ݒ�
	//MV1SetPosition(m_weaponHandle, vector);
	//MV1SetPosition(m_weaponHandle, m_weaponPos);

	//3D���f���̉�]�n���Z�b�g����
	//MV1SetRotationXYZ(m_weaponHandle, VGet(5.0f, 0.0f, 0.0f));

	//MV1DrawModel(m_weaponHandle);

	DrawFormatString(0, 300, 0xffffff, "vector.x : %f", vector.x);
	DrawFormatString(0, 320, 0xffffff, "vector.y : %f", vector.y);
	DrawFormatString(0, 340, 0xffffff, "vector.z : %f", vector.z);

	DrawFormatString(0, 400, 0xffffff, "m_weaponPosition.x : %f", m_weaponFramePosition.x);
	DrawFormatString(0, 440, 0xffffff, "m_weaponPosition.y : %f", m_weaponFramePosition.y);
	DrawFormatString(0, 480, 0xffffff, "m_weaponPosition.z : %f", m_weaponFramePosition.z);


	//���f���`��
	MV1DrawModel(m_weaponHandle);
}

void WeaponSummary::End()
{
	//���������
	MV1DeleteModel(m_weaponHandle);
}
