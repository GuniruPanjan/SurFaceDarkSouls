#include "MyLibrary.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	//�ő哖���蔻��|���S����
	constexpr int kMaxColHitPoly = 3000;
	//�ǉ����o�������̍ő厎�s��
	constexpr int kMaxColHitTry = 20;
	//�ǉ����o�����ɃX���C�h�����鋗��
	constexpr float kColHitSlideLength = 1.0f;
	//�ǃ|���S�������|���S�����𔻒f���邽�߂̕ϐ�
	constexpr float kWallPolyBorder = 0.4f;
	//�ǃ|���S���Ɣ��f���邽�߂̍����ϐ�
	constexpr float kWallPolyHeight = 5.0f;

	//�d��
	constexpr float kGravity = -0.018f;
	//�ő�d�͉����x
	constexpr float kMaxGravity = -2.0f;

	//�␳�O���F
	const int kBeforeColor = 0xffffff;
	//�␳�O�\����F
	const int kBeforePlanColor = 0x00ff00;
	//�␳����F
	const int kAfterColor = 0xffff00;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="mapStageCollisionHandle">�L�����N�^�[�̃X�e�[�W�����蔻��n���h��</param>
MyLibrary::Physics::Physics(int mapStageCollisionHandle)
{
	m_stageCollisionHandle = mapStageCollisionHandle;
}

/// <summary>
/// �Փ˕��̓o�^
/// </summary>
/// <param name="collidable">�ǉ����铖���蔻��</param>
void MyLibrary::Physics::Entry(std::shared_ptr<Collidable> collidable)
{
	//�o�^
	bool found = (std::find(m_collidables.begin(), m_collidables.end(), collidable) != m_collidables.end());

	if (!found)
	{
		m_collidables.emplace_back(collidable);
	}
	//���ɓo�^����Ă���G���[
	else
	{
		assert(0 && "�w���collidable�͓o�^�ς݂ł�");
	}

}

/// <summary>
/// �Փ˕��̓o�^�폜
/// </summary>
/// <param name="collidable">�폜���铖���蔻��</param>
void MyLibrary::Physics::Exit(std::shared_ptr<Collidable> collidable)
{
	bool found = (std::find(m_collidables.begin(), m_collidables.end(), collidable) != m_collidables.end());
	if (found)
	{
		m_collidables.remove(collidable);
	}
	//�o�^����Ă��Ȃ�������G���[
	else
	{
		assert(0 && "�w���collidable���o�^����Ă��܂���");
	}

}

/// <summary>
/// �X�V
/// </summary>
void MyLibrary::Physics::Update()
{
	//�����蔻��̃��O���c��
	m_preCollideInfo = m_newCollideInfo;
	m_newCollideInfo.clear();
	m_preTriggerInfo = m_newTriggerInfo;
	m_newTriggerInfo.clear();
	m_onCollideInfo.clear();

	//�ړ�
	for (auto& item : m_collidables)
	{
		auto pos = item->rigidbody.GetPos();
		auto velocity = item->rigidbody.GetVelocity();

		//�d�͂𗘗p����ݒ�Ȃ�A�d�͂�ǉ�
		if (item->rigidbody.GetUseGravity())
		{
			velocity = velocity + LibVec3(0.0f, kGravity, 0.0f);

			//�ő�d�͂��傫��������
			if (velocity.y < kMaxGravity)
			{
				velocity = LibVec3(velocity.x, kMaxGravity, velocity.z);
			}
		}

		auto nextPos = pos + velocity;

		item->rigidbody.SetVelocity(velocity);

		//���Ƃ��Ƃ̏��A�\������f�o�b�O�\��
#if _DEBUG

		for (const auto& collider : item->m_colliders)
		{
			auto kind = collider->GetKind();
			if (kind == CollidableData::Kind::Capsule)
			{
				auto capsuleData = dynamic_cast<MyLibrary::CollidableDataCapsule*> (collider.get());
				auto vec = capsuleData->m_vec;
				auto len = capsuleData->m_len;
				auto radius = capsuleData->m_radius;
				MyLibrary::DebugDraw::AddDrawCapsule(pos, vec, radius, len, kBeforeColor);
				MyLibrary::DebugDraw::AddDrawCapsule(nextPos, vec, radius, len, kBeforePlanColor);
			}
			else if (kind == CollidableData::Kind::Sphere)
			{
				auto sphereData = dynamic_cast<MyLibrary::CollidableDataSphere*> (collider.get());
				auto radius = sphereData->m_radius;
				MyLibrary::DebugDraw::AddDrawSphere(pos, radius, kBeforeColor);
				MyLibrary::DebugDraw::AddDrawSphere(pos, radius, kBeforePlanColor);
			}
			else if (kind == CollidableData::Kind::Rect)
			{
				auto rectData = dynamic_cast<MyLibrary::CollidableDataRect*> (collider.get());
				auto size = rectData->m_size;
				MyLibrary::DebugDraw::AddDrawRect(pos, size, kBeforeColor);
				MyLibrary::DebugDraw::AddDrawRect(pos, size, kBeforePlanColor);
			}

		}
#endif
		//�\��|�W�V�����ݒ�
		item->rigidbody.SetNextPos(nextPos);

	}

	//�����蔻��`�F�b�N�inextPos�w��j
	CheckCollide();

	for (auto& item : m_collidables)
	{
		if (item->GetTag() == ObjectTag::Player || item->GetTag() == ObjectTag::Enemy ||
			item->GetTag() == ObjectTag::Boss)
		{
			float rad = 0;
			int madelHandle = -1;

			for (auto& col : item->m_colliders)
			{
				rad = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_radius;

				madelHandle = m_stageCollisionHandle;
			}
			m_hitDim = MV1CollCheck_Sphere(madelHandle, -1, item->rigidbody.GetNextPosVECTOR(), rad);
		}
		else
		{
			continue;
		}

		//�ǂƏ��̓����蔻����s��
		CheckWallAndFloor(item);
		//�ǂƂ̓����蔻�菈��
		FixPositionWithWall(item);
		//���Ƃ̓����蔻�菈��
		FixNowPositionWithFloor(item);

		//���o�����v���C���[�̎��͂̃|���S�������������
		MV1CollResultPolyDimTerminate(m_hitDim);

	}

	CheckSendOnCollideInfo(m_preCollideInfo, m_newCollideInfo, false);
	CheckSendOnCollideInfo(m_preTriggerInfo, m_newTriggerInfo, true);

	//�ʒu����
	FixPosition();

	for (const auto& info : m_onCollideInfo)
	{
		if (info.kind == eOnCollideInfoKind::CollideEnter)
		{
			info.mySelf->OnCollideEnter(info.person);
		}
		else if (info.kind == eOnCollideInfoKind::CollideStay)
		{
			info.mySelf->OnCollideStay(info.person);
		}
		else if (info.kind == eOnCollideInfoKind::CollideExit)
		{
			info.mySelf->OnCollideExit(info.person);
		}
		else if (info.kind == eOnCollideInfoKind::TriggerEnter)
		{
			info.mySelf->OnTriggerEnter(info.person);
		}
		else if (info.kind == eOnCollideInfoKind::TriggerStay)
		{
			info.mySelf->OnTriggerStay(info.person);
		}
		else if (info.kind == eOnCollideInfoKind::TriggerExit)
		{
			info.mySelf->OnTriggerExit(info.person);
		}
	}

}

/// <summary>
/// �����蔻��`�F�b�N
/// </summary>
void MyLibrary::Physics::CheckCollide()
{
	std::vector<OnCollideInfoData> onCollideInfo;
	//�Փ˒ʒm�A�|�W�V�����␳
	bool doCheck = true;
	int checkCount = 0;     //�`���b�N��
	while (doCheck)
	{
		doCheck = false;
		checkCount++;

		//2�d���[�v�őS�I�u�W�F�N�g�����蔻��
		//FIXME : �d���̂ŋ߂��I�u�W�F�N�g���m�̂ݓ����蔻�肷��ȂǍH�v������
		for (const auto& objA : m_collidables)
		{
			for (const auto& objB : m_collidables)
			{
				//����I�u�W�F�N�g�Ȃ瑁�����^�[��
				if (objA == objB)
					continue;

				for (const auto& colA : objA->m_colliders)
				{
					for (const auto& colB : objB->m_colliders)
					{
						if (!IsCollide(objA->rigidbody, objB->rigidbody, colA.get(), colB.get())) continue;

						bool isTrigger = colA->IsTrigger() || colB->IsTrigger();

						if (isTrigger)
						{
							AddNewCollideInfo(objA, objB, m_newTriggerInfo);
						}
						else
						{
							AddNewCollideInfo(objA, objB, m_newCollideInfo);
						}

						//Trigger�̏ꍇ�͈ʒu�␳�͂��Ȃ�
						if (isTrigger) continue;

						auto primary = objA;
						auto secondary = objB;

						if (primary == secondary)
						{
							break;
						}

						auto primaryCollider = colA;
						auto secondaryCollider = colB;
						if (objA->priority < objB->priority)
						{
							primary = objB;
							secondary = objA;
							primaryCollider = colB;
							secondaryCollider = colA;
						}

						FixNextPosition(primary->rigidbody, secondary->rigidbody, primaryCollider.get(), secondaryCollider.get());
						//�ʒu�␳�������������x���߂���s��
						doCheck = true;
						break;
					}
					if (doCheck) break;
				}
				if (doCheck) break;
			}
			if (doCheck) break;
		}
		if (doCheck && checkCount > 800)
		{
#if _DEBUG
			printfDx("�K��񐔂𒴂��܂���");
#endif
			break;
		}
	}
}

/// <summary>
/// ��̃I�u�W�F�N�g���ڐG���Ă��邩�ǂ���
/// </summary>
/// <param name="rigidA">�I�u�W�F�N�gA�̕����f�[�^</param>
/// <param name="rigidB">�I�u�W�F�N�gB�̕����f�[�^</param>
/// <param name="colliderA">�I�u�W�F�N�gA�̓����蔻��f�[�^</param>
/// <param name="colliderB">�I�u�W�F�N�gB�̓����蔻��f�[�^</param>
/// <returns></returns>
bool MyLibrary::Physics::IsCollide(const Rigidbody& rigidA, const Rigidbody& rigidB, CollidableData* colliderA, CollidableData* colliderB) const
{
	bool isCollide = false;

	auto kindA = colliderA->GetKind();
	auto kindB = colliderB->GetKind();

	if (kindA == MyLibrary::CollidableData::Kind::Capsule && kindB == MyLibrary::CollidableData::Kind::Capsule)
	{
		auto colA = dynamic_cast<MyLibrary::CollidableDataCapsule*>(colliderA);
		auto colB = dynamic_cast<MyLibrary::CollidableDataCapsule*>(colliderB);

		auto atob = rigidA.GetNextPos() - rigidB.GetNextPos();
		auto atobLength = atob.Length();

		//���݂��̋������A���ꂼ�ꔼ�a�𑫂������̂�菬������Γ�����
		isCollide = (atobLength < colA->m_radius + colB->m_radius);
	}

	return isCollide;
}

/// <summary>
/// ���������I�u�W�F�N�g�̃y�A��o�^����
/// </summary>
/// <param name="objA">�I�u�W�F�N�gA</param>
/// <param name="objB">�I�u�W�F�N�gB</param>
/// <param name="info">�o�^����z��</param>
void MyLibrary::Physics::AddNewCollideInfo(const std::shared_ptr<Collidable>& objA, const std::shared_ptr<Collidable>& objB, SendCollideInfo& info)
{
	bool isPairA = info.find(objA) != info.end();
	bool isPairB = info.find(objB) != info.end();
	if (isPairA || isPairB)
	{
		std::shared_ptr<Collidable> parent = objA;
		std::shared_ptr<Collidable> child = objB;
		if (isPairB)
		{
			parent = objB;
			child = objA;
		}
		bool isChild = std::find(info[parent].begin(), info[parent].end(), child) != info[parent].end();
		if (!isChild)
		{
			info[parent].emplace_back(child);
		}
	}
	else
	{
		info[objA].emplace_back(objB);
	}
}

/// <summary>
/// �ړ��\��̍��W���C������
/// </summary>
/// <param name="primaryRigid">�D��x�������I�u�W�F�N�g�̕����f�[�^</param>
/// <param name="secondaryRigid">�D��x���Ⴂ�I�u�W�F�N�g�̕����f�[�^</param>
/// <param name="primaryCollider">�D��x�������I�u�W�F�N�g�̓����蔻��f�[�^</param>
/// <param name="secondaryCollider">�D��x���Ⴂ�I�u�W�F�N�g�̓����蔻��f�[�^</param>
void MyLibrary::Physics::FixNextPosition(const Rigidbody& primaryRigid, Rigidbody& secondaryRigid, CollidableData* primaryCollider, CollidableData* secondaryCollider) const
{
	//�����蔻��̎�ʖ��ɕ␳���@��ς���
	auto primaryKind = primaryCollider->GetKind();
	auto secondaryKind = secondaryCollider->GetKind();

	if (primaryKind == MyLibrary::CollidableData::Kind::Capsule && secondaryKind == MyLibrary::CollidableData::Kind::Capsule)
	{
		auto primaryToSecondary = secondaryRigid.GetNextPos() - primaryRigid.GetNextPos();
		auto primaryToSecondaryN = primaryToSecondary.Normalize();

		auto primaryColliderData = dynamic_cast<MyLibrary::CollidableDataCapsule*>(primaryCollider);
		auto secondaryColliderData = dynamic_cast<MyLibrary::CollidableDataCapsule*>(secondaryCollider);
		auto awayDist = primaryColliderData->m_radius + secondaryColliderData->m_radius + 0.0001f; //���̂܂܂��Ƃ�����ʒu�ɂȂ邩��]���ɗ���
		auto primaryToNewSecondaryPos = primaryToSecondaryN * awayDist;
		auto fixedPos = primaryRigid.GetNextPos() + primaryToNewSecondaryPos;
		fixedPos.y = secondaryRigid.GetPos().y;
		secondaryRigid.SetNextPos(fixedPos);

	}
}

/// <summary>
/// ��ޖ��ɏՓ˒ʒm���΂��z��ɒǉ�����
/// </summary>
/// <param name="preSendInfo">�Փ˂����I�u�W�F�N�g�̃��X�g�̃��O</param>
/// <param name="newSendInfo">�Փ˂����I�u�W�F�N�g�̃��X�g</param>
/// <param name="isTrigger">�������邩�ǂ���</param>
void MyLibrary::Physics::CheckSendOnCollideInfo(SendCollideInfo& preSendInfo, SendCollideInfo& newSendInfo, bool isTrigger)
{
	for (auto& parent : newSendInfo)
	{
		//�ȑO�̏��ɐe�Ƃ��ēo�^����Ă��邩
		bool isPreParent = preSendInfo.find(parent.first) != preSendInfo.end();
		bool isAllEnter = true;

		for (auto& child : parent.second)
		{
			bool isPreChild = false;
			if (isPreChild)
			{
				//�ȑO�̏��Ɏq�Ƃ��ēo�^����Ă��邩
				auto& preParent = preSendInfo[parent.first];
				isPreChild = std::find(preParent.begin(), preParent.end(), child) != preParent.end();

			}

			//��������Ă����ꍇ��Enter���Ă�(�q�Ƃ��ēo�^����Ă��Ȃ�)
			if (!isPreChild)
			{
				if (isTrigger)
				{
					AddOnCollideInfo(parent.first, child, eOnCollideInfoKind::TriggerEnter);
					AddOnCollideInfo(child, parent.first, eOnCollideInfoKind::TriggerEnter);
				}
				else
				{
					AddOnCollideInfo(parent.first, child, eOnCollideInfoKind::CollideEnter);
					AddOnCollideInfo(child, parent.first, eOnCollideInfoKind::CollideEnter);
				}
			}

			//Stary�͖��x�Ă�
			if (isTrigger)
			{
				AddOnCollideInfo(parent.first, child, eOnCollideInfoKind::TriggerStay);
				AddOnCollideInfo(child, parent.first, eOnCollideInfoKind::TriggerStay);
			}
			else
			{
				AddOnCollideInfo(parent.first, child, eOnCollideInfoKind::CollideStay);
				AddOnCollideInfo(child, parent.first, eOnCollideInfoKind::CollideStay);
			}

			//�o�^����Ă��������폜
			if (isPreChild)
			{
				preSendInfo[parent.first].remove(child);
			}
			//�S�ēo�^����Ă��Ȃ������Ƃ���
			else
			{
				isAllEnter = false;
			}
		}

		//�S�ēo�^����Ă�����e�̏�������
		if (isAllEnter)
		{
			preSendInfo.erase(parent.first);
		}
	}

	//�c���Ă���O��񂩂�Exist���Ă�(�o�^���c���Ă���=���񔲂���)
	for (auto& parent : preSendInfo)
	{
		for (auto& child : parent.second)
		{
			if(isTrigger)
			{
				AddOnCollideInfo(parent.first, child, eOnCollideInfoKind::TriggerExit);
				AddOnCollideInfo(child, parent.first, eOnCollideInfoKind::TriggerExit);
			}
			else
			{
				AddOnCollideInfo(parent.first, child, eOnCollideInfoKind::CollideExit);
				AddOnCollideInfo(child, parent.first, eOnCollideInfoKind::CollideExit);
			}
		}
	}
}

/// <summary>
/// �Փ˒ʒm���΂��z��ɒǉ�����
/// </summary>
/// <param name="mySelf">���g</param>
/// <param name="person">�Փ˂�������</param>
/// <param name="kind">�����蔻��̎��</param>
void MyLibrary::Physics::AddOnCollideInfo(const std::shared_ptr<Collidable>& mySelf, const std::shared_ptr<Collidable>& person, eOnCollideInfoKind kind)
{
	OnCollideInfoData addInfo;
	addInfo.mySelf = mySelf;
	addInfo.person = person;
	addInfo.kind = kind;
	m_onCollideInfo.emplace_back(addInfo);
}

/// <summary>
/// �ŏI�I�Ȉʒu�����肷��
/// </summary>
void MyLibrary::Physics::FixPosition()
{
	for (auto& item : m_collidables)
	{
		//Pos���X�V����̂ŁAvelocity�������Ɉړ�����velocity�ɏC��
		LibVec3 toFixedPos = item->rigidbody.GetNextPos() - item->rigidbody.GetPos();
		item->rigidbody.SetVelocity(toFixedPos);

		//�ʒu�m��
		item->rigidbody.SetPos(item->rigidbody.GetNextPos());
	}
}

/// <summary>
/// �`�F�b�N�����|���S�����ǃ|���S�������|���S�����𔻒f����
/// </summary>
/// <param name="col">�`�F�b�N����I�u�W�F�N�g</param>
void MyLibrary::Physics::CheckWallAndFloor(std::shared_ptr<Collidable>& col)
{
	//�ǃ|���S���Ə��|���S���̐�������������
	m_wallNum = 0;
	m_floorNum = 0;

	//���o���ꂽ�|���S���̐������J��Ԃ�
	for (int i = 0; i < m_hitDim.HitNum; i++)
	{
		//�|���S���̖@����Y�������ǃ|���S���{�[�_�[�ɒB���Ă��邩�ǂ����ŕǃ|���S�������|���S�����𔻒f����
		if (m_hitDim.Dim[i].Normal.y < kWallPolyBorder && m_hitDim.Dim[i].Normal.y > -kWallPolyBorder)
		{
			//�ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A�v���C���[��Y���W��荂���|���S���̂ݓ����蔻����s��
			if (m_hitDim.Dim[i].Position[0].y > col->rigidbody.GetPos().y + kWallPolyHeight ||
				m_hitDim.Dim[i].Position[1].y > col->rigidbody.GetPos().y + kWallPolyHeight ||
				m_hitDim.Dim[i].Position[2].y > col->rigidbody.GetPos().y + kWallPolyHeight)
			{
				//�|���S���̐������E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
				if (m_wallNum < ColInfo::kMaxColHitPoly)
				{
					//�|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɒǉ�����
					m_pWallPoly[m_wallNum] = &m_hitDim.Dim[i];

					//�ǃ|���S���̐������Z����
					m_wallNum++;
				}
			}
		}
		else
		{
			//�|���S���̐������E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
			if (m_floorNum < ColInfo::kMaxColHitPoly)
			{
				//�|���S���̍\���̂̃A�h���X�����|���S���|�C���^�z��ɕۑ�����
				m_pFloorPoly[m_floorNum] = &m_hitDim.Dim[i];

				//���|���S���̐������Z����
				m_floorNum;
			}
		}
	}
}

/// <summary>
/// �ǃ|���S���Ƃ̓����蔻����`�F�b�N���A�ړ�������
/// </summary>
/// <param name="col">�`�F�b�N����I�u�W�F�N�g</param>
void MyLibrary::Physics::FixPositionWithWall(std::shared_ptr<Collidable>& col)
{
	float radius = 0.0f;
	VECTOR vec = VGet(0.0f, 0.0f, 0.0f);
	for (auto& col : col->m_colliders)
	{
		radius = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_radius;
		vec = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_vec.ConversionToVECTOR();
	}

	//�ǃ|���S�����Ȃ��ꍇ�͉������Ȃ�
	if (m_wallNum == 0) return;

	//�ǃ|���S���Ƃ̓����蔻�菈��
	//�ǂɓ����������ǂ����̃t���O�͏�����Ԃł́u�������Ă��Ȃ��v�ɂ��Ă���
	m_isHitFlag = false;

	//�ړ��������ǂ����ŏ����𕪊�
	if (col->rigidbody.GetDir().Length() != 0.0f)
	{
		//�ǃ|���S���̐������J��Ԃ�
		for (int i = 0; i < m_wallNum; i++)
		{
			//i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
			m_pPoly = m_pWallPoly[i];

			//�|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
			if (!HitCheck_Capsule_Triangle(VAdd(col->rigidbody.GetNextPosVECTOR(), vec), VSub(col->rigidbody.GetNextPosVECTOR(), vec), radius,
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2])) continue;

			//�����ɂ�����|���S���ƃv���C���[���������Ă���Ƃ������ƂȂ̂ŁA�|���S���ɓ��������t���O�𗧂Ă�
			m_isHitFlag = true;

			//�ǂ��l�������ړ����O�ς��g���ĎZ�o
			MyLibrary::LibVec3 SlideVec;

			VECTOR ret;
			ret = VCross(col->rigidbody.GetVelocityVECTOR(), m_pPoly->Normal);
			//�i�s�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o
			SlideVec = MyLibrary::LibVec3(ret.x, ret.y, ret.z);

			//������ړ��O�̍��W�ɑ��������̂�V���ȍ��W�Ƃ���
			col->rigidbody.SetNextPos(col->rigidbody.GetPos() + SlideVec);

			//�V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
			bool isHitWallPolygon = false;
			for (int j = 0; j < m_wallNum; j++)
			{
				//j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				m_pPoly = m_pWallPoly[j];

				//�������Ă����烋�[�v���甲����
				if (HitCheck_Capsule_Triangle(VAdd(col->rigidbody.GetNextPosVECTOR(), vec), VSub(col->rigidbody.GetNextPosVECTOR(), vec), radius,
					m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]))
				{
					//true�ɂ���
					isHitWallPolygon = true;
					break;
				}
			}

			//�S�Ẵ|���S���Ɠ������Ă��Ȃ������炱���Ń��[�v�I��
			if (!isHitWallPolygon)
			{
				//�q�b�g�t���O��|��
				m_isHitFlag = false;
				break;
			}
		}
	}
	else
	{
		//�ړ����Ă��Ȃ��ꍇ�̏���

		//�ǃ|���S���̐������J��Ԃ�
		for (int i = 0; i < m_wallNum; i++)
		{
			//i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
			m_pPoly = m_pWallPoly[i];

			//�|���S���ɓ������Ă����瓖�������t���O�𗧂Ă���Ń��[�v���甲����
			if (HitCheck_Capsule_Triangle(VAdd(col->rigidbody.GetNextPosVECTOR(), vec), VSub(col->rigidbody.GetNextPosVECTOR(), vec), radius,
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]))
			{
				m_isHitFlag = true;
				break;
			}
		}


		//�ǂɓ������Ă�����ǂ��牟���o���������s��
		if (m_isHitFlag)
		{
			FixPositionWithWallInternal(col);
		}
	}
}

