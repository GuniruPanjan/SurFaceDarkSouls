#include "Weapon.h"

Weapon::Weapon() :
	m_weaponHandle(-1),
	m_weaponSize(0.0f),
	m_weaponFrameIndex(0),
	m_weaponPos(VGet(0.0f, -2.0f, 0.0f)),
	m_weaponFramePosition(VGet(0.0f,0.0f,0.0f))
{
}

Weapon::~Weapon()
{
	MV1DeleteModel(m_weaponHandle);
}

void Weapon::Init()
{
	m_weaponSize = 0.5f;

	m_weaponHandle = MV1LoadModel("Data/Weapon/Sword.mv1");

	//�T�C�Y�ύX
	MV1SetScale(m_weaponHandle, VGet(m_weaponSize, m_weaponSize, m_weaponSize));
}

void Weapon::Update(MATRIX& matrix)
{
	//�A�^�b�`���郂�f����MV1SetMatrix�̐ݒ�𖳌�������
	MV1SetMatrix(m_weaponHandle, MGetIdent());

	//�t���[��������
	m_weaponFrameIndex = MV1SearchFrame(m_weaponHandle, "2:Sphere");

	//�A�^�b�`���郂�f���̃t���[���̍��W���擾����
	m_weaponFramePosition = MV1GetFramePosition(m_weaponHandle, m_weaponFrameIndex);

	//�A�^�b�`���郂�f�����t���[���̍��W�����_�ɂ��邽�߂̕��s�ړ��s����쐬
	m_transMatrix = MGetTranslate(VScale(m_weaponFramePosition, 0.0f));

	m_mixMatrix = MMult(m_transMatrix, matrix);
}

void Weapon::Draw(VECTOR& vector)
{
	//���������s����A�^�b�`���郂�f���ɃZ�b�g
	//MV1SetMatrix(m_weaponHandle, m_mixMatrix);

	//�x�N�g�����s��ŕϊ�
	m_weaponPos = VTransform(m_weaponPos, m_mixMatrix);

	//vector = VAdd(vector, m_weaponPos);

	//���f���̍��W�ݒ�
	MV1SetPosition(m_weaponHandle, vector);

	//3D���f���̉�]�n���Z�b�g����
	MV1SetRotationXYZ(m_weaponHandle, VGet(5.0f, 0.0f, 0.0f));

	DrawFormatString(0, 300, 0xffffff, "m_weaponPos.x : %f", m_weaponPos.x);
	DrawFormatString(0, 320, 0xffffff, "m_weaponPos.y : %f", m_weaponPos.y);
	DrawFormatString(0, 340, 0xffffff, "m_weaponPos.z : %f", m_weaponPos.z);


	//���f���`��
	MV1DrawModel(m_weaponHandle);
}

void Weapon::End()
{
	MV1DeleteModel(m_weaponHandle);
}