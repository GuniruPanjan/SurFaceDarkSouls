#pragma once
#include "SceneBase.h"

/// <summary>
/// ゲームのクリアシーンを管理するクラス
/// </summary>
class SceneClear : public SceneBase
{
public:
	//コンストラクタ
	SceneClear();
	//デストラクタ
	virtual ~SceneClear();

	//初期化処理
	virtual void Init();

	//更新処理
	virtual std::shared_ptr<SceneBase> Update();

	//描画処理
	virtual void Draw();

	//終了処理
	virtual void End();

private:
	//Pad入力所得変数
	int m_pad;
};

