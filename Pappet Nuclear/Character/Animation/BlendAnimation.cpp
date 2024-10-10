#include "BlendAnimation.h"
#include "DxLib.h"

BlendAnimation::BlendAnimation()
{
}

BlendAnimation::~BlendAnimation()
{
}

/// <summary>
/// ���f���P�̂̃A�j���[�V�����u�����h���s���֐�
/// </summary>
/// <param name="time">�A�j���[�V�����̍Đ�����</param>
/// <param name="handle">�u�����h���郂�f��</param>
/// <param name="BlendNumber">�u�����h����A�j���[�V�����i���o�[</param>
/// <param name="DNumber">�u�����h�ŊO���A�j���[�V�����i���o�[</param>
/// <param name="rate">�u�����h��</param>
/// <param name="Done">�u�����h�ŊO���A�j���[�V��������</param>
/// <param name="Bone">�u�����h����A�j���[�V��������</param>
/// <param name="one">��񂾂����s���锻��</param>
void BlendAnimation::AnimationBlend(float& time, int& handle, int& BlendNumber, int& DNumber, float& rate, bool& Done, bool& Bone, bool& one)
{
	if (Done == true && Bone == false)
	{
		//��񂾂����s
		if (one == false)
		{
			rate = 0.0f;

			one = true;
		}

		//�u�����h��0�ɂ���
		MV1SetAttachAnimBlendRate(handle, DNumber, 1.0f - rate);

		//�A�j���[�V�����u�����h
		MV1SetAttachAnimBlendRate(handle, BlendNumber, rate);

		time = 0.0f;

		if (rate >= 1.0f)
		{
			Bone = true;
			Done = false;
		}
	}
	else if (Bone == true)
	{
		one = false;
	}
}
