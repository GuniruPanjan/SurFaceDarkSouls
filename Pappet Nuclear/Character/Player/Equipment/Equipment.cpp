#include "Equipment.h"

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
Equipment::~Equipment()
{
}

/// <summary>
/// 初期化処理
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
/// 更新処理
/// </summary>
void Equipment::Update()
{
	//パッド入力所得
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

	//左
	if (m_xpad.Buttons[2] == 1)
	{
		m_button++;
	}
	//右
	else if (m_xpad.Buttons[3] == 1)
	{
		m_button--;

	}
	else
	{
		//初期化
		m_button = 0;

		m_one = false;

	}

	//左選択
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
	//右選択
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
		//右の装備変更
		if (m_equipmentSelect[0] == 1)
		{
			m_rightEquipmentBoxColor = 0xffff00;
			m_leftEquipmentBoxColor = 0x000000;

			//Aボタンを押すと
			if (m_xpad.Buttons[12] == 1)
			{
				m_rightEquipmentOpen = true;

				m_waitTime = 0;
			}
		}
		//左の装備変更
		if (m_equipmentSelect[1] == 1)
		{
			m_leftEquipmentBoxColor = 0xffff00;
			m_rightEquipmentBoxColor = 0x000000;

			//Aボタンを押すと
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

/// <summary>
/// 右手装備の更新処理
/// </summary>
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
				m_equipmentRightFist = true;
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
				m_equipmentRightFist = false;
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

/// <summary>
/// 左手装備の更新処理
/// </summary>
void Equipment::LeftUpdate()
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
	//下選択
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
		//素手装備
		if (m_leftItem[0] == 1)
		{
			//Aボタンを押すと
			if (m_xpad.Buttons[12] == 1)
			{
				m_equipmentLeftFist = true;
				m_equipmentShield = false;

				m_leftEquipmentOpen = false;

				m_waitTime = 0;

			}

			m_leftEquipmentSelectY = 100;
		}
		//盾装備
		if (m_leftItem[1] == 1)
		{
			//Aボタンを押すと
			if (m_xpad.Buttons[12] == 1)
			{
				m_equipmentLeftFist = false;
				m_equipmentShield = true;

				m_leftEquipmentOpen = false;

				m_waitTime = 0;
			}

			m_leftEquipmentSelectY = 300;
		}

		//Bボタンを押すと
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
/// 描画処理
/// </summary>
void Equipment::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, DrawBox(0, 0, 1600, 1600, 0x000000, true), false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGraph(0, 0, DrawBox(200, 200, 400, 400, m_rightEquipmentBoxColor, true), false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//拳だった場合
	if (m_equipmentRightFist == true)
	{
		DrawGraph(180, 220, m_fist, true);
	}
	//剣だった場合
	if (m_equipmentSword == true)
	{
		DrawGraph(150, 200, m_sword, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGraph(0, 0, DrawBox(600, 200, 800, 400, m_leftEquipmentBoxColor, true), false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//拳だった場合
	if (m_equipmentLeftFist == true)
	{
		DrawGraph(580, 220, m_fist, true);
	}
	//盾だった場合
	if (m_equipmentShield == true)
	{
		DrawGraph(550, 190, m_shield, true);
	}


	//フォントのサイズ変更
	SetFontSize(100);

	DrawString(100, 30, "装備メニュー", 0xffffff);

	SetFontSize(80);

	DrawString(100, 220, "右\n手", 0xffffff);

	DrawString(500, 220, "左\n手", 0xffffff);


	//フォントのサイズを戻す
	SetFontSize(40);

	DrawString(100, 800, "Bボタンで戻る", 0xffffff);

}

/// <summary>
/// 右手の装備描画処理
/// </summary>
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

/// <summary>
/// 左手の装備描画処理
/// </summary>
void Equipment::LeftDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, DrawBox(0, 0, 1600, 1600, 0x000000, true), false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(150, m_leftEquipmentSelectY, DrawBox(150, m_leftEquipmentSelectY, 350, m_leftEquipmentSelectY + 200, 0xffff00, true), false);

	DrawGraph(140, 100, m_fist, true);
	DrawGraph(100, 300, m_shield, true);


	//素手装備
	if (m_leftItem[0] == 1)
	{
		DrawString(400, 200, "己が信じれる唯一の武器", 0xffffff);
	}
	//盾装備
	if (m_leftItem[1] == 1)
	{
		DrawString(400, 400, "歪な紋様の盾", 0xffffff);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Equipment::End()
{
}
