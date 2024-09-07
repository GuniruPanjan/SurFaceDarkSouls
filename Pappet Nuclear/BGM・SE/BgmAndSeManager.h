#pragma once
#include "DxLib.h"

class BgmAndSeManager
{
public:
	BgmAndSeManager();
	virtual ~BgmAndSeManager();

	void Init();
	void Update();
	void End();

private:
	int m_titleBGM;
	int m_gameBGM;
	int m_bossBGM;
	int m_clearBGM;
};

