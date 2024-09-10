#pragma once
#include "Scene/SceneBase.h"
#include<memory>

//class SceneBase;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	void Init();
	void Update();
	void Draw();
	void End();

	bool GetEnd() { return m_pScene->GetEnd(); }

private:
	std::shared_ptr<SceneBase> m_pScene;
};

