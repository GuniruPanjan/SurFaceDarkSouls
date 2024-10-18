#pragma once
#include "DxLib.h"
#include "Col/RectCol.h"
#include "Col/SphereCol.h"
#include "Character/Player/Item/ItemManager.h"
#include<memory>

class Player;
class Effect;

/// <summary>
/// マップを管理するクラス
/// </summary>
class Map
{
public:
	//コンストラクタ
	Map();
	//デストラクタ
	virtual ~Map();

	//初期化処理
	void Init();
	//更新処理
	void Update();

	/// <summary>
	/// アイテムのポジション設定
	/// </summary>
	/// <param name="number">アイテムのナンバー</param>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="z">Z座標</param>
	void ItemPos(int number, float x, float y, float z);

	//描画処理
	void Draw();

	//終了処理
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

	//マップのコリジョンハンドルを返す
	int GetCollisionMap() { return m_collisionHandle; }

	//マップのボス入り口に入ったか返す
	bool GetRoomEntered() { return m_bossRoomEntered; }

	//マップの休息場所を返す
	bool GetSavePossible() { return m_saveSpot; }

	//現在のアイテムの状態を返す
	bool GetItem(int max) { return item->GetItem(max); }

	//アイテムが取れるか返す
	bool SetItemSpot(int max, bool set) { return m_itemSpot[max] = set; }

	//マップのポジションを返す
	VECTOR GetVectorMapPos() { return m_MapPosition; }

	//マップの休息ポイントを返す
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

