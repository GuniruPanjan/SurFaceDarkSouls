#pragma once
#include "DxLib.h"
#include<memory>

class SEManager
{
public:
	SEManager();
	virtual ~SEManager();

	void SceneInit();
	void CharaInit();
	void BossInit();
	void Update(int volume);
	void End();

	int GetButtonSE() { return m_buttonSE; }
	int GetSelectSE() { return m_selectSE; }
	int GetHitSE() { return m_hitSE; }
	int GetPlayerHitSE() { return m_playerHitSE; }
	int GetAttackSE() { return m_attackSE; }
	int GetWalkSE() { return m_walkSE; }
	int GetHeelSE() { return m_playerHeelSE; }
	int GetRestSE() { return m_playerRestSE; }
	int GetBossVoiceSE() { return m_bossVoiceSE; }
	int GetBossAttackSE1() { return m_bossAttackSE[0]; }
	int GetBossAttackSE2() { return m_bossAttackSE[1]; }
	int GetBossAttackSE3() { return m_bossAttackSE[2]; }
	int GetBossWalkSE() { return m_bossWalkSE; }
	int GetDiedSE() { return m_diedSE; }

private:
	//SE�֌W
	int m_buttonSE;         //�{�^����SE
	int m_selectSE;         //�I����������SE
	int m_hitSE;            //�G�l�~�[�ƃv���C���[�ƃ{�X��Hit����SE
	int m_playerHitSE;      //�{�X�̍U����Hit����SE
	int m_attackSE;         //�G�l�~�[�ƃv���C���[�̍U������SE
	int m_walkSE;           //�G�l�~�[�ƃv���C���[�̕�������SE
	int m_playerHeelSE;     //�񕜂�������SE
	int m_playerRestSE;     //�x����������SE
	int m_bossVoiceSE;      //�{�X�̙��KSE
	int m_bossAttackSE[3];  //�{�X�̍U���R�p�^�[��
	int m_bossWalkSE;       //�{�X����������SE
	int m_diedSE;           //���񂾎���SE
	int m_volumePal;        //����
};

