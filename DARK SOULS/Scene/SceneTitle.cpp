#include "SceneTitle.h"
#include "SceneGame.h"

SceneTitle::SceneTitle():
	m_pad(0)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_backScene = MyLoadGraph("Data/SceneBack/PuppetNuclearTitle.png", 30, 30);
}

std::shared_ptr<SceneBase> SceneTitle::Update()
{
	//パッド入力所得
	m_pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//Aボタン押したら
	if (m_pad & PAD_INPUT_1)
	{
		return std::make_shared<SceneGame>();
	}

	return shared_from_this();  //自身のポインタを返す
}

void SceneTitle::Draw()
{
	DrawGraph(0, 0, m_backScene, false);

	DrawString(240, 300, "Title", 0xffffff);
}

void SceneTitle::End()
{
}
