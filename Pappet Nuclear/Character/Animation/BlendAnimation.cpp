#include "BlendAnimation.h"
#include "DxLib.h"

BlendAnimation::BlendAnimation()
{
}

BlendAnimation::~BlendAnimation()
{
}

/// <summary>
/// モデル単体のアニメーションブレンドを行う関数
/// </summary>
/// <param name="time">アニメーションの再生時間</param>
/// <param name="handle">ブレンドするモデル</param>
/// <param name="BlendNumber">ブレンドするアニメーションナンバー</param>
/// <param name="DNumber">ブレンドで外すアニメーションナンバー</param>
/// <param name="rate">ブレンド率</param>
/// <param name="Done">ブレンドで外すアニメーション判定</param>
/// <param name="Bone">ブレンドするアニメーション判定</param>
/// <param name="one">一回だけ実行する判定</param>
void BlendAnimation::AnimationBlend(float& time, int& handle, int& BlendNumber, int& DNumber, float& rate, bool& Done, bool& Bone, bool& one)
{
	if (Done == true && Bone == false)
	{
		//一回だけ実行
		if (one == false)
		{
			rate = 0.0f;

			one = true;
		}

		//ブレンドを0にする
		MV1SetAttachAnimBlendRate(handle, DNumber, 1.0f - rate);

		//アニメーションブレンド
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
