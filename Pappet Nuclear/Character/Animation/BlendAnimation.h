#pragma once

/// <summary>
/// �A�j���[�V�������u�����h����
/// </summary>
class BlendAnimation
{
public:
	BlendAnimation();
	virtual ~BlendAnimation();

	//�P�̃��f���̏ꍇ
	void AnimationBlend(float& time, int& handle, int& BlendNumber, int& DNumber, float& rate, bool& Done, bool& Bone, bool& one);

	//�z�񉻂��Ă郂�f���̏ꍇ
	//void ArrayAnimationBlend(float& time)
};

