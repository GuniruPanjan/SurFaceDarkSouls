#include "HitObject.h"
#include "AttackObject.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="radius">���a</param>
/// <param name="len">����</param>
/// <param name="vec">�x�N�g��</param>
HitObject::HitObject(float radius, float len, MyLibrary::LibVec3 vec) :
	ObjectBase(Priority::Low, ObjectTag::Hit),
	m_pPhysics(),
	m_lastHitObjectAttack(0),
	m_hitObjectTag(),
	m_isEnemy(false),
	m_isHit(false)
{
	//�����蔻��̐ݒ�
	auto collider = Collidable::AddCollider(MyLibrary::CollidableData::Kind::Capsule, true);
	auto capsuleCol = dynamic_cast<MyLibrary::CollidableDataCapsule*>(collider.get());
	capsuleCol->m_radius = radius;
	capsuleCol->m_len = len;
	capsuleCol->m_vec = vec;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
HitObject::~HitObject()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="physics">�����N���X�̃|�C���^</param>
/// <param name="pos">�ݒ���W</param>
/// <param name="isEnemy">�����傪Enemy���ǂ���</param>
void HitObject::Init(std::shared_ptr<MyLibrary::Physics> physics, MyLibrary::LibVec3 pos, bool isEnemy)
{
	m_pPhysics = physics;
	m_isEnemy = isEnemy;

	Collidable::Init(m_pPhysics);

	rigidbody.Init();
	rigidbody.SetPos(pos);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="pos">�ݒ���W</param>
void HitObject::Update(MyLibrary::LibVec3 pos)
{
	rigidbody.SetPos(pos);
}

/// <summary>
/// �����蔻����폜
/// </summary>
/// <param name="physics">�����N���X�̃|�C���^</param>
void HitObject::Finalize(std::shared_ptr<MyLibrary::Physics> physics)
{
	Collidable::Finalize(physics);
}

/// <summary>
/// ���̃I�u�W�F�N�g�ɓ���������
/// </summary>
/// <param name="collidable"></param>
void HitObject::OnTriggerEnter(const std::shared_ptr<Collidable>& collidable)
{
	m_hitObjectTag = collidable->GetTag();
	if (m_isEnemy)
	{
		if (m_hitObjectTag == ObjectTag::Attack)
		{
			AttackObject* col = dynamic_cast<AttackObject*>(collidable.get());
			m_lastHitObjectAttack = col->GetAttack();
		}
		m_isHit = true;
	}
	else
	{
		if (m_hitObjectTag == ObjectTag::Attack)
		{
			AttackObject* col = dynamic_cast<AttackObject*>(collidable.get());
			m_lastHitObjectAttack = col->GetAttack();
		}
		m_isHit = true;

	}
}

/// <summary>
/// ���������I�u�W�F�N�g�̍U���͂��擾
/// </summary>
/// <returns></returns>
int HitObject::GetIsAttackNum()
{
	return m_lastHitObjectAttack;
}

/// <summary>
/// ���̃I�u�W�F�N�g�ɓ����������ǂ���
/// </summary>
/// <returns></returns>
bool HitObject::GetIsHit()
{
	//true��Ԃ����Ƃ�����false�ɂ���
	if (m_isHit)
	{
		m_isHit = false;
		return true;
	}

	return false;
}
