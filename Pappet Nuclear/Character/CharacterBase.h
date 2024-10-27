#pragma once
#include "DxLib.h"
#include "BGM・SE/SEManager.h"
#include "Col/CapsuleCol.h"
#include "Col/SphereCol.h"
#include "Col/RectCol.h"
#include "Singleton/HandleManager.h"
#include "Effect/Effect.h"
#include "Animation/BlendAnimation.h"
#include "Library/MyLibrary.h"
#include "Object/AttackObject.h"
#include "Object/HitObject.h"
#include <memory>
#include <map>
#include <string>

//だいたいのアニメーション
#define  ANIMATION   30
#define D2R(deg) ((deg)*DX_PI_F/180.0f)
#define PLAYER_MAX_HITCOLL  500    //処理するコリジョンポリゴンの最大数
#define ENEMY_NOW 5  //敵の配列で出す数

class Map;   //マップクラス
class ItemManager;    //アイテムマネージャークラス

/// <summary>
/// キャラクターの基底クラス
/// </summary>
class CharacterBase : public MyLibrary::Collidable
{
public:
	//ステータスの構造体
	struct Status
	{
		float s_hp;       //体力
		float s_stamina;  //スタミナ
		float s_attack;   //攻撃力
		int s_muscle;     //筋力
		int s_skill;      //技量
		float s_defense;  //防御力
		float s_speed;    //速度
		int s_core;       //落とすコア
	};

	//コンストラクタ
	//CharacterBase() :
	//	m_hp(0.0f),
	//	m_attack(0.0f),
	//	m_handle(-1),
	//	m_modelSize(0.0f),
	//	m_angle(0.0f),
	//	m_speed(0.0f),
	//	m_bounceDis(0.0f),
	//	m_death(false),
	//	m_oneInit(false),
	//	m_posX(0.0f),
	//	m_posY(0.0f),
	//	m_posZ(0.0f),
	//	m_moveflag(false),
	//	m_moveAttack(false),
	//	m_moveAttackEnd(true),
	//	m_damageReceived(false),
	//	m_attackNumber(0),
	//	m_playTime(0.0f),
	//	m_animStand(-1),
	//	m_animWalk(-1),
	//	m_animRun(-1),
	//	m_animRoll(-1),
	//	m_animHit(-1),
	//	m_animDeath(-1),
	//	m_animAttack1(-1),
	//	m_animAttack2(-1),
	//	m_animAttack3(-1),
	//	m_len(0.0f),
	//	m_capsuleRadius(0.0f),
	//	m_sphereRadius(0.0f),
	//	m_move(VGet(0.0f, 0.0f, 0.0f)),
	//	m_pos(VGet(m_posX, m_posY, m_posZ)),
	//	m_drawPos(VGet(0.0f, 0.0f, 0.0f)),
	//	m_prevPos(VGet(0.0f, 0.0f, 0.0f)),
	//	m_nowPos(VGet(0.0f, 0.0f, 0.0f)),
	//	m_moveVector(VGet(0.0f, 0.0f, 0.0f)),
	//	m_mapHitColl(VGet(0.0f,0.0f,0.0f)),
	//	m_HitFlag(false),
	//	m_WallNum(0),
	//	m_FloorNum(0),
	//	m_HitDimNum(0),
	//	m_effectActivation(false),
	//	m_playerDif(VGet(0.0f,0.0f,0.0f)),
	//	m_shieldDif(VGet(0.0f,0.0f,0.0f)),
	//	m_animBlend(1.0f),
	//	m_animBlendOne(false),
	//	HitDim(),
	//	m_Wall(),
	//	m_Floor(),
	//	m_Poly()
	//{
	//	for (int i = 0; i < ANIMATION; i++)
	//	{
	//		m_animation[i] = -1;
	//		m_totalAnimTime[i] = 0.0f;
	//		m_animOne[i] = false;
	//	}
	//}

	//コンストラクタ
	CharacterBase(Priority priority, ObjectTag tag);

	//デストラクタ
	virtual ~CharacterBase();

	//virtualで継承先を呼び出す

	//初期化処理
	virtual void Init(){};

