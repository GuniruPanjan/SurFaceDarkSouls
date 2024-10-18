#include "ItemManager.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ItemManager::ItemManager()
{
	for (int i = 0; i < ITEM_NUMBER; i++)
	{
		m_item[i] = false;
		m_getItem[i] = false;
		m_one[i] = false;
	}

	s_item.SmallCore = 0;
	s_item.MediumCore = 0;
	s_item.Rubbish = 0;
	s_item.BlackSword = 0;
	s_item.SmallShield = 0;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ItemManager::~ItemManager()
{
}

/// <summary>
/// ����������
/// </summary>
void ItemManager::Init()
{
}

/// <summary>
/// �X�V����
/// </summary>
void ItemManager::Update()
{
	for (int i = 0; i < ITEM_NUMBER; i++)
	{
		//�A�C�e������
		if (m_getItem[i] == true)
		{
			ItemGet(i, 0, s_item.BlackSword);
			ItemGet(i, 1, s_item.SmallShield);
			ItemGet(i, 2, s_item.Rubbish);
			
		}
	}
}

/// <summary>
/// �A�C�e������������Ƃ��̊֐�
/// </summary>
/// <param name="array">�z��</param>
/// <param name="itemNumber">�A�C�e���̔ԍ�</param>
/// <param name="item">�A�C�e��</param>
void ItemManager::ItemGet(int array, int itemNumber, int& item)
{
	if (array == itemNumber)
	{
		//��񂾂��s��
		if (m_one[array] == false)
		{
			item += 1;

			m_one[array] = true;
		}
		
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void ItemManager::Draw()
{
#if false
	DrawFormatString(100, 200, 0xffffff, "1 : %d", s_item.SmallCore);
	DrawFormatString(100, 260, 0xffffff, "2 : %d", s_item.MediumCore);
	DrawFormatString(100, 320, 0xffffff, "3 : %d", s_item.Rubbish);
	DrawFormatString(100, 380, 0xffffff, "4 : %d", s_item.BlackSword);
	DrawFormatString(100, 440, 0xffffff, "5 : %d", s_item.SmallShield);
#endif
}

/// <summary>
/// �I������
/// </summary>
void ItemManager::End()
{
}

/// <summary>
/// �A�C�e���̏����\���̔��f
/// </summary>
/// <param name="max">�A�C�e���̔ԍ�</param>
/// <param name="item">�A�C�e���������ł��邩���f����</param>
/// <returns>�A�C�e���������ł��邩�Ԃ�</returns>
bool ItemManager::SetItem(int max, bool item)
{
	return m_item[max] = item;
}

/// <summary>
/// ���������A�C�e��
/// </summary>
/// <param name="max">�A�C�e���̔ԍ�</param>
/// <param name="item">�A�C�e�����������������f����</param>
/// <returns>���������A�C�e����Ԃ�</returns>
bool ItemManager::SetGetItem(int max, bool item)
{
	return m_getItem[max] = item;
}
