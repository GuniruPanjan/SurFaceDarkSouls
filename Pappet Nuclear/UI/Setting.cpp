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
	m_volume(false)
{
	for (int i = 0; i < 3; i++)
	{
		m_select[i] = 0;
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
	m_black = LoadGraph("Data/SceneBack/Black.png");
	m_back = MyLoadGraph("Data/SceneBack/Black.png", 13, 13);
	m_white = LoadGraph("Data/SceneBack/White.png");

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


	m_button = 0;
	m_thumb = 0;
	m_one = false;
	m_settingScene = false;
	m_brightness = false;
	m_volume = false;

	m_brightnessColor = 0xffffff;
	m_bgmColor = 0xffffff;
	m_returnColor = 0xffffff;

	m_blackPal = 0;
	m_whitePal = 0;
}

void Setting::Update()
{
	//パッド入力所得
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

	if (m_waitTime > 10)
	{
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
		//右
		else if (m_xpad.ThumbLX > 2000)
		{
			m_thumb++;
		}
		//左
		else if (m_xpad.ThumbLX < 0)
		{
			m_thumb--;
		}
		else
		{
			//初期化
			m_button = 0;
			m_thumb = 0;

			m_one = false;
		}

		//上選択時
		if (m_select[0] == 1 && m_button > 0 && m_one == false &&
			m_brightness == false && m_volume == false)
		{
			m_select[2] = 1;
			m_select[0] = 0;

			m_one = true;
		}
		if (m_select[1] == 1 && m_button > 0 && m_one == false &&
			m_brightness == false && m_volume == false)
		{
			m_select[0] = 1;
			m_select[1] = 0;

			m_one = true;
		}
		if (m_select[2] == 1 && m_button > 0 && m_one == false &&
			m_brightness == false && m_volume == false)
		{
			m_select[1] = 1;
			m_select[2] = 0;

			m_one = true;
		}

		//下選択時
		if (m_select[0] == 1 && m_button < 0 && m_one == false &&
			m_brightness == false && m_volume == false)
		{
			m_select[1] = 1;
			m_select[0] = 0;

			m_one = true;
		}
		if (m_select[1] == 1 && m_button < 0 && m_one == false &&
			m_brightness == false && m_volume == false)
		{
			m_select[2] = 1;
			m_select[1] = 0;

			m_one = true;
		}
		if (m_select[2] == 1 && m_button < 0 && m_one == false &&
			m_brightness == false && m_volume == false)
		{
			m_select[0] = 1;
			m_select[2] = 0;

			m_one = true;
		}

		//右選択(明るさ)
		if (m_brightSelect[0] == 1 && m_thumb > 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[0] = 0;
			m_brightSelect[1] = 1;

			m_one = true;
		}
		if (m_brightSelect[1] == 1 && m_thumb > 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[1] = 0;
			m_brightSelect[2] = 1;

			m_one = true;
		}
		if (m_brightSelect[2] == 1 && m_thumb > 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[2] = 0;
			m_brightSelect[3] = 1;

			m_one = true;
		}
		if (m_brightSelect[3] == 1 && m_thumb > 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[3] = 0;
			m_brightSelect[4] = 1;

			m_one = true;
		}
		if (m_brightSelect[4] == 1 && m_thumb > 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[4] = 0;
			m_brightSelect[0] = 1;

			m_one = true;
		}
		//左選択(明るさ)
		if (m_brightSelect[0] == 1 && m_thumb < 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[0] = 0;
			m_brightSelect[4] = 1;

			m_one = true;
		}
		if (m_brightSelect[1] == 1 && m_thumb < 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[1] = 0;
			m_brightSelect[0] = 1;

			m_one = true;
		}
		if (m_brightSelect[2] == 1 && m_thumb < 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[2] = 0;
			m_brightSelect[1] = 1;

			m_one = true;
		}
		if (m_brightSelect[3] == 1 && m_thumb < 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[3] = 0;
			m_brightSelect[2] = 1;

			m_one = true;
		}
		if (m_brightSelect[4] == 1 && m_thumb < 0 && m_one == false &&
			m_brightness == true && m_volume == false)
		{
			m_brightSelect[4] = 0;
			m_brightSelect[3] = 1;

			m_one = true;
		}
		//Aボタン押したら
		//明るさ設定
		if (m_xpad.Buttons[12] == 1 && m_select[0] == 1 && 
			m_brightness == false && m_volume == false)
		{
			updateBriht[2] = 1;
			m_brightSelect[2] = 1;

			m_brightness = true;
		}
		//音量設定
		if (m_xpad.Buttons[12] == 1 && m_select[1] == 1 &&
			m_brightness == false && m_volume == false)
		{
			updateVolume[2] = 1;
			m_volumeSelect[2] = 1;

			m_volume = true;
		}
		//元の画面に戻る
		if (m_xpad.Buttons[12] == 1 && m_select[2] == 1 &&
			m_brightness == false && m_volume == false)
		{
			m_waitTime = 0;

			m_settingScene = false;
		}
		//明るさ設定を押したら
		if (m_brightness == true)
		{
			//Bボタンを押したら
			if (m_xpad.Buttons[13] == 1)
			{
				m_brightness = false;
			}
		}
		//音量設定を押したら
		if (m_volume == true)
		{
			//Bボタンを押したら
			if (m_xpad.Buttons[13] == 1)
			{
				m_volume = false;
			}
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

	//選択中の色を変える
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

	//フォントのサイズ変更
	SetFontSize(50);

	DrawString(50, 70, "設定", 0xffffff);

	SetFontSize(35);

	DrawString(50, 180, "明るさ", m_brightnessColor);
	DrawString(50, 240, "音量", m_bgmColor);
	DrawString(50, 300, "戻る", m_returnColor);

	DrawBox(200, 180, 240, 220, m_brightColor[0], true);
	DrawBox(280, 180, 320, 220, m_brightColor[1], true);
	DrawBox(360, 180, 400, 220, m_brightColor[2], true);
	DrawBox(440, 180, 480, 220, m_brightColor[3], true);
	DrawBox(520, 180, 560, 220, m_brightColor[4], true);

	DrawBox(200, 240, 240, 280, m_volumeColor[0], true);
	DrawBox(280, 240, 320, 280, m_volumeColor[1], true);
	DrawBox(360, 240, 400, 280, m_volumeColor[2], true);
	DrawBox(440, 240, 480, 280, m_volumeColor[3], true);
	DrawBox(520, 240, 560, 280, m_volumeColor[4], true);

	//フォントのサイズを戻す
	SetFontSize(20);

	DrawFormatString(0, 0, 0xffffff, "m_thumb : %d", m_thumb);
}

void Setting::SettingDraw()
{
	//明るさ
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
	//画面を暗くする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_blackPal);
	DrawGraph(0, 0, m_black, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//画面を明るくする
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
	int handle = LoadGraph(FileName);  //画像のロード
	if (handle != -1)  //画像のロードに成功した場合
	{
		int SizeX, SizeY;  //画像サイズを格納するための変数を用意

		GetGraphSize(handle, &SizeX, &SizeY);  //ロードした画像のサイズ取得

		int NowScreen = GetDrawScreen();    //現在の描画対象画面を一時保存

		SizeX /= XSize;
		SizeY /= YSize;

		int miniHandle = MakeScreen(SizeX, SizeY, TRUE);  //サイズ変更後のグラフィックハンドルを作成
		if (miniHandle == -1)   //ハンドルの作成に失敗した場合
		{
			DeleteGraph(handle);   //メモリリークしないように、本来のグラフィックハンドルを削除
		}
		SetDrawScreen(miniHandle);   //描画対象画面を先ほど作ったサイズのグラフィックハンドルに変更
		DrawExtendGraph(0, 0, SizeX, SizeY, handle, TRUE);   //ロードした画像を描画
		DeleteGraph(handle);   //不要になった本来のサイズのグラフィックハンドルを削除
		SetDrawScreen(NowScreen);  //現在の描画対象画面を元の画面に戻す

		return miniHandle;  //縮めた画像のグラフィックハンドルを返す
	}
	else   //画像のロードに失敗した場合
	{
		return -1;   //エラー発生
	}
}
