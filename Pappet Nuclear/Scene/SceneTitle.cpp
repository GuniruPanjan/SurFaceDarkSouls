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
	m_setButton(false),
	m_waitTime(0),
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
	DeleteGraph(m_start);
	DeleteGraph(m_setting);
	DeleteGraph(m_end);
	MV1DeleteModel(m_playerHandle);
	MV1DeleteModel(m_anim);
}

void SceneTitle::Init()
{
	//m_backScene = MyLoadGraph("Data/SceneBack/PuppetNuclearTitle.png", 30, 30);
	//m_start = MyLoadGraph("Data/UI/STARTButton.png", 30, 30);
	//m_setting = MyLoadGraph("Data/UI/SettingButton.png", 30, 30);
	//m_end = MyLoadGraph("Data/UI/EndButton.png", 30, 30);
	m_backScene = MyLoadGraph("Data/SceneBack/PuppetNuclearTitleMini.png", 1, 1);
	m_start = MyLoadGraph("Data/UI/STARTButtonMini.png", 1, 1);
	m_setting = MyLoadGraph("Data/UI/SettingButtonMini.png", 1, 1);
	m_end = MyLoadGraph("Data/UI/EndButtonMini.png", 1, 1);

	m_playerHandle = MV1LoadModel("Data/Player/PlayerModel.mv1");
	m_anim = MV1LoadModel("Data/PlayerAnimation/JumpingDown.mv1");

	//アニメーションアタッチ
	m_animation = MV1AttachAnim(m_playerHandle, 1, m_anim, TRUE);

	//時間
	m_totalAnimationTime = MV1GetAttachAnimTotalTime(m_playerHandle, m_animation);

	m_playTime = 28.0f;

	m_pos = VGet(485.0f, 0.0f, -800.0f);

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

	//設定関係
	setting->Init();
	bgmse->TitleInit();
	bgmse->TitleBGM();
	se->SceneInit();

	m_one = false;
	m_blend = false;
}

std::shared_ptr<SceneBase> SceneTitle::Update()
{
	if (setting->GetSettingScene() == false)
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

		m_playTime += 0.5f;

		//DrawFormatString(0, 0, 0xffffff, "m_select0 : %d", m_select[0]);
		//DrawFormatString(0, 20, 0xffffff, "m_select1 : %d", m_select[1]);
		//DrawFormatString(0, 40, 0xffffff, "m_select2 : %d", m_select[2]);

		//上選択時
		if (m_select[0] == 1 && m_button > 0 && m_one == false)
		{
			m_select[2] = 1;
			m_select[0] = 0;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_blend = false;

			m_one = true;
		}
		if (m_select[1] == 1 && m_button > 0 && m_one == false)
		{
			m_select[0] = 1;
			m_select[1] = 0;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_blend = false;

			m_one = true;
		}
		if (m_select[2] == 1 && m_button > 0 && m_one == false)
		{
			m_select[1] = 1;
			m_select[2] = 0;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_blend = false;

			m_one = true;
		}

		//下選択時
		if (m_select[0] == 1 && m_button < 0 && m_one == false)
		{
			m_select[1] = 1;
			m_select[0] = 0;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_blend = false;

			m_one = true;
		}
		if (m_select[1] == 1 && m_button < 0 && m_one == false)
		{
			m_select[2] = 1;
			m_select[1] = 0;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_blend = false;

			m_one = true;
		}
		if (m_select[2] == 1 && m_button < 0 && m_one == false)
		{
			m_select[0] = 1;
			m_select[2] = 0;

			PlaySoundMem(se->GetSelectSE(), DX_PLAYTYPE_BACK, true);

			m_blend = false;

			m_one = true;
		}

		if (m_waitTime > 10)
		{
			//Aボタン押したら
			if (m_xpad.Buttons[12] == 1 && m_select[0] == 1)
			{
				PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

				return std::make_shared<SceneGame>();

				map->End();
			}
			//設定シーン
			if (m_xpad.Buttons[12] == 1 && m_select[1] == 1)
			{
				PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

				m_setButton = true;

				m_waitTime = 0;

				setting->SetSettingScene(m_setButton);
			}
			//終了
			if (m_xpad.Buttons[12] == 1 && m_select[2] == 1)
			{
				PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

				SetEnd(true);

				//DxLib_End();
			}
		}
		else
		{
			m_waitTime++;
		}

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


	}
	//設定を開く
	if (setting->GetSettingScene() == true)
	{
		setting->Update();
	}

	if (m_playTime >= m_totalAnimationTime && m_animation != -1)
	{
		m_playTime = 80.0f;
	}
	if (m_animation != -1)
	{
		MV1SetAttachAnimTime(m_playerHandle, m_animation, m_playTime);
	}

	bgmse->Update(setting->GetVolume());
	se->Update(setting->GetVolume());

	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);

	return shared_from_this();  //自身のポインタを返す
}

void SceneTitle::Draw()
{
	//DrawCube3D(VGet(0.0f, 0.0f, 0.0f), VGet(700.0f, 300.0f, 300.0f), 0xffffff, 0xffffff, TRUE);

	map->Draw();

	MV1SetPosition(m_playerHandle, m_pos);

	MV1DrawModel(m_playerHandle);

	//3Dモデルの回転地をセットする
	MV1SetRotationXYZ(m_playerHandle, VGet(0.0f, 160.0f, 0.0f));

	//DrawGraph(-50, 0, m_backScene, TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pal[0]);
	//DrawGraph(200, 220, m_start, TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pal[1]);
	//DrawGraph(200, 280, m_setting, TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pal[2]);
	//DrawGraph(200, 340, m_end, TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(120, 0, m_backScene, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pal[0]);
	DrawGraph(500, 350, m_start, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pal[1]);
	DrawGraph(500, 500, m_setting, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pal[2]);
	DrawGraph(500, 650, m_end, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//設定画面を描画
	if (setting->GetSettingScene() == true)
	{
		setting->Draw();
	}

	setting->SettingDraw();

	//DrawString(240, 300, "Title", 0xffffff);
	
}

void SceneTitle::End()
{
	DeleteGraph(m_backScene);
	DeleteGraph(m_start);
	DeleteGraph(m_setting);
	DeleteGraph(m_end);
	MV1DeleteModel(m_playerHandle);
	MV1DeleteModel(m_anim);
	setting->End();
	bgmse->End();
	se->End();
}
