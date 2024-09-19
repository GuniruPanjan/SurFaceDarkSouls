#pragma once
#include "DxLib.h"
#include "BGMÅESE/SEManager.h"
#include<memory>

class UIManager
{
public:
	UIManager();
	virtual ~UIManager();

	int MyLoadGraph(const char* FileName, int XSize, int YSize);

protected:
	int m_heelStone;
	int m_fist;
	int m_eqFist;
	int m_sword;
	int m_eqSword;
	int m_shield; 
	int m_eqShield;

	std::shared_ptr<SEManager> se = std::make_shared<SEManager>();
};

