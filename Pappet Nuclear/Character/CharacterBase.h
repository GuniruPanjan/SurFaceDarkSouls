#pragma once
#include "DxLib.h"
#include "Character/Effect/Effect.h"
#include "Col/CapsuleCol.h"
#include "Col/SphereCol.h"
#include<memory>
//だいたいのアニメーション
#define  ANIMATION   30
#define D2R(deg) ((deg)*DX_PI_F/180.0f)
#define PLAYER_MAX_HITCOLL  260    //処理するコリジョンポリゴンの最大数

class Map;   //マップクラス

/// <summary>
/// キャラクターの基底クラス
/// </summary>
class CharacterBase
{
public:
	CharacterBase() :
		m_hp(0.0f),
		m_attack(0.0f),
		m_handle(-1),
		m_modelSize(0.0f),
		m_angle(0.0f),
		m_speed(0.0f),
		m_bounceDis(0.0f),
		m_death(false),
		m_oneInit(false),
		m_posX(0.0f),
		m_posY(0.0f),
		m_posZ(0.0f),
		m_moveflag(false),
		m_moveAttack(false),
		m_moveAttackEnd(true),
		m_damageReceived(false),
		m_attackNumber(0),
		m_playTime(0.0f),
		m_animStand(-1),
		m_animWalk(-1),
		m_animRun(-1),
		m_animRoll(-1),
		m_animHit(-1),
		m_animDeath(-1),
		m_animAttack1(-1),
		m_animAttack2(-1),
		m_animAttack3(-1),
		m_len(0.0f),
		m_capsuleRadius(0.0f),
		m_sphereRadius(0.0f),
		m_move(VGet(0.0f, 0.0f, 0.0f)),
		m_pos(VGet(m_posX, m_posY, m_posZ)),
		m_drawPos(VGet(0.0f, 0.0f, 0.0f)),
		m_prevPos(VGet(0.0f, 0.0f, 0.0f)),
		m_nowPos(VGet(0.0f, 0.0f, 0.0f)),
		m_moveVector(VGet(0.0f, 0.0f, 0.0f)),
		m_mapHitColl(VGet(0.0f,0.0f,0.0f)),
		m_HitFlag(false),
		m_WallNum(0),
		m_FloorNum(0),
		m_HitDimNum(0)
	{
		for (int i = 0; i < ANIMATION; i++)
		{
			m_animation[i] = -1;
			m_totalAnimTime[i] = 0.0f;
		}
	}

	virtual ~CharacterBase(){}

	//virtualで継承先を呼び出す

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void End() = 0;

protected:
	float m_hp;  //キャラのHP
	float m_attack;  //キャラの攻撃力
	int m_handle;  //キャラのモデルハンドル
	float m_modelSize;  //キャラのモデルサイズ
	float m_angle;  //キャラのアングル
	float m_speed;  //キャラのスピード
	float m_bounceDis;    //キャラを押し出す距離
	bool m_death;   //キャラの死亡判定
	bool m_oneInit;     //一回だけ初期化する
	float m_posX;  //キャラのX座標
	float m_posY;  //キャラのY座標
	float m_posZ;  //キャラのZ座標
	bool m_moveflag;  //キャラが動いたか判断するフラグ
	bool m_moveAttack;  //キャラが攻撃したかどうか判断するフラグ
	bool m_moveAttackEnd;  //キャラの攻撃が終了したかどうか判断するフラグ
	bool m_damageReceived;  //キャラがダメージを受けたかどうか判断するフラグ
	int m_attackNumber;   //キャラの攻撃が何段階目か判断する変数
	float m_playTime;  //キャラのアニメーションを進める時間
	int m_animStand;  //キャラの立っているアニメーション格納変数
	int m_animWalk;   //キャラの歩くアニメーション格納変数
	int m_animRun;    //キャラの走るアニメーション格納変数
	int m_animRoll;   //キャラのローディングアニメーション格納変数
	int m_animHit;    //キャラが攻撃を受けた時のアニメーション格納変数
	int m_animDeath;  //キャラが死んだ時のアニメーション格納変数
	int m_animAttack1;   //キャラの攻撃アニメーション格納変数
	int m_animAttack2;   //キャラの攻撃アニメーション格納変数
	int m_animAttack3;   //キャラの攻撃アニメーション格納変数
	int m_animation[ANIMATION];  //キャラのアニメーション格納変数
	float m_totalAnimTime[ANIMATION];  //キャラのアニメーション再生時間
	VECTOR m_move;  //キャラの移動
	VECTOR m_pos;  //キャラのポジション
	VECTOR m_drawPos;   //キャラのモデルを描画するポジション
	VECTOR m_prevPos;  //キャラのアニメーションで移動しているフレームの座標取得
	VECTOR m_nowPos;  //キャラのアニメーション後の座標を取得する
	VECTOR m_moveVector;  //キャラのアニメーションでの座標移動値を入れる

	//当たり判定用のメンバ変数
	Pos3 m_colPos; //当たり判定用のメンバ変数
	Pos3 m_colAttackPos;  //攻撃の当たり判定用のメンバ変数
	Pos3 m_colDeathPos;  //死んだ時初期化するあたり判定用のメンバ変数
	Pos3 m_initializationPos;   //アタックの当たり判定を初期化するポジション
	Vec3 m_vec;  //キャラの当たり判定用のベクターメンバ変数
	Vec3 m_deathVec;  //キャラが死んだ時用のベクターメンバ変数
	float m_len;  //長さ
	float m_capsuleRadius;  //カプセルの半径
	float m_sphereRadius;   //スフィアの半径
	CapsuleCol m_capsuleCol;  //カプセルの当たり判定
	SphereCol m_sphereCol;  //スフィアの当たり判定
	VECTOR m_mapHitColl;    //キャラクターのマップとの当たり判定

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