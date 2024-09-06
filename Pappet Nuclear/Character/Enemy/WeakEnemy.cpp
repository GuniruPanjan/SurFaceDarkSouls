#include "Character/Player/Player.h"
#include "WeakEnemy.h"

WeakEnemy::WeakEnemy()
{
	for (int i = 0; i < ENEMY_NOW; i++)
	{
		m_weakEnemyHp[i] = 0;
		m_weakEnemyPos[i] = VGet(0.0f, 0.0f, 0.0f);
		m_weakPlayTime[i] = 0.0f;
		m_weakEnemyMove[i] = VGet(0.0f, 0.0f, 0.0f);
		m_weakEnemyMoveAttack[i] = false;
		m_weakEnemyAngle[i] = 0.0f;
	}
}

WeakEnemy::~WeakEnemy()
{
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

	m_weakEnemyPos[0] = VGet(500.0f, m_posY, m_posZ);
	m_weakEnemyPos[1] = VGet(300.0f, m_posY, -500.0f);
	m_weakEnemyPos[2] = VGet(700.0f, m_posY, -400.0f);
	m_weakEnemyPos[3] = VGet(650.0f, m_posY, -200.0f);
	m_weakEnemyPos[4] = VGet(300.0f, m_posY, 100.0f);


	m_weakEnemyMoveAttack[max] = false;

	//一回だけ実行
	if (m_oneInit == false)
	{
		//モデル複製
		m_weakEnemyHandle[max] = MV1DuplicateModel(m_handle);
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
	m_colAttack[max].Init(m_colAttackPos[max], m_attackRadius);


	//アニメーションアタッチ
	m_weakEnemyAnimation[0][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animStand, TRUE);

	//エネミーが死んだアニメーションだった場合
	if (m_weakEnemyAnimation[2][max] != -1)
	{
		//アニメーションデタッチ
		MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[2][max]);

		m_weakPlayTime[max] = 0.0f;

		m_weakEnemyAnimation[2][max] = -1;
	}
	

}

