#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include <cmath>
#include <memory>
#include "Scene/SceneManager.h"
#include "Character/Player/Item/ItemManager.h"
#include "Character/Effect/Effect.h"
#include "Icon/Icon.h"

namespace
{
	constexpr float Width = 720;
	constexpr float Height = 1280;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//名前変更
	SetWindowText("PuppetNuclear");

	//画面の大きさ
	//SetWindowSize(Height, Width);
	// windowモード設定
	SetGraphMode(1600, 1000, 32);
	ChangeWindowMode(false);

	SetWindowIconID(IDI_ICON1);    //アイコンの設定


	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//Effekseerを初期化する
	//引数には画面に表示する最大パーティクル数を設定する
	if (Effekseer_Init(15000) == -1)
	{
		DxLib_End();
		return -1;
	}

	Effekseer_InitDistortion();
	//SetChangeScreenModeGraphicsSystemResetFlag(false);

	//Dxライブラリのデバイスロストしたときのコールバックを設定
	//ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);



	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	//シーンを管理するポインタ
	std::shared_ptr<SceneManager> pScene = std::make_shared<SceneManager>();
	std::shared_ptr<ItemManager> pItem = std::make_shared<ItemManager>();

	pScene->Init();
	pItem->Init();

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		//ゲーム更新
		pScene->Update();
		Effekseer_Sync3DSetting();


		UpdateEffekseer3D();

		//ゲームの描画
		pScene->Draw();

		//裏画面を表画面を入れ替える
		ScreenFlip();


		if (pScene->GetEnd() == true)
		{
			break;
		}

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}
	pScene->End();
	pItem->End();

	Effect::GetInstance().Destroy();

	Effkseer_End();
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}