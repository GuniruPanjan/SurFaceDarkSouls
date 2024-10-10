#pragma once

/// <summary>
/// �A�j���[�V�������u�����h����
/// </summary>
class BlendAnimation
{
public:
	BlendAnimation();
	virtual ~BlendAnimation();

	/// <summary>
	/// ���f���P�̂̃A�j���[�V�����u�����h���s���֐�
	/// </summary>
	/// <param name="time">�A�j���[�V�����Đ�����</param>
	/// <param name="handle">�u�����h���郂�f��</param>
	/// <param name="BlendNumber">�u�����h����A�j���[�V�����i���o�[</param>
	/// <param name="DNumber">�u�����h�ŊO���A�j���[�V�����i���o�[</param>
	/// <param name="rate">�u�����h��</param>
	/// <param name="Done">�u�����h�ŊO���A�j���[�V��������</param>
	/// <param name="Bone">�u�����h����A�j���[�V��������</param>
	/// <param name="one">��񂾂����s���锻��</param>
	void AnimationBlend(float& time, int& handle, int& BlendNumber, int& DNumber, float& rate, bool& Done, bool& Bone, bool& one);

	//�z�񉻂��Ă郂�f���̏ꍇ
	//void ArrayAnimationBlend(float& time)
};

