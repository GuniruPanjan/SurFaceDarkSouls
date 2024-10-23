#include "EnemyOne.h"

namespace
{
	//�L�����N�^�[��
	constexpr const char* cCharacterName = "Immortal";
	//���f���p�X
	constexpr const char* cModelPath = "Data/Enemy/EnemyModel.mv1";
	//���f���̊g�嗦
	constexpr float cModelSizeScale = 0.4f;
	//�����o�������蔻��̔��a
	constexpr float cCollisionRadius = 14.0f;
	//�����o�������蔻��̒���
	constexpr float cCollisionLen = 40.0f;
	//�����o�������蔻��̒���
	MyLibrary::LibVec3 cCollisionVec = MyLibrary::LibVec3(0.0f, 2.0f, 0.0f);
	//���G�͈�
	constexpr float cSearchRadius = 120.0f;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyOne::EnemyOne() :
	EnemyBase(Collidable::Priority::Middle)
{
	//�����蔻��̐ݒ�
	InitCollision(cCollisionVec, cCollisionLen, cCollisionRadius);
	//���f���̓ǂݍ���
	LoadModel(cModelPath);
	//���G�͈͂̐ݒ�
	m_searchRadius = cSearchRadius;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyOne::~EnemyOne()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="physics">�����N���X�̃|�C���^</param>
void EnemyOne::Init(std::shared_ptr<MyLibrary::Physics> physics)
{
	//���
	m_pPhysics = physics;

	Collidable::Init(m_pPhysics);

	//�����N���X�̏�����
	InitRigidbody();

	//���S���W�̐ݒ�
	CenterPos(1.0f, cModelSizeScale);

	//�����蔻��̍��W��ݒ�
	m_collisionPos = rigidbody.GetPos();

	//���f���̍��W��ݒ�
	SetModelPos(cModelSizeScale);
	MV1SetPosition(m_handle, m_modelPos.ConversionToVECTOR());

	//���G��������铖���蔻����쐬
	InitSearch(m_searchRadius);

	//���f���̃T�C�Y�ݒ�
	MV1SetScale(m_handle, VGet(cModelSizeScale, cModelSizeScale, cModelSizeScale));

}

void EnemyOne::Update(MyLibrary::LibVec3 playerPos, bool isChase)
{
}

void EnemyOne::Draw()
{
}
