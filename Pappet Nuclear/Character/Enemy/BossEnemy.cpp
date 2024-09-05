#include "BossEnemy.h"
#include "Character/Player/Player.h"
#include "Map/Map.h"

BossEnemy::BossEnemy() :
	m_gameClear(false),
	m_bossDistance(false),
	m_bossBattle(false),
	m_bossMoveAttack(false),
	m_bossMoveAttackPattern(false),
	m_bossAttack1(false),
	m_bossAttack2(false),
	m_bossAttack3(false),
	m_bossAttack(-1),
	m_one(false),
	m_bossAttackRadius1(0.0f),
	m_bossAttackRadius2(0.0f),
	m_bossAttackRadius3(0.0f),
	m_outPush(VGet(0.0f, 0.0f, 0.0f)),
	m_effectActivation(false),
	m_effect(0),
	m_outVec(VGet(0.0f, 0.0f, 0.0f)),
	m_distanceVec(VGet(0.0f,0.0f,0.0f)),
	m_length(0.0f)
{
}

BossEnemy::~BossEnemy()
{
}

void BossEnemy::Init()
{
	//敵のHP初期化
	m_hp = 1200.0f;

	//敵の攻撃力初期化
	m_attack = 30.0f;

	//敵のスピード強化
	m_speed = 0.01f;

	m_posX = -600.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;

	m_pos = VGet(m_posX, m_posY, m_posZ);

	m_bossBattle = false;

	m_bossMoveAttack = false;
	m_bossAttack = -1;

	m_bossAttack1 = false;
	m_bossAttack2 = false;
	m_bossAttack3 = false;

	//当たり判定
	m_colPos = Pos3(m_pos.x - 2.0f, m_pos.y + 35.0f, m_pos.z);
	m_colBossAttackPos1 = Pos3(m_pos.x - 50.0f, m_pos.y + 35.0f, m_pos.z);
	m_colBossAttackPos2 = Pos3(m_pos.x - 50.0f, m_pos.y + 35.0f, m_pos.z);
	m_colBossAttackPos3 = Pos3(m_pos.x, m_pos.y + 35.0f, m_pos.z);
	m_initializationPos = Pos3(0.0f, -1000.0f, 0.0f);
	m_vec = Vec3(0.0f, m_pos.y + 2.0f, 0.0f);
	m_len = 40.0f;
	m_capsuleRadius = 35.0f;
	m_sphereRadius = 120.0f;
	m_bossAttackRadius1 = 60.0f;
	m_bossAttackRadius2 = 40.0f;
	m_bossAttackRadius3 = 130.0f;
	m_capsuleCol.Init(m_colPos, m_vec, m_len, m_capsuleRadius);
	m_colDistance.Init(m_colPos, m_sphereRadius);
	m_colBossAttackSphere1.Init(m_initializationPos, m_bossAttackRadius1);
	m_colBossAttackSphere2.Init(m_initializationPos, m_bossAttackRadius2);
	m_colBossAttackSphere3.Init(m_initializationPos, m_bossAttackRadius3);

	//一回だけ初期化する
	if (m_one == false)
	{
		effect->BossInit();

		m_one = true;
	}
	
}

