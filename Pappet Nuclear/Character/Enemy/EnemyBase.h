#pragma once
#include "Character/CharacterBase.h"

class Player;

/// <summary>
/// エネミーのベースクラス
/// </summary>
class EnemyBase : public CharacterBase
{

public:
	//コンストラクタ
	EnemyBase();
	//デストラクタ
	virtual ~EnemyBase();

	//virtualで継承先を呼び出す
	//初期化処理
	void Init() {};
	//更新処理
	void Update() {};
	//描画処理
	void Draw() {};
	//終了処理
	virtual void End();

protected:
	bool m_enemySearchFlag[ENEMY_NOW];  //敵の索敵フラグ
	bool m_enemyWait[ENEMY_NOW];    //敵が一定距離を保つフラグ
	bool m_enemyDeath;              //敵が死んだ判定
	int m_randomAction[ENEMY_NOW];    //敵のランダム行動を判断する変数
	int m_animLeftWalking;   //敵の左周りのモーション格納変数
	int m_animRightWalking;   //敵の右周りのモーション格納変数
	int m_weakEnemyAnimation[ANIMATION][ENEMY_NOW];      //敵のアニメーション
	bool m_weakAnimOne[ANIMATION][ENEMY_NOW];            //敵のアニメーションを一回だけ実行
	float m_weakAnimBlend[ENEMY_NOW];                    //敵のアニメーションブレンド率
	int m_core;               //倒したときにもらえるコア
	int m_baseCore;           //コアをまとめる変数
	float m_weakEnemyTotalAnimationTime[ANIMATION][ENEMY_NOW];    //敵のアニメーションの総時間
	float m_searchRadius;  //円の当たり判定
	float m_distanceRadius;  //円の半径
	float m_attackRadius;   //攻撃半径
	float m_moveTurning[ENEMY_NOW];   //時計回りに旋回するための法線ベクトル
	float m_moveReverseTurning[ENEMY_NOW];  //反時計周りに旋回するための法線ベクトル
	float m_randomNextActionTime[ENEMY_NOW];   //次にランダム行動するための時間
	Pos3 m_colSearchPos[ENEMY_NOW];  //索敵範囲の当たり判定
	Pos3 m_colDistancePos[ENEMY_NOW];   //一定距離を保つための判定
	Pos3 m_colAttackPos[ENEMY_NOW];    //攻撃の当たり判定
	SphereCol m_colSearch[ENEMY_NOW];  //スフィア型の当たり判定
	SphereCol m_colDistance[ENEMY_NOW];  //一定距離を保つスフィア型の当たり判定
	SphereCol m_colAttack[ENEMY_NOW];   //攻撃の当たり判定

	//ボスだけの変数
	int m_bossModelHandle;   //ボスのモデルハンドル
	float m_bossSize;        //ボスのモデルサイズ変数
	int m_bossAnimStand;     //ボスの立ちアニメーション格納変数
	int m_bossAnimDeath;     //ボスの死亡アニメーション格納変数
	int m_bossAnimWalk;      //ボスの歩きアニメーション格納変数
	int m_bossAnimTurnRight;      //ボスの回転アニメーション格納変数
	int m_bossAnimTurnLeft;      //ボスの回転アニメーション格納変数
	int m_bossAnimAttack1;   //ボスの攻撃アニメーション格納変数
	int m_bossAnimAttack2;   //ボスの攻撃アニメーション格納変数
	int m_bossAnimAttack3;   //ボスの攻撃アニメーション格納変数
	int m_bossAnimation[ANIMATION];  //ボスのアニメーション格納変数
	float m_bossTotalAnimTime[ANIMATION];  //ボスのアニメーション再生時間
	bool m_bossAnimOne[ANIMATION];      //ボスのアニメーションを一回だけ実行
	SphereCol m_bossColDistance;        //一定距離を保つスフィア型の当たり判定
};

