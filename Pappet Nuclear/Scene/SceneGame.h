#pragma once
#include "Camera/Camera.h"
#include "Character/Player/Player.h"
#include "Character/Enemy/Enemy.h"
#include "Character/Player/Equipment/Equipment.h"
#include "Map/Map.h"
#include "UI/UI.h"
#include "SceneBase.h"
class SceneGame : public SceneBase
{
public:
	SceneGame();
	virtual ~SceneGame();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:
	bool m_one;    //一回だけ実行
	//ポインタで管理
	std::shared_ptr<Player> player = std::make_shared<Player>();
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
	std::shared_ptr<Map> map = std::make_shared<Map>();
	std::shared_ptr<UI> ui = std::make_shared<UI>();
	std::shared_ptr<Equipment> equipment = std::make_shared<Equipment>();
};

