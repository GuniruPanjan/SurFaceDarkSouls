#include "Equipment.h"

Equipment::Equipment():
	m_equipmentLeave(true),
	m_rightEquipmentOpen(false),
	m_waitTime(0),
	m_rightEquipmentBoxColor(0),
	m_rightEquipmentSelectY(0),
	m_button(0),
	m_one(false),
	m_equipmentFist(true),
	m_equipmentSword(false)
{
	for (int i = 0; i < 2; i++)
	{
		m_equipmentSelect[i] = 0;
	}
}

Equipment::~Equipment()
{
}

void Equipment::Init()
{
	m_equipmentSelect[0] = 1;
	m_equipmentSelect[1] = 0;
	m_rightItem[0] = 1;
	m_rightItem[1] = 0;

	m_rightEquipmentBoxColor = 0x000000;
}

void Equipment::Update()
{
	//パッド入力所得
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

	if (m_waitTime > 10)
	{
		//右の装備変更
		if (m_equipmentSelect[0] == 1)
		{
			m_rightEquipmentBoxColor = 0xffff00;

			//Aボタンを押すと
			if (m_xpad.Buttons[12] == 1)
			{
				m_rightEquipmentOpen = true;

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
		//Bボタンを押すと戻る
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

void Equipment::RightUpdate()
{
	//パッド入力所得
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

	//上
	if (m_xpad.Buttons[0] == 1)
	{
		m_button++;
	}
	//下
	else if (m_xpad.Buttons[1] == 1)
	{
		m_button--;
	}
	else
	{
		//初期化
		m_button = 0;

		m_one = false;
	}
	//上選択
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
	//下選択
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
		//素手装備
		if (m_rightItem[0] == 1)
		{
			//Aボタンを押すと
			if (m_xpad.Buttons[12] == 1)
			{
				m_equipmentFist = true;
				m_equipmentSword = false;

				m_rightEquipmentOpen = false;

				m_waitTime = 0;

			}

			m_rightEquipmentSelectY = 100;
		}
		//剣装備
		if (m_rightItem[1] == 1)
		{
			//Aボタンを押すと
			if (m_xpad.Buttons[12] == 1)
			{
				m_equipmentFist = false;
				m_equipmentSword = true;

				m_rightEquipmentOpen = false;

				m_waitTime = 0;
			}

			m_rightEquipmentSelectY = 300;
		}

		//Bボタンを押すと
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

void Equipment::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, DrawBox(0, 0, 1600, 1600, 0x000000, true), false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGraph(0, 0, DrawBox(200, 200, 400, 400, m_rightEquipmentBoxColor, true), false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//拳だった場合
	if (m_equipmentFist == true)
	{
		DrawGraph(180, 220, m_fist, true);
	}
	//剣だった場合
	if (m_equipmentSword == true)
	{
		DrawGraph(150, 200, m_sword, true);
	}

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//DrawGraph(0, 0, DrawBox(600, 200, 800, 400, 0x000000, true), false);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フォントのサイズ変更
	SetFontSize(100);

	DrawString(100, 30, "装備メニュー", 0xffffff);

	SetFontSize(80);

	DrawString(100, 220, "右\n手", 0xffffff);

	//DrawString(500, 220, "左\n手", 0xffffff);


	//フォントのサイズを戻す
	SetFontSize(40);

	DrawString(100, 800, "Bボタンで戻る", 0xffffff);

}

void Equipment::RightDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, DrawBox(0, 0, 1600, 1600, 0x000000, true), false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(150, m_rightEquipmentSelectY, DrawBox(150, m_rightEquipmentSelectY, 350, m_rightEquipmentSelectY + 200, 0xffff00, true), false);

	DrawGraph(140, 100, m_fist, true);
	DrawGraph(100, 300, m_sword, true);


	//素手装備
	if (m_rightItem[0] == 1)
	{
		DrawString(400, 200, "己が信じれる唯一の武器", 0xffffff);
	}
	//剣装備
	if (m_rightItem[1] == 1)
	{
		DrawString(400, 400, "護身用の武器", 0xffffff);
	}
}

void Equipment::End()
{
}
