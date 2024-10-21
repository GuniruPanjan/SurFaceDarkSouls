#pragma once
#include <memory>
#include <string>
#include "Library/MyLibrary.h"

class Camera;
class Player;
class Enemy;
class Map;
class UI;

/// <summary>
/// ゲーム自体を管理するクラス
/// </summary>
class GameManager
{
public:
	enum StageName : int
	{
		FirstStage,      //一番最初のステージ
		SecondStage,     //二番目のステージ
		ThreeStage,      //三番目のステージ
		FourStage,       //四番目のステージ
		LastStage,       //最後のステージ
		RestStage        //休息ステージ
	};

public:
	//コンストラクタ
	GameManager();
	//デストラクタ
	virtual ~GameManager();

	//初期化
	void Init();
	//更新
	void Update();
	//最初のステージの更新
	void FirstUpdate();
	//二つ目のステージの更新
	void SecondUpdate();
	//三つ目のステージの更新
	void ThreeUpdate();
	//四つ目のステージの更新
	void FourUpdate();
	//最後のステージの更新
	void LastUpdate();
	//休息ステージの更新
	void RestUpdate();
	//描画
	void Draw();
	//終了
	void End();

private:
	//ステージ名
	std::string m_stageName;

	//プレイヤークラスポインタ
	std::shared_ptr<Player> m_pPlayer;
	//敵クラスポインタ
	std::shared_ptr<Enemy> m_pEnemy;
	//カメラクラスポインタ
	std::shared_ptr<Camera> m_pCamera;
	//マップクラスポインタ
	std::shared_ptr<Map> m_pMap;
	//UIクラスポインタ
	std::shared_ptr<UI> m_pUI;

	//物理
	std::shared_ptr<MyLibrary::Physics> m_pPhysics;

	//プレイヤーが死亡したかの判定
	bool m_playerDead;
};

