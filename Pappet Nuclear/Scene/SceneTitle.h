#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:
	//Pad“ü—ÍŠ“¾•Ï”
	int m_pad;
	int m_right;
};