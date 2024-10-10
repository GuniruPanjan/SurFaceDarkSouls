#pragma once

/// <summary>
/// アニメーションをブレンドする
/// </summary>
class BlendAnimation
{
public:
	BlendAnimation();
	virtual ~BlendAnimation();

	/// <summary>
	/// モデル単体のアニメーションブレンドを行う関数
	/// </summary>
	/// <param name="time">アニメーション再生時間</param>
	/// <param name="handle">ブレンドするモデル</param>
	/// <param name="BlendNumber">ブレンドするアニメーションナンバー</param>
	/// <param name="DNumber">ブレンドで外すアニメーションナンバー</param>
	/// <param name="rate">ブレンド率</param>
	/// <param name="Done">ブレンドで外すアニメーション判定</param>
	/// <param name="Bone">ブレンドするアニメーション判定</param>
	/// <param name="one">一回だけ実行する判定</param>
	void AnimationBlend(float& time, int& handle, int& BlendNumber, int& DNumber, float& rate, bool& Done, bool& Bone, bool& one);

	//配列化してるモデルの場合
	//void ArrayAnimationBlend(float& time)
};

