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
	int m_sword;

	std::shared_ptr<SEManager> se = std::make_shared<SEManager>();
};

