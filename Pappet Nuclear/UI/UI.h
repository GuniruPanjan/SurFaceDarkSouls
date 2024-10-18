#pragma once
#include "UIBase.h"

class Player;
class Enemy;
class Equipment;
class Map;
class ItemManager;

/// <summary>
/// UI�֌W�̃N���X
/// </summary>
class UI : public UIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UI();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UI();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="player">�v���C���[�̌Ăяo��</param>
	/// <param name="enemy">�G�l�~�[�̌Ăяo��</param>
	void Init(Player& player, Enemy& enemy);

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="player">�v���C���[�̌Ăяo��</param>
	/// <param name="enemy">�G�l�~�[�̌Ăяo��</param>
	/// <param name="eq">�����̌Ăяo��</param>
	/// <param name="map">�}�b�v�̌Ăяo��</param>
	/// <param name="item">�A�C�e���̌Ăяo��</param>
	void Draw(Player& player, Enemy& enemy, Equipment& eq, Map& map, ItemManager& item);

	/// <summary>
	/// ���񂾂Ƃ��̕`��
	/// </summary>
	void DiedDraw();

	/// <summary>
	/// �I������
	/// </summary>
	void End();

private:
	unsigned int m_hpColor = 0xff0000;    //HP�J���[
	unsigned int m_staminaColor = 0x00ff00;       //�X�^�~�i�J���[
	//�v���C���[��UI�֌W�ϐ�
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
	int m_equipmentUI;
	int m_youDied;

	//�G��UI�ϐ�
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