void BossEnemy::Update(Player& player, Map& map)
{
	m_colPos = Pos3(m_pos.x - 2.0f, m_pos.y + 35.0f, m_pos.z);
	m_colDistance.Update(m_colPos);

	//アニメーション再生速度
	if (m_bossAttack1 == true || m_bossAttack2 == true)
	{
		m_playTime += 0.1f;
	}
	else
	{
		m_playTime += 0.5f;
	}

	//ボスの部屋に入った
	if (map.GetRoomEntered() == true)
	{
		if (m_bossDistance == false || m_bossMoveAttackPattern == true)
		{

			float X = m_pos.x - player.GetPosX();
			float Z = m_pos.z - player.GetPosZ();

			//ボスからプレイヤーのベクトルを算出
			m_distanceVec = VSub(m_pos, player.GetPos());

			//Y軸は0
			m_distanceVec.y = 0.0f;

			//2人の距離を算出
			m_length = VSize(m_distanceVec);

			//ベクトルを正規化する
			m_outVec = VScale(m_distanceVec, 1.0f / m_length);

			//攻撃パターン1の時はプレイヤーの方を向く
			if (m_bossBattle == true && m_bossMoveAttack == false || m_bossMoveAttackPattern == true)
			{
				//プレイヤーの方を向く
				m_angle = atan2f(X, Z);

			}

			//ボスの戦闘状態移行
			m_bossBattle = true;
		}
	}

	if (m_bossDistance == false && m_bossBattle == true && m_bossMoveAttack == false)
	{
		//敵が移動する
		m_pos = VAdd(m_pos, m_move);
	}

	//敵が死亡したら
	if (m_hp <= 0.0f)
	{
	}
	else
	{
		m_capsuleCol.Update(m_colPos, m_vec);
	}

	if (m_bossAttack == -1)
	{
		m_colBossAttackSphere1.Update(m_initializationPos);
		m_colBossAttackSphere2.Update(m_initializationPos);
		m_colBossAttackSphere3.Update(m_initializationPos);
	}

	//攻撃判定を正面に持っていく
	m_colBossAttackPos1.x = m_pos.x + sinf(m_angle) * -75.0f;
	m_colBossAttackPos1.z = m_pos.z - cosf(m_angle) * 75.0f;
	m_colBossAttackPos2.x = m_pos.x + sinf(m_angle) * -75.0f;
	m_colBossAttackPos2.z = m_pos.z - cosf(m_angle) * 75.0f;
	m_colBossAttackPos3 = Pos3(m_pos.x, m_pos.y + 35.0f, m_pos.z);

	Action(player);

	Animation(m_playTime);
}

void BossEnemy::Action(Player& player)
{
	//プレイヤーと敵の相対距離を算出
	VECTOR tracking = VSub(player.GetPos(), m_pos);

	//ボスの戦闘状態
	if (m_bossBattle == true && m_bossDistance == false && m_bossMoveAttack == false)
	{
		m_speed = 0.01f;

		m_move = VScale(tracking, m_speed);
	}
	//射程距離に入った
	if (m_bossDistance == true)
	{
		//行動が終わるまで一回実行
		if (m_bossMoveAttack == false)
		{
			m_bossAttack = GetRand(2);

			m_bossMoveAttack = true;
		}
		//攻撃の当たり判定
		if (m_bossAttack == 0 && m_bossAttack1 == true)
		{
			

			//一定時間をすぎると向かない
			if (m_playTime >= 30.0f)
			{
				m_bossMoveAttackPattern = false;
			}

			if (m_playTime >= 38.0f && m_playTime <= 43.0f)
			{
				m_colBossAttackSphere1.Update(m_colBossAttackPos1);
			}
			else
			{
				m_colBossAttackSphere1.Update(m_initializationPos);
			}
		}
		if (m_bossAttack == 1 && m_bossAttack2 == true)
		{
			

			//一定時間をすぎると向かない
			if (m_playTime >= 1.0f)
			{
				m_bossMoveAttackPattern = false;
			}

			if (m_playTime >= 7.0f && m_playTime <= 11.0f)
			{
				m_colBossAttackSphere2.Update(m_colBossAttackPos2);
			}
			else
			{
				m_colBossAttackSphere2.Update(m_initializationPos);
			}
		}
		if (m_bossAttack == 2 && m_bossAttack3 == true)
		{
			if (m_effectActivation == false)
			{
				m_effect = PlayEffekseer3DEffect(effect->GetBossAttackEffect3());

				SetPosPlayingEffekseer3DEffect(m_effect, m_pos.x, 0.0f, m_pos.z);

				m_effectActivation = true;
			}
			

			if (m_playTime >= 58.0f && m_playTime <= 63.0f)
			{
				m_colBossAttackSphere3.Update(m_colBossAttackPos3);
			}
			else
			{
				m_colBossAttackSphere3.Update(m_initializationPos);
			}
		}
	}

	//エフェクト更新
	effect->Update();
}

