#pragma once
#include "EffekseerForDXLib.h"

class Effect
{
public:
	Effect();
	virtual ~Effect();

	void PlayerInit();
	void BossInit();
	void Update();
	void Draw();
	void End();

	int GetBossAttackEffect3() { return m_effectJump; }    //ジャンプ攻撃

private:
	int m_effectJump;            //ジャンプ攻撃のエフェクト
};

