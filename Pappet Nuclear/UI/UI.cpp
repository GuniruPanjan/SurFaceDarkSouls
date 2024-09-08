#include "UI.h"
#include "DxLib.h"
#include "Character/Player/Player.h"
#include "Character/Enemy/Enemy.h"

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
	m_heelStone(0),
	m_fist(0),
	m_enemyBossName(0),
	m_youDied(0)
{
}

UI::~UI()
{
	DeleteGraph(m_heelStone);
}

void UI::Init(Player& player, Enemy& enemy)
{
	//m_heelStone = LoadGraph("Data/UI/HeelStoneMini.png");
	//m_fist = LoadGraph("Data/UI/FistUi.png");
	//m_youDied = MyLoadGraph("Data/UI/YOUDIEDGraph.png", 20, 20);

	m_heelStone = MyLoadGraph("Data/UI/HeelStoneMini.png", 3, 3);
	m_fist = MyLoadGraph("Data/UI/FistUi.png", 3, 3);
	m_youDied = MyLoadGraph("Data/UI/YOUDIEDGraph.png", 10, 10);

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

	m_enemyBossName = "�匴�̏b";

	m_enemyBossHpExpressionDivide1 = 0.392f;
	m_enemyBossHpExpressionDivide2 = 0.39f;
	m_enemyBossHpPosX1 = 100.0f;
	m_enemyBossHpPosX2 = 101.0f;
	m_enemyBossHpPosY1 = 335.0f;
	m_enemyBossHpPosY2 = 336.0f;
	m_enemyBossHpPosY3 = 350.0f;
	m_enemyBossHpPosY4 = 349.0f;

	m_enemyBossHpCover = enemy.GetBossHp() * m_enemyBossHpExpressionDivide1;
}

void UI::Draw(Player& player, Enemy& enemy)
{
	//DrawBox(m_hpPosX1, m_hpPosY1, m_hpPosX1 + m_hpCover, m_hpPosY3, 0xffffff, TRUE);
	//DrawBox(m_hpPosX2, m_hpPosY2, m_hpPosX2 + (player.GetHp() * m_hpExpressionDivide2), m_hpPosY4, m_hpColor, TRUE);
	//DrawBox(m_staminaPosX1, m_staminaPosY1, m_staminaCover, m_staminaPosY3, 0xffffff, TRUE);
	//DrawBox(m_staminaPosX2, m_staminaPosY2, player.GetStamina() * m_staminaExpressionDivide2, m_staminaPosY4, m_staminaColor, TRUE);

	DrawBox(m_hpPosX1, m_hpPosY1, m_hpPosX1 + m_hpCover * 3.0f, m_hpPosY3 * 3.0f, 0xffffff, TRUE);
	DrawBox(m_hpPosX2 * 3.0f, m_hpPosY2 * 3.0f, m_hpPosX2 + (player.GetHp() * m_hpExpressionDivide2) * 3.0f, m_hpPosY4 * 3.0f, m_hpColor, TRUE);
	DrawBox(m_staminaPosX1, m_staminaPosY1 * 3.0f, m_staminaCover * 3.0f, m_staminaPosY3 * 3.0f, 0xffffff, TRUE);
	DrawBox(m_staminaPosX2 * 3.0f, m_staminaPosY2 * 3.0f, player.GetStamina() * m_staminaExpressionDivide2 * 3.0f, m_staminaPosY4 * 3.0f, m_staminaColor, TRUE);

	//�A�C�e����UI
	//DrawBox(m_ItemColumn1X1, m_ItemColumn1Y1, m_ItemColumn1X2, m_ItemColumn1Y2, 0xffffff, TRUE);
	//DrawBox(m_ItemColumn2X1, m_ItemColumn2Y1, m_ItemColumn2X2, m_ItemColumn2Y2, 0xffffff, TRUE);
	DrawBox(m_ItemColumn1X1 * 3.0f, m_ItemColumn1Y1 * 1.5f, m_ItemColumn1X2 * 3.0f, m_ItemColumn1Y2 * 1.8f, 0xffffff, TRUE);
	DrawBox(m_ItemColumn2X1 * 3.0f, m_ItemColumn2Y1 * 1.9f, m_ItemColumn2X2 * 3.0f, m_ItemColumn2Y2 * 2.1f, 0xffffff, TRUE);

	//DrawGraph(-3, 305, m_fist, TRUE);
	DrawGraph(0, 460, m_fist, TRUE);


	//�񕜃A�C�e����0�ȏゾ��
	if (player.GetRecoveryNumber() > 0)
	{
		//DrawGraph(-3, 385, m_heelStone, TRUE);
		DrawGraph(0, 750, m_heelStone, TRUE);


		//DrawFormatString(70, 445, 0x000000, "%d", player.GetRecoveryNumber());

		SetFontSize(60);

		DrawFormatString(70 * 3.0f, 445 * 2.0f, 0x000000, "%d", player.GetRecoveryNumber());

		//�t�H���g�̃T�C�Y��߂�
		SetFontSize(40);
	}

	//BossHP
	if (enemy.GetBattale() == true)
	{
		//DrawString(100, 320, m_enemyBossName, 0xffffff);
		//DrawBox(m_enemyBossHpPosX1, m_enemyBossHpPosY1, m_enemyBossHpPosX1 + m_enemyBossHpCover, m_enemyBossHpPosY3, 0xffffff, TRUE);
		//DrawBox(m_enemyBossHpPosX2, m_enemyBossHpPosY2, m_enemyBossHpPosX2 + (enemy.GetBossHp() * m_enemyBossHpExpressionDivide2), m_enemyBossHpPosY4, m_hpColor, TRUE);

		DrawString(100 * 3.0f, 310 * 2.0f, m_enemyBossName, 0xffffff);
		DrawBox(m_enemyBossHpPosX1 * 3.2f, m_enemyBossHpPosY1 * 2.0f, m_enemyBossHpPosX1 + m_enemyBossHpCover * 3.0f, m_enemyBossHpPosY3 * 2.0f, 0xffffff, TRUE);
		DrawBox(m_enemyBossHpPosX2 * 3.2f, m_enemyBossHpPosY2 * 2.0f, m_enemyBossHpPosX2 + (enemy.GetBossHp() * m_enemyBossHpExpressionDivide2) * 3.0f, m_enemyBossHpPosY4 * 2.0f, m_hpColor, TRUE);
	}
}