void BossEnemy::Animation(float& time)
{
	//敵が死んだときのアニメーション
	if (m_hp <= 0.0f)
	{
		if (m_bossAnimation[0] != -1 || m_bossAnimation[3] != -1 || m_bossAnimation[4] != -1 ||
			m_bossAnimation[5] != -1 || m_bossAnimation[6] != -1)
		{
			m_bossAttack1 = false;
			m_bossAttack2 = false;
			m_bossAttack3 = false;


			//アニメーションデタッチ
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[0]);
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[3]);
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[4]);
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[5]);
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[6]);


			//アニメーションアタッチ
			m_bossAnimation[2] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimDeath, TRUE);

			time = 0.0f;

			m_bossAnimation[0] = -1;
			m_bossAnimation[3] = -1;
			m_bossAnimation[4] = -1;
			m_bossAnimation[5] = -1;
			m_bossAnimation[6] = -1;

		}
	}
	if (m_bossBattle == true)
	{
		//敵が攻撃してない時
		if (m_bossMoveAttack == false)
		{
			if (m_bossAnimation[0] != -1 || m_bossAnimation[4] != -1 || m_bossAnimation[5] != -1 ||
				m_bossAnimation[6] != -1)
			{
				m_bossAttack1 = false;
				m_bossAttack2 = false;
				m_bossAttack3 = false;

				//アニメーションデタッチ
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[0]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[4]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[5]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[6]);

				//アニメーションアタッチ
				m_bossAnimation[3] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimWalk, TRUE);

				time = 0.0f;

				m_bossAnimation[0] = -1;
				m_bossAnimation[4] = -1;
				m_bossAnimation[5] = -1;
				m_bossAnimation[6] = -1;

			}
		}
		//攻撃パターン1
		if (m_bossAttack == 0 && m_bossMoveAttack == true)
		{
			if (m_bossAnimation[0] != -1 || m_bossAnimation[3] != -1 || m_bossAnimation[5] != -1 ||
				m_bossAnimation[6] != -1)
			{
				m_bossAttack1 = true;
				m_bossAttack2 = false;
				m_bossAttack3 = false;

				m_bossMoveAttackPattern = true;

				//アニメーションデタッチ
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[0]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[3]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[5]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[6]);

				//アニメーションアタッチ
				m_bossAnimation[4] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack1, TRUE);

				//攻撃力
				m_attack = 50.0f;

				time = 0.0f;

				m_bossAnimation[0] = -1;
				m_bossAnimation[3] = -1;
				m_bossAnimation[5] = -1;
				m_bossAnimation[6] = -1;

			}
		}
		//攻撃パターン2
		if (m_bossAttack == 1 && m_bossMoveAttack == true)
		{
			if (m_bossAnimation[0] != -1 || m_bossAnimation[3] != -1 || m_bossAnimation[4] != -1 ||
				m_bossAnimation[6] != -1)
			{
				m_bossAttack1 = false;
				m_bossAttack2 = true;
				m_bossAttack3 = false;

				m_bossMoveAttackPattern = true;

				//アニメーションデタッチ
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[0]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[3]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[4]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[6]);

				//アニメーションアタッチ
				m_bossAnimation[5] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack2, TRUE);

				//攻撃力
				m_attack = 30.0f;

				time = 0.0f;

				m_bossAnimation[0] = -1;
				m_bossAnimation[3] = -1;
				m_bossAnimation[4] = -1;
				m_bossAnimation[6] = -1;
			}
		}
		//攻撃パターン3
		if (m_bossAttack == 2 && m_bossMoveAttack == true)
		{
			if (m_bossAnimation[0] != -1 || m_bossAnimation[3] != -1 || m_bossAnimation[4] != -1 ||
				m_bossAnimation[5] != -1)
			{
				m_bossAttack1 = false;
				m_bossAttack2 = false;
				m_bossAttack3 = true;

				//アニメーションデタッチ
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[0]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[3]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[4]);
				MV1DetachAnim(m_bossModelHandle, m_bossAnimation[5]);

				//アニメーションアタッチ
				m_bossAnimation[6] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack3, TRUE);

				//攻撃力
				m_attack = 80.0f;

				time = 0.0f;

				m_bossAnimation[0] = -1;
				m_bossAnimation[3] = -1;
				m_bossAnimation[4] = -1;
				m_bossAnimation[5] = -1;
			}

		}
		
	}

	//再生時間がアニメーションの総再生時間に達したら再生時間を0に戻す
	if (time >= m_bossTotalAnimTime[0] && m_bossAnimation[0] != -1)
	{
		time = 0.0f;
	}
	if (time >= m_bossTotalAnimTime[2] && m_bossAnimation[2] != -1)
	{
		//ボスを倒したらゲームクリア
		m_gameClear = true;

		time = 120.0f;
	}
	if (time >= m_bossTotalAnimTime[3] && m_bossAnimation[3] != -1)
	{
		time = 0.0f;
	}
	if (time >= m_bossTotalAnimTime[4] && m_bossAnimation[4] != -1)
	{
		m_bossMoveAttack = false;

		m_bossAttack1 = false;

		m_effectActivation = false;

		time = 0.0f;
	}
	if (time >= m_bossTotalAnimTime[5] && m_bossAnimation[5] != -1)
	{
		m_bossMoveAttack = false;

		m_bossAttack2 = false;

		m_effectActivation = false;

		time = 0.0f;
	}
	if (time >= m_bossTotalAnimTime[6] && m_bossAnimation[6] != -1)
	{
		m_bossMoveAttack = false;

		m_bossAttack3 = false;

		m_effectActivation = false;

		time = 0.0f;
	}
	//再生時間をセットする
	if (m_bossAnimation[0] != -1)
	{
		MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[0], time);
	}
	if (m_bossAnimation[2] != -1)
	{
		MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[2], time);
	}
	if (m_bossAnimation[3] != -1)
	{
		MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[3], time);
	}
	if (m_bossAnimation[4] != -1)
	{
		MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[4], time);
	}
	if (m_bossAnimation[5] != -1)
	{
		MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[5], time);
	}
	if (m_bossAnimation[6] != -1)
	{
		MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[6], time);
	}
}

