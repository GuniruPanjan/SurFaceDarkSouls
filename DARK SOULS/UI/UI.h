#pragma once

class Player;
class Enemy;

class UI
{
public:
	UI();
	virtual ~UI();

	void Init(Player& player, Enemy& enemy);
	void Draw(Player& player, Enemy& enemy);
	void End();

private:
	unsigned int m_hpColor = 0xff0000;
	unsigned int m_staminaColor = 0x00ff00;
	float m_hpCover;
	float m_staminaCover;
	float m_hpExpressionDivide1;
	float m_hpExpressionDivide2;
	float m_staminaExpressionDivide1;
	float m_staminaExpressionDivide2;
	float m_hpPosX1;
	float m_hpPosY1;
	float m_hpPosX2;
	float m_hpPosY2;
	float m_staminaPosX1;
	float m_staminaPosY1;
	float m_staminaPosX2;
	float m_staminaPosY2;
};

