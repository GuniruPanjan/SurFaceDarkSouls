#pragma once
#include "DxLib.h"
#include "Col/RectCol.h"
#include "Col/SphereCol.h"
#include "Character/Player/Item/ItemManager.h"
#include<memory>

class Player;
class Effect;

class Map
{
public:
	Map();
	virtual ~Map();

	void Init();
	void Update();
	void ItemPos(int number, float x, float y, float z);
	void Draw();
	void End();

	/// <summary>
	/// キャラクターとの当たり判定
	/// </summary>
	/// <param name="col">プレイヤーのカプセル</param>
	/// <returns></returns>
	bool CapsuleIsHit(const CapsuleCol& col);

	/// <summary>
	/// プレイヤーの休息判定
	/// </summary>
	/// <param name="col">プレイヤーのカプセル</param>
	/// <returns></returns>
	bool CapsuleSaveHit(const CapsuleCol& col);

	/// <summary>
	/// アイテムの当たり判定
	/// </summary>
	/// <param name="col">プレイヤーとの当たり判定</param>
	/// <param name="max">アイテムの配列</param>
	/// <returns></returns>
	bool CapsuleItemHit(const CapsuleCol& col, int max);

	int GetCollisionMap() { return m_collisionHandle; }
	bool GetRoomEntered() { return m_bossRoomEntered; }
	bool GetSavePossible() { return m_saveSpot; }
	bool GetItem(int max) { return item->GetItem(max); }
	bool SetItemSpot(int max, bool set) { return m_itemSpot[max] = set; }
	bool SetGetItem(int max, bool get) { return item->SetGetItem(max, get); }
	VECTOR GetVectorMapPos() { return m_MapPosition; }
	VECTOR GetRestPos() { return m_restPos; }

private:
	int m_handle;   //マップのデータを入れる変数
	int m_collisionHandle;   //マップのコリジョンのデータを入れる変数
	int m_light;    //ライトを作る変数
	int m_itemModel[ITEM_NUMBER];         //マップに置くアイテムのモデル変数
	float m_size;   //モデルのサイズ変数
	float m_Xposition;    //Xポジション
	float m_Yposition;    //Yポジション
	float m_Zposition;    //Zポジション
	float m_XCollisionposition;    //Xポジション
	float m_YCollisionposition;    //Yポジション
	float m_ZCollisionposition;    //Zポジション
	bool m_bossRoomEntered;    //ボス部屋に入った判定
	bool m_saveSpot;        //回復スポットを使える判定
	bool m_oneInit;         //一回だけ初期化する
	bool m_itemSpot[ITEM_NUMBER];        //アイテムを所得できる場所
	VECTOR m_MapPosition;   //マップのポジション
	VECTOR m_collisionMapPosition;   //コリジョンのポジション設定
	VECTOR m_restPos;        //休息するポジション


	//Colの当たり判定
	float m_sphereRadius;
	float m_itemRadius;
	Pos3 m_rectPos;
	Pos3 m_spherePos;
	Pos3 m_itemPos[ITEM_NUMBER];
	Size m_rectSize;
	RectCol m_rectCol;
	SphereCol m_sphereCol;
	SphereCol m_itemCol[ITEM_NUMBER];
	unsigned int m_color = 0xffffff;
	unsigned int m_sphereColor = 0xffffff;
	unsigned int m_itemColor[ITEM_NUMBER];

	//スマートポインタ
	std::shared_ptr<ItemManager> item = std::make_shared<ItemManager>();
};

