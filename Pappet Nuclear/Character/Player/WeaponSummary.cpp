#include "WeaponSummary.h"
#include "Singleton/HandleManager.h"

namespace
{
	int a;
	MATRIX temp;
	MATRIX mat;

	//�V���O���g��
	auto& handle = HandleManager::GetInstance();
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
WeaponSummary::WeaponSummary():
	m_weaponHandle(-1),
	m_weaponSize(0.0f),
	m_weaponFrameIndex(0),
	m_weaponFramePosition(VGet(0.0f, 0.0f, 0.0f)),
	m_weaponPosition(VGet(0.0f,0.0f,0.0f))
{
	m_transMatrix = MV1GetFrameLocalWorldMatrix(0, 0);
	m_mixMatrix = MV1GetFrameLocalWorldMatrix(0, 0);
	m_weaponMatrixY = MGetRotY(5.655f);
	m_weaponMatrixZ = MGetRotZ(1.795f);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WeaponSummary::~WeaponSummary()
{
	//���������
	MV1DeleteModel(m_weaponHandle);
	MV1DeleteModel(pshield->m_shieldHandle);

	//���������
	handle.Clear();
}

/// <summary>
/// ����������
/// </summary>
void WeaponSummary::Init()
{
	m_weaponSize = 0.5f;

	m_weaponHandle = handle.GetModelHandle("Data/Weapon/Sword.mv1");

	m_weaponPosition = VGet(0.0f, 1.947f, -1.947f);

	//�T�C�Y�ύX
	MV1SetScale(m_weaponHandle, VGet(m_weaponSize, m_weaponSize, m_weaponSize));


	//���̏�����
	pshield->m_shieldSize = 1.0f;
	pshield->m_shieldHandle = handle.GetModelHandle("Data/Weapon/Shield.mv1");
	pshield->m_mixMatrix = MV1GetFrameLocalMatrix(0, 0);
	pshield->m_shieldFrameIndex = 0;
	pshield->m_shieldFramePosition = VGet(0.0f, 0.0f, 0.0f);
	pshield->m_shieldPos = VGet(0.0f, 0.0f, 7.787f);
	pshield->m_transMatrix = MV1GetFrameLocalWorldMatrix(0, 0);
	pshield->m_weaponMatrixY = MGetRotY(3.142f);
	pshield->m_weaponMatrixZ = MGetRotZ(0.0f);
}

/// <summary>
/// �E��̑����̍X�V����
/// </summary>
/// <param name="mat">�E��̍s��</param>
void WeaponSummary::RightUpdate(MATRIX mat)
{
	MV1SetMatrix(m_weaponHandle, MGetIdent());

	//�t���[��������
	m_weaponFrameIndex = MV1SearchFrame(m_weaponHandle, "2:Sphere");

	m_weaponFramePosition = MV1GetFramePosition(m_weaponHandle, m_weaponFrameIndex);

	m_weaponPosition = VAdd(m_weaponFramePosition, m_weaponPosition);

	//�A�^�b�`���郂�f�����t���[���̍��W�����_�ɂ��邽�߂̕��s�ړ��s����쐬
	m_transMatrix = MGetTranslate(VScale(m_weaponPosition, -1.0f));

	m_transMatrix = MMult(m_transMatrix, m_weaponMatrixY);
	m_transMatrix = MMult(m_transMatrix, m_weaponMatrixZ);

	m_mixMatrix = MMult(m_transMatrix, mat);

	MV1SetMatrix(m_weaponHandle, m_mixMatrix);
}

/// <summary>
/// ����̍X�V����
/// </summary>
/// <param name="mat">����̍s��</param>
void WeaponSummary::LeftUpdate(MATRIX mat)
{
	MV1SetMatrix(pshield->m_shieldHandle, MGetIdent());

	//�t���[��������
	pshield->m_shieldFrameIndex = MV1SearchFrame(pshield->m_shieldHandle, "0:fbx");

	pshield->m_shieldFramePosition = MV1GetFramePosition(pshield->m_shieldHandle, pshield->m_shieldFrameIndex);

	pshield->m_shieldPos = VAdd(pshield->m_shieldFramePosition, pshield->m_shieldPos);

	//�A�^�b�`���郂�f�����t���[���̍��W�����_�ɂ��邽�߂̕��s�ړ��s����쐬
	pshield->m_transMatrix = MGetTranslate(VScale(pshield->m_shieldPos, -1.0f));

	pshield->m_transMatrix = MMult(pshield->m_transMatrix, pshield->m_weaponMatrixY);
	pshield->m_transMatrix = MMult(pshield->m_transMatrix, pshield->m_weaponMatrixZ);

	pshield->m_mixMatrix = MMult(pshield->m_transMatrix, mat);

	MV1SetMatrix(pshield->m_shieldHandle, pshield->m_mixMatrix);
}

/// <summary>
/// �E��̑����̕`�揈��
/// </summary>
void WeaponSummary::RightDraw()
{
	//���f���`��
	MV1DrawModel(m_weaponHandle);
}

/// <summary>
/// ����̑����̕`�揈��
/// </summary>
void WeaponSummary::LeftDraw()
{
	//���f���`��
	MV1DrawModel(pshield->m_shieldHandle);
}

/// <summary>
/// �I������
/// </summary>
void WeaponSummary::End()
{
	//���������
	MV1DeleteModel(m_weaponHandle);
	MV1DeleteModel(pshield->m_shieldHandle);

	//���������
	handle.Clear();
}
