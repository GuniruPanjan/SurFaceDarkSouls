#pragma once
#define ITEM_NUMBER 30

/// <summary>
/// アイテムの構造体
/// </summary>
struct Item
{
	int SmallCore = 0;    //小型のコア
	int MediumCore = 0;   //中型のコア
	int Rubbish = 0;      //ゴミ
};


class ItemManager
{
public:
	ItemManager();
	virtual ~ItemManager();

	void Init();
	void Update();
	void ItemGet(int array, int itemNumber, int& item);
	void Draw();
	void End();

	bool GetItem(int max) { return m_item[max]; }
	bool SetItem(int max, bool item);
	bool SetGetItem(int max, bool item);


private:
	//アイテムが存在している
	bool m_item[ITEM_NUMBER];
	//プレイヤーがアイテムをとった
	bool m_getItem[ITEM_NUMBER];

	//構造体
	Item s_item;
};

