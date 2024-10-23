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
	m_nowAnimNo(-1),
	m_animBlendRate(1.0f),
	m_animTime(0.5f),
	m_isHit(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterBase::~CharacterBase()
{
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
