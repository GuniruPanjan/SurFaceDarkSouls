#include "ItemManager.h"
#include "DxLib.h"

ItemManager::ItemManager()
{
	for (int i = 0; i < ITEM_NUMBER; i++)
	{
		m_item[i] = false;
		m_getItem[i] = false;
	}

	s_item.SmallCore = 0;
	s_item.MediumCore = 0;
	s_item.Rubbish = 0;
}

ItemManager::~ItemManager()
{
}

void ItemManager::Init()
{
}

void ItemManager::Update()
{
	for (int i = 0; i < ITEM_NUMBER; i++)
	{
		//�A�C�e������
		if (m_getItem[i] == true)
		{
			//�ł��Ă邪�񋓌^���������Ă�
			ItemGet(i, 0, s_item.SmallCore);
			ItemGet(i, 1, s_item.MediumCore);
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
		item += 1;

		m_item[array] = true;
		m_getItem[itemNumber] = false;
	}
}

void ItemManager::Draw()
{
	DrawFormatString(100, 200, 0xffffff, "1 : %d", s_item.SmallCore);
	DrawFormatString(100, 260, 0xffffff, "2 : %d", s_item.MediumCore);
	DrawFormatString(100, 320, 0xffffff, "3 : %d", s_item.Rubbish);
	DrawFormatString(100, 380, 0xffffff, "%d : bool = %d", 0, m_getItem[0]);
}

void ItemManager::End()
{
}

/// <summary>
/// �A�C�e���̑���
/// </summary>
/// <param name="max">�A�C�e���̔ԍ�</param>
/// <param name="item">�A�C�e�����Ƃ��������f����</param>
/// <returns>�A�C�e���̑��݂�Ԃ�</returns>
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
