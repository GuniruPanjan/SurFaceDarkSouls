#pragma once
#define ITEM_NUMBER 30

/// <summary>
/// アイテムを管理するクラス
/// </summary>
class ItemManager
{
private:
	//アイテムの構造体
	struct Item
	{
		int SmallCore = 0;    //小型のコア
		int MediumCore = 0;   //中型のコア
		int Rubbish = 0;      //ゴミ
		int BlackSword = 0;   //黒い直剣
		int SmallShield = 0;  //小さい盾
	};

public:
	//コンストラクタ
	ItemManager();
	//デストラクタ
	virtual ~ItemManager();

	//初期化処理
	void Init();

	//更新処理
	void Update();

	/// <summary>
	/// アイテムを手に入れる
	/// </summary>
	/// <param name="array">配列</param>
	/// <param name="itemNumber">アイテムナンバー</param>
	/// <param name="item">アイテム</param>
	void ItemGet(int array, int itemNumber, int& item);

	//描画処理
	void Draw();

	//終了処理
	void End();

	//アイテムの存在を返す
	bool GetItem(int max) { return m_item[max]; }
	//とったアイテムを返す
	bool GetSetItem(int max) { return m_getItem[max]; }
	//アイテムの存在を決める
	bool SetItem(int max, bool item);
	//アイテムをとったか判断する
	bool SetGetItem(int max, bool item);


private:
	//アイテムが存在している
	bool m_item[ITEM_NUMBER];
	//プレイヤーがアイテムをとった
	bool m_getItem[ITEM_NUMBER];
	//一回だけ行う
	bool m_one[ITEM_NUMBER];

	//構造体
	Item s_item;
};

