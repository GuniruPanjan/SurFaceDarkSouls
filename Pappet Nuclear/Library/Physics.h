#pragma once
#include "LibVec3.h"

#include <list>
#include <vector>
#include <unordered_map>

namespace MyLibrary
{
	class Collidable;

	namespace ColInfo
	{
		//�ő哖���蔻��|���S����
		constexpr int kMaxColHitPoly = 3000;
		//�ǉ����o�������̍ő厎�s��
		constexpr int kMaxColHitTry = 20;
		//�ǉ����o�����ɃX���C�h�����鋗��
		constexpr float kColHitSlideLength = 1.0f;
	}

	/// <summary>
	/// �����E�Փ˔��肷��I�u�W�F�N�g��o�^���A�����ړ��E�Փ˂�ʒm����
	/// </summary>
	class Physics final
	{
	private:
		//�����蔻��̎��
		enum class eOnCollideInfoKind
		{
			CollideEnter,
			CollideStay,
			CollideExit,
			TriggerEnter,
			TriggerStay,
			TriggerExit
		};

		//�����Ɠ��������I�u�W�F�N�g�̏��
		struct OnCollideInfoData
		{
			std::shared_ptr<Collidable> mySelf;    //�������M
			std::shared_ptr<Collidable> person;    //������������
			eOnCollideInfoKind kind;               //���
		};

		using SendCollideInfo = std::unordered_map<std::shared_ptr<Collidable>, std::list<std::shared_ptr<Collidable>>>;

	public:
		//�R���X�g���N�^
		Physics(int mapStageCollisionHandle);

		//�Փ˕��̓o�^�E�o�^����
		void Entry(std::shared_ptr<Collidable> collidable);
		void Exit(std::shared_ptr<Collidable> collidable);

		//�X�V(�o�^�I�u�W�F�N�g�̕����ړ��A�Փ˒ʒm)
		void Update();

	private:
		//�����蔻��`�F�b�N
		void CheckCollide();
		//��̃I�u�W�F�N�g���ڑ����Ă��邩�ǂ���
		bool IsCollide(const Rigidbody& rigidA, const Rigidbody& rigidB, CollidableData* colliderA, CollidableData* colliderB) const;
		//���������I�u�W�F�N�g�̃y�A��o�^����
		void AddNewCollideInfo(const std::shared_ptr<Collidable>& objA, const std::shared_ptr<Collidable>& objB, SendCollideInfo& info);
		//�ړ��\��̍��W���C������
		void FixNextPosition(const Rigidbody& primaryRigid, Rigidbody& secondaryRigid, CollidableData* primaryCollider, CollidableData* secondaryCollider) const;
		//��ޖ��ɏՓ˒ʒm���΂��z��ɒǉ�����
		void CheckSendOnCollideInfo(SendCollideInfo& preSendInfo, SendCollideInfo& newSendInfo, bool isTrigger);
		//�Փ˒ʒm���΂��z��ɒǉ�����
		void AddOnCollideInfo(const std::shared_ptr<Collidable>& mySelf, const std::shared_ptr<Collidable>& person, eOnCollideInfoKind kind);
		//�ŏI�I�Ȉʒu�����肷��
		void FixPosition();

	private:
		//�`�F�b�N�����|���S�����ǃ|���S�������|���S�����𔻒f���ێ�����
		void CheckWallAndFloor(std::shared_ptr<Collidable>& col);
		//�ǃ|���S���Ƃ̓����蔻����`�F�b�N���A�ړ�������
		void FixPositionWithWall(std::shared_ptr<Collidable>& col);
		//�ǂ̒����牟���o��
		void FixPositionWithWallInternal(std::shared_ptr<Collidable>& col);
		//���|���S���Ƃ̓����蔻����`�F�b�N���A�ړ�������
		void FixNowPositionWithFloor(std::shared_ptr<Collidable>& col);

	private:
		//�o�^���ꂽCollidable�̃��X�g
		std::list<std::shared_ptr<Collidable>> m_collidables;
		//�Փ˂����I�u�W�F�N�g�̃��X�g
		std::list<OnCollideInfoData> m_onCollideInfo;

		//�Փ˂����I�u�W�F�N�g�̃��X�g
		SendCollideInfo m_newCollideInfo;
		//�Փ˂����I�u�W�F�N�g�̃��X�g�̃��O
		SendCollideInfo m_preCollideInfo;
		//�Փ˂��������o�����Ȃ��I�u�W�F�N�g�̃��X�g
		SendCollideInfo m_newTriggerInfo;
		//�Փ˂��������o�����Ȃ��I�u�W�F�N�g�̃��X�g�̃��O
		SendCollideInfo m_preTriggerInfo;

		//�}�b�v�����蔻��̃n���h��
		int m_stageCollisionHandle;

	private:
		//�ړ��������ǂ���
		bool m_isMoveFlag = false;
		//�|���S���ɓ����������ǂ���
		bool m_isHitFlag = false;
		//�ǃ|���S���Ɣ��f���ꂽ�|���S����
		int m_wallNum = 0;
		//���|���S���Ɣ��f���ꂽ�|���S����
		int m_floorNum = 0;

		//�����蔻�茋�ʍ\����
		MV1_COLL_RESULT_POLY_DIM m_hitDim{};
		//�ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
		MV1_COLL_RESULT_POLY* m_pWallPoly[ColInfo::kMaxColHitPoly]{};
		//���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
		MV1_COLL_RESULT_POLY* m_pFloorPoly[ColInfo::kMaxColHitPoly]{};
		//�|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏd�g�p����|�C���^
		MV1_COLL_RESULT_POLY* m_pPoly = nullptr;
	};
}


