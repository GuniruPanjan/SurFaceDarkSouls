#include "UI.h"
#include "DxLib.h"
#include "Character/Player/Player.h"
#include "Character/Enemy/Enemy.h"
#include "Character/Player/Equipment/Equipment.h"

UI::UI():
	m_hpCover(0.0f),
	m_staminaCover(0.0f),
	m_hpExpressionDivide1(0.0f),
	m_hpExpressionDivide2(0.0f),
	m_staminaExpressionDivide1(0.0f),
	m_staminaExpressionDivide2(0.0f),
	m_hpPosX1(0.0f),
	m_hpPosY1(0.0f),
	m_hpPosX2(0.0f),
	m_hpPosY2(0.0f),
	m_hpPosY3(0.0f),
	m_hpPosY4(0.0f),
	m_staminaPosX1(0.0f),
	m_staminaPosY1(0.0f),
	m_staminaPosX2(0.0f),
	m_staminaPosY2(0.0f),
	m_staminaPosY3(0.0f),
	m_staminaPosY4(0.0f),
	m_enemyBossHpCover(0.0f),
	m_enemyBossHpExpressionDivide1(0.0f),
	m_enemyBossHpExpressionDivide2(0.0f),
	m_enemyBossHpPosX1(0.0f),
	m_enemyBossHpPosX2(0.0f),
	m_enemyBossHpPosY1(0.0f),
	m_enemyBossHpPosY2(0.0f),
	m_enemyBossHpPosY3(0.0f),
	m_enemyBossHpPosY4(0.0f),
	m_ItemColumn1X1(0.0f),
	m_ItemColumn1X2(0.0f),
	m_ItemColumn1Y1(0.0f),
	m_ItemColumn1Y2(0.0f),
	m_ItemColumn2X1(0.0f),
	m_ItemColumn2X2(0.0f),
	m_ItemColumn2Y1(0.0f),
	m_ItemColumn2Y2(0.0f),
	m_enemyBossName(0),
	m_equipmentUI(0),
	m_youDied(0)
{
}

UI::~UI()
{
	DeleteGraph(m_youDied);

}

void UI::Init(Player& player, Enemy& enemy)
{
	//m_heelStone = LoadGraph("Data/UI/HeelStoneMini.png");
	//m_fist = LoadGraph("Data/UI/FistUi.png");
	//m_youDied = MyLoadGraph("Data/UI/YOUDIEDGraph.png", 20, 20);

	m_equipmentUI = MyLoadGraph("Data/UI/EquipmentUI.png", 2, 2);
	m_youDied = MyLoadGraph("Data/UI/YOUDIEDGraph Mini.png", 1, 1);

	m_hpExpressionDivide1 = 0.9f;
	m_hpExpressionDivide2 = 0.89f;
	m_staminaExpressionDivide1 = 0.9f;
	m_staminaExpressionDivide2 = 0.89f;
	m_hpPosX1 = 0.0f;
	m_hpPosX2 = 1.0f;
	m_hpPosY1 = 0.0f;
	m_hpPosY2 = 1.0f;
	m_hpPosY3 = 15.0f;
	m_hpPosY4 = 14.0f;
	m_staminaPosX1 = 0.0f;
	m_staminaPosX2 = 1.0f;
	m_staminaPosY1 = 20.0f;
	m_staminaPosY2 = 21.0f;
	m_staminaPosY3 = 35.0f;
	m_staminaPosY4 = 34.0f;

	m_ItemColumn1X1 = 20.0f;
	m_ItemColumn1Y1 = 310.0f;
	m_ItemColumn1X2 = 80.0f;
	m_ItemColumn1Y2 = 380.0f;
	m_ItemColumn2X1 = 20.0f;
	m_ItemColumn2Y1 = 390.0f;
	m_ItemColumn2X2 = 80.0f;
	m_ItemColumn2Y2 = 460.0f;

	m_hpCover = player.GetHp() * m_hpExpressionDivide1;
	m_staminaCover = player.GetStamina() * m_staminaExpressionDivide1;

	m_enemyBossName = "大原の獣";

	m_enemyBossHpExpressionDivide1 = 0.392f;
	m_enemyBossHpExpressionDivide2 = 0.39f;
	m_enemyBossHpPosX1 = 300.0f;
	m_enemyBossHpPosX2 = 301.0f;
	m_enemyBossHpPosY1 = 335.0f;
	m_enemyBossHpPosY2 = 336.0f;
	m_enemyBossHpPosY3 = 350.0f;
	m_enemyBossHpPosY4 = 349.0f;

	//m_enemyBossHpCover = enemy.GetBossHp() * m_enemyBossHpExpressionDivide1;
	m_enemyBossHpCover = enemy.GetBossHp();

}

