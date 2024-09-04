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
		else
		{
			//初期化
			m_button = 0;

			m_one = false;
		}

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

		//Aボタン押したら
		if (m_xpad.Buttons[12] == 1 && m_select[0] == 1)
		{

		}
		//設定シーン
		if (m_xpad.Buttons[12] == 1 && m_select[1] == 1)
		{

		}
		//元の画面に戻る
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

	//フォントのサイズ変更
	SetFontSize(50);

	DrawString(50, 70, "設定", 0xffffff);

	SetFontSize(35);

	DrawString(50, 180, "明るさ", 0xffffff);
	DrawString(50, 240, "音量", 0xffffff);
	DrawString(50, 300, "戻る", 0xffffff);

	//フォントのサイズを戻す
	SetFontSize(20);

	DrawFormatString(0, 0, 0xffffff, "m_select0 : %d", m_select[0]);
	DrawFormatString(0, 20, 0xffffff, "m_select1 : %d", m_select[1]);
	DrawFormatString(0, 40, 0xffffff, "m_select1 : %d", m_select[2]);
}

void Setting::SettingDraw()
{
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
