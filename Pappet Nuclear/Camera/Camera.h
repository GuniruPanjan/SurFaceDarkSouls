#pragma once
#include "Character/Player/Player.h"
#include "Character/Enemy/Enemy.h"
#include <cmath>

class Map;

/// <summary>
/// カメラを管理するクラス
/// </summary>
class Camera
{
public:
	//コンストラクタ
	Camera();
	//デストラクタ
	virtual ~Camera();

	//初期化処理
	void Init();
	//更新処理
	void Update(Player& player);
	//ロックオン処理
	void LockUpdate(Player& player, Enemy& enemy, int max);
	//雑魚敵のロックオン処理
	void WeakLockUpdate(Player& player, Enemy& enemy, int weak);
	//カメラのマップ当たり判定
	void HitObj(Map& map);
	//描画処理
	void Draw();
	//終了処理
	void End();

	float GetAngleX() { return m_cameraAngle.x; }       //カメラのアングル取得X座標
	float GetAngleY() { return m_cameraAngle.y; }       //カメラのアングル取得Y座標
	float GetAngleZ() { return m_cameraAngle.z; }       //カメラのアングル取得Z座標
	VECTOR GetAngle() { return m_cameraAngle; }         //カメラのアングル所得

private:
	DINPUT_JOYSTATE input;

	//カメラのポジション
	VECTOR m_cameraPos = VGet(0.0f, 0.0f, 0.0f);

	//カメラのターゲット
	VECTOR m_cameraTarget = VGet(0.0f, 0.0f, 0.0f);

	//カメラのアングル
	VECTOR m_cameraAngle = VGet(0.0f, 0.0f, 0.0f);

	float m_x, m_z;
	float m_radius;

	//マップとの当たり判定
	bool m_HitFlag;              //ポリゴンに当たったかどうかを記憶しておくのに使う変数
	int m_WallNum;               //壁ポリゴンと判断されたポリゴンの数
	int m_FloorNum;              //床ポリゴンと判断されたポリゴンの数
	MV1_COLL_RESULT_POLY_DIM HitDim;      //キャラの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
	int m_HitDimNum;        //HitDimの有効な配列要素数
	MV1_COLL_RESULT_POLY* m_Wall[PLAYER_MAX_HITCOLL];     //壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* m_Floor[PLAYER_MAX_HITCOLL];    //床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* m_Poly;  //ポリゴンの構造体にアクセスするためにしようするポインタ
};