void UI::Draw(Player& player, Enemy& enemy, Equipment& eq)
{
	//DrawBox(m_hpPosX1, m_hpPosY1, m_hpPosX1 + m_hpCover, m_hpPosY3, 0xffffff, TRUE);
	//DrawBox(m_hpPosX2, m_hpPosY2, m_hpPosX2 + (player.GetHp() * m_hpExpressionDivide2), m_hpPosY4, m_hpColor, TRUE);
	//DrawBox(m_staminaPosX1, m_staminaPosY1, m_staminaCover, m_staminaPosY3, 0xffffff, TRUE);
	//DrawBox(m_staminaPosX2, m_staminaPosY2, player.GetStamina() * m_staminaExpressionDivide2, m_staminaPosY4, m_staminaColor, TRUE);

	DrawBox(m_hpPosX1, m_hpPosY1, m_hpPosX1 + m_hpCover * 3.0f, m_hpPosY3 * 3.0f, 0xffffff, TRUE);
	if (player.GetHp() > 0)
	{
		DrawBox(m_hpPosX2 * 3.0f, m_hpPosY2 * 3.0f, m_hpPosX2 + (player.GetHp() * m_hpExpressionDivide2) * 3.0f, m_hpPosY4 * 3.0f, m_hpColor, TRUE);
	}
	DrawBox(m_staminaPosX1, m_staminaPosY1 * 3.0f, m_staminaCover * 3.0f, m_staminaPosY3 * 3.0f, 0xffffff, TRUE);
	DrawBox(m_staminaPosX2 * 3.0f, m_staminaPosY2 * 3.0f, player.GetStamina() * m_staminaExpressionDivide2 * 3.0f, m_staminaPosY4 * 3.0f, m_staminaColor, TRUE);

	//アイテム欄UI
	//DrawBox(m_ItemColumn1X1, m_ItemColumn1Y1, m_ItemColumn1X2, m_ItemColumn1Y2, 0xffffff, TRUE);
	//DrawBox(m_ItemColumn2X1, m_ItemColumn2Y1, m_ItemColumn2X2, m_ItemColumn2Y2, 0xffffff, TRUE);
	//DrawBox(m_ItemColumn1X1 * 14.1f, m_ItemColumn1Y1 * 2.0f, m_ItemColumn1X2 * 5.2f, m_ItemColumn1Y2 * 2.1f, 0xffffff, TRUE);
	//DrawBox(m_ItemColumn1X1 * 0.0f, m_ItemColumn1Y1 * 2.0f, m_ItemColumn1X2 * 1.6f, m_ItemColumn1Y2 * 2.1f, 0xffffff, TRUE);
	//DrawBox(m_ItemColumn2X1 * 6.5f, m_ItemColumn2Y1 * 1.9f, m_ItemColumn2X2 * 3.5f, m_ItemColumn2Y2 * 2.0f, 0xffffff, TRUE);

	DrawGraph(-70, 600, m_equipmentUI, TRUE);

	//DrawGraph(-3, 305, m_fist, TRUE);


	//右装備
	//拳装備
	if (eq.GetRightFist() == true)
	{
		DrawGraph(160, 720, m_eqFist, TRUE);
	}
	//剣装備
	if (eq.GetSword() == true)
	{
		DrawGraph(160, 725, m_eqSword, TRUE);
	}
	
	
	//左装備
	//拳装備
	if (eq.GetLeftFist() == true)
	{
		DrawGraph(25, 720, m_eqFist, TRUE);
	}
	//盾装備
	if (eq.GetShield() == true)
	{
		DrawGraph(25, 720, m_eqShield, TRUE);
	}


	//回復アイテムが0以上だと
	if (player.GetRecoveryNumber() > 0)
	{
		//DrawGraph(-3, 385, m_heelStone, TRUE);
		DrawGraph(82, 785, m_heelStone, TRUE);


		//DrawFormatString(70, 445, 0x000000, "%d", player.GetRecoveryNumber());

		SetFontSize(60);

		DrawFormatString(140, 840, 0x000000, "%d", player.GetRecoveryNumber());

		//フォントのサイズを戻す
		SetFontSize(40);
	}

	//BossHP
	if (enemy.GetBattale() == true)
	{
		//DrawString(100, 320, m_enemyBossName, 0xffffff);
		//DrawBox(m_enemyBossHpPosX1, m_enemyBossHpPosY1, m_enemyBossHpPosX1 + m_enemyBossHpCover, m_enemyBossHpPosY3, 0xffffff, TRUE);
		//DrawBox(m_enemyBossHpPosX2, m_enemyBossHpPosY2, m_enemyBossHpPosX2 + (enemy.GetBossHp() * m_enemyBossHpExpressionDivide2), m_enemyBossHpPosY4, m_hpColor, TRUE);

		DrawString(100 * 3.0f, 310 * 2.0f, m_enemyBossName, 0xffffff);
		DrawBox(m_enemyBossHpPosX1, m_enemyBossHpPosY1 * 2.0f, m_enemyBossHpPosX1 + m_enemyBossHpCover, m_enemyBossHpPosY3 * 2.0f, 0xffffff, TRUE);

		if (enemy.GetBossHp() > 0.0f)
		{
			DrawBox(m_enemyBossHpPosX2, m_enemyBossHpPosY2 * 2.0f, m_enemyBossHpPosX2 + enemy.GetBossHp(), m_enemyBossHpPosY4 * 2.0f, m_hpColor, TRUE);
		}
		
	}
}

void UI::DiedDraw()
{
	//死んだ時に描画する
	//DrawGraph(-250, 0, m_youDied, true);
	DrawGraph(-150, 60, m_youDied, true);

}

void UI::End()
{
	DeleteGraph(m_youDied);
}

int UI::MyLoadGraph(const char* FileName, int XSize, int YSize)
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
