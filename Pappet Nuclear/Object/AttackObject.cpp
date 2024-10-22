#include "AttackObject.h"

AttackObject::AttackObject(float radius) :
	ObjectBase(Priority::Middle, ObjectTag::Attack),
	m_isEnemy(false),
	m_isTriggerEnter(false)
{
	//当たり判定の設定
	auto collider = Collidable::AddCollider(MyLibrary::CollidableData::Kind::Sphere, true);
	auto sphereCol = dynamic_cast<MyLibrary::CollidableDataSphere*>(collider.get());
	sphereCol->m_radius = radius;
}

AttackObject::~AttackObject()
{
}

void AttackObject::Init(std::shared_ptr<MyLibrary::Physics> physics, MyLibrary::LibVec3 pos, bool isEnemy)
{
	m_pPhysics = physics;
	m_isEnemy = isEnemy;

	Collidable::Init(m_pPhysics);

	rigidbody.Init();
	rigidbody.SetPos(pos);
}

void AttackObject::Update(MyLibrary::LibVec3 pos)
{
	rigidbody.SetPos(pos);
}

void AttackObject::Finalize(std::shared_ptr<MyLibrary::Physics> physics)
{
	Collidable::Finalize(physics);
}

void AttackObject::OnTriggerEnter(const std::shared_ptr<Collidable>& collidable)
{
	//アタッチしたオブジェクトが敵じゃないなら
	if (!m_isEnemy)
	{
		auto tag = collidable->GetTag();
		if (tag == ObjectTag::Enemy)
		{
			m_isTriggerEnter = true;
		}
	}
	//アタッチしたオブジェクトが敵なら
	else
	{
		auto tag = collidable->GetTag();
		if (tag == ObjectTag::Player)
		{
			m_isTriggerEnter = true;
		}
	}
}

bool AttackObject::GetIsTrigger()
{
	return m_isTriggerEnter;
}

void AttackObject::IsTriggerReset()
{
	m_isTriggerEnter = false;
}