/// <summary>
/// �ǂ̒����牟���o��
/// </summary>
/// <param name="col">�`�F�b�N����I�u�W�F�N�g</param>
void MyLibrary::Physics::FixPositionWithWallInternal(std::shared_ptr<Collidable>& col)
{
	float radius = 0.0f;
	VECTOR vec = VGet(0.0f, 0.0f, 0.0f);
	for (auto& col : col->m_colliders)
	{
		radius = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_radius;
		vec = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_vec.ConversionToVECTOR();
	}

	//�ǂ���̉����o�����������݂�ő吔�����J��Ԃ�
	for (int i = 0; i < ColInfo::kMaxColHitTry; i++)
	{
		//������\���̂���ǃ|���S����S�Č���
		bool isHitWall = false;
		//�ǃ|���S���̐������J��Ԃ�
		for (int j = 0; j < m_wallNum; j++)
		{
			//j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
			m_pPoly = m_pWallPoly[j];

			//�|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
			if (!HitCheck_Capsule_Triangle(VAdd(col->rigidbody.GetNextPosVECTOR(), vec), VSub(col->rigidbody.GetNextPosVECTOR(), vec), radius,
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2])) continue;

			auto ret = VAdd(col->rigidbody.GetNextPosVECTOR(), VScale(m_pPoly->Normal, kColHitSlideLength));

			MyLibrary::LibVec3 set;
			set = MyLibrary::LibVec3(ret.x, ret.y, ret.z);

			//�������Ă�����K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
			col->rigidbody.SetNextPos(set);

			//�ړ����������ŕǃ|���S���Ɛڑ����Ă��邩�ǂ����𔻒�
			for (int k = 0; k < m_wallNum; k++)
			{
				//�������Ă����烋�[�v�𔲂���
				m_pPoly = m_pWallPoly[k];
				if (HitCheck_Capsule_Triangle(VAdd(col->rigidbody.GetNextPosVECTOR(), vec), VSub(col->rigidbody.GetNextPosVECTOR(), vec), radius,
					m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]))
				{
					isHitWall = true;
					break;
				}

			}

			//�S�Ẵ|���S���Ɠ������Ă��Ȃ������炱���Ń��[�v�I��
			if (!isHitWall) break;
		}

		//���[�v�I��
		if (!isHitWall) break;
	}
}

