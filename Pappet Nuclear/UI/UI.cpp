#include "UI.h"
#include "DxLib.h"
#include "Character/Player/Player.h"
#include "Character/Enemy/Enemy.h"
#include "Character/Player/Equipment/Equipment.h"
#include "Character/Player/Item/ItemManager.h"
#include "Map/Map.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
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
	m_enemyBossName(0),
	m_equipmentUI(0),
	m_youDied(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UI::~UI()
{
	//���������
	DeleteGraph(m_youDied);
	DeleteGraph(m_equipmentUI);
}

/// <summary>
/// ����������
/// </summary>
/// <param name="player">�v���C���[�Ăяo��</param>
/// <param name="enemy">�G�l�~�[�Ăяo��</param>
void UI::Init(Player& player, Enemy& enemy)
{
	//�摜�ǂݍ���
	m_equipmentUI = MyLoadGraph("Data/UI/EquipmentUI.png", 2, 2);
	m_youDied = MyLoadGraph("Data/UI/YOUDIEDGraph Mini.png", 1, 1);

	//UI�̃|�W�V�����ݒ�
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

	m_hpCover = player.GetHp() * m_hpExpressionDivide1;    //�v���C���[��HP
	m_staminaCover = player.GetStamina() * m_staminaExpressionDivide1;       //�v���C���[�̃X�^�~�i

	//�{�X�̖��O�ݒ�
	m_enemyBossName = "�匴�̏b";

	//�{�X��HP�|�W�V�����ݒ�
	m_enemyBossHpExpressionDivide1 = 0.392f;
	m_enemyBossHpExpressionDivide2 = 0.39f;
	m_enemyBossHpPosX1 = 300.0f;
	m_enemyBossHpPosX2 = 301.0f;
	m_enemyBossHpPosY1 = 335.0f;
	m_enemyBossHpPosY2 = 336.0f;
	m_enemyBossHpPosY3 = 350.0f;
	m_enemyBossHpPosY4 = 349.0f;

	m_enemyBossHpCover = enemy.GetBossHp();    //�{�X��HP
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="player">�v���C���[�Ăяo��</param>
/// <param name="enemy">�G�l�~�[�Ăяo��</param>
/// <param name="eq">�����Ăяo��</param>
/// <param name="map">�}�b�v�Ăяo��</param>
/// <param name="item">�A�C�e���Ăяo��</param>
void UI::Draw(Player& player, Enemy& enemy, Equipment& eq, Map& map, ItemManager& item)
{
	//�v���C���[��HPUI�̊O�g
	DrawBox(m_hpPosX1, m_hpPosY1, m_hpPosX1 + m_hpCover * 3.0f, m_hpPosY3 * 3.0f, 0xffffff, TRUE);

	//�v���C���[��HPUI
	if (player.GetHp() > 0)
	{
		DrawBox(m_hpPosX2 * 3.0f, m_hpPosY2 * 3.0f, m_hpPosX2 + (player.GetHp() * m_hpExpressionDivide2) * 3.0f, m_hpPosY4 * 3.0f, m_hpColor, TRUE);
	}

	//�v���C���[�̃X�^�~�iUI�̊O�g
	DrawBox(m_staminaPosX1, m_staminaPosY1 * 3.0f, m_staminaCover * 3.0f, m_staminaPosY3 * 3.0f, 0xffffff, TRUE);

	//�v���C���[�̃X�^�~�iUI
	DrawBox(m_staminaPosX2 * 3.0f, m_staminaPosY2 * 3.0f, player.GetStamina() * m_staminaExpressionDivide2 * 3.0f, m_staminaPosY4 * 3.0f, m_staminaColor, TRUE);

	//�A�C�e����UI
	DrawGraph(-70, 600, m_equipmentUI, TRUE);


	//�E����
	//������
	if (eq.GetRightFist() == true)
	{
		DrawGraph(160, 720, m_eqFist, TRUE);
	}
	//������
	if (eq.GetSword() == true)
	{
		DrawGraph(160, 725, m_eqSword, TRUE);
	}
	
	
	//������
	//������
	if (eq.GetLeftFist() == true)
	{
		DrawGraph(25, 720, m_eqFist, TRUE);
	}
	//������
	if (eq.GetShield() == true)
	{
		DrawGraph(25, 720, m_eqShield, TRUE);
	}


	//�񕜃A�C�e����0�ȏゾ��
	if (player.GetRecoveryNumber() > 0)
	{
		DrawGraph(82, 785, m_heelStone, TRUE);

		SetFontSize(60);

		DrawFormatString(140, 840, 0x000000, "%d", player.GetRecoveryNumber());


		//�t�H���g�̃T�C�Y��߂�
		SetFontSize(40);
	}

	//�A�C�e����x�����ł����
	if (map.GetSavePossible() == true)
	{
		DrawFormatString(650, 800, 0x000000, "Y�{�^���ŋx������");
	}
	for (int i = 0; i < ITEM_NUMBER; i++)
	{
		if (map.GetItem(i) == true)
		{
			DrawFormatString(650, 800, 0x000000, "Y�{�^���ŃA�C�e�����Ƃ�");
		}
	}
	


	//BossHP
	if (enemy.GetBattale() == true)
	{
		//�{�X�̖��O
		DrawString(100 * 3.0f, 310 * 2.0f, m_enemyBossName, 0xffffff);

		//�{�X��HPUI�̊O�g
		DrawBox(m_enemyBossHpPosX1, m_enemyBossHpPosY1 * 2.0f, m_enemyBossHpPosX1 + m_enemyBossHpCover, m_enemyBossHpPosY3 * 2.0f, 0xffffff, TRUE);

		//�{�X��HPUI
		if (enemy.GetBossHp() > 0.0f)
		{
			DrawBox(m_enemyBossHpPosX2, m_enemyBossHpPosY2 * 2.0f, m_enemyBossHpPosX2 + enemy.GetBossHp(), m_enemyBossHpPosY4 * 2.0f, m_hpColor, TRUE);
		}
		
	}
}

/// <summary>
/// ���񂾂Ƃ��̕`�揈��
/// </summary>
void UI::DiedDraw()
{
	//���񂾎��ɕ`�悷��
	DrawGraph(-150, 60, m_youDied, true);

}

/// <summary>
/// �I������
/// </summary>
void UI::End()
{
	//���������
	DeleteGraph(m_youDied);
	DeleteGraph(m_equipmentUI);
}