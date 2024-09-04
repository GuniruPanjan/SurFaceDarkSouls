#include "Setting.h"

Setting::Setting():
	m_black(0),
	m_white(0),
	m_blackPal(0),
	m_whitePal(0),
	m_button(0),
	m_one(false)
{
	for (int i = 0; i < 2; i++)
	{
		m_select[i] = 0;
	}
}

Setting::~Setting()
{
	DeleteGraph(m_black);
	DeleteGraph(m_white);
}

void Setting::Init()
{
	m_black = LoadGraph("Data/SceneBack/Black.png");
	m_white = LoadGraph("Data/SceneBack/White.png");

	m_select[0] = 1;
	m_select[1] = 0;

	m_button = 0;
	m_one = false;

	m_blackPal = 0;
	m_whitePal = 0;
}

void Setting::Update()
{
	//�p�b�h���͏���
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

	//��
	if (m_xpad.ThumbLY > 2000)
	{
		m_button++;
	}
	//��
	else if (m_xpad.ThumbLY < 0)
	{
		m_button--;
	}
	else
	{
		//������
		m_button = 0;

		m_one = false;
	}

	DrawFormatString(0, 0, 0xffffff, "m_select0 : %d", m_select[0]);
	DrawFormatString(0, 20, 0xffffff, "m_select1 : %d", m_select[1]);
}

void Setting::Draw()
{
	//��ʂ��Â�����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_blackPal);
	DrawGraph(0, 0, m_black, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//��ʂ𖾂邭����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_whitePal);
	DrawGraph(0, 0, m_white, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t�H���g�̃T�C�Y�ύX
	SetFontSize(50);

	DrawString(50, 80, "�ݒ�", 0xffffff);

	SetFontSize(35);

	DrawString(50, 180, "���邳", 0xffffff);
	DrawString(50, 240, "����", 0xffffff);

	//�t�H���g�̃T�C�Y��߂�
	SetFontSize(20);
}

void Setting::End()
{
	DeleteGraph(m_black);
	DeleteGraph(m_white);
}
