#pragma once
#include "Camera/Camera.h"
#include "Character/Player/Player.h"
#include "Character/Enemy/Enemy.h"
#include "Character/Player/Equipment/Equipment.h"
#include "Character/Animation/BlendAnimation.h"
#include "Map/Map.h"
#include "UI/UI.h"
#include "SceneBase.h"

/// <summary>
/// ゲームシーンを管理するクラス
/// </summary>
class SceneGame : public SceneBase
{
public:
	//コンストラクタ
	SceneGame();

	//デストラクタ
	virtual ~SceneGame();

	//初期化処理
	virtual void Init();

	//更新処理
	virtual std::shared_ptr<SceneBase> Update();

	//描画処理
	virtual void Draw();

	//終了処理
	virtual void End();

private:

	bool m_one;    //一回だけ実行
	//スマートポインタで管理
	std::shared_ptr<Player> player = std::make_shared<Player>();
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
	std::shared_ptr<Map> map = std::make_shared<Map>();
	std::shared_ptr<UI> ui = std::make_shared<UI>();
	std::shared_ptr<Equipment> equipment = std::make_shared<Equipment>();
	std::shared_ptr<BlendAnimation> panim = std::make_shared<BlendAnimation>();
};

