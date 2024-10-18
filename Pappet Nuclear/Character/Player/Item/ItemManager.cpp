#include "ItemManager.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
ItemManager::~ItemManager()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void ItemManager::Init()
{
}

/// <summary>
/// 更新処理
/// </summary>
void ItemManager::Update()
{
	for (int i = 0; i < ITEM_NUMBER; i++)
	{
		//アイテム所得
		if (m_getItem[i] == true)
		{
			ItemGet(i, 0, s_item.BlackSword);
			ItemGet(i, 1, s_item.SmallShield);
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
		//一回だけ行う
		if (m_one[array] == false)
		{
			item += 1;

			m_one[array] = true;
		}
		
	}
}

/// <summary>
/// 描画処理
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
/// 終了処理
/// </summary>
void ItemManager::End()
{
}

/// <summary>
/// アイテムの所得可能かの判断
/// </summary>
/// <param name="max">アイテムの番号</param>
/// <param name="item">アイテムが所得できるか判断する</param>
/// <returns>アイテムが所得できるか返す</returns>
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
