#include "Setting.h"
#include "UI/SelectManager.h"
#include "UI/UIBase.h"

namespace
{
	int selectDecision = 0;     //�I���������̂����肷��ϐ�
	int brightDecision = 0;     //���邳�����肷��ϐ�
	int volumeDecision = 0;     //���ʂ����肷��ϐ�
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
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
	m_titleMenu(false),
	m_xpad()
{
	for (int i = 0; i < 3; i++)
	{
		m_menuSelect[i] = 0;
		m_menuColor[i] = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		m_brightColor[i] = 0;
		m_volumeColor[i] = 0;
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Setting::~Setting()
{
	//���������
	DeleteGraph(m_black);
	DeleteGraph(m_back);
	DeleteGraph(m_white);
	se->End();
}

/// <summary>
/// ����������
/// </summary>
void Setting::Init()
{
	//�摜�ǂݍ���
	m_black = LoadGraph("Data/SceneBack/BlackMini.png");         //14.1 KB (14,532 �o�C�g)
	m_back = ui->MyLoadGraph("Data/SceneBack/BlackMini.png", 1, 1);
	m_white = LoadGraph("Data/SceneBack/WhiteMini.png");         //14.1 KB (14,529 �o�C�g)

	selectDecision = 0;

	//���邳�F������
	m_brightColor[0] = 0xffffff;
	m_brightColor[1] = 0xffffff;
	m_brightColor[2] = 0xffff00;
	m_brightColor[3] = 0xffffff;
	m_brightColor[4] = 0xffffff;

	//���ʐF������
	m_volumeColor[0] = 0xffffff;
	m_volumeColor[1] = 0xffffff;
	m_volumeColor[2] = 0xffff00;
	m_volumeColor[3] = 0xffffff;
	m_volumeColor[4] = 0xffffff;

	m_menuSelect[0] = 1;
	m_menuSelect[1] = 0;
	m_menuSelect[2] = 0;

	//���ʃT�C�Y
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

/// <summary>
/// �X�V����
/// </summary>
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
			m_thumb--;
		}
		//��
		else if (m_xpad.ThumbLX < 0)
		{
			m_thumb++;
		}
		else
		{
			//������
			m_button = 0;
			m_thumb = 0;

			m_one = false;
		}

		//�I��
		if (m_brightness == false && m_volume == false)
		{
			pselect->Menu_Update(m_button, m_one, m_xpad.Buttons[12], selectDecision, pselect->Eight);
		}
		//���邳�̑I��
		if (m_brightness == true && m_volume == false)
		{
			pselect->Menu_Update(m_thumb, m_one, m_xpad.Buttons[13], brightDecision, pselect->Six);
		}
		//���ʂ̑I��
		if (m_brightness == false && m_volume == true)
		{
			pselect->Menu_Update(m_thumb, m_one, m_xpad.Buttons[13], volumeDecision, pselect->Six);
		}
		
		//A�{�^������������
		if (m_xpad.Buttons[12] == 1)
		{
			PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

			//���邳�ݒ�
			if (selectDecision == 8)
			{
				m_brightness = true;
			}
			//���ʐݒ�
			if (selectDecision == 9)
			{
				m_volume = true;
			}
			//���̉�ʂɖ߂�
			if (selectDecision == 10)
			{
				m_settingScene = false;
			}
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

/// <summary>
/// ���j���[�X�V����
/// </summary>
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

/// <summary>
/// �`��
/// </summary>
void Setting::Draw()
{
	//�w�i�̐F�𔖂�����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, m_back, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�I�𒆂̐F��ς���
	if (m_brightness == false && m_volume == false)
	{
		if (pselect->NowSelect == pselect->Eight)
		{
			m_brightnessColor = 0xffff00;
			m_bgmColor = 0xffffff;
			m_returnColor = 0xffffff;
		}
		if (pselect->NowSelect == pselect->Nine)
		{
			m_brightnessColor = 0xffffff;
			m_bgmColor = 0xffff00;
			m_returnColor = 0xffffff;
		}
		if (pselect->NowSelect == pselect->Ten)
		{
			m_brightnessColor = 0xffffff;
			m_bgmColor = 0xffffff;
			m_returnColor = 0xffff00;
		}
	}
	//���邳��I��
	if (m_brightness == true)
	{
		BrightColorDraw(5, 0, 1, 2, 3, 4, 125, 0);
		BrightColorDraw(6, 1, 0, 2, 3, 4, 125 / 2, 0);
		BrightColorDraw(7, 2, 1, 0, 3, 4, 0, 0);
		BrightColorDraw(8, 3, 1, 2, 0, 4, 0, 125 / 2);
		BrightColorDraw(9, 4, 1, 2, 3, 0, 0, 125);
	}

	//���ʂ�I��
	if (m_volume == true)
	{
		VolumeColorDraw(5, 0, 1, 2, 3, 4, 0);
		VolumeColorDraw(6, 1, 0, 2, 3, 4, 60);
		VolumeColorDraw(7, 2, 1, 0, 3, 4, 130);
		VolumeColorDraw(8, 3, 1, 2, 0, 4, 190);
		VolumeColorDraw(9, 4, 1, 2, 3, 0, 255);
	}

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

	pselect->Draw();

	//�t�H���g�̃T�C�Y��߂�
	SetFontSize(40);
}

/// <summary>
/// �I�𒆂̐F��ς���
/// </summary>
/// <param name="select">�񋓌^</param>
/// <param name="now">�I�����Ă����</param>
/// <param name="other1">����ȊO�P</param>
/// <param name="other2">����ȊO�Q</param>
/// <param name="other3">����ȊO�R</param>
/// <param name="other4">����ȊO�S</param>
/// <param name="black">�����摜�̃u�����h��</param>
/// <param name="white">�����摜�̃u�����h��</param>
void Setting::BrightColorDraw(int select, int now, int other1, int other2, int other3, int other4, int black, int white)
{
	if (pselect->NowSelect == select)
	{
		m_brightColor[now] = 0xffff00;
		m_brightColor[other1] = 0xffffff;
		m_brightColor[other2] = 0xffffff;
		m_brightColor[other3] = 0xffffff;
		m_brightColor[other4] = 0xffffff;

		m_blackPal = black;
		m_whitePal = white;
	}
}

/// <summary>
/// �I�𒆂̐F��ς���
/// </summary>
/// <param name="select">�񋓌^</param>
/// <param name="now">�I�����Ă����</param>
/// <param name="other1">����ȊO�P</param>
/// <param name="other2">����ȊO�Q</param>
/// <param name="other3">����ȊO�R</param>
/// <param name="other4">����ȊO�S</param>
/// <param name="volume">����</param>
void Setting::VolumeColorDraw(int select, int now, int other1, int other2, int other3, int other4, int volume)
{
	if (pselect->NowSelect == select)
	{
		m_volumeColor[now] = 0xffff00;
		m_volumeColor[other1] = 0xffffff;
		m_volumeColor[other2] = 0xffffff;
		m_volumeColor[other3] = 0xffffff;
		m_volumeColor[other4] = 0xffffff;

		m_volumeSize = volume;
	}
}

/// <summary>
/// �ݒ�̕`�揈��
/// </summary>
/// <param name="volume">����</param>
void Setting::SettingDraw(int volume)
{
	se->Update(volume);

	//���邳
	if (brightDecision == 6)
	{
		m_blackPal = 125;
		m_whitePal = 0;
	}
	if (brightDecision == 7)
	{
		m_blackPal = 125 / 2;
		m_whitePal = 0;
	}
	if (brightDecision == 8)
	{
		m_blackPal = 0;
		m_whitePal = 0;
	}
	if (brightDecision == 9)
	{
		m_blackPal = 0;
		m_whitePal = 125 / 2;
	}
	if (brightDecision == 10)
	{
		m_blackPal = 0;
		m_whitePal = 125;
	}

	//����
	if (volumeDecision == 6)
	{
		m_volumeSize = 0;
	}
	if (volumeDecision == 7)
	{
		m_volumeSize = 60;
	}
	if (volumeDecision == 8)
	{
		m_volumeSize = 130;
	}
	if (volumeDecision == 9)
	{
		m_volumeSize = 190;
	}
	if (volumeDecision == 10)
	{
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

/// <summary>
/// �I������
/// </summary>
void Setting::End()
{
	//���������
	DeleteGraph(m_black);
	DeleteGraph(m_back);
	DeleteGraph(m_white);
	se->End();
}