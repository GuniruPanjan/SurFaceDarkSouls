#include "SceneClear.h"
#include "SceneTitle.h"

SceneClear::SceneClear():
	m_pad(0)
{
}

SceneClear::~SceneClear()
{
}

void SceneClear::Init()
{
	setting->Init();
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

	return shared_from_this();  //自身のポインタを返す
}

void SceneClear::Draw()
{
	DrawString(240, 300, "Clear", 0xffffff);
}

void SceneClear::End()
{
}
