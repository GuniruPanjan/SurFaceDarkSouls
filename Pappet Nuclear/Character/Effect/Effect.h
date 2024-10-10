#pragma once
#include "EffekseerForDXLib.h"

class Effect
{
public:
	Effect();
	virtual ~Effect();

	void PlayerInit();
	void BossInit();
	void AllInit();
	void Update();
	void Draw();
	void End();

	int GetBossAttackEffect3() { return m_effectJump; }    //�W�����v�U��
	int GetRestEffect() { return m_effectRest; }    //�x��
	int GetHeelEffect() { return m_effectHeel; }    //��
	int GetHitEffect() { return m_effectHit; }      //�q�b�g��
	int GetItemEffect() { return m_effectItem; }    //�A�C�e��

private:
	int m_effectJump;            //�W�����v�U���̃G�t�F�N�g
	int m_effectRest;            //�x������Ƃ��̃G�t�F�N�g
	int m_effectHeel;            //�񕜂���Ƃ��̃G�t�F�N�g
	int m_effectHit;             //�q�b�g���̃G�t�F�N�g
	int m_effectItem;            //�A�C�e���̃G�t�F�N�g
};