void WeakEnemy::Update(Player& player, int max)
{
	m_oneInit = true;
	
	m_weakColPos[max] = Pos3(m_weakEnemyPos[max].x - 2.0f, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	//m_colSearchPos[max] = Pos3(m_weakEnemyPos[max].x, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);
	m_colDistancePos[max] = Pos3(m_weakEnemyPos[max].x, m_weakEnemyPos[max].y + 35.0f, m_weakEnemyPos[max].z);

	m_weakPlayTime[max] += 0.5f;

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
		//敵が移動する
		m_weakEnemyPos[max] = VAdd(m_weakEnemyPos[max], m_weakEnemyMove[max]);
	}

	//攻撃判定を正面に持ってくる
	m_colAttackPos[max].x = m_weakEnemyPos[max].x + sinf(m_weakEnemyAngle[max]) * -25.0f;
	m_colAttackPos[max].z = m_weakEnemyPos[max].z - cosf(m_weakEnemyAngle[max]) * 25.0f;

	//敵が死亡したら
	if (m_weakEnemyHp[max] <= 0.0f)
	{
		DrawFormatString(0, 240, 0xffffff, "敵が死んだ");

		m_weakCapsuleCol[max].Update(m_colDeathPos, m_deathVec);

		m_colSearch[max].Update(m_colDeathPos);
	}
	else
	{
		m_weakCapsuleCol[max].Update(m_weakColPos[max], m_vec);

		//とりあえず置いとく
		m_colSearch[max].Update(m_colSearchPos[max]);
		m_colDistance[max].Update(m_colDistancePos[max]);
	}

	//索敵の当たり判定を正面に持ってくる
	m_colSearchPos[max].x = m_weakEnemyPos[max].x + sinf(m_weakEnemyAngle[max]) * -80.0f;
	m_colSearchPos[max].z = m_weakEnemyPos[max].z - cosf(m_weakEnemyAngle[max]) * 80.0f;

	Action(player, max);

	Animation(m_weakPlayTime[max], max);
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
				if (m_weakPlayTime[max] >= 22 && m_weakPlayTime[max] <= 35)
				{
					m_colAttack[max].Update(m_colAttackPos[max]);
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
		if (m_weakEnemyAnimation[3][max] != -1 || m_weakEnemyAnimation[4][max] != -1 || m_weakEnemyAnimation[5][max] != -1 ||
			m_weakEnemyAnimation[6][max] != -1)
		{
			//アニメーションデタッチ
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);


			//アニメーションアタッチ
			m_weakEnemyAnimation[0][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animStand, TRUE);

			time = 0.0f;

			m_weakEnemyAnimation[3][max] = -1;
			m_weakEnemyAnimation[4][max] = -1;
			m_weakEnemyAnimation[5][max] = -1;
			m_weakEnemyAnimation[6][max] = -1;

		}
	}
	//敵がプレイヤーを見つけた時(臨戦態勢)
	if (m_enemySearchFlag[max] == true && m_enemyWait[max] == false && m_weakEnemyMoveAttack[max] == false)
	{
		if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[4][max] != -1 || m_weakEnemyAnimation[5][max] != -1 ||
			m_weakEnemyAnimation[6][max] != -1)
		{
			//アニメーションデタッチ
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);


			//アニメーションアタッチ
			m_weakEnemyAnimation[3][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animWalk, TRUE);

			time = 0.0f;

			m_weakEnemyAnimation[0][max] = -1;
			m_weakEnemyAnimation[4][max] = -1;
			m_weakEnemyAnimation[5][max] = -1;
			m_weakEnemyAnimation[6][max] = -1;

		}
	}
	//敵の射程圏内に入ったとき
	//左周り
	if (m_randomAction[max] == 0 && m_enemyWait[max] == true)
	{
		if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[3][max] != -1 || m_weakEnemyAnimation[5][max] != -1 ||
			m_weakEnemyAnimation[6][max] != -1)
		{
			//アニメーションデタッチ
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);

			//アニメーションアタッチ
			m_weakEnemyAnimation[4][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animLeftWalking, TRUE);

			time = 0.0f;

			m_weakEnemyAnimation[0][max] = -1;
			m_weakEnemyAnimation[3][max] = -1;
			m_weakEnemyAnimation[5][max] = -1;
			m_weakEnemyAnimation[6][max] = -1;

		}
	}
	//右周り
	if (m_randomAction[max] == 1 && m_enemyWait[max] == true)
	{
		if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[3][max] != -1 || m_weakEnemyAnimation[4][max] != -1 ||
			m_weakEnemyAnimation[6][max] != -1)
		{
			//アニメーションデタッチ
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);

			//アニメーションアタッチ
			m_weakEnemyAnimation[5][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animRightWalking, TRUE);

			time = 0.0f;

			m_weakEnemyAnimation[0][max] = -1;
			m_weakEnemyAnimation[3][max] = -1;
			m_weakEnemyAnimation[4][max] = -1;
			m_weakEnemyAnimation[6][max] = -1;

		}
	}
	//攻撃モーション
	if (m_randomAction[max] == 2 && m_enemyWait[max] == true)
	{
		if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[3][max] != -1 || m_weakEnemyAnimation[4][max] != -1 ||
			m_weakEnemyAnimation[5][max] != -1)
		{
			//アニメーションデタッチ
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);

			//アニメーションアタッチ
			m_weakEnemyAnimation[6][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animAttack1, TRUE);

			time = 0.0f;

			m_weakEnemyAnimation[0][max] = -1;
			m_weakEnemyAnimation[3][max] = -1;
			m_weakEnemyAnimation[4][max] = -1;
			m_weakEnemyAnimation[5][max] = -1;
		}
	}

	//敵が死んだら死ぬアニメーションを入れる
	if (m_weakEnemyHp[max] <= 0.0f)
	{
		if (m_weakEnemyAnimation[0][max] != -1 || m_weakEnemyAnimation[1][max] != -1 || m_weakEnemyAnimation[3][max] != -1 ||
			m_weakEnemyAnimation[4][max] != -1 || m_weakEnemyAnimation[5][max] != -1 || m_weakEnemyAnimation[6][max] != -1)
		{
			//アニメーションデタッチ
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[1][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max]);
			MV1DetachAnim(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max]);

			//アニメーションアタッチ
			m_weakEnemyAnimation[2][max] = MV1AttachAnim(m_weakEnemyHandle[max], 0, m_animDeath, TRUE);

			time = 0.0f;

			m_weakEnemyAnimation[0][max] = -1;
			m_weakEnemyAnimation[1][max] = -1;
			m_weakEnemyAnimation[3][max] = -1;
			m_weakEnemyAnimation[4][max] = -1;
			m_weakEnemyAnimation[5][max] = -1;
			m_weakEnemyAnimation[6][max] = -1;

		}
	}

	//再生時間がアニメーションの総再生時間に達したら再生時間を0に戻す
	if (time >= m_weakEnemyTotalAnimationTime[0][max] && m_weakEnemyAnimation[0][max] != -1)
	{
		time = 0.0f;
	}
	if (time >= m_weakEnemyTotalAnimationTime[2][max] && m_weakEnemyAnimation[2][max] != -1)
	{
		time = 120.0f;
	}
	if (time >= m_weakEnemyTotalAnimationTime[3][max] && m_weakEnemyAnimation[3][max] != -1)
	{
		time = 0.0f;
	}
	if (time >= m_weakEnemyTotalAnimationTime[4][max] && m_weakEnemyAnimation[4][max] != -1)
	{
		time = 0.0f;
	}
	if (time >= m_weakEnemyTotalAnimationTime[5][max] && m_weakEnemyAnimation[5][max] != -1)
	{
		time = 0.0f;
	}
	if (time >= m_weakEnemyTotalAnimationTime[6][max] && m_weakEnemyAnimation[6][max] != -1)
	{
		m_weakEnemyMoveAttack[max] = false;

		m_randomNextActionTime[max] = 50.0f;

		time = 0.0f;
	}

	//再生時間をセットする
	if (m_weakEnemyAnimation[0][max] != -1)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[0][max], time);
	}
	if (m_weakEnemyAnimation[2][max] != -1)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[2][max], time);
	}
	if (m_weakEnemyAnimation[3][max] != -1)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[3][max], time);
	}
	if (m_weakEnemyAnimation[4][max] != -1)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[4][max], time);
	}
	if (m_weakEnemyAnimation[5][max] != -1)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[5][max], time);
	}
	if (m_weakEnemyAnimation[6][max] != -1)
	{
		MV1SetAttachAnimTime(m_weakEnemyHandle[max], m_weakEnemyAnimation[6][max], time);
	}
}

