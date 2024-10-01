#include "Character/Player/Player.h"
#include "Map/Map.h"
#include "WeakEnemy.h"

namespace
{
	int walkTime;
	bool oneInit[ENEMY_NOW];    //初期化一回
	bool hitFlag[ENEMY_NOW];    //マップの当たったフラグ
	bool  attack[ENEMY_NOW];    //敵の攻撃SEを一回流す
	VECTOR mapHitCol[ENEMY_NOW];   //マップとの当たり判定
	VECTOR difPlayer[ENEMY_NOW];           //プレイヤーとの距離
	float difPSize[ENEMY_NOW];            //プレイヤーとの距離
	VECTOR difShield[ENEMY_NOW];           //盾との距離
	float difSSize[ENEMY_NOW];            //盾との距離
	bool a[ENEMY_NOW];  //攻撃を一回だけ与える
}

WeakEnemy::WeakEnemy()
{
	for (int i = 0; i < ENEMY_NOW; i++)
	{
		m_weakEnemyHandle[i] = 0;
		m_weakEnemyHp[i] = 0;
		m_weakEnemyPos[i] = VGet(0.0f, 0.0f, 0.0f);
		m_weakDrawPos[i] = VGet(0.0f, 0.0f, 0.0f);
		m_weakPlayTime[i] = 0.0f;
		m_weakEnemyMove[i] = VGet(0.0f, 0.0f, 0.0f);
		m_outPush[i] = VGet(0.0f, 0.0f, 0.0f);
		m_weakEnemyMoveAttack[i] = false;
		m_weakEnemyAngle[i] = 0.0f;
		m_hitSE[i] = 0;
		m_attackSE[i] = 0;
		m_walkSE[i] = 0;
		m_diedSE[i] = 0;
		oneInit[i] = false;
		hitFlag[i] = false;
		m_bounceX[i] = 0.0f;
		m_bounceZ[i] = 0.0f;
		m_bounceAngle[i] = 0.0f;
		m_playerHit[i] = false;
		m_effectWeakHit[i] = 0;
		m_death[i] = false;
	}
}

WeakEnemy::~WeakEnemy()
{
	//メモリ解放
	for (int i = 0; i < ENEMY_NOW; i++)
	{
		MV1DeleteModel(m_weakEnemyHandle[i]);
	}
}

void WeakEnemy::Init(int max)
{
	//敵のHP初期化
	m_weakEnemyHp[max] = 200.0f;

	//敵の攻撃力初期化
	m_attack = 10.0f;

	//敵のスピード初期化
	m_speed = 0.01f;

	m_weakPlayTime[max] = 0.0f;

	m_posX = 100.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;

	//死亡判定を初期化する
	m_death[max] = false;

	m_weakEnemyPos[0] = VGet(500.0f, m_posY, m_posZ);
	m_weakEnemyPos[1] = VGet(300.0f, m_posY, -500.0f);
	m_weakEnemyPos[2] = VGet(600.0f, m_posY, -400.0f);
	m_weakEnemyPos[3] = VGet(650.0f, m_posY, -200.0f);
	m_weakEnemyPos[4] = VGet(300.0f, m_posY, 100.0f);

	//コア初期化
	m_core = 100;

	m_weakEnemyMoveAttack[max] = false;

	//一回だけ実行
	if (m_oneInit == false)
	{
		se->CharaInit();

		m_oneInit = true;
	}

	//一回だけ実行
	if (oneInit[max] == false)
	{
		//モデル複製
		m_weakEnemyHandle[max] = MV1DuplicateModel(m_handle);

		//アニメーションアタッチ
		m_weakEnemyAnimation[0][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animStand, TRUE);
		m_weakEnemyAnimation[1][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animHit, TRUE);
		m_weakEnemyAnimation[2][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animDeath, TRUE);
		m_weakEnemyAnimation[3][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animWalk, TRUE);
		m_weakEnemyAnimation[4][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animLeftWalking, TRUE);
		m_weakEnemyAnimation[5][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animRightWalking, TRUE);
		m_weakEnemyAnimation[6][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animAttack1, TRUE);

		//総再生時間
		m_weakEnemyTotalAnimationTime[0][max] = MV1GetAttachAnimTotalTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
		m_weakEnemyTotalAnimationTime[1][max] = MV1GetAttachAnimTotalTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[1][max]);
		m_weakEnemyTotalAnimationTime[2][max] = MV1GetAttachAnimTotalTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[2][max]);
		m_weakEnemyTotalAnimationTime[3][max] = MV1GetAttachAnimTotalTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
		m_weakEnemyTotalAnimationTime[4][max] = MV1GetAttachAnimTotalTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
		m_weakEnemyTotalAnimationTime[5][max] = MV1GetAttachAnimTotalTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
		m_weakEnemyTotalAnimationTime[6][max] = MV1GetAttachAnimTotalTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);

		oneInit[max] = true;
	}
	
	for (int i = 0; i < max; i++)
	{
		a[i] = false;
	}

	//アニメーションブレンドの初期化
	for (int i = 0; i < ANIMATION; i++)
	{
		m_weakAnimOne[i][max] = false;
	}


	//サイズ変更
	MV1SetScale(m_weakEnemyHandle[max], VGet(m_modelSize, m_modelSize, m_modelSize));

	//当たり判定
	m_weakColPos[max] = Pos3(m_weakEnemyPos[max].x - 2.0f, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	m_colDeathPos = Pos3(0.0f, -1000.0f, 0.0f);
	m_colSearchPos[max] = Pos3(m_weakEnemyPos[max].x, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	m_colDistancePos[max] = Pos3(m_weakEnemyPos[max].x, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	m_colAttackPos[max] = Pos3(m_weakEnemyPos[max].x - 50.0f, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	m_initializationPos = Pos3(0.0f, -1000.0f, 0.0f);
	m_vec = Vec3(0.0f, m_weakEnemyPos[max].y + 2.0f, 0.0f);
	m_deathVec = Vec3(0.0f, 0.0f, 0.0f);
	m_len = 40.0f;
	m_capsuleRadius = 14.0f;
	m_searchRadius = 120.0f;
	m_distanceRadius = 80.0f;
	m_attackRadius = 18.0f;
	m_weakCapsuleCol[max].Init(m_weakColPos[max], m_vec, m_len, m_capsuleRadius);
	m_colSearch[max].Init(m_colSearchPos[max], m_searchRadius);
	m_colDistance[max].Init(m_colDistancePos[max], m_distanceRadius);
	//m_colAttack[max].Init(m_colAttackPos[max], m_attackRadius);
	m_colAttack[max].Init(Pos3(1000.0f, 1000.0f, 1000.0f), m_attackRadius);

	attack[max] = false;

	walkTime = 0;

	//エネミーが死んだアニメーションだった場合
	//if (m_weakEnemyAnimation[1][max] != -1 || m_weakEnemyAnimation[2][max] != -1 || m_weakEnemyAnimation[3][max] != -1 ||
	//	m_weakEnemyAnimation[4][max] != -1 || m_weakEnemyAnimation[5][max] != -1 || m_weakEnemyAnimation[6][max] != -1)
	//{
	//	//アニメーションデタッチ
	//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[1][max]);
	//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[2][max]);
	//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
	//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
	//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
	//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);

	//	m_weakEnemyAnimation[0][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animStand, TRUE);

	//	m_weakPlayTime[max] = 0.0f;

	//	m_weakEnemyAnimation[1][max] = -1;
	//	m_weakEnemyAnimation[2][max] = -1;
	//	m_weakEnemyAnimation[3][max] = -1;
	//	m_weakEnemyAnimation[4][max] = -1;
	//	m_weakEnemyAnimation[5][max] = -1;
	//	m_weakEnemyAnimation[6][max] = -1;

	//}

	//エネミーが死んだアニメーションだった場合
	if (m_weakAnimOne[1][max] == true || m_weakAnimOne[2][max] == true || m_weakAnimOne[3][max] == true ||
		m_weakAnimOne[4][max] == true || m_weakAnimOne[5][max] == true || m_weakAnimOne[6][max] == true)
	{
		//アニメーションブレンドを0にする
		MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[1][max], 0.0f);
		MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[2][max], 0.0f);
		MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max], 0.0f);
		MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max], 0.0f);
		MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max], 0.0f);
		MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max], 0.0f);

		//アニメーションブレンド
		MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max], 1.0f);

		m_weakPlayTime[max] = 0.0f;

		m_weakAnimOne[1][max] = false;
		m_weakAnimOne[2][max] = false;
		m_weakAnimOne[3][max] = false;
		m_weakAnimOne[4][max] = false;
		m_weakAnimOne[5][max] = false;
		m_weakAnimOne[6][max] = false;

		m_weakAnimOne[0][max] = true;
	}
	
	//ブレンドする
	MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max], 1.0f);

	m_weakAnimOne[0][max] = true;
	
	//ブレンドを0にする
	MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[1][max], 0.0f);
	MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[2][max], 0.0f);
	MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max], 0.0f);
	MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max], 0.0f);
	MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max], 0.0f);
	MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max], 0.0f);


	m_hitSE[max] = se->GetHitSE();
	m_attackSE[max] = se->GetAttackSE();
	m_walkSE[max] = se->GetWalkSE();
	m_diedSE[max] = se->GetDiedSE();

}

