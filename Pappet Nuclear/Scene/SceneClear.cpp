#include "SceneClear.h"
#include "SceneTitle.h"

SceneClear::SceneClear():
	m_pad(0)
{
}

SceneClear::~SceneClear()
{
	//メモリ解放
	DeleteGraph(m_backScene);
}

void SceneClear::Init()
{
	//m_backScene = MyLoadGraph("Data/SceneBack/CLEARBack.png", 10, 10);
	m_backScene = MyLoadGraph("Data/SceneBack/CLEARBackMini.png", 2, 2);

	//設定関係
	setting->Init();
	bgmse->ClearInit();
	bgmse->ClearBGM();
}

std::shared_ptr<SceneBase> SceneClear::Update()
{
	//パッド入力所得
	m_pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//Aボタン押したら
	if (m_pad & PAD_INPUT_1)
	{
		return std::make_shared<SceneTitle>();
	}

	bgmse->Update(setting->GetVolume());

	return shared_from_this();  //自身のポインタを返す
}

void SceneClear::Draw()
{
	//DrawString(240, 300, "Clear", 0xffffff);

	//DrawGraph(220, 100, m_backScene, false);

	DrawGraph(430, 100, m_backScene, false);

	setting->SettingDraw();
}

void SceneClear::End()
{
	//メモリ解放
	DeleteGraph(m_backScene);
	setting->End();
	bgmse->End();
}