void UI::DiedDraw()
{
	//���񂾎��ɕ`�悷��
	//DrawGraph(-250, 0, m_youDied, true);
	DrawGraph(-340, 0, m_youDied, true);

}

void UI::End()
{
}

int UI::MyLoadGraph(const char* FileName, int XSize, int YSize)
{
	int handle = LoadGraph(FileName);  //�摜�̃��[�h
	if (handle != -1)  //�摜�̃��[�h�ɐ��������ꍇ
	{
		int SizeX, SizeY;  //�摜�T�C�Y���i�[���邽�߂̕ϐ���p��

		GetGraphSize(handle, &SizeX, &SizeY);  //���[�h�����摜�̃T�C�Y�擾

		int NowScreen = GetDrawScreen();    //���݂̕`��Ώۉ�ʂ��ꎞ�ۑ�

		SizeX /= XSize;
		SizeY /= YSize;

		int miniHandle = MakeScreen(SizeX, SizeY, TRUE);  //�T�C�Y�ύX��̃O���t�B�b�N�n���h�����쐬
		if (miniHandle == -1)   //�n���h���̍쐬�Ɏ��s�����ꍇ
		{
			DeleteGraph(handle);   //���������[�N���Ȃ��悤�ɁA�{���̃O���t�B�b�N�n���h�����폜
		}
		SetDrawScreen(miniHandle);   //�`��Ώۉ�ʂ��قǍ�����T�C�Y�̃O���t�B�b�N�n���h���ɕύX
		DrawExtendGraph(0, 0, SizeX, SizeY, handle, TRUE);   //���[�h�����摜��`��
		DeleteGraph(handle);   //�s�v�ɂȂ����{���̃T�C�Y�̃O���t�B�b�N�n���h�����폜
		SetDrawScreen(NowScreen);  //���݂̕`��Ώۉ�ʂ����̉�ʂɖ߂�

		return miniHandle;  //�k�߂��摜�̃O���t�B�b�N�n���h����Ԃ�
	}
	else   //�摜�̃��[�h�Ɏ��s�����ꍇ
	{
		return -1;   //�G���[����
	}
}
