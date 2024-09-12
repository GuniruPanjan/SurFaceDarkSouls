#include "Setting.h"

namespace
{
	int updateBriht[5];
	int updateVolume[5];
}

Setting::Setting():
	m_black(0),
	m_white(0),
	m_back(0),
	m_blackPal(0),
	m_whitePal(0),
	m_button(0),
	m_thumb(0),
	m_waitTime(0),
	m_brightnessColor(0),
	m_bgmColor(0),
	m_returnColor(0),
	m_one(false),
	m_settingScene(false),
	m_brightness(false),
	m_volume(false),
	m_volumeSize(0),
	m_equipmentMenu(false),
	m_returnMenu(true),
	m_titleMenu(false)
{
	for (int i = 0; i < 3; i++)
	{
		m_select[i] = 0;
		m_menuSelect[i] = 0;
		m_menuColor[i] = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		m_brightSelect[i] = 0;
		m_volumeSelect[i] = 0;
		m_brightColor[i] = 0;
		m_volumeColor[i] = 0;
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
	//m_black = LoadGraph("Data/SceneBack/Black.png");
	//m_back = MyLoadGraph("Data/SceneBack/Black.png", 15, 15);
	//m_white = LoadGraph("Data/SceneBack/White.png");

	m_black = LoadGraph("Data/SceneBack/BlackMini.png");
	m_back = MyLoadGraph("Data/SceneBack/BlackMini.png", 1, 1);
	m_white = LoadGraph("Data/SceneBack/WhiteMini.png");

	m_select[0] = 1;
	m_select[1] = 0;
	m_select[2] = 0;

	m_brightSelect[0] = updateBriht[0];
	m_brightSelect[1] = updateBriht[1];
	m_brightSelect[2] = updateBriht[2];
	m_brightSelect[3] = updateBriht[3];
	m_brightSelect[4] = updateBriht[4];

	m_brightColor[0] = 0xffffff;
	m_brightColor[1] = 0xffffff;
	m_brightColor[2] = 0xffff00;
	m_brightColor[3] = 0xffffff;
	m_brightColor[4] = 0xffffff;

	m_volumeSelect[0] = updateVolume[0];
	m_volumeSelect[1] = updateVolume[1];
	m_volumeSelect[2] = updateVolume[2];
	m_volumeSelect[3] = updateVolume[3];
	m_volumeSelect[4] = updateVolume[4];

	m_volumeColor[0] = 0xffffff;
	m_volumeColor[1] = 0xffffff;
	m_volumeColor[2] = 0xffff00;
	m_volumeColor[3] = 0xffffff;
	m_volumeColor[4] = 0xffffff;

	m_menuSelect[0] = 1;
	m_menuSelect[1] = 0;
	m_menuSelect[2] = 0;

	m_volumeSize = 130;

	m_button = 0;
	m_thumb = 0;
	m_one = false;
	m_settingScene = false;
	m_brightness = false;
	m_volume = false;
	m_equipmentMenu = false;
	m_returnMenu = true;
	m_titleMenu = false;

	m_brightnessColor = 0xffffff;
	m_bgmColor = 0xffffff;
	m_returnColor = 0xffffff;

	m_blackPal = 0;
	m_whitePal = 0;

	se->SceneInit();
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
		//�E
		else if (m_xpad.ThumbLX > 2000)
		{
			m_thumb++;
		}
		//��
		else if (m_xpad.ThumbLX < 0)
		{
			m_thumb--;
		}
		else
		{
			//������
			m_button = 0;
			m_thumb = 0;

			m_one = false;
		}

		//��I����
		if (m_select[0] == 1 && m_button > 0 && m_one == false &&
			m_brightness == false && m_volume == false)
		{
			m_select[2] = 1;
			m_select[0] = 0;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_select[1] == 1 && m_button > 0 && m_one == false &&
			m_brightness == false && m_volume == false)
		{
			m_select[0] = 1;
			m_select[1] = 0;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_select[2] == 1 && m_button > 0 && m_one == false &&
			m_brightness == false && m_volume == false)
		{
			m_select[1] = 1;
			m_select[2] = 0;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}

		//���I����
		if (m_select[0] == 1 && m_button < 0 && m_one == false &&
			m_brightness == false && m_volume == false)
		{
			m_select[1] = 1;
			m_select[0] = 0;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_select[1] == 1 && m_button < 0 && m_one == false &&
			m_brightness == false && m_volume == false)
		{
			m_select[2] = 1;
			m_select[1] = 0;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_select[2] == 1 && m_button < 0 && m_one == false &&
			m_brightness == false && m_volume == false)
		{
			m_select[0] = 1;
			m_select[2] = 0;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}

		//�E�I��(���邳)
		if (m_brightSelect[0] == 1 && m_thumb > 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[0] = 0;
			m_brightSelect[1] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_brightSelect[1] == 1 && m_thumb > 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[1] = 0;
			m_brightSelect[2] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_brightSelect[2] == 1 && m_thumb > 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[2] = 0;
			m_brightSelect[3] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_brightSelect[3] == 1 && m_thumb > 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[3] = 0;
			m_brightSelect[4] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_brightSelect[4] == 1 && m_thumb > 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[4] = 0;
			m_brightSelect[0] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		//���I��(���邳)
		if (m_brightSelect[0] == 1 && m_thumb < 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[0] = 0;
			m_brightSelect[4] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_brightSelect[1] == 1 && m_thumb < 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[1] = 0;
			m_brightSelect[0] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_brightSelect[2] == 1 && m_thumb < 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[2] = 0;
			m_brightSelect[1] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_brightSelect[3] == 1 && m_thumb < 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[3] = 0;
			m_brightSelect[2] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_brightSelect[4] == 1 && m_thumb < 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[4] = 0;
			m_brightSelect[3] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		//�E�I��(����)
		if (m_volumeSelect[0] == 1 && m_thumb > 0 && m_one == false &&
			m_volume == true && m_brightness == false)
		{
			m_volumeSelect[0] = 0;
			m_volumeSelect[1] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_volumeSelect[1] == 1 && m_thumb > 0 && m_one == false &&
			m_volume == true && m_brightness == false)
		{
			m_volumeSelect[1] = 0;
			m_volumeSelect[2] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_volumeSelect[2] == 1 && m_thumb > 0 && m_one == false &&
			m_volume == true && m_brightness == false)
		{
			m_volumeSelect[2] = 0;
			m_volumeSelect[3] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_volumeSelect[3] == 1 && m_thumb > 0 && m_one == false &&
			m_volume == true && m_brightness == false)
		{
			m_volumeSelect[3] = 0;
			m_volumeSelect[4] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_volumeSelect[4] == 1 && m_thumb > 0 && m_one == false &&
			m_volume == true && m_brightness == false)
		{
			m_volumeSelect[4] = 0;
			m_volumeSelect[0] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		//���I��(����)
		if (m_volumeSelect[0] == 1 && m_thumb < 0 && m_one == false &&
			m_volume == true && m_brightness == false)
		{
			m_volumeSelect[0] = 0;
			m_volumeSelect[4] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_volumeSelect[1] == 1 && m_thumb < 0 && m_one == false &&
			m_volume == true && m_brightness == false)
		{
			m_volumeSelect[1] = 0;
			m_volumeSelect[0] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_volumeSelect[2] == 1 && m_thumb < 0 && m_one == false &&
			m_volume == true && m_brightness == false)
		{
			m_volumeSelect[2] = 0;
			m_volumeSelect[1] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_volumeSelect[3] == 1 && m_thumb < 0 && m_one == false &&
			m_volume == true && m_brightness == false)
		{
			m_volumeSelect[3] = 0;
			m_volumeSelect[2] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}
		if (m_volumeSelect[4] == 1 && m_thumb < 0 && m_one == false &&
			m_volume == true && m_brightness == false)
		{
			m_volumeSelect[4] = 0;
			m_volumeSelect[3] = 1;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_one = true;
		}

		//A�{�^����������
		//���邳�ݒ�
		if (m_xpad.Buttons[12] == 1 && m_select[0] == 1 && 
			m_brightness == false && m_volume == false)
		{
			updateBriht[2] = 1;
			m_brightSelect[2] = 1;

			PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

			m_brightness = true;
		}
		//���ʐݒ�
		if (m_xpad.Buttons[12] == 1 && m_select[1] == 1 &&
			m_brightness == false && m_volume == false)
		{
			updateVolume[2] = 1;
			m_volumeSelect[2] = 1;

			PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

			m_volume = true;
		}
		//���̉�ʂɖ߂�
		if (m_xpad.Buttons[12] == 1 && m_select[2] == 1 &&
			m_brightness == false && m_volume == false)
		{
			m_waitTime = 0;

			PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

			m_settingScene = false;
		}
		//���邳�ݒ����������
		if (m_brightness == true)
		{
			//B�{�^������������
			if (m_xpad.Buttons[13] == 1)
			{
				PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

				m_brightness = false;
			}
		}
		//���ʐݒ����������
		if (m_volume == true)
		{
			//B�{�^������������
			if (m_xpad.Buttons[13] == 1)
			{
				PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

				m_volume = false;
			}
		}
	}
	else
	{
		m_waitTime++;
	}

	se->Update(m_volumeSize);
	
}

void Setting::MenuUpdate()
{
	//�p�b�h���͏���
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

	//��
	if (m_xpad.Buttons[0] == 1)
	{
		m_button++;
	}
	//��
	else if (m_xpad.Buttons[1] == 1)
	{
		m_button--;
	}
	else
	{
		//������
		m_button = 0;

		m_one = false;
	}

	//��I��
	if (m_menuSelect[0] == 1 && m_button > 0 && m_one == false)
	{
		m_menuSelect[2] = 1;
		m_menuSelect[0] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	if (m_menuSelect[1] == 1 && m_button > 0 && m_one == false)
	{
		m_menuSelect[0] = 1;
		m_menuSelect[1] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	if (m_menuSelect[2] == 1 && m_button > 0 && m_one == false)
	{
		m_menuSelect[1] = 1;
		m_menuSelect[2] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	//���I��
	if (m_menuSelect[0] == 1 && m_button < 0 && m_one == false)
	{
		m_menuSelect[1] = 1;
		m_menuSelect[0] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	if (m_menuSelect[1] == 1 && m_button < 0 && m_one == false)
	{
		m_menuSelect[2] = 1;
		m_menuSelect[1] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	if (m_menuSelect[2] == 1 && m_button < 0 && m_one == false)
	{
		m_menuSelect[0] = 1;
		m_menuSelect[2] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	//A�{�^����������
	//�������j���[
	if (m_xpad.Buttons[12] == 1 && m_menuSelect[0] == 1)
	{
		PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

		m_equipmentMenu = true;
	}
	//�߂�
	if (m_xpad.Buttons[12] == 1 && m_menuSelect[1] == 1)
	{
		PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

		m_returnMenu = false;
	}
	//�^�C�g���ɖ߂�
	if (m_xpad.Buttons[12] == 1 && m_menuSelect[2] == 1)
	{
		PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

		m_titleMenu = true;
	}

}

void Setting::Draw()
{
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	//DrawGraph(30, 30, m_back, false);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, m_back, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�I�𒆂̐F��ς���
	if (m_select[0] == 1)
	{
		m_brightnessColor = 0xffff00;
		m_bgmColor = 0xffffff;
		m_returnColor = 0xffffff;

	}
	if (m_select[1] == 1)
	{
		m_brightnessColor = 0xffffff;
		m_bgmColor = 0xffff00;
		m_returnColor = 0xffffff;
	}
	if (m_select[2] == 1)
	{
		m_brightnessColor = 0xffffff;
		m_bgmColor = 0xffffff;
		m_returnColor = 0xffff00;
	}
	if (m_brightSelect[0] == 1)
	{
		m_brightColor[0] = 0xffff00;
		m_brightColor[1] = 0xffffff;
		m_brightColor[2] = 0xffffff;
		m_brightColor[3] = 0xffffff;
		m_brightColor[4] = 0xffffff;
	}
	if (m_brightSelect[1] == 1)
	{
		m_brightColor[0] = 0xffffff;
		m_brightColor[1] = 0xffff00;
		m_brightColor[2] = 0xffffff;
		m_brightColor[3] = 0xffffff;
		m_brightColor[4] = 0xffffff;
	}
	if (m_brightSelect[2] == 1)
	{
		m_brightColor[0] = 0xffffff;
		m_brightColor[1] = 0xffffff;
		m_brightColor[2] = 0xffff00;
		m_brightColor[3] = 0xffffff;
		m_brightColor[4] = 0xffffff;
	}
	if (m_brightSelect[3] == 1)
	{
		m_brightColor[0] = 0xffffff;
		m_brightColor[1] = 0xffffff;
		m_brightColor[2] = 0xffffff;
		m_brightColor[3] = 0xffff00;
		m_brightColor[4] = 0xffffff;
	}
	if (m_brightSelect[4] == 1)
	{
		m_brightColor[0] = 0xffffff;
		m_brightColor[1] = 0xffffff;
		m_brightColor[2] = 0xffffff;
		m_brightColor[3] = 0xffffff;
		m_brightColor[4] = 0xffff00;
	}
	if (m_volumeSelect[0] == 1)
	{
		m_volumeColor[0] = 0xffff00;
		m_volumeColor[1] = 0xffffff;
		m_volumeColor[2] = 0xffffff;
		m_volumeColor[3] = 0xffffff;
		m_volumeColor[4] = 0xffffff;

	}
	if (m_volumeSelect[1] == 1)
	{
		m_volumeColor[0] = 0xffffff;
		m_volumeColor[1] = 0xffff00;
		m_volumeColor[2] = 0xffffff;
		m_volumeColor[3] = 0xffffff;
		m_volumeColor[4] = 0xffffff;

	}
	if (m_volumeSelect[2] == 1)
	{
		m_volumeColor[0] = 0xffffff;
		m_volumeColor[1] = 0xffffff;
		m_volumeColor[2] = 0xffff00;
		m_volumeColor[3] = 0xffffff;
		m_volumeColor[4] = 0xffffff;

	}
	if (m_volumeSelect[3] == 1)
	{
		m_volumeColor[0] = 0xffffff;
		m_volumeColor[1] = 0xffffff;
		m_volumeColor[2] = 0xffffff;
		m_volumeColor[3] = 0xffff00;
		m_volumeColor[4] = 0xffffff;

	}
	if (m_volumeSelect[4] == 1)
	{
		m_volumeColor[0] = 0xffffff;
		m_volumeColor[1] = 0xffffff;
		m_volumeColor[2] = 0xffffff;
		m_volumeColor[3] = 0xffffff;
		m_volumeColor[4] = 0xffff00;

	}

	////�t�H���g�̃T�C�Y�ύX
	//SetFontSize(50);

	//DrawString(50, 70, "�ݒ�", 0xffffff);

	//SetFontSize(35);

	//DrawString(50, 180, "���邳", m_brightnessColor);
	//DrawString(50, 240, "����", m_bgmColor);
	//DrawString(50, 300, "�߂�", m_returnColor);

	//DrawBox(200, 180, 240, 220, m_brightColor[0], true);
	//DrawBox(280, 180, 320, 220, m_brightColor[1], true);
	//DrawBox(360, 180, 400, 220, m_brightColor[2], true);
	//DrawBox(440, 180, 480, 220, m_brightColor[3], true);
	//DrawBox(520, 180, 560, 220, m_brightColor[4], true);

	//DrawBox(200, 240, 240, 280, m_volumeColor[0], true);
	//DrawBox(280, 240, 320, 280, m_volumeColor[1], true);
	//DrawBox(360, 240, 400, 280, m_volumeColor[2], true);
	//DrawBox(440, 240, 480, 280, m_volumeColor[3], true);
	//DrawBox(520, 240, 560, 280, m_volumeColor[4], true);

	////�t�H���g�̃T�C�Y��߂�
	//SetFontSize(20);

	//�t�H���g�̃T�C�Y�ύX
	SetFontSize(150);

	DrawString(100, 70, "�ݒ�", 0xffffff);

	SetFontSize(100);

	DrawString(100, 340, "���邳", m_brightnessColor);
	DrawString(100, 500, "����", m_bgmColor);
	DrawString(100, 660, "�߂�", m_returnColor);

	DrawBox(500, 340, 620, 460, m_brightColor[0], true);
	DrawBox(700, 340, 820, 460, m_brightColor[1], true);
	DrawBox(900, 340, 1020, 460, m_brightColor[2], true);
	DrawBox(1100, 340, 1220, 460, m_brightColor[3], true);
	DrawBox(1300, 340, 1420, 460, m_brightColor[4], true);

	DrawBox(500, 500, 620, 620, m_volumeColor[0], true);
	DrawBox(700, 500, 820, 620, m_volumeColor[1], true);
	DrawBox(900, 500, 1020, 620, m_volumeColor[2], true);
	DrawBox(1100, 500, 1220, 620, m_volumeColor[3], true);
	DrawBox(1300, 500, 1420, 620, m_volumeColor[4], true);

	//�t�H���g�̃T�C�Y��߂�
	SetFontSize(40);

	//DrawFormatString(0, 0, 0xffffff, "m_thumb : %d", m_thumb);
}

void Setting::SettingDraw()
{
	//���邳
	if (m_brightSelect[0] == 1)
	{
		updateBriht[0] = 1;
		updateBriht[1] = 0;
		updateBriht[2] = 0;
		updateBriht[3] = 0;
		updateBriht[4] = 0;

		m_blackPal = 125;
		m_whitePal = 0;
	}
	if (m_brightSelect[1] == 1)
	{
		updateBriht[0] = 0;
		updateBriht[1] = 1;
		updateBriht[2] = 0;
		updateBriht[3] = 0;
		updateBriht[4] = 0;

		m_blackPal = 125 / 2;
		m_whitePal = 0;
	}
	if (m_brightSelect[2] == 1)
	{
		updateBriht[0] = 0;
		updateBriht[1] = 0;
		updateBriht[2] = 1;
		updateBriht[3] = 0;
		updateBriht[4] = 0;

		m_blackPal = 0;
		m_whitePal = 0;
	}
	if (m_brightSelect[3] == 1)
	{
		updateBriht[0] = 0;
		updateBriht[1] = 0;
		updateBriht[2] = 0;
		updateBriht[3] = 1;
		updateBriht[4] = 0;

		m_blackPal = 0;
		m_whitePal = 75 / 2;
	}
	if (m_brightSelect[4] == 1)
	{
		updateBriht[0] = 0;
		updateBriht[1] = 0;
		updateBriht[2] = 0;
		updateBriht[3] = 0;
		updateBriht[4] = 1;

		m_blackPal = 0;
		m_whitePal = 75;
	}
	//����
	if (m_volumeSelect[0] == 1)
	{
		updateVolume[0] = 1;
		updateVolume[1] = 0;
		updateVolume[2] = 0;
		updateVolume[3] = 0;
		updateVolume[4] = 0;

		m_volumeSize = 0;
	}
	if (m_volumeSelect[1] == 1)
	{
		updateVolume[0] = 0;
		updateVolume[1] = 1;
		updateVolume[2] = 0;
		updateVolume[3] = 0;
		updateVolume[4] = 0;

		m_volumeSize = 60;
	}
	if (m_volumeSelect[2] == 1)
	{
		updateVolume[0] = 0;
		updateVolume[1] = 0;
		updateVolume[2] = 1;
		updateVolume[3] = 0;
		updateVolume[4] = 0;

		m_volumeSize = 130;
	}
	if (m_volumeSelect[3] == 1)
	{
		updateVolume[0] = 0;
		updateVolume[1] = 0;
		updateVolume[2] = 0;
		updateVolume[3] = 1;
		updateVolume[4] = 0;

		m_volumeSize = 190;
	}
	if (m_volumeSelect[4] == 1)
	{
		updateVolume[0] = 0;
		updateVolume[1] = 0;
		updateVolume[2] = 0;
		updateVolume[3] = 0;
		updateVolume[4] = 1;

		m_volumeSize = 255;
	}

	//��ʂ��Â�����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_blackPal);
	DrawGraph(0, 0, m_black, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//��ʂ𖾂邭����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_whitePal);
	DrawGraph(0, 0, m_white, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Setting::MenuDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, m_back, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (m_menuSelect[0] == 1)
	{
		m_menuColor[0] = 0xffff00;
		m_menuColor[1] = 0xffffff;
		m_menuColor[2] = 0xffffff;
	}
	if (m_menuSelect[1] == 1)
	{
		m_menuColor[0] = 0xffffff;
		m_menuColor[1] = 0xffff00;
		m_menuColor[2] = 0xffffff;
	}
	if (m_menuSelect[2] == 1)
	{
		m_menuColor[0] = 0xffffff;
		m_menuColor[1] = 0xffffff;
		m_menuColor[2] = 0xffff00;
	}

	//�t�H���g�̃T�C�Y�ύX
	SetFontSize(150);

	DrawString(100, 70, "���j���[", 0xffffff);

	SetFontSize(100);

	DrawString(100, 340, "����", m_menuColor[0]);
	DrawString(100, 500, "�߂�", m_menuColor[1]);
	DrawString(100, 660, "�^�C�g����", m_menuColor[2]);

	//�t�H���g�̃T�C�Y��߂�
	SetFontSize(40);
}

void Setting::End()
{
	DeleteGraph(m_black);
	DeleteGraph(m_back);
	DeleteGraph(m_white);
	se->End();
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
