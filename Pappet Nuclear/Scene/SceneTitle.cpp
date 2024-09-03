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

	//�ʏ�̕`�挋�ʂ��������ރX�N���[���ƁA�t�B���^�[�̏������ʂ��������ރX�N���[���̍쐬
	ColorScreeen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	HighBringhtScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
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
	//DrawCube3D(VGet(0.0f, 0.0f, 0.0f), VGet(700.0f, 300.0f, 300.0f), 0xffffff, 0xffffff, TRUE);

	DrawGraph(-50, 0, m_backScene, false);

	DrawString(240, 300, "Title", 0xffffff);
}

void SceneTitle::End()
{
}
