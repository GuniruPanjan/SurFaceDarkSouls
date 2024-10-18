#pragma once
#include "DxLib.h"
#include "BGM・SE/BgmManager.h"
#include "UI/Setting.h"
#include "UI/UI.h"
#include<memory>

/// <summary>
/// シーンのベースを管理するクラス
/// </summary>
class SceneBase : public std::enable_shared_from_this<SceneBase>
{
public:
	//コンストラクタ
	SceneBase():
		m_end(false)
	{}

	//デストラクタ
	virtual ~SceneBase(){}

	//virtualで継承先を呼び出す

	//初期化処理
	virtual void Init() = 0;

	//更新処理
	virtual std::shared_ptr<SceneBase> Update() = 0;

	//描画処理
	virtual void Draw() = 0;

	//終了処理
	virtual void End() = 0;

	/// <summary>
	/// 判定をとる
	/// </summary>
	/// <returns>終了判定を返す</returns>
	bool GetEnd() { return m_end; }

	/// <summary>
	/// 終了判定を決める
	/// </summary>
	/// <param name="end">判定をとる</param>
	/// <returns>結果を返す</returns>
	bool SetEnd(bool end) { return m_end = end; }

protected:
	//変数を入れる
	int m_backScene = 0;
	bool m_end;   //ゲーム終了変数

	//スマートポインタ
	std::shared_ptr<Setting> setting = std::make_shared<Setting>();
	std::shared_ptr<BgmManager> pbgm = std::make_shared<BgmManager>();
	std::shared_ptr<UI> pui = std::make_shared<UI>();
};

