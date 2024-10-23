#pragma once
#include "ObjectBase.h"

/// <summary>
/// �U�����󂯂铖���蔻��N���X
/// </summary>
class HitObject : public ObjectBase
{
public:
	//�R���X�g���N�^
	HitObject(float radius, float len, MyLibrary::LibVec3 vec);
	//�f�X�g���N�^
	~HitObject();

	//������
	void Init(std::shared_ptr<MyLibrary::Physics> physics, MyLibrary::LibVec3 pos, bool isEnemy);
	//�X�V
	void Update(MyLibrary::LibVec3 pos);

	//�����蔻��폜
	void Finalize(std::shared_ptr<MyLibrary::Physics> physics) override;

	//�ق��̃I�u�W�F�N�g�ɓ���������
	void OnTriggerEnter(const std::shared_ptr<Collidable>& collidable) override;

	//���������I�u�W�F�N�g�̍U���͂��擾
	int GetIsAttackNum();

	//�ق��̃I�u�W�F�N�g�ɓ��������ǂ���
	bool GetIsHit();
private:
	//�����N���X�̃|�C���^
	std::shared_ptr<MyLibrary::Physics> m_pPhysics;

	//�Ō�ɓ��������I�u�W�F�N�g�̍U����
	int m_lastHitObjectAttack;
	//���������I�u�W�F�N�g�̃^�O
	ObjectTag m_hitObjectTag;
	//���̃N���X�̎����傪�G���ǂ���
	bool m_isEnemy;
	//�ق��̃I�u�W�F�N�g�ɂ����������ǂ���
	bool m_isHit;

};

