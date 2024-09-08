#pragma once
#include "DxLib.h"
#include<memory>

class BgmAndSeManager
{
public:
	BgmAndSeManager();
	virtual ~BgmAndSeManager();

	void TitleInit();
	void GameInit();
	void ClearInit();
	void Update(int volume);
	void TitleBGM();
	void GameBGM();
	void BossBGM();
	void ClearBGM();
	void End();

	int GetBossBGM() { return m_bossBGM; }

private:
	//BGMŠÖŒW
	int m_titleBGM;
	int m_gameBGM;
	int m_bossBGM;
	int m_clearBGM;
	int m_volumePal;
};

