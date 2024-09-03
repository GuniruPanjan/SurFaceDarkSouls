#pragma once
#include "DxLib.h"
#include "Col/RectCol.h"
#include "Col/SphereCol.h"

class Player;

class Map
{
public:
	Map();
	virtual ~Map();

	void Init();
	void Update(Player& player);
	void Draw();
	void End();

	bool CapsuleIsHit(const CapsuleCol& col);
	bool CapsuleSaveHit(const CapsuleCol& col);

	int GetCollisionMap() { return m_collisionHandle; }
	bool GetRoomEntered() { return m_bossRoomEntered; }
	bool GetSavePossible() { return m_saveSpot; }
	VECTOR GetVectorMapPos() { return m_MapPosition; }

private:
	int m_handle;   //マップのデータを入れる変数
	int m_collisionHandle;   //マップのコリジョンのデータを入れる変数
	int m_right;    //ライトを作る変数
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
	VECTOR m_MapPosition;   //マップのポジション
	VECTOR m_collisionMapPosition;   //コリジョンのポジション設定

	//Colの当たり判定
	float m_sphereRadius;
	Pos3 m_rectPos;
	Pos3 m_spherePos;
	Size m_rectSize;
	RectCol m_rectCol;
	SphereCol m_sphereCol;
	unsigned int m_color = 0xffffff;
	unsigned int m_sphereColor = 0xffffff;
};

