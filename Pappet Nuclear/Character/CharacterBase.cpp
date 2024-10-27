#include "CharacterBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="priority">�D��x</param>
/// <param name="tag">�^�O</param>
CharacterBase::CharacterBase(Priority priority, ObjectTag tag):
	Collidable(priority, tag),
	m_handle(-1),
	m_prevAnimNo(-1),
	m_nowAnimIdx(-1),
	m_nowAnimNo(-1),
	m_animBlendRate(1.0f),
	m_animTime(0.5f),
	m_isAnimationFinish(false),
	m_isHit(false),
	m_attackRadius(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterBase::~CharacterBase()
{
}

/// <summary>
/// ���f���̒��S���W���v�Z
/// </summary>
/// <param name="modeldefaultSize">���f���̂��Ƃ��Ƃ̃T�C�Y</param>
/// <param name="modelSize">���f���̊g�嗦</param>
void CharacterBase::CalculationCenterPos(float modeldefaultSize, float modelSize)
{
	m_centerPos = rigidbody.GetPos();
	m_centerPos.y += (modeldefaultSize * modelSize) / 2;
}

/// <summary>
/// �_���[�W��������铖���蔻����쐬
/// </summary>
/// <param name="radius">���a</param>
/// <param name="len">����</param>
/// <param name="vec">�x�N�^�[</param>
void CharacterBase::InitHitBox(float radius, float len, MyLibrary::LibVec3 vec, bool isEnemy)
{
	phit = std::make_shared<HitObject>(radius, len, vec);
	phit->Init(m_pPhysics, m_centerPos, isEnemy);
}

/// <summary>
/// �U����������铖���蔻����쐬
/// </summary>
/// <param name="radius">���a</param>
void CharacterBase::InitAttackBox(float radius, MyLibrary::LibVec3 pos, bool isEnemy)
{
	pattack = std::make_shared<AttackObject>(radius);
	pattack->Init(m_pPhysics, pos, isEnemy);
}

/// <summary>
/// �A�j���[�V�����X�V
/// </summary>
/// <param name="attachNo">�X�V���������A�j���[�V�����ԍ�</param>
/// <param name="time">���[�v������</param>
/// <returns></returns>
bool CharacterBase::UpdateAnimation(int attachNo, float time)
{
	//�A�j���[�V�������ݒ肳��Ă��Ȃ������瑁�����^�[��
	if (attachNo == -1) return false;

	//�A�j���[�V������i�s������
	float nowFrame = MV1GetAttachAnimTime(m_handle, attachNo);   //���݂̍Đ��J�E���g���擾
	nowFrame += m_animTime;

	//���ݍĐ����̃A�j���[�V�����̑��J�E���g���擾����
	float totalAnimCount = MV1GetAttachAnimTotalTime(m_handle, attachNo);
	bool isLoop = false;

	while (totalAnimCount <= nowFrame)
	{
		nowFrame -= totalAnimCount;
		nowFrame += time;
		isLoop = true;
	}

	//�i�߂����Ԃɐݒ�
	MV1SetAttachAnimTime(m_handle, attachNo, nowFrame);

	return isLoop;
}

/// <summary>
/// �A�j���[�V�����ύX
/// </summary>
/// <param name="animIndex">�ύX��̃A�j���[�V�����ԍ�</param>
/// <param name="changeSpeed">�ύX�����A�j���[�V�����̍Đ����x</param>
void CharacterBase::ChangeAnimation(int animIndex, float changeSpeed)
{
	//�Â��A�j���[�V�������A�^�b�`����Ă���ꍇ�͂��̎��_�Ō����Ă���
	if (m_prevAnimNo != -1)
	{
		MV1DetachAnim(m_handle, m_prevAnimNo);
	}

	//���ݍĐ����̃A�j���[�V�����͕ύX�ڂ̃A�j���[�V�����̈���
	m_prevAnimNo = m_nowAnimNo;

	//�ύX��̃A�j���[�V���������߂Đݒ肷��
	m_nowAnimNo = MV1AttachAnim(m_handle, animIndex);

	//�؂�ւ��̏u�Ԃ͕ύX�O�̃A�j���[�V�������Đ�������Ԃɂ���
	m_animBlendRate = 0.0f;

	m_animTime = changeSpeed;

	//�ύX�O�̃A�j���[�V����100%
	MV1SetAttachAnimBlendRate(m_handle, m_prevAnimNo, 1.0f - m_animBlendRate);
	//�ύX��̃A�j���[�V����0%
	MV1SetAttachAnimBlendRate(m_handle, m_nowAnimNo, m_animBlendRate);
}
