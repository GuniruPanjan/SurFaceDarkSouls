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

	int GetBossAttackEffect1() { return m_effectClaw1; }   //爪攻撃1
	int GetBossAttackEffect2() { return m_effectClaw2; }   //爪攻撃2
	int GetBossAttackEffect3() { return m_effectJump; }    //ジャンプ攻撃

private:
	int m_effectClaw1;           //爪攻撃のエフェクト1
	int m_effectClaw2;           //爪攻撃のエフェクト2
	int m_effectJump;            //ジャンプ攻撃のエフェクト
};