/// <summary>
/// ���|���S���Ƃ̓����蔻����`�F�b�N���A�ړ�������
/// </summary>
/// <param name="col">�`�F�b�N����I�u�W�F�N�g</param>
void MyLibrary::Physics::FixNowPositionWithFloor(std::shared_ptr<Collidable>& col)
{
	//���|���S�����Ȃ��ꍇ�͉������Ȃ�
	if (m_floorNum == 0) return;

	float radius = 0.0f;
	VECTOR vec = VGet(0.0f, 0.0f, 0.0f);
	for (auto& col : col->m_colliders)
	{
		radius = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_radius;
		vec = dynamic_cast<MyLibrary::CollidableDataCapsule*> (col.get())->m_vec.ConversionToVECTOR();
	}

	//���|���S���Ƃ̓����蔻�菈��
	//�����������ǂ����̃t���O������
	bool isHitFlag = false;

	//���|���S���Ƃ̓����蔻��
	//��ԍ������|���S���ɂԂ���ׂ̔���p�ϐ���������
	float PolyMaxPosY = 0.0f;

	//���|���S���̐������J��Ԃ�
	for (int i = 0; i < m_floorNum; i++)
	{
		//i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
		m_pPoly = m_pFloorPoly[i];

		//�|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
		if (HitCheck_Capsule_Triangle(VAdd(col->rigidbody.GetNextPosVECTOR(), vec), VSub(col->rigidbody.GetNextPosVECTOR(), vec), radius,
			m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2])) continue;

		float mostHeightY = m_pPoly->Position[0].y;

		if (mostHeightY < m_pPoly->Position[1].y)
		{
			mostHeightY = m_pPoly->Position[1].y;
		}

		if (mostHeightY < m_pPoly->Position[2].y)
		{
			mostHeightY = m_pPoly->Position[2].y;
		}

		//���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
		if (m_isHitFlag && PolyMaxPosY > mostHeightY) continue;

		//�|���S���ɓ��������t���O�𗧂Ă�
		m_isHitFlag = true;

		//�ڐG����Y���W��ێ�����
		PolyMaxPosY = mostHeightY;
	}

	//���|���S���̓����蔻�肩�A�W�����v�͂�0����������(���~���̏ꍇ)�ǂ����ŏ����𕪊�
	if (m_isHitFlag)
	{
		//�ڐG�����|���S���ň�ԍ���Y���W���v���C���[��Y���W�ɂ���
		auto set = col->rigidbody.GetNextPos();
		set.y = PolyMaxPosY + radius;
		col->rigidbody.SetNextPos(set);
	}
}
