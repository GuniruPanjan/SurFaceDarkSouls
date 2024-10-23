#pragma once
#include "EnemyBase.h"


/// <summary>
/// 雑魚敵を管理するクラス
/// </summary>
class WeakEnemy : public EnemyBase
{
public:
	//コンストラクタ
	WeakEnemy();
	//デストラクタ
	virtual ~WeakEnemy();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="max">敵の最大数</param>
	void Init(int max);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="player">プレイヤー呼び出し</param>
	/// <param name="max">敵の最大数</param>
	/// <param name="volume">音量</param>
	void Update(Player& player, int max, int volume);

	/// <summary>
	/// 敵の行動処理をまとめる
	/// </summary>
	/// <param name="player">プレイヤー呼び出し</param>
	/// <param name="max">敵の最大数</param>
	void Action(Player& player, int max);

	/// <summary>
	/// 敵のアニメーション関連をまとめる
	/// </summary>
	/// <param name="time">アニメーション再生時間</param>
	/// <param name="max">敵の最大数</param>
	void Animation(float& time, int max);

	/// <summary>
	/// 敵のアニメーションをブレンドする関数
	/// </summary>
	/// <param name="time">アニメーション再生時間</param>
	/// <param name="max">敵の最大数</param>
	/// <param name="blendNumber">ブレンドしたいアニメーション格納番号</param>
	/// <param name="DNumber">ブレンドで外したいアニメーション格納番号</param>
	void BlendAnimation(float& time, int max, int blendNumber, int DNumber);

	/// <summary>
	/// マップとの当たり判定
	/// </summary>
	/// <param name="map">マップの呼び出し</param>
	/// <param name="max">敵の最大数</param>
	void HitMap(Map& map, int max);

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="max">敵の最大数</param>
	void Draw(int max);

	/// <summary>
	/// 終了処理
	/// </summary>
	/// <param name="max">敵の最大数</param>
	void End(int max);

	//攻撃の当たり判定
	bool isSphereHit(const SphereCol& col, float damage,int max);
	//索敵範囲の当たり判定
	bool isSeachHit(const CapsuleCol& col,int max);
	//プレイヤーとの当たり判定
	bool isPlayerHit(const CapsuleCol& col,VECTOR& vec, float speed, int max);
	//距離を保つ当たり判定
	bool isDistanceHit(const CapsuleCol& col,int max);

	VECTOR GetPos(int max) { return m_weakEnemyPos[max]; }              //エネミーのポジション所得
	float GetPosX(int max) { return m_weakEnemyPos[max].x; }            //エネミーのポジション所得X座標
	float GetPosY(int max) { return m_weakEnemyPos[max].y; }            //エネミーのポジション所得Y座標
	float GetPosZ(int max) { return m_weakEnemyPos[max].z; }            //エネミーのポジション所得Z座標
	float GetDamage() { return m_status.s_attack; }                     //エネミーの攻撃力所得
	float GetWeakHp(int max) { return m_weakEnemyHp[max]; }             //エネミーのHP所得
	VECTOR GetOutPush(int max) { return m_outPush[max]; }               //プレイヤーを押し出すベクター
	const CapsuleCol GetCol(int max) { return m_weakCapsuleCol[max]; }  //エネミーのカプセル所得
	const SphereCol GetAttackCol(int max) { return m_colAttack[max]; }  //エネミーの球体所得
	bool GetPlayerHit(int max) { return m_playerHit[max]; }             //プレイヤーに攻撃が当たった判定

	//コア所得
	int GetCore() { return m_core; }


private:
	unsigned int m_color = 0xffffff;
	unsigned int m_seachColor = 0xffffff;
	unsigned int m_distanceColor = 0xffffff;

	//配列化するための変数
	int m_weakEnemyHandle[ENEMY_NOW];                    //敵のハンドル
	float m_weakEnemyHp[ENEMY_NOW];                      //敵のHP
	VECTOR m_weakEnemyPos[ENEMY_NOW];                    //敵のポジション
	VECTOR m_weakDrawPos[ENEMY_NOW];                     //敵のDrawポジション
	VECTOR m_weakEnemyMove[ENEMY_NOW];                   //敵の移動ベクトル
	bool m_weakEnemyMoveAttack[ENEMY_NOW];               //敵の攻撃判定
	float m_weakEnemyAngle[ENEMY_NOW];                   //敵のアングル
	Pos3 m_weakColPos[ENEMY_NOW];                        //敵の当たり判定ポジション
	CapsuleCol m_weakCapsuleCol[ENEMY_NOW];              //敵の当たり判定カプセル
	float m_bounceX[ENEMY_NOW];                          //X軸方向算出
	float m_bounceZ[ENEMY_NOW];                          //Z軸方向算出
	float m_bounceAngle[ENEMY_NOW];                      //押し出すアングル
	VECTOR m_outPush[ENEMY_NOW];                         //押し出すベクトル
	bool m_playerHit[ENEMY_NOW];                         //プレイヤーに当たる判定
	bool m_death[ENEMY_NOW];                             //死んだ判定

	//アニメーション関係
	float m_weakPlayTime[ENEMY_NOW];                     //敵のアニメーション時間
	bool m_weakAnimBlendOne[ENEMY_NOW];                       //敵のブレンドを0にする判定

	//SE代入変数
	int m_hitSE[ENEMY_NOW];
	int m_attackSE[ENEMY_NOW];
	int m_walkSE[ENEMY_NOW];
	int m_diedSE[ENEMY_NOW];

	//エフェクト変数
	int m_effectWeakHit[ENEMY_NOW];                          //攻撃が当たった時のエフェクト
};

