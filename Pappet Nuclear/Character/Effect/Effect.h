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

	int GetBossAttackEffect3() { return m_effectJump; }    //�W�����v�U��

private:
	int m_effectJump;            //�W�����v�U���̃G�t�F�N�g
};

