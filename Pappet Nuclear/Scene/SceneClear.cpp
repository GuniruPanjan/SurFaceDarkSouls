#include "SceneClear.h"
#include "SceneTitle.h"

SceneClear::SceneClear():
	m_pad(0)
{
}

SceneClear::~SceneClear()
{
	//���������
	DeleteGraph(m_backScene);
}

void SceneClear::Init()
{
	//m_backScene = MyLoadGraph("Data/SceneBack/CLEARBack.png", 10, 10);
	m_backScene = MyLoadGraph("Data/SceneBack/CLEARBackMini.png", 2, 2);

	//�ݒ�֌W
	setting->Init();
	bgmse->ClearInit();
	bgmse->ClearBGM();
}

std::shared_ptr<SceneBase> SceneClear::Update()
{
	//�p�b�h���͏���
	m_pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//A�{�^����������
	if (m_pad & PAD_INPUT_1)
	{
		return std::make_shared<SceneTitle>();
	}

	bgmse->Update(setting->GetVolume());

	return shared_from_this();  //���g�̃|�C���^��Ԃ�
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
	//���������
	DeleteGraph(m_backScene);
	setting->End();
	bgmse->End();
}
