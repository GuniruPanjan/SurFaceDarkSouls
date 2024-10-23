#include "CharacterBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="priority">優先度</param>
/// <param name="tag">タグ</param>
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
/// デストラクタ
/// </summary>
CharacterBase::~CharacterBase()
{
}

/// <summary>
/// アニメーション更新
/// </summary>
/// <param name="attachNo">更新させたいアニメーション番号</param>
/// <param name="time">ループしたか</param>
/// <returns></returns>
bool CharacterBase::UpdateAnimation(int attachNo, float time)
{
	//アニメーションが設定されていなかったら早期リターン
	if (attachNo == -1) return false;

	//アニメーションを進行させる
	float nowFrame = MV1GetAttachAnimTime(m_handle, attachNo);   //現在の再生カウントを取得
	nowFrame += m_animTime;

	//現在再生中のアニメーションの総カウントを取得する
	float totalAnimCount = MV1GetAttachAnimTotalTime(m_handle, attachNo);
	bool isLoop = false;

	while (totalAnimCount <= nowFrame)
	{
		nowFrame -= totalAnimCount;
		nowFrame += time;
		isLoop = true;
	}

	//進めた時間に設定
	MV1SetAttachAnimTime(m_handle, attachNo, nowFrame);

	return isLoop;
}

/// <summary>
/// アニメーション変更
/// </summary>
/// <param name="animIndex">変更後のアニメーション番号</param>
/// <param name="changeSpeed">変更したアニメーションの再生速度</param>
void CharacterBase::ChangeAnimation(int animIndex, float changeSpeed)
{
	//古いアニメーションがアタッチされている場合はこの時点で決しておく
	if (m_prevAnimNo != -1)
	{
		MV1DetachAnim(m_handle, m_prevAnimNo);
	}

	//現在再生中のアニメーションは変更目のアニメーションの扱い
	m_prevAnimNo = m_nowAnimNo;

	//変更後のアニメーションを改めて設定する
	m_nowAnimNo = MV1AttachAnim(m_handle, animIndex);

	//切り替えの瞬間は変更前のアニメーションが再生される状態にする
	m_animBlendRate = 0.0f;

	m_animTime = changeSpeed;

	//変更前のアニメーション100%
	MV1SetAttachAnimBlendRate(m_handle, m_prevAnimNo, 1.0f - m_animBlendRate);
	//変更後のアニメーション0%
	MV1SetAttachAnimBlendRate(m_handle, m_nowAnimNo, m_animBlendRate);
}
