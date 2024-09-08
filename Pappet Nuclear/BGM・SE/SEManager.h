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
	//SE関係
	int m_buttonSE;         //ボタンのSE
	int m_selectSE;         //選択した時のSE
	int m_hitSE;            //エネミーとプレイヤーとボスのHit時のSE
	int m_playerHitSE;      //ボスの攻撃のHit時のSE
	int m_attackSE;         //エネミーとプレイヤーの攻撃時のSE
	int m_walkSE;           //エネミーとプレイヤーの歩く時のSE
	int m_playerHeelSE;     //回復した時のSE
	int m_playerRestSE;     //休息した時のSE
	int m_bossVoiceSE;      //ボスの咆哮SE
	int m_bossAttackSE[3];  //ボスの攻撃３パターン
	int m_bossWalkSE;       //ボスが歩く時のSE
	int m_diedSE;           //死んだ時のSE
	int m_volumePal;        //音量
};

