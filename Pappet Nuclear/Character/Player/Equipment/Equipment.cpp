#include "Equipment.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Equipment::Equipment():
	m_equipmentLeave(true),
	m_rightEquipmentOpen(false),
	m_leftEquipmentOpen(false),
	m_waitTime(0),
	m_rightEquipmentBoxColor(0),
	m_leftEquipmentBoxColor(0),
	m_rightEquipmentSelectY(0),
	m_button(0),
	m_one(false),
	m_equipmentRightFist(true),
	m_equipmentLeftFist(true),
	m_equipmentSword(false),
	m_equipmentShield(false),
	m_xpad()
{
	for (int i = 0; i < 2; i++)
	{
		m_equipmentSelect[i] = 0;
		m_rightItem[i] = 0;
		m_leftItem[i] = 0;
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Equipment::~Equipment()
{
}

/// <summary>
/// ����������
/// </summary>
void Equipment::Init()
{
	m_equipmentSelect[0] = 1;
	m_equipmentSelect[1] = 0;
	m_rightItem[0] = 1;
	m_rightItem[1] = 0;
	m_leftItem[0] = 1;
	m_leftItem[1] = 0;

	m_rightEquipmentBoxColor = 0x000000;
	m_leftEquipmentBoxColor = 0x000000;
}

/// <summary>
/// �X�V����
/// </summary>
void Equipment::Update()
{
	//�p�b�h���͏���
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

	//��
	if (m_xpad.Buttons[2] == 1)
	{
		m_button++;
	}
	//�E
	else if (m_xpad.Buttons[3] == 1)
	{
		m_button--;

	}
	else
	{
		//������
		m_button = 0;

		m_one = false;

	}

	//���I��
	if (m_equipmentSelect[0] == 1 && m_button > 0 && m_one == false)
	{
		m_equipmentSelect[1] = 1;
		m_equipmentSelect[0] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	if (m_equipmentSelect[1] == 1 && m_button > 0 && m_one == false)
	{
		m_equipmentSelect[0] = 1;
		m_equipmentSelect[1] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	//�E�I��
	if (m_equipmentSelect[0] == 1 && m_button < 0 && m_one == false)
	{
		m_equipmentSelect[1] = 1;
		m_equipmentSelect[0] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	if (m_equipmentSelect[1] == 1 && m_button < 0 && m_one == false)
	{
		m_equipmentSelect[0] = 1;
		m_equipmentSelect[1] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}


	if (m_waitTime > 10)
	{
		//�E�̑����ύX
		if (m_equipmentSelect[0] == 1)
		{
			m_rightEquipmentBoxColor = 0xffff00;
			m_leftEquipmentBoxColor = 0x000000;

			//A�{�^����������
			if (m_xpad.Buttons[12] == 1)
			{
				m_rightEquipmentOpen = true;

				m_waitTime = 0;
			}
		}
		//���̑����ύX
		if (m_equipmentSelect[1] == 1)
		{
			m_leftEquipmentBoxColor = 0xffff00;
			m_rightEquipmentBoxColor = 0x000000;

			//A�{�^����������
			if (m_xpad.Buttons[12] == 1)
			{
				m_leftEquipmentOpen = true;

				m_waitTime = 0;
			}
		}
	}
	else
	{
		m_waitTime++;
	}
	

	if (m_waitTime > 10)
	{
		//B�{�^���������Ɩ߂�
		if (m_xpad.Buttons[13] == 1)
		{
			m_equipmentLeave = false;

			m_waitTime = 0;
		}
		else
		{
			m_equipmentLeave = true;
		}
	}
	else
	{
		m_equipmentLeave = true;
	}
	
}

/// <summary>
/// �E�葕���̍X�V����
/// </summary>
void Equipment::RightUpdate()
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
	if (m_rightItem[0] == 1 && m_button > 0 && m_one == false)
	{
		m_rightItem[1] = 1;
		m_rightItem[0] = 0;

		

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	if (m_rightItem[1] == 1 && m_button > 0 && m_one == false)
	{
		m_rightItem[0] = 1;
		m_rightItem[1] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	//���I��
	if (m_rightItem[0] == 1 && m_button < 0 && m_one == false)
	{
		m_rightItem[1] = 1;
		m_rightItem[0] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	if (m_rightItem[1] == 1 && m_button < 0 && m_one == false)
	{
		m_rightItem[0] = 1;
		m_rightItem[1] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}


	if (m_waitTime > 10)
	{
		//�f�葕��
		if (m_rightItem[0] == 1)
		{
			//A�{�^����������
			if (m_xpad.Buttons[12] == 1)
			{
				m_equipmentRightFist = true;
				m_equipmentSword = false;

				m_rightEquipmentOpen = false;

				m_waitTime = 0;

			}

			m_rightEquipmentSelectY = 100;
		}
		//������
		if (m_rightItem[1] == 1)
		{
			//A�{�^����������
			if (m_xpad.Buttons[12] == 1)
			{
				m_equipmentRightFist = false;
				m_equipmentSword = true;

				m_rightEquipmentOpen = false;

				m_waitTime = 0;
			}

			m_rightEquipmentSelectY = 300;
		}

		//B�{�^����������
		if (m_xpad.Buttons[13] == 1)
		{
			m_rightEquipmentOpen = false;

			m_waitTime = 0;
		}
	}
	else
	{
		m_waitTime++;
	}
	
}

/// <summary>
/// ���葕���̍X�V����
/// </summary>
void Equipment::LeftUpdate()
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
	if (m_leftItem[0] == 1 && m_button > 0 && m_one == false)
	{
		m_leftItem[1] = 1;
		m_leftItem[0] = 0;



		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	if (m_leftItem[1] == 1 && m_button > 0 && m_one == false)
	{
		m_leftItem[0] = 1;
		m_leftItem[1] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	//���I��
	if (m_leftItem[0] == 1 && m_button < 0 && m_one == false)
	{
		m_leftItem[1] = 1;
		m_leftItem[0] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}
	if (m_leftItem[1] == 1 && m_button < 0 && m_one == false)
	{
		m_leftItem[0] = 1;
		m_leftItem[1] = 0;

		PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

		m_one = true;
	}


	if (m_waitTime > 10)
	{
		//�f�葕��
		if (m_leftItem[0] == 1)
		{
			//A�{�^����������
			if (m_xpad.Buttons[12] == 1)
			{
				m_equipmentLeftFist = true;
				m_equipmentShield = false;

				m_leftEquipmentOpen = false;

				m_waitTime = 0;

			}

			m_leftEquipmentSelectY = 100;
		}
		//������
		if (m_leftItem[1] == 1)
		{
			//A�{�^����������
			if (m_xpad.Buttons[12] == 1)
			{
				m_equipmentLeftFist = false;
				m_equipmentShield = true;

				m_leftEquipmentOpen = false;

				m_waitTime = 0;
			}

			m_leftEquipmentSelectY = 300;
		}

		//B�{�^����������
		if (m_xpad.Buttons[13] == 1)
		{
			m_leftEquipmentOpen = false;

			m_waitTime = 0;
		}
	}
	else
	{
		m_waitTime++;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Equipment::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, DrawBox(0, 0, 1600, 1600, 0x000000, true), false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGraph(0, 0, DrawBox(200, 200, 400, 400, m_rightEquipmentBoxColor, true), false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//���������ꍇ
	if (m_equipmentRightFist == true)
	{
		DrawGraph(180, 220, m_fist, true);
	}
	//���������ꍇ
	if (m_equipmentSword == true)
	{
		DrawGraph(150, 200, m_sword, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGraph(0, 0, DrawBox(600, 200, 800, 400, m_leftEquipmentBoxColor, true), false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//���������ꍇ
	if (m_equipmentLeftFist == true)
	{
		DrawGraph(580, 220, m_fist, true);
	}
	//���������ꍇ
	if (m_equipmentShield == true)
	{
		DrawGraph(550, 190, m_shield, true);
	}


	//�t�H���g�̃T�C�Y�ύX
	SetFontSize(100);

	DrawString(100, 30, "�������j���[", 0xffffff);

	SetFontSize(80);

	DrawString(100, 220, "�E\n��", 0xffffff);

	DrawString(500, 220, "��\n��", 0xffffff);


	//�t�H���g�̃T�C�Y��߂�
	SetFontSize(40);

	DrawString(100, 800, "B�{�^���Ŗ߂�", 0xffffff);

}

/// <summary>
/// �E��̑����`�揈��
/// </summary>
void Equipment::RightDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, DrawBox(0, 0, 1600, 1600, 0x000000, true), false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(150, m_rightEquipmentSelectY, DrawBox(150, m_rightEquipmentSelectY, 350, m_rightEquipmentSelectY + 200, 0xffff00, true), false);

	DrawGraph(140, 100, m_fist, true);
	DrawGraph(100, 300, m_sword, true);


	//�f�葕��
	if (m_rightItem[0] == 1)
	{
		DrawString(400, 200, "�Ȃ��M�����B��̕���", 0xffffff);
	}
	//������
	if (m_rightItem[1] == 1)
	{
		DrawString(400, 400, "��g�p�̕���", 0xffffff);
	}
}

/// <summary>
/// ����̑����`�揈��
/// </summary>
void Equipment::LeftDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, DrawBox(0, 0, 1600, 1600, 0x000000, true), false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(150, m_leftEquipmentSelectY, DrawBox(150, m_leftEquipmentSelectY, 350, m_leftEquipmentSelectY + 200, 0xffff00, true), false);

	DrawGraph(140, 100, m_fist, true);
	DrawGraph(100, 300, m_shield, true);


	//�f�葕��
	if (m_leftItem[0] == 1)
	{
		DrawString(400, 200, "�Ȃ��M�����B��̕���", 0xffffff);
	}
	//������
	if (m_leftItem[1] == 1)
	{
		DrawString(400, 400, "�c�Ȗ�l�̏�", 0xffffff);
	}
}

/// <summary>
/// �I������
/// </summary>
void Equipment::End()
{
}
