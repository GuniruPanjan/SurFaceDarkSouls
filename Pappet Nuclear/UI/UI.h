#pragma once
#include "UIManager.h"

class Player;
class Enemy;
class Equipment;

class UI : public UIManager
{
public:
	UI();
	virtual ~UI();

	void Init(Player& player, Enemy& enemy);
	void Draw(Player& player, Enemy& enemy, Equipment& eq);
	void DiedDraw();
	void End();

	int MyLoadGraph(const char* FileName, int XSize, int YSize);

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
	float m_hpPosY3;
	float m_hpPosY4;
	float m_staminaPosX1;
	float m_staminaPosY1;
	float m_staminaPosX2;
	float m_staminaPosY2;
	float m_staminaPosY3;
	float m_staminaPosY4;
	float m_ItemColumn1X1;
	float m_ItemColumn1X2;
	float m_ItemColumn1Y1;
	float m_ItemColumn1Y2;
	float m_ItemColumn2X1;
	float m_ItemColumn2X2;
	float m_ItemColumn2Y1;
	float m_ItemColumn2Y2;
	int m_equipmentUI;
	int m_youDied;

	//ìGÇÃUIïœêî
	float m_enemyBossHpCover;
	float m_enemyBossHpExpressionDivide1;
	float m_enemyBossHpExpressionDivide2;
	float m_enemyBossHpPosX1;
	float m_enemyBossHpPosY1;
	float m_enemyBossHpPosX2;
	float m_enemyBossHpPosY2;
	float m_enemyBossHpPosY3;
	float m_enemyBossHpPosY4;
	const char *m_enemyBossName;
};

