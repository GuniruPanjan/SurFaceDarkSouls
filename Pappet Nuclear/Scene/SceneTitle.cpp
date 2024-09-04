#include "SceneTitle.h"
#include "SceneGame.h"

SceneTitle::SceneTitle():
	m_pad(0),
	m_right(0),
	m_start(0),
	m_setting(0),
	m_end(0),
	m_button(0),
	m_one(false),
	m_blend(false),
	m_analog(VGet(0.0f,0.0f,0.0f)),
	m_cameraPos(VGet(0.0f,0.0f,0.0f)),
	m_playerHandle(0),
	m_anim(0),
	m_animation(0),
	m_totalAnimationTime(0.0f),
	m_playTime(0.0f),
	m_pos(VGet(0.0f,0.0f,0.0f))
{
	for (int i = 0; i < 3; i++)
	{
		m_select[i] = 0;
		m_pal[i] = 0;
	}
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_backScene);
	MV1DeleteModel(m_playerHandle);
}

void SceneTitle::Init()
{
	m_backScene = MyLoadGraph("Data/SceneBack/PuppetNuclearTitle.png", 30, 30);
	m_start = MyLoadGraph("Data/UI/STARTButton.png", 30, 30);
	m_setting = MyLoadGraph("Data/UI/SettingButton.png", 30, 30);
	m_end = MyLoadGraph("Data/UI/EndButton.png", 30, 30);
	m_playerHandle = MV1LoadModel("Data/Player/PlayerModel.mv1");
	m_anim = MV1LoadModel("Data/PlayerAnimation/JumpingDown.mv1");

	//アニメーションアタッチ
	m_animation = MV1AttachAnim(m_playerHandle, 1, m_anim, TRUE);

	//時間
	m_totalAnimationTime = MV1GetAttachAnimTotalTime(m_playerHandle, m_animation);

	m_playTime = 0.0f;

	m_pos = VGet()

	m_select[0] = 1;
	m_select[1] = 0;
	m_select[2] = 0;

	for (int i = 0; i < 3; i++)
	{
		m_pal[i] = 255;
	}

	m_cameraPos = VGet(550.0f, 20.0f, -450.0f);
	m_cameraTarget = VGet(485.0f, 80.0f, -550.0f);

	map->Init();

	m_one = false;
	m_blend = false;
}

std::shared_ptr<SceneBase> SceneTitle::Update()
{
	if (m_settingScene == false)
	{
		//パッド入力所得
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

		//上
		if (m_xpad.ThumbLY > 2000)
		{
			m_button++;
		}
		//下
		else if (m_xpad.ThumbLY < 0)
		{
			m_button--;
		}
		else
		{
			//初期化
			m_button = 0;

			m_one = false;
		}

		//DrawFormatString(0, 0, 0xffffff, "m_select0 : %d", m_select[0]);
		//DrawFormatString(0, 20, 0xffffff, "m_select1 : %d", m_select[1]);
		//DrawFormatString(0, 40, 0xffffff, "m_select2 : %d", m_select[2]);

		//上選択時
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

		//下選択時
		if (m_select[0] == 1 && m_button < 0 && m_one == false)
		{
			m_select[1] = 1;
			m_select[0] = 0;

			m_blend = false;

			m_one = true;
		}
		if (m_select[1] == 1 && m_button < 0 && m_one == false)
		{
			m_select[2] = 1;
			m_select[1] = 0;

			m_blend = false;

			m_one = true;
		}
		if (m_select[2] == 1 && m_button < 0 && m_one == false)
		{
			m_select[0] = 1;
			m_select[2] = 0;

			m_blend = false;

			m_one = true;
		}

		//Aボタン押したら
		if (m_xpad.Buttons[12] == 1 && m_select[0] == 1)
		{
			return std::make_shared<SceneGame>();

			map->End();
		}
		//設定シーン
		if (m_xpad.Buttons[12] == 1 && m_select[1] == 1)
		{
			m_settingScene = true;
		}
		//終了
		if (m_xpad.Buttons[12] == 1 && m_select[2] == 1)
		{
			DxLib_End();
		}
	}

	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);

	return shared_from_this();  //自身のポインタを返す
}

void SceneTitle::Draw()
{
	//DrawCube3D(VGet(0.0f, 0.0f, 0.0f), VGet(700.0f, 300.0f, 300.0f), 0xffffff, 0xffffff, TRUE);



	if (m_select[0] == 1)
	{
		if (m_blend == false)
		{
			if (m_pal[0] < 256)
			{
				m_pal[0] += 2;
			}
			else
			{
				m_blend = true;
			}
			
		}
		if (m_blend == true)
		{
			if (m_pal[0] > 125)
			{
				m_pal[0] -= 2;
			}
			else
			{
				m_blend = false;
			}
		}
		

		m_pal[1] = 255;
		m_pal[2] = 255;
	}
	if (m_select[1] == 1)
	{
		if (m_blend == false)
		{
			if (m_pal[1] < 256)
			{
				m_pal[1] += 2;
			}
			else
			{
				m_blend = true;
			}
		}
		if (m_blend == true)
		{
			if (m_pal[1] > 125)
			{
				m_pal[1] -= 2;
			}
			else
			{
				m_blend = false;
			}
		}

		m_pal[0] = 255;
		m_pal[2] = 255;
	}
	if (m_select[2] == 1)
	{
		if (m_blend == false)
		{
			if (m_pal[2] < 256)
			{
				m_pal[2] += 2;
			}
			else
			{
				m_blend = true;
			}
		}
		if (m_blend == true)
		{
			if (m_pal[2] > 125)
			{
				m_pal[2] -= 2;
			}
			else
			{
				m_blend = false;
			}
		}
		

		m_pal[1] = 255;
		m_pal[0] = 255;
	}

	map->Draw();

	DrawGraph(-50, 0, m_backScene, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pal[0]);
	DrawGraph(200, 220, m_start, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pal[1]);
	DrawGraph(200, 280, m_setting, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pal[2]);
	DrawGraph(200, 340, m_end, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	

	//DrawString(240, 300, "Title", 0xffffff);
	
}

void SceneTitle::End()
{
}