void BossEnemy::Draw()
{
	//方向ベクトル
	Vec3 vec = m_vec.GetNormalized() * m_len * 0.5f;

	Pos3 pos1 = m_colPos + vec;
	Pos3 pos2 = m_colPos - vec;

	//敵が生きている時は描画
	if (m_hp > 0.0f)
	{
		//DrawCapsule3D(pos1.GetVector(), pos2.GetVector(), m_capsuleRadius, 16, m_color, 0, false);

		////攻撃の範囲描画
		//DrawSphere3D(m_colPos.GetVector(), m_sphereRadius, 16, m_distanceColor, m_distanceColor, false);

		////攻撃判定描画
		//DrawSphere3D(m_colBossAttackPos1.GetVector(), m_bossAttackRadius1, 16, 0xffffff, 0xffffff, false);
		//DrawSphere3D(m_colBossAttackPos2.GetVector(), m_bossAttackRadius2, 16, 0xffffff, 0xffffff, false);
		//DrawSphere3D(m_colBossAttackPos3.GetVector(), m_bossAttackRadius3, 16, 0xffffff, 0xffffff, false);
	}

	DrawFormatString(150, 300, 0xffffff, "エフェクト : %d", IsEffekseer3DEffectPlaying(effect->GetBossAttackEffect3()));

	//3Dモデルポジション設定
	MV1SetPosition(m_bossModelHandle, m_pos);

	//3Dモデル描画
	MV1DrawModel(m_bossModelHandle);

	//3Dモデルの回転地をセットする
	MV1SetRotationXYZ(m_bossModelHandle, VGet(0.0f, m_angle, 0.0f));

	//エフェクトの描画
	effect->Draw();
}

void BossEnemy::End()
{
	//メモリ解放
	effect->End();
}

bool BossEnemy::isSphereHit(const SphereCol& col, float damage)
{
	bool isHit = m_capsuleCol.IsHitSphere(col);

	//ダメージを受けた判定
	if (isHit)
	{
		m_color = 0xffff00;

		//ダメージを一回だけ与える
		if (m_damageReceived == false)
		{
			m_hp = m_hp - damage;

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

bool BossEnemy::isPlayerHit(const CapsuleCol& col, VECTOR vec, float bounce)
{
	bool isHit = m_capsuleCol.IsHitCapsule(col);

	//プレイヤーと当たった時
	if (isHit)
	{
		m_color = 0xffff00;

		//法線ベクトルをとれるようにしておく
		m_outPush = VAdd(m_outPush, VScale(vec, 1.0f));
	}
	else
	{
		m_outPush = VGet(0.0f, 0.0f, 0.0f);

		m_color = 0xffffff;
	}

	return isHit;
}

bool BossEnemy::isCapsuleHit(const CapsuleCol& col)
{
	bool isHit = m_colDistance.IsHitCapsule(col);

	//一定範囲内にプレイヤーが入った時
	if (isHit)
	{
		m_distanceColor = 0xffff00;

		m_bossDistance = true;
	}
	else
	{
		m_distanceColor = 0xffffff;

		m_bossDistance = false;
	}

	return isHit;
}