void WeakEnemy::Update(Player& player, int max, int volume)
{
	m_oneInit = true;
	
	m_weakColPos[max] = Pos3(m_weakEnemyPos[max].x - 2.0f, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	m_colDistancePos[max] = Pos3(m_weakEnemyPos[max].x, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);

	m_weakPlayTime[max] += 0.5f;

	//押し出すアングルを算出
	m_bounceX[max] = m_weakEnemyPos[max].x - player.GetPosX();
	m_bounceZ[max] = m_weakEnemyPos[max].z - player.GetPosX();

	m_bounceAngle[max] = atan2f(m_bounceX[max], m_bounceZ[max]);

	//プレイヤーとの距離
	difPlayer[max] = VSub(player.GetPos(), m_weakDrawPos[max]);
	//盾との距離
	difShield[max] = VSub(player.GetShieldPos(), m_weakDrawPos[max]);

	difPSize[max] = VSize(difPlayer[max]);
	difSSize[max] = VSize(difShield[max]);

	//索敵で発見された処理&敵が攻撃してない時
	if (m_enemySearchFlag[max] == true && m_weakEnemyMoveAttack[max] == false)
	{
		float X = m_weakEnemyPos[max].x - player.GetPosX();
		float Z = m_weakEnemyPos[max].z - player.GetPosZ();

		//プレイヤーの方を向く
		m_weakEnemyAngle[max] = atan2f(X, Z);

		//法線ベクトル
		m_moveTurning[max] = atan2f(-X, Z);
		m_moveReverseTurning[max] = atan2f(X, -Z);
	}

	//攻撃してないなら
	if (m_weakEnemyMoveAttack[max] == false)
	{
		walkTime++;

		//敵が移動する
		m_weakEnemyPos[max] = VAdd(m_weakEnemyPos[max], m_weakEnemyMove[max]);

		if (walkTime >= 30)
		{
			//PlaySoundMem(m_walkSE[max], DX_PLAYTYPE_BACK, true);

			walkTime = 0;
		}
	}
	else
	{
		walkTime = 0;
	}

	//攻撃判定を正面に持ってくる
	m_colAttackPos[max].x = m_weakEnemyPos[max].x + sinf(m_weakEnemyAngle[max]) * -25.0f;
	m_colAttackPos[max].z = m_weakEnemyPos[max].z - cosf(m_weakEnemyAngle[max]) * 25.0f;

	//敵が死亡したら
	if (m_weakEnemyHp[max] <= 0.0f)
	{
		m_weakCapsuleCol[max].Update(m_colDeathPos, m_deathVec);

		m_colSearch[max].Update(m_colDeathPos);

		m_weakEnemyPos[max] = VGet(0.0f, -10000.0f, 0.0f);

		//一回だけ実行
		if (m_death[max] == false)
		{
			//コアを手に入れる
			m_baseCore = m_baseCore + m_core;

			m_death[max] = true;
		}
	}
	else
	{
		m_weakCapsuleCol[max].Update(m_weakColPos[max], m_vec);

		//とりあえず置いとく
		m_colSearch[max].Update(m_colSearchPos[max]);
		m_colDistance[max].Update(m_colDistancePos[max]);

		//ポジション代入
		m_weakDrawPos[max] = m_weakEnemyPos[max];
	}

	//盾よりプレイヤーの方が距離近かったら
	if (difPSize[max] < difSSize[max])
	{
		m_playerHit[max] = true;
	}
	else
	{
		m_playerHit[max] = false;
	}

	//索敵の当たり判定を正面に持ってくる
	m_colSearchPos[max].x = m_weakEnemyPos[max].x + sinf(m_weakEnemyAngle[max]) * -80.0f;
	m_colSearchPos[max].z = m_weakEnemyPos[max].z - cosf(m_weakEnemyAngle[max]) * 80.0f;

	//マップとの当たり判定
	mapHitCol[max] = VGet(m_weakColPos[max].x, m_weakColPos[max].y, m_weakColPos[max].z);

	Action(player, max);

	Animation(m_weakPlayTime[max], max);

	se->Update(volume);
	//エフェクト更新
	//effect->Update();
}

/// <summary>
/// プレイヤーへの攻撃や間合いの取り方などをまとめる関数
/// </summary>
/// <param name="player"></param>
void WeakEnemy::Action(Player& player, int max)
{

	//敵に発見された場合
	if (m_enemySearchFlag[max] == true)
	{
		//プレイヤーと敵の相対距離を算出
		VECTOR tracking = VSub(player.GetPos(), m_weakEnemyPos[max]);

		//角度を出しプレイヤーの周りを旋回運動させる
		MATRIX mtx = MGetRotY(D2R(m_moveTurning[max]) + DX_PI_F / 2);
		MATRIX mtxR = MGetRotY(D2R(m_moveReverseTurning[max]) - DX_PI_F / 2);

		if (m_enemyWait[max] == false && m_weakEnemyMoveAttack[max] == false)
		{
			m_speed = 0.01f;

			m_weakEnemyMove[max] = VScale(tracking, m_speed);

			//攻撃の当たり判定初期化
			m_colAttack[max].Update(Pos3(1000.0f, -1000.0f, 1000.0f));
		}
		//敵が近くにいた時の処理
		else
		{
			m_weakEnemyMove[max] = VNorm(tracking);

			m_speed = 0.3f;

			m_weakEnemyMove[max] = VScale(m_weakEnemyMove[max], m_speed);

			//ランダムで0が出たら左周り
			if (m_randomAction[max] == 0)
			{
				m_weakEnemyMove[max] = VTransform(m_weakEnemyMove[max], mtx);

				m_weakEnemyMoveAttack[max] = false;
			}
			//ランダムで1が出たら右周り
			if (m_randomAction[max] == 1)
			{
				m_weakEnemyMove[max] = VTransform(m_weakEnemyMove[max], mtxR);

				m_weakEnemyMoveAttack[max] = false;
			}
			//ランダムで2が出たら攻撃
			if (m_randomAction[max] == 2)
			{
				//アニメーションフレーム中に攻撃判定をだす
				if (m_weakPlayTime[max] >= 22 && m_weakPlayTime[max] <= 35 && a[max] == false)
				{
					m_colAttack[max].Update(m_colAttackPos[max]);

					if (attack[max] == false)
					{
						PlaySoundMem(m_attackSE[max], DX_PLAYTYPE_BACK, true);

						attack[max] = true;
					}

					a[max] = true;
				}
				else if (m_weakPlayTime[max] >= 35)
				{
					attack[max] = false;
					a[max] = false;
				}
				else
				{
					m_colAttack[max].Update(m_initializationPos);
				}

				m_weakEnemyMoveAttack[max] = true;
			}
		}

	}
	//敵に発見されてないとき
	else
	{
		//敵が動かないようにする
		m_weakEnemyMove[max] = VGet(0.0f, 0.0f, 0.0f);
	}

	m_randomNextActionTime[max] += 0.1f;

	if (m_randomNextActionTime[max] >= 50.0f)
	{
		m_randomAction[max] = GetRand(2);

		m_randomNextActionTime[max] = 0.0f;
	}

}

void WeakEnemy::Animation(float& time, int max)
{
	//敵がプレイヤーを見つけてないとき
	if (m_enemySearchFlag[max] == false)
	{
		//if (m_weakEnemyAnimation[3][max] != -1 || m_weakEnemyAnimation[4][max] != -1 || m_weakEnemyAnimation[5][max] != -1 ||
		//	m_weakEnemyAnimation[6][max] != -1)
		//{
		//	//アニメーションデタッチ
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);


		//	//アニメーションアタッチ
		//	m_weakEnemyAnimation[0][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animStand, TRUE);

		//	time = 0.0f;

		//	m_weakEnemyAnimation[3][max] = -1;
		//	m_weakEnemyAnimation[4][max] = -1;
		//	m_weakEnemyAnimation[5][max] = -1;
		//	m_weakEnemyAnimation[6][max] = -1;

		//}

		BlendAnimation(time, max, 0, 3);
		BlendAnimation(time, max, 0, 4);
		BlendAnimation(time, max, 0, 5);
		BlendAnimation(time, max, 0, 6);


	}
	//敵がプレイヤーを見つけた時(臨戦態勢)
	if (m_enemySearchFlag[max] == true && m_enemyWait[max] == false && m_weakEnemyMoveAttack[max] == false)
	{
		//if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[4][max] != -1 || m_weakEnemyAnimation[5][max] != -1 ||
		//	m_weakEnemyAnimation[6][max] != -1)
		//{
		//	//アニメーションデタッチ
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);


		//	//アニメーションアタッチ
		//	m_weakEnemyAnimation[3][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animWalk, TRUE);

		//	time = 0.0f;

		//	m_weakEnemyAnimation[0][max] = -1;
		//	m_weakEnemyAnimation[4][max] = -1;
		//	m_weakEnemyAnimation[5][max] = -1;
		//	m_weakEnemyAnimation[6][max] = -1;

		//}

		BlendAnimation(time, max, 3, 0);
		BlendAnimation(time, max, 3, 4);
		BlendAnimation(time, max, 3, 5);
		BlendAnimation(time, max, 3, 6);
	}
	//敵の射程圏内に入ったとき
	//左周り
	if (m_randomAction[max] == 0 && m_enemyWait[max] == true)
	{
		//if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[3][max] != -1 || m_weakEnemyAnimation[5][max] != -1 ||
		//	m_weakEnemyAnimation[6][max] != -1)
		//{
		//	//アニメーションデタッチ
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);

		//	//アニメーションアタッチ
		//	m_weakEnemyAnimation[4][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animLeftWalking, TRUE);

		//	time = 0.0f;

		//	m_weakEnemyAnimation[0][max] = -1;
		//	m_weakEnemyAnimation[3][max] = -1;
		//	m_weakEnemyAnimation[5][max] = -1;
		//	m_weakEnemyAnimation[6][max] = -1;

		//}

		BlendAnimation(time, max, 4, 0);
		BlendAnimation(time, max, 4, 3);
		BlendAnimation(time, max, 4, 5);
		BlendAnimation(time, max, 4, 6);

	}
	//右周り
	if (m_randomAction[max] == 1 && m_enemyWait[max] == true)
	{
		//if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[3][max] != -1 || m_weakEnemyAnimation[4][max] != -1 ||
		//	m_weakEnemyAnimation[6][max] != -1)
		//{
		//	//アニメーションデタッチ
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);

		//	//アニメーションアタッチ
		//	m_weakEnemyAnimation[5][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animRightWalking, TRUE);

		//	time = 0.0f;

		//	m_weakEnemyAnimation[0][max] = -1;
		//	m_weakEnemyAnimation[3][max] = -1;
		//	m_weakEnemyAnimation[4][max] = -1;
		//	m_weakEnemyAnimation[6][max] = -1;

		//}

		BlendAnimation(time, max, 5, 0);
		BlendAnimation(time, max, 5, 3);
		BlendAnimation(time, max, 5, 4);
		BlendAnimation(time, max, 5, 6);

	}
	//攻撃モーション
	if (m_randomAction[max] == 2 && m_enemyWait[max] == true)
	{
		//if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[3][max] != -1 || m_weakEnemyAnimation[4][max] != -1 ||
		//	m_weakEnemyAnimation[5][max] != -1)
		//{
		//	//アニメーションデタッチ
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);

		//	//アニメーションアタッチ
		//	m_weakEnemyAnimation[6][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animAttack1, TRUE);

		//	time = 0.0f;

		//	m_weakEnemyAnimation[0][max] = -1;
		//	m_weakEnemyAnimation[3][max] = -1;
		//	m_weakEnemyAnimation[4][max] = -1;
		//	m_weakEnemyAnimation[5][max] = -1;
		//}

		BlendAnimation(time, max, 6, 0);
		BlendAnimation(time, max, 6, 3);
		BlendAnimation(time, max, 6, 4);
		BlendAnimation(time, max, 6, 5);

	}

	//敵が死んだら死ぬアニメーションを入れる
	if (m_weakEnemyHp[max] <= 0.0f)
	{
		//if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[1][max] != -1 || m_weakEnemyAnimation[3][max] != -1 ||
		//	m_weakEnemyAnimation[4][max] != -1 || m_weakEnemyAnimation[5][max] != -1 || m_weakEnemyAnimation[6][max] != -1)
		//{
		//	//アニメーションデタッチ
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[1][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
		//	MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);

		//	//アニメーションアタッチ
		//	m_weakEnemyAnimation[2][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animDeath, TRUE);

		//	time = 0.0f;

		//	m_weakEnemyAnimation[0][max] = -1;
		//	m_weakEnemyAnimation[1][max] = -1;
		//	m_weakEnemyAnimation[3][max] = -1;
		//	m_weakEnemyAnimation[4][max] = -1;
		//	m_weakEnemyAnimation[5][max] = -1;
		//	m_weakEnemyAnimation[6][max] = -1;

		//}

		BlendAnimation(time, max, 2, 0);
		BlendAnimation(time, max, 2, 1);
		BlendAnimation(time, max, 2, 3);
		BlendAnimation(time, max, 2, 4);
		BlendAnimation(time, max, 2, 5);
		BlendAnimation(time, max, 2, 6);
	}

	//再生時間がアニメーションの総再生時間に達したら再生時間を0に戻す
	//if (time >= m_weakEnemyTotalAnimationTime[0][max] && m_weakEnemyAnimation[0][max] != -1)
	//{
	//	time = 0.0f;
	//}
	if (time >= m_weakEnemyTotalAnimationTime[0][max] && m_weakAnimOne[0][max] == true)
	{
		time = 0.0f;
	}
	//if (time >= m_weakEnemyTotalAnimationTime[2][max] && m_weakEnemyAnimation[2][max] != -1)
	//{
	//	time = 120.0f;
	//}
	if (time >= m_weakEnemyTotalAnimationTime[2][max] && m_weakAnimOne[2][max] == true)
	{
		time = 120.0f;
	}
	//if (time >= m_weakEnemyTotalAnimationTime[3][max] && m_weakEnemyAnimation[3][max] != -1)
	//{
	//	time = 0.0f;
	//}
	if (time >= m_weakEnemyTotalAnimationTime[3][max] && m_weakAnimOne[3][max] == true)
	{
		time = 0.0f;
	}
	//if (time >= m_weakEnemyTotalAnimationTime[4][max] && m_weakEnemyAnimation[4][max] != -1)
	//{
	//	time = 0.0f;
	//}
	if (time >= m_weakEnemyTotalAnimationTime[4][max] && m_weakAnimOne[4][max] == true)
	{
		time = 0.0f;
	}
	//if (time >= m_weakEnemyTotalAnimationTime[5][max] && m_weakEnemyAnimation[5][max] != -1)
	//{
	//	time = 0.0f;
	//}
	if (time >= m_weakEnemyTotalAnimationTime[5][max] && m_weakAnimOne[5][max] == true)
	{
		time = 0.0f;
	}
	//if (time >= m_weakEnemyTotalAnimationTime[6][max] && m_weakEnemyAnimation[6][max] != -1)
	//{
	//	m_weakEnemyMoveAttack[max] = false;

	//	m_randomNextActionTime[max] = 50.0f;

	//	time = 0.0f;
	//}
	if (time >= m_weakEnemyTotalAnimationTime[6][max] && m_weakAnimOne[6][max] == true)
	{
		m_weakEnemyMoveAttack[max] = false;

		m_randomNextActionTime[max] = 50.0f;

		time = 0.0f;
	}

	//再生時間をセットする
	//if (m_weakEnemyAnimation[0][max] != -1)
	//{
	//	MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max], time);
	//}
	if (m_weakAnimOne[0][max] == true)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max], time);
	}
	//if (m_weakEnemyAnimation[2][max] != -1)
	//{
	//	MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[2][max], time);
	//}
	if (m_weakAnimOne[2][max] == true)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[2][max], time);
	}
	//if (m_weakEnemyAnimation[3][max] != -1)
	//{
	//	MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max], time);
	//}
	if (m_weakAnimOne[3][max] == true)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max], time);
	}
	//if (m_weakEnemyAnimation[4][max] != -1)
	//{
	//	MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max], time);
	//}
	if (m_weakAnimOne[4][max] == true)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max], time);
	}
	//if (m_weakEnemyAnimation[5][max] != -1)
	//{
	//	MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max], time);
	//}
	if (m_weakAnimOne[5][max] == true)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max], time);
	}
	//if (m_weakEnemyAnimation[6][max] != -1)
	//{
	//	MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max], time);
	//}
	if (m_weakAnimOne[6][max] == true)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max], time);
	}
}