void WeakEnemy::Draw(int max)
{
	//方向ベクトル
	Vec3 vec = m_vec.GetNormalized() * m_len * 0.5f;

	Pos3 pos1 = m_weakColPos[max] + vec;
	Pos3 pos2 = m_weakColPos[max] - vec;

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

	//3Dモデルポジション設定
	MV1SetPosition(m_weakEnemyHandle[max], m_weakEnemyPos[max]);

	//3Dモデル描画
	MV1DrawModel(m_weakEnemyHandle[max]);

	//3Dモデルの回転地をセットする
	MV1SetRotationXYZ(m_weakEnemyHandle[max], VGet(0.0f, m_weakEnemyAngle[max], 0.0f));

	//DrawFormatString(0, 320, 0xffffff, "m_colposX : %f m_colposY : %f m_colposZ : %f", m_colPos.x, m_colPos.y, m_colPos.z);
	//DrawFormatString(0, 220, 0xffffff, "m_EnemyHp : %f", m_hp);
	//DrawFormatString(0, 180, 0xffffff, "m_randomTime : %f", m_randomNextActionTime);
	//DrawFormatString(0, 160, 0xffffff, "m_randomAction : %f", m_randomAction);
	//DrawFormatString(0, 140, 0xffffff, "m_playTime : %f", m_playTime);

	//if (m_enemySearchFlag == true)
	//{
	//	DrawFormatString(0, 250, 0xffffff, "発見された");
	//}
}

void WeakEnemy::End(int max)
{
}

bool WeakEnemy::isSphereHit(const SphereCol& col, float damage, int max)
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
