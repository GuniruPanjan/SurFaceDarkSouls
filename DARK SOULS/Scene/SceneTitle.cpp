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
	//�p�b�h���͏���
	m_pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//A�{�^����������
	if (m_pad & PAD_INPUT_1)
	{
		return std::make_shared<SceneGame>();
	}

	return shared_from_this();  //���g�̃|�C���^��Ԃ�
}

void SceneTitle::Draw()
{
	DrawGraph(0, 0, m_backScene, false);

	DrawString(240, 300, "Title", 0xffffff);
}

void SceneTitle::End()
{
}
