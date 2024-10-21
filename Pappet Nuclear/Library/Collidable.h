#pragma once
#include "ObjectTag.h"
#include <List>
#include <memory>

namespace MyLibrary
{

	class Rigidbody;
	class Physics;
	class CollidableData;

	class Collidable : public std::enable_shared_from_this<Collidable>
	{
		friend Physics;
	public:

		//�ʒu�␳�̗D��x�̔���
		enum class Priority : int
		{
			Low,        //��
			Middle,     //��
			High,       //��
			Static,     //�����Ȃ�
		};

	public:
		//�R���X�g���N�^
		Collidable(Priority priority, ObjectTag tag);
		//�f�X�g���N�^
		virtual ~Collidable();
		//������
		virtual void Init(std::shared_ptr<MyLibrary::Physics> physics);
		//�I��
		virtual void Finalize(std::shared_ptr<MyLibrary::Physics> physics);

		//�����蔻��֐�
		virtual void OnCollideEnter(const std::shared_ptr<Collidable>& collider){}
		virtual void OnCollideStay(const std::shared_ptr<Collidable>& collider){}
		virtual void OnCollideExit(const std::shared_ptr<Collidable>& collider){}
		virtual void OnTriggerEnter(const std::shared_ptr<Collidable>& collider){}
		virtual void OnTriggerStay(const std::shared_ptr<Collidable>& collider){}
		virtual void OnTriggerExit(const std::shared_ptr<Collidable>& collider){}

		//�^�O������
		ObjectTag GetTag() const { return tag; }
		//�D��x������
		Priority GetPriority() const { return priority; }

		//�����蔻��𖳎�����^�O�̒ǉ��ƍ폜
		void AddIgnoreTag(ObjectTag tag);
		void RemoveIgnoreTag(ObjectTag tag);

		//�����蔻��𖳎�����Ώۂ��ǂ���
		bool IsIgnoreTarget(const std::shared_ptr<Collidable> target);

	protected:
		//�����蔻���ǉ�
		std::shared_ptr<CollidableData> AddCollider(const CollidableData::Kind kind, bool isTrigger);

	protected:
		//�����f�[�^
		Rigidbody rigidbody;
		//�����蔻����
		std::list<std::shared_ptr<CollidableData>> m_colliders;


	private:
		//�^�O
		ObjectTag tag;
		//�D��x
		Priority priority;

		//�����蔻��𖳎�����^�O�̃��X�g
		std::list<ObjectTag> ignoreTags;
	};

}


