#pragma once

/// <summary>
/// アニメーションをブレンドする
/// </summary>
class BlendAnimation
{
public:
	BlendAnimation();
	virtual ~BlendAnimation();

	//単体モデルの場合
	void AnimationBlend(float& time, int& handle, int& BlendNumber, int& DNumber, float& rate, bool& Done, bool& Bone, bool& one);

	//配列化してるモデルの場合
	//void ArrayAnimationBlend(float& time)
};

