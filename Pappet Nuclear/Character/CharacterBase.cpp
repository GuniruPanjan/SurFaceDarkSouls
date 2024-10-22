#include "CharacterBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="priority">�D��x</param>
/// <param name="tag">�^�O</param>
CharacterBase::CharacterBase(Priority priority, ObjectTag tag):
	Collidable(priority, tag),
	m_handle(-1),
	m_animTime(0.5f)
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

}
