#include "Setting.h"

Setting::Setting():
	m_black(0),
	m_white(0),
	m_back(0),
	m_blackPal(0),
	m_whitePal(0),
	m_button(0),
	m_waitTime(0),
	m_one(false),
	m_settingScene(false)
{
	for (int i = 0; i < 3; i++)
	{
		m_select[i] = 0;
	}
}

Setting::~Setting()
{
	DeleteGraph(m_black);
	DeleteGraph(m_back);
	DeleteGraph(m_white);
}

void Setting::Init()
{
	m_black = LoadGraph("Data/SceneBack/Black.png");
	m_back = MyLoadGraph("Data/SceneBack/Black.png", 13, 13);
	m_white = LoadGraph("Data/SceneBack/White.png");

	m_select[0] = 1;
	m_select[1] = 0;
	m_select[2] = 0;

	m_button = 0;
	m_one = false;
	m_settingScene = false;

	m_blackPal = 0;
	m_whitePal = 0;
}

void Setting::Update()
{
	//�p�b�h���͏���
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

	if (m_waitTime > 10)
	{
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

		//��I����
		if (m_select[0] == 1 && m_button > 0 && m_one == false)
		{
			m_select[2] = 1;
			m_select[0] = 0;

			m_one = true;
		}
		if (m_select[1] == 1 && m_button > 0 && m_one == false)
		{
			m_select[0] = 1;
			m_select[1] = 0;

			m_one = true;
		}
		if (m_select[2] == 1 && m_button > 0 && m_one == false)
		{
			m_select[1] = 1;
			m_select[2] = 0;

			m_one = true;
		}

		//���I����
		if (m_select[0] == 1 && m_button < 0 && m_one == false)
		{
			m_select[1] = 1;
			m_select[0] = 0;

			m_one = true;
		}
		if (m_select[1] == 1 && m_button < 0 && m_one == false)
		{
			m_select[2] = 1;
			m_select[1] = 0;

			m_one = true;
		}
		if (m_select[2] == 1 && m_button < 0 && m_one == false)
		{
			m_select[0] = 1;
			m_select[2] = 0;

			m_one = true;
		}

		//A�{�^����������
		if (m_xpad.Buttons[12] == 1 && m_select[0] == 1)
		{

		}
		//�ݒ�V�[��
		if (m_xpad.Buttons[12] == 1 && m_select[1] == 1)
		{

		}
		//���̉�ʂɖ߂�
		if (m_xpad.Buttons[12] == 1 && m_select[2] == 1)
		{
			m_waitTime = 0;

			m_settingScene = false;
		}
	}
	else
	{
		m_waitTime++;
	}
	
}

void Setting::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(30, 30, m_back, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t�H���g�̃T�C�Y�ύX
	SetFontSize(50);

	DrawString(50, 70, "�ݒ�", 0xffffff);

	SetFontSize(35);

	DrawString(50, 180, "���邳", 0xffffff);
	DrawString(50, 240, "����", 0xffffff);
	DrawString(50, 300, "�߂�", 0xffffff);

	//�t�H���g�̃T�C�Y��߂�
	SetFontSize(20);

	DrawFormatString(0, 0, 0xffffff, "m_select0 : %d", m_select[0]);
	DrawFormatString(0, 20, 0xffffff, "m_select1 : %d", m_select[1]);
	DrawFormatString(0, 40, 0xffffff, "m_select1 : %d", m_select[2]);
}

void Setting::SettingDraw()
{
	//��ʂ��Â�����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_blackPal);
	DrawGraph(0, 0, m_black, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//��ʂ𖾂邭����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_whitePal);
	DrawGraph(0, 0, m_white, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Setting::End()
{
	DeleteGraph(m_black);
	DeleteGraph(m_back);
	DeleteGraph(m_white);
}

int Setting::MyLoadGraph(const char* FileName, int XSize, int YSize)
{
	int handle = LoadGraph(FileName);  //�摜�̃��[�h
	if (handle != -1)  //�摜�̃��[�h�ɐ��������ꍇ
	{
		int SizeX, SizeY;  //�摜�T�C�Y���i�[���邽�߂̕ϐ���p��

		GetGraphSize(handle, &SizeX, &SizeY);  //���[�h�����摜�̃T�C�Y�擾

		int NowScreen = GetDrawScreen();    //���݂̕`��Ώۉ�ʂ��ꎞ�ۑ�

		SizeX /= XSize;
		SizeY /= YSize;

		int miniHandle = MakeScreen(SizeX, SizeY, TRUE);  //�T�C�Y�ύX��̃O���t�B�b�N�n���h�����쐬
		if (miniHandle == -1)   //�n���h���̍쐬�Ɏ��s�����ꍇ
		{
			DeleteGraph(handle);   //���������[�N���Ȃ��悤�ɁA�{���̃O���t�B�b�N�n���h�����폜
		}
		SetDrawScreen(miniHandle);   //�`��Ώۉ�ʂ��قǍ�����T�C�Y�̃O���t�B�b�N�n���h���ɕύX
		DrawExtendGraph(0, 0, SizeX, SizeY, handle, TRUE);   //���[�h�����摜��`��
		DeleteGraph(handle);   //�s�v�ɂȂ����{���̃T�C�Y�̃O���t�B�b�N�n���h�����폜
		SetDrawScreen(NowScreen);  //���݂̕`��Ώۉ�ʂ����̉�ʂɖ߂�

		return miniHandle;  //�k�߂��摜�̃O���t�B�b�N�n���h����Ԃ�
	}
	else   //�摜�̃��[�h�Ɏ��s�����ꍇ
	{
		return -1;   //�G���[����
	}
}
