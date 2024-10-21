#include "MyLibrary.h"
#include "DxLib.h"
#include <cassert>

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="priority">�D��x</param>
/// <param name="tag">�^�O</param>
MyLibrary::Collidable::Collidable(Priority priority, ObjectTag tag):
	priority(priority),
	tag(tag)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MyLibrary::Collidable::~Collidable()
{
}

/// <summary>
/// ������(���M�ɓ����蔻���ǉ�)
/// </summary>
/// <param name="physics">�����N���X</param>
void MyLibrary::Collidable::Init(std::shared_ptr<MyLibrary::Physics> physics)
{
	physics->Entry(shared_from_this());   //�������Ɏ��g��Ԃ�
}

/// <summary>
/// �I��(���g�̓����蔻����폜)
/// </summary>
/// <param name="physics">�����N���X</param>
void MyLibrary::Collidable::Finalize(std::shared_ptr<MyLibrary::Physics> physics)
{
	physics->Exit(shared_from_this());    //�������o�^����
}

/// <summary>
/// �����蔻��𖳎�����^�O�̒ǉ�
/// </summary>
/// <param name="tag">�ǉ�����^�O</param>
void MyLibrary::Collidable::AddIgnoreTag(ObjectTag tag)
{
	//�����蔻��𖳎�����^�O�̃��X�g�ɒǉ��\��̃^�O�����݂��邩���m�F
	bool found = (std::find(ignoreTags.begin(), ignoreTags.end(), tag) != ignoreTags.end());
	//���X�g�̒��Ɋ��ɑ��݂��Ă�����x�����o��
	if (found)
	{
		assert(0 && "�w��^�O�͊��ɒǉ�����Ă��܂�");
	}
	else     //���݂��Ă��Ȃ�������ǉ�����
	{
		ignoreTags.emplace_back(tag);
	}
}

/// <summary>
/// �����蔻��𖳎�����^�O�̍폜
/// </summary>
/// <param name="tag">�폜����^�O</param>
void MyLibrary::Collidable::RemoveIgnoreTag(ObjectTag tag)
{
	//�����蔻��𖳎�����^�O�̃��X�g�ɒǉ��\��̃^�O�����݂��邩���m�F
	bool found = (std::find(ignoreTags.begin(), ignoreTags.end(), tag) != ignoreTags.end());
	//���X�g�̒��Ɋ��ɑ��݂��Ă�����x�����o��
	if (found)
	{
		assert(0 && "�w��^�O�͊��ɑ��݂��Ă��܂���");
	}
	else
	{
		ignoreTags.emplace_back(tag);
	}
}

/// <summary>
/// �����蔻��𖳎�����Ώۂ��ǂ���
/// </summary>
/// <param name="target">��������Ώۂ��m�F�����������蔻��</param>
/// <returns></returns>
bool MyLibrary::Collidable::IsIgnoreTarget(const std::shared_ptr<Collidable> target)
{
	//�m�F�����������蔻��̃^�O����������^�O�̃��X�g�Ɋ܂܂�Ă��邩�ǂ������ׂ�
	bool found = (std::find(ignoreTags.begin(), ignoreTags.end(), target->GetTag()) != ignoreTags.end());
	return found;
}

/// <summary>
/// �����蔻���ǉ�
/// </summary>
/// <param name="kind">�����蔻��̎��</param>
/// <param name="isTrigger">�����o����������邩�ǂ���</param>
/// <returns></returns>
std::shared_ptr<MyLibrary::CollidableData> MyLibrary::Collidable::AddCollider(const CollidableData::Kind kind, bool isTrigger)
{
	std::shared_ptr<CollidableData> add;

	//��ނɂ���Ēǉ����铖���蔻��̔h�����ύX����
	if (kind == CollidableData::Kind::Capsule)
	{
		add = std::make_shared<CollidableDataCapsule>(isTrigger);
	}
	else if (kind == CollidableData::Kind::Sphere)
	{
		add = std::make_shared<CollidableDataSphere>(isTrigger);
	}
	else if (kind == CollidableData::Kind::Rect)
	{
		add = std::make_shared<CollidableDataRect>(isTrigger);
	}
	else
	{
		assert(0 && "�w�肳�ꂽ��ނ̓����蔻���ǉ��ł��܂���ł���");
	}

	//�����蔻���ǉ�����
	m_colliders.emplace_back(add);

	return add;
}
