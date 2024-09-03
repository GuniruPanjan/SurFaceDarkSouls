#include "SceneTitle.h"
#include "SceneGame.h"

SceneTitle::SceneTitle():
	m_pad(0),
	m_right(0)
{
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_backScene);
	DeleteGraph(m_right);
}

void SceneTitle::Init()
{
	m_backScene = MyLoadGraph("Data/SceneBack/PuppetNuclearTitle.png", 30, 30);
	m_right = MyLoadGraph("Data/SceneBack/A.png", 12, 12);
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
	//DrawCube3D(VGet(0.0f, 0.0f, 0.0f), VGet(700.0f, 300.0f, 300.0f), 0xffffff, 0xffffff, TRUE);

	//描画輝度を緑色にする
	SetDrawBright(255, 255, 255);

	//画像のRGB成分を無視する
	SetIgnoreDrawGraphColor(TRUE);

	//画像描画
	DrawGraph(5, 5, m_right, TRUE);

	//画像のRGB成分を無視する設定を解除する
	SetIgnoreDrawGraphColor(FALSE);

	//描画輝度ももとに戻す
	SetDrawBright(255, 255, 255);

	DrawGraph(-50, 0, m_backScene, TRUE);

	DrawString(240, 300, "Title", 0x000000);

	

	
}

void SceneTitle::End()
{
}
