#include "RectObject.h"

RectObject::RectObject(float width, float hight, float depth) :
	ObjectBase(Priority::Middle, ObjectTag::Shield),
	m_isEnter(false),
	m_isTriggerEnter(false)
{
	//�����蔻��̐ݒ�
	auto collider = Collidable::AddCollider(MyLibrary::CollidableData::Kind::Rect, true);
	auto rectCol = dynamic_cast<MyLibrary::CollidableDataRect*>(collider.get());
	rectCol->m_size = MyLibrary::LibVec3::Size(width, hight, depth);
}

RectObject::~RectObject()
{
}

void RectObject::Init(std::shared_ptr<MyLibrary::Physics> physics, MyLibrary::LibVec3 pos, bool isEnter)
{
	m_pPhysics = physics;
	m_isEnter = isEnter;

	Collidable::Init(m_pPhysics);

	rigidbody.Init();
	rigidbody.SetPos(pos);
}

void RectObject::Update(MyLibrary::LibVec3 pos)
{
	rigidbody.SetPos(pos);
}

void RectObject::Finalize(const std::shared_ptr<MyLibrary::Physics> physics)
{
	Collidable::Finalize(physics);
}

void RectObject::OnTriggerEnter(const std::shared_ptr<Collidable>& collidable)
{
	//�A�^�b�`�����I�u�W�F�N�g���{�X�������������Ȃ��Ȃ�
	if (!m_isEnter)
	{
		auto tag = collidable->GetTag();
		if (tag == ObjectTag::Attack)
		{
			m_isTriggerEnter = true;
		}
	}
	//�A�^�b�`�����I�u�W�F�N�g���{�X����������Ȃ�
	else
	{
		auto tag = collidable->GetTag();
		if (tag == ObjectTag::Player)
		{
			m_isTriggerEnter = true;
		}
	}
}

bool RectObject::GetIsTrigger()
{
	return m_isTriggerEnter;
}

void RectObject::IsTriggerReset()
{
	m_isTriggerEnter = false;
}
