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
	m_enemyBossName(0)
{
}

UI::~UI()
{
}

void UI::Init(Player& player, Enemy& enemy)
{
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

	m_hpCover = player.GetHp() * m_hpExpressionDivide1;
	m_staminaCover = player.GetStamina() * m_staminaExpressionDivide1;

	m_enemyBossName = "—R‹H";

	m_enemyBossHpExpressionDivide1 = 0.392f;
	m_enemyBossHpExpressionDivide2 = 0.39f;
	m_enemyBossHpPosX1 = 50.0f;
	m_enemyBossHpPosX2 = 51.0f;
	m_enemyBossHpPosY1 = 335.0f;
	m_enemyBossHpPosY2 = 336.0f;
	m_enemyBossHpPosY3 = 350.0f;
	m_enemyBossHpPosY4 = 349.0f;

	m_enemyBossHpCover = enemy.GetBossHp() * m_enemyBossHpExpressionDivide1;
}

void UI::Draw(Player& player, Enemy& enemy)
{
	DrawBox(m_hpPosX1, m_hpPosY1, m_hpPosX1 + m_hpCover, m_hpPosY3, 0xffffff, TRUE);
	DrawBox(m_hpPosX2, m_hpPosY2, m_hpPosX2 + (player.GetHp() * m_hpExpressionDivide2), m_hpPosY4, m_hpColor, TRUE);
	DrawBox(m_staminaPosX1, m_staminaPosY1, m_staminaCover, m_staminaPosY3, 0xffffff, TRUE);
	DrawBox(m_staminaPosX2, m_staminaPosY2, player.GetStamina() * m_staminaExpressionDivide2, m_staminaPosY4, m_staminaColor, TRUE);

	//BossHP
	if (enemy.GetBattale() == true)
	{
		DrawString(100, 320, m_enemyBossName, 0xffffff);
		DrawBox(m_enemyBossHpPosX1, m_enemyBossHpPosY1, m_enemyBossHpPosX1 + m_enemyBossHpCover, m_enemyBossHpPosY3, 0xffffff, TRUE);
		DrawBox(m_enemyBossHpPosX2, m_enemyBossHpPosY2, m_enemyBossHpPosX2 + (enemy.GetBossHp() * m_enemyBossHpExpressionDivide2), m_enemyBossHpPosY4, m_hpColor, TRUE);
	}
}

void UI::End()
{
}
