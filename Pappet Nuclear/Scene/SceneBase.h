#pragma once
#include "DxLib.h"
#include "BGMESE/BgmAndSeManager.h"
#include "UI/Setting.h"
#include<memory>

class SceneBase : public std::enable_shared_from_this<SceneBase>
{
public:
	SceneBase(){}

	virtual ~SceneBase(){}

	//virtual‚ÅŒp³æ‚ğŒÄ‚Ño‚·

	virtual void Init() = 0;
	virtual std::shared_ptr<SceneBase> Update() = 0;
	virtual void Draw() = 0;
	virtual void End() = 0;

	int MyLoadGraph(const char* FileName, int XSize, int YSize);

protected:
	//•Ï”‚ğ“ü‚ê‚é
	int m_backScene = 0;

	std::shared_ptr<Setting> setting = std::make_shared<Setting>();
	std::shared_ptr<BgmAndSeManager> bgmse = std::make_shared<BgmAndSeManager>();
};

