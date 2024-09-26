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
	int GetRestEffect() { return m_effectRest; }    //休息
	int GetHeelEffect() { return m_effectHeel; }    //回復
	int GetHitEffect() { return m_effectHit; }      //ヒット時

private:
	int m_effectJump;            //ジャンプ攻撃のエフェクト
	int m_effectRest;            //休息するときのエフェクト
	int m_effectHeel;            //回復するときのエフェクト
	int m_effectHit;             //ヒット時のエフェクト
};

