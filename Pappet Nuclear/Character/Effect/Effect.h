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

	int GetBossAttackEffect1() { return m_effectClaw1; }   //�܍U��1
	int GetBossAttackEffect2() { return m_effectClaw2; }   //�܍U��2
	int GetBossAttackEffect3() { return m_effectJump; }    //�W�����v�U��

private:
	int m_effectClaw1;           //�܍U���̃G�t�F�N�g1
	int m_effectClaw2;           //�܍U���̃G�t�F�N�g2
	int m_effectJump;            //�W�����v�U���̃G�t�F�N�g
};

