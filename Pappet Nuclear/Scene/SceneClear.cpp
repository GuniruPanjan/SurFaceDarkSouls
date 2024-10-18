#include "SceneClear.h"
#include "SceneTitle.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneClear::SceneClear():
	m_pad(0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
SceneClear::~SceneClear()
{
	//メモリ解放
	DeleteGraph(m_backScene);
}

/// <summary>
/// 初期化処理
/// </summary>
void SceneClear::Init()
{
	//読み込み
	m_backScene = pui->MyLoadGraph("Data/SceneBack/CLEARBackMini.png", 2, 2);

	//設定関係
	setting->Init();
	pbgm->ClearInit();
	pbgm->ClearBGM();
}

/// <summary>
/// 更新処理
/// </summary>
/// <returns>シーンを返す</returns>
std::shared_ptr<SceneBase> SceneClear::Update()
{
	//パッド入力所得
	m_pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//Aボタン押したら
	if (m_pad & PAD_INPUT_1)
	{
		return std::make_shared<SceneTitle>();
	}

	pbgm->Update(setting->GetVolume());

	return shared_from_this();  //自身のポインタを返す
}

/// <summary>
/// 描画処理
/// </summary>
void SceneClear::Draw()
{
	DrawGraph(430, 100, m_backScene, false);

	setting->SettingDraw(setting->GetVolume());
}

/// <summary>
/// 終了処理
/// </summary>
void SceneClear::End()
{
	//メモリ解放
	DeleteGraph(m_backScene);
	setting->End();
	pbgm->End();
}