	//モデルの中心座標を計算
	virtual void CalculationCenterPos(float modeldefaultSize, float modelSize);

	//ダメージ判定をする当たり判定を作成
	virtual void InitHitBox(float radius, float len, MyLibrary::LibVec3 vec, bool isEnemy);

	//攻撃判定をする当たり判定を作成
	virtual void InitAttackBox(float radius, MyLibrary::LibVec3 pos, bool isEnemy);

	//更新処理
	virtual void Update(){};

	//衝突したとき
	virtual void OnCollideEnter(const std::shared_ptr<Collidable>& col) = 0;

	//描画処理
	virtual void Draw(){};

	//終了処理
	virtual void End(){};

protected:
	//アニメーション更新管理
	bool UpdateAnimation(int attachNo, float time = 0.0f);
	//アニメーション変更管理
	void ChangeAnimation(int animIndex, float changeSpeed = 0.5f);

protected:
	//物理クラスのポインタ
	std::shared_ptr<MyLibrary::Physics> m_pPhysics;
	//モデル座標
	MyLibrary::LibVec3 m_modelPos;
	//モデルの中心座標
	MyLibrary::LibVec3 m_centerPos;
	//当たり判定座標
	MyLibrary::LibVec3 m_collisionPos;
	//攻撃の判定座標
	MyLibrary::LibVec3 m_attackPos;
	//移動ベクトル
	MyLibrary::LibVec3 m_moveVec;
	
	//攻撃の半径
	float m_attackRadius;

	//ステータス
	Status m_status;

	int m_handle;  //キャラのモデルハンドル
	float m_modelSize;  //キャラのモデルサイズ
	float m_angle;  //キャラのアングル
	float m_bounceDis;    //キャラを押し出す距離
	bool m_death;   //キャラの死亡判定
	bool m_isHit;    //攻撃を受けたかどうか判定
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
	float m_animBlend; //キャラのアニメーションブレンド率
	bool m_animBlendOne;   //キャラのアニメーションブレンド率の初期化を一回だけ行う
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
	bool m_animOne[ANIMATION];   //キャラのアニメーションを入れる為の変数
	VECTOR m_move;  //キャラの移動
	VECTOR m_pos;  //キャラのポジション
	VECTOR m_drawPos;   //キャラのモデルを描画するポジション
	VECTOR m_prevPos;  //キャラのアニメーションで移動しているフレームの座標取得
	VECTOR m_nowPos;  //キャラのアニメーション後の座標を取得する
	VECTOR m_moveVector;  //キャラのアニメーションでの座標移動値を入れる

	//アニメーション関係
	std::map<std::string, int> m_animIdx;
	int m_nowAnimIdx;
	int m_nowAnimNo;             //現在のアニメーション
	int m_prevAnimNo;            //変更前のアニメーション
	float m_animBlendRate;       //アニメーションのブレンド率
	float m_animTime;            //アニメーション再生速度
	bool m_isAnimationFinish;    //アニメーションが終わったかどうか

	//エフェクトに関する変数
	bool m_effectActivation;     //エフェクトを発動する

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
	VECTOR m_playerDif;      //プレイヤーとの距離を求める
	VECTOR m_shieldDif;     //盾との距離を求める

	//マップとの当たり判定
	bool m_HitFlag;              //ポリゴンに当たったかどうかを記憶しておくのに使う変数
	int m_WallNum;               //壁ポリゴンと判断されたポリゴンの数
	int m_FloorNum;              //床ポリゴンと判断されたポリゴンの数
	MV1_COLL_RESULT_POLY_DIM HitDim;      //キャラの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
	int m_HitDimNum;        //HitDimの有効な配列要素数
	MV1_COLL_RESULT_POLY* m_Wall[PLAYER_MAX_HITCOLL];     //壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* m_Floor[PLAYER_MAX_HITCOLL];    //床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* m_Poly;  //ポリゴンの構造体にアクセスするためにしようするポインタ

	//スマートポインタ
	std::shared_ptr<SEManager> se = std::make_shared<SEManager>();
	std::shared_ptr<HitObject> phit = std::make_shared<HitObject>();
	std::shared_ptr<AttackObject> pattack = std::make_shared<AttackObject>();
};