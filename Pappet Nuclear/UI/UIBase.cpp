#include "UIBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
UIBase::UIBase()
{
	//画像読み込み
	m_heelStone = MyLoadGraph("Data/UI/HeelStoneMini.png", 6, 6);
	m_fist = MyLoadGraph("Data/UI/FistUi.png", 4, 4);
	m_eqFist = MyLoadGraph("Data/UI/FistUi.png", 7, 7);
	m_sword = MyLoadGraph("Data/UI/SwordUI.png", 3, 3);
	m_eqSword = MyLoadGraph("Data/UI/SwordUI.png", 7, 7);
	m_shield = MyLoadGraph("Data/UI/Shield.png", 3, 3);
	m_eqShield = MyLoadGraph("Data/UI/Shield.png", 7, 7);
}

/// <summary>
/// デストラクタ
/// </summary>
UIBase::~UIBase()
{
	//メモリ解放
	DeleteGraph(m_heelStone);
	DeleteGraph(m_fist);
	DeleteGraph(m_sword);
	DeleteGraph(m_shield);
	DeleteGraph(m_eqFist);
	DeleteGraph(m_eqSword);
	DeleteGraph(m_eqShield);
}

/// <summary>
/// 画像のサイズを変えてロードする関数
/// </summary>
/// <param name="FileName">画像のFileName</param>
/// <param name="XSize">画像の横幅を割る数</param>
/// <param name="YSize">画像の縦幅を割る数</param>
/// <returns>サイズを変えた画像を返す</returns>
int UIBase::MyLoadGraph(const char* FileName, int XSize, int YSize)
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