void WeakEnemy::BlendAnimation(float& time, int max, int blendNumber, int DNumber)
{
	if (m_weakAnimOne[DNumber][max] == true && m_weakAnimOne[blendNumber][max] == false)
	{
		m_weakAnimBlend[max] = 0.0f;

		for (m_weakAnimBlend[max] = 0.0f; m_weakAnimBlend[max] < 1.0f; m_weakAnimBlend[max]++)
		{
			//ブレンドを0にする
			MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[DNumber][max], 1.0f - m_weakAnimBlend[max]);

			//アニメーションブレンド
			MV1SetAttachAnimBlendRate(m_weakEnemyHandle[max], m_weakEnemyAnimation[blendNumber][max], m_weakAnimBlend[max]);
		}

		time = 0.0f;
		m_weakAnimOne[blendNumber][max] = true;
		m_weakAnimOne[DNumber][max] = false;

	}
}

void WeakEnemy::HitMap(Map& map, int max)
{
	int j;

	//プレイヤーの周囲にあるコリジョンのポリゴンを取得する
	HitDim = MV1CollCheck_Sphere(map.GetCollisionMap(), -1, map.GetVectorMapPos(), 1500.0f);

	//検出したプレイヤーの周囲のポリゴン情報を解放する
	MV1CollResultPolyDimTerminate(HitDim);

	for (int w = 0; w < max + 1; w++)
	{
		//検出されたポリゴンが壁ポリゴン(XZ平面に垂直なポリゴン)か床ポリゴン(XZ平面に垂直ではないポリゴン)かを判断する
		for (int i = 0; i < HitDim.HitNum; i++)
		{
			//XZ平面に垂直かどうかはポリゴンの法線のY成分が0に限りなく近いかどうかで判断する
			if (HitDim.Dim[i].Normal.y < 0.000001f && HitDim.Dim[i].Normal.y > -0.0000001f)
			{
				if (HitDim.Dim[i].Position[0].y > m_weakEnemyPos[w].y + 1.0f ||
					HitDim.Dim[i].Position[1].y > m_weakEnemyPos[w].y + 1.0f ||
					HitDim.Dim[i].Position[2].y > m_weakEnemyPos[w].y + 1.0f)
				{
					//ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
					if (m_WallNum < PLAYER_MAX_HITCOLL)
					{
						//ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
						m_Wall[m_WallNum] = &HitDim.Dim[i];

						//壁ポリゴンの数を加算する
						m_WallNum++;
					}
				}
			}
		}

		//壁ポリゴンと当たり判定処理
		if (m_WallNum != 0)
		{
			//壁に当たったかどうかのフラグは初期状態では「当たっていない」にしておく
			hitFlag[w] = false;

			//移動したかどうかで処理を分岐
			if (m_moveflag == true)
			{
				//壁ポリゴンの数だけ繰り返し
				for (int i = 0; i < m_WallNum; i++)
				{
					//i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					m_Poly = m_Wall[i];

					//ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
					if (HitCheck_Capsule_Triangle(mapHitCol[w], VAdd(mapHitCol[w], VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == false) continue;

					//ここにきたらポリゴンとプレイヤーが当たっているということなので、ポリゴンに当たったフラグを立てる
					hitFlag[w] = true;

					//新たな移動座標で壁ポリゴンと当たっていないかどうかを判定する
					for (j = 0; j < m_WallNum; j++)
					{
						//j番目の壁ポリゴンと当たっていないかどうかを判定する
						m_Poly = m_Wall[j];

						//当たっていたらループから抜ける
						if (HitCheck_Capsule_Triangle(mapHitCol[w], VAdd(mapHitCol[w], VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true) break;
					}

					//jがm_WallNumだった場合はどのポリゴンとも当たらなかったということなので
					//壁に当たったフラグを倒したうえでループから抜ける
					if (j == m_WallNum)
					{
						hitFlag[w] = false;
						break;
					}

				}
			}
			else
			{
				//移動していない場合の処理

				//壁ポリゴンの数だけ繰り返し
				for (int i = 0; i < m_WallNum; i++)
				{
					//i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					m_Poly = m_Wall[i];

					//ポリゴンに当たっていたら当たったフラグを立てた上でループから抜ける
					if (HitCheck_Capsule_Triangle(mapHitCol[w], VAdd(mapHitCol[w], VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true)
					{
						hitFlag[w] = true;
						break;
					}

				}
			}

			//壁に当たっていたら壁から押し出す処理を行う
			if (hitFlag[w] == true)
			{
				//壁からの押し出し処理を試みる最大数だけ繰り返す
				for (int i = 0; i < PLAYER_MAX_HITCOLL; i++)
				{
					//壁ポリゴンの数だけ繰り返し
					for (int k = 0; k < m_WallNum; k++)
					{
						//j番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
						m_Poly = m_Wall[k];

						//プレイヤーと当たっているか判定
						if (HitCheck_Capsule_Triangle(mapHitCol[w], VAdd(mapHitCol[w], VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == false) continue;

						//当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
						m_weakEnemyPos[w] = VAdd(m_weakEnemyPos[w], VScale(m_Poly->Normal, 1.0f));

						//移動した上で壁ポリゴンと接触しているかどうかを判定
						for (j = 0; j < m_WallNum; j++)
						{
							//当たっていたらループを抜ける
							m_Poly = m_Wall[j];
							if (HitCheck_Capsule_Triangle(mapHitCol[w], VAdd(mapHitCol[w], VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true) break;

						}

						//すべてのポリゴンと当たっていなかったらループ終了
						if (j == m_WallNum) break;
					}

					//iがm_WallNumではない場合は全部のポリゴンで押し出しを試みる前にすべての壁ポリゴンと接触しなくなったということなのでループから抜ける
					if (i != m_WallNum) break;
				}
			}
		}
	}
}

void WeakEnemy::Draw(int max)
{
	//方向ベクトル
	Vec3 vec = m_vec.GetNormalized() * m_len * 0.5f;

	Pos3 pos1 = m_weakColPos[max] + vec;
	Pos3 pos2 = m_weakColPos[max] - vec;

#if false

	if (m_weakEnemyHp[max] > 0.0f)
	{
		DrawCapsule3D(pos1.GetVector(), pos2.GetVector(), m_capsuleRadius, 16, m_color, 0, false);

		//索敵範囲円の3D描画
		DrawSphere3D(m_colSearchPos[max].GetVector(), m_searchRadius, 16, m_seachColor, m_seachColor, false);

		//一定距離の範囲描画
		DrawSphere3D(m_colDistancePos[max].GetVector(), m_distanceRadius, 16, m_distanceColor, m_distanceColor, false);

		//攻撃判定描画
		DrawSphere3D(m_colAttackPos[max].GetVector(), m_attackRadius, 16, 0xffffff, 0xffffff, false);
	}

	//DrawFormatString(0, 320, 0xffffff, "m_colposX : %f m_colposY : %f m_colposZ : %f", m_colPos.x, m_colPos.y, m_colPos.z);
	//DrawFormatString(0, 220, 0xffffff, "m_EnemyHp : %f", m_hp);
	//DrawFormatString(0, 180, 0xffffff, "m_randomTime : %f", m_randomNextActionTime);
	//DrawFormatString(0, 160, 0xffffff, "m_randomAction : %f", m_randomAction);
	//DrawFormatString(0, 140, 0xffffff, "m_playTime : %f", m_playTime);

	//if (m_enemySearchFlag == true)
	//{
	//	DrawFormatString(0, 250, 0xffffff, "発見された");
	//}

	DrawFormatString(0, 140, 0xffffff, "m_anim0 : %f", m_weakEnemyTotalAnimationTime[0][max]);
	DrawFormatString(0, 200, 0xffffff, "m_anim1 : %f", m_weakEnemyTotalAnimationTime[1][max]);
	DrawFormatString(0, 260, 0xffffff, "m_anim2 : %f", m_weakEnemyTotalAnimationTime[2][max]);
	DrawFormatString(0, 320, 0xffffff, "m_anim3 : %f", m_weakEnemyTotalAnimationTime[3][max]);
	DrawFormatString(0, 380, 0xffffff, "m_anim4 : %f", m_weakEnemyTotalAnimationTime[4][max]);
	DrawFormatString(0, 440, 0xffffff, "m_anim5 : %f", m_weakEnemyTotalAnimationTime[5][max]);
	DrawFormatString(0, 500, 0xffffff, "m_anim6 : %f", m_weakEnemyTotalAnimationTime[6][max]);

#endif

	//DrawFormatString(0, 260, 0xffffff, "m_animblend : %f", m_weakAnimBlend[0]);
	//DrawFormatString(0, 320, 0xffffff, "m_animblend : %f", m_weakAnimBlend[1]);
	//DrawFormatString(0, 380, 0xffffff, "m_animblend : %f", m_weakAnimBlend[2]);
	//DrawFormatString(0, 440, 0xffffff, "m_animblend : %f", m_weakAnimBlend[3]);
	//DrawFormatString(0, 500, 0xffffff, "m_animblend : %f", m_weakAnimBlend[4]);


	//3Dモデルポジション設定
	MV1SetPosition(m_weakEnemyHandle[max], m_weakDrawPos[max]);

	//3Dモデル描画
	MV1DrawModel(m_weakEnemyHandle[max]);

	//3Dモデルの回転地をセットする
	MV1SetRotationXYZ(m_weakEnemyHandle[max], VGet(0.0f, m_weakEnemyAngle[max], 0.0f));

	//攻撃された時のエフェクトのポジション
	SetPosPlayingEffekseer3DEffect(m_effectWeakHit[max], m_weakDrawPos[max].x, m_weakDrawPos[max].y + 40.0f, m_weakDrawPos[max].z);

	//effect->Draw();
}

void WeakEnemy::End(int max)
{
	//メモリ解放
	for (int i = 0; i < ENEMY_NOW; i++)
	{
		MV1DeleteModel(m_weakEnemyHandle[i]);
	}
}

bool WeakEnemy::isSphereHit(const SphereCol& col, float damage, int max, Effect& ef)
{
	bool isHit = m_weakCapsuleCol[max].IsHitSphere(col);

	//ダメージを受けた判定
	if (isHit)
	{
		m_color = 0xffff00;

		//ダメージを一回だけ与える
		if (m_damageReceived == false)
		{
			m_weakEnemyHp[max] = m_weakEnemyHp[max] - damage;

			//m_effectHit[max] = PlayEffekseer3DEffect(effect->GetHitEffect());
			m_effectWeakHit[max] = PlayEffekseer3DEffect(ef.GetHitEffect());

			PlaySoundMem(m_hitSE[max], DX_PLAYTYPE_BACK, true);

			m_damageReceived = true;
		}

	}
	else
	{
		m_damageReceived = false;

		m_color = 0xffffff;
	}

	return isHit;
}

bool WeakEnemy::isSeachHit(const CapsuleCol& col, int max)
{
	bool isHit = m_colSearch[max].IsHitCapsule(col);

	//プレイヤーを見つけた判定
	if (isHit)
	{
		m_seachColor = 0xffff00;

		m_enemySearchFlag[max] = true;
	}
	else
	{
		m_seachColor = 0xffffff;

		m_enemySearchFlag[max] = false;
	}

	return isHit;
}

bool WeakEnemy::isPlayerHit(const CapsuleCol& col,VECTOR& vec, float speed, int max)
{
	bool isHit = m_weakCapsuleCol[max].IsHitCapsule(col);

	MATRIX mts = MGetRotY(D2R(m_bounceAngle[max]));

	//プレイヤーと当たった時
	if (isHit)
	{
		m_outPush[max] = VScale(vec, speed);

		m_outPush[max] = VTransform(m_outPush[max], mts);
	}
	else
	{
		m_outPush[max] = VGet(0.0f, 0.0f, 0.0f);
	}

	return isHit;
}

bool WeakEnemy::isDistanceHit(const CapsuleCol& col, int max)
{
	bool isHit = m_colDistance[max].IsHitCapsule(col);

	//一定範囲内にプレイヤーが入った時
	if (isHit)
	{
		m_distanceColor = 0xffff00;

		m_enemyWait[max] = true;
	}
	else
	{
		m_distanceColor = 0xffffff;

		m_enemyWait[max] = false;
	}

	return isHit;
}
