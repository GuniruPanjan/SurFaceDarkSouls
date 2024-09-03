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

	//�`��P�x��ΐF�ɂ���
	SetDrawBright(255, 255, 255);

	//�摜��RGB�����𖳎�����
	SetIgnoreDrawGraphColor(TRUE);

	//�摜�`��
	DrawGraph(5, 5, m_right, TRUE);

	//�摜��RGB�����𖳎�����ݒ����������
	SetIgnoreDrawGraphColor(FALSE);

	//�`��P�x�����Ƃɖ߂�
	SetDrawBright(255, 255, 255);

	DrawGraph(-50, 0, m_backScene, TRUE);

	DrawString(240, 300, "Title", 0x000000);

	

	
}

void SceneTitle::End()
{
}
