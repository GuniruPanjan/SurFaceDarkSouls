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
		//アイテム所得
		if (m_getItem[i] == true)
		{
			//できてるが列挙型が悪さしてる
			ItemGet(i, 0, s_item.SmallCore);
			ItemGet(i, 1, s_item.MediumCore);
			ItemGet(i, 2, s_item.Rubbish);
			
		}
	}
}

/// <summary>
/// アイテムを所得するときの関数
/// </summary>
/// <param name="array">配列</param>
/// <param name="itemNumber">アイテムの番号</param>
/// <param name="item">アイテム</param>
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
/// アイテムの存在
/// </summary>
/// <param name="max">アイテムの番号</param>
/// <param name="item">アイテムをとったか判断する</param>
/// <returns>アイテムの存在を返す</returns>
bool ItemManager::SetItem(int max, bool item)
{
	return m_item[max] = item;
}

/// <summary>
/// 所得したアイテム
/// </summary>
/// <param name="max">アイテムの番号</param>
/// <param name="item">アイテムを所得したか判断する</param>
/// <returns>所得したアイテムを返す</returns>
bool ItemManager::SetGetItem(int max, bool item)
{
	return m_getItem[max] = item;
}
