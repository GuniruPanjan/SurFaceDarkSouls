#pragma once
#include "DxLib.h"
#include "UI/Setting.h"
#include<memory>

class SceneBase : public std::enable_shared_from_this<SceneBase>
{
public:
	SceneBase(){}

	virtual ~SceneBase(){}

	//virtualで継承先を呼び出す

	virtual void Init() = 0;
	virtual std::shared_ptr<SceneBase> Update() = 0;
	virtual void Draw() = 0;
	virtual void End() = 0;

	int MyLoadGraph(const char* FileName, int XSize, int YSize);

protected:
	//変数を入れる
	int m_backScene = 0;

	std::shared_ptr<Setting> setting = std::make_shared<Setting>();
};

