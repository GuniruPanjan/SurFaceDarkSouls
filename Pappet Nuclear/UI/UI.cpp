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
	m_staminaPosX1(0.0f),
	m_staminaPosY1(0.0f),
	m_staminaPosX2(0.0f),
	m_staminaPosY2(0.0f)
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
	m_hpPosY1 = 15.0f;
	m_hpPosY2 = 14.0f;
	m_staminaPosX1 = 35.0f;
	m_staminaPosX2 = 34.0f;

	m_hpCover = player.GetHp() * m_hpExpressionDivide1;
	m_staminaCover = player.GetStamina() * m_staminaExpressionDivide1;

}

void UI::Draw(Player& player, Enemy& enemy)
{
	DrawBox(0.0f, 0.0f, m_hpCover, m_hpPosY1, 0xffffff, TRUE);
	DrawBox(1.0f, 1.0f, player.GetHp() * m_hpExpressionDivide2, m_hpPosY2, m_hpColor, TRUE);
	DrawBox(0.0f, 20.0f, m_staminaCover, m_staminaPosX1, 0xffffff, TRUE);
	DrawBox(1.0f, 21.0f, player.GetStamina() * m_staminaExpressionDivide2, m_staminaPosX2, m_staminaColor, TRUE);


}

void UI::End()
{
}
