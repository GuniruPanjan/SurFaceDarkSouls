#include "BossEnemy.h"
#include "Character/Player/Player.h"
#include "Map/Map.h"

namespace
{
	bool attack;    //攻撃SEの判定
	bool patternOne;    //pattern変数を一回だけ変更する
	int walkTime;   //歩くSE間隔
	float difPSize;   //プレイヤーとの距離
	float difSSize;   //盾との距離
	float correctionAngle;    //敵がプレイヤーの位置によって方向を補正するための変数
}

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
	m_bounceAngle(0.0f),
	m_outPush(VGet(0.0f, 0.0f, 0.0f)),
	m_playerHit(false),
	m_turnLeft(false),
	m_turnRight(false)
{
}

BossEnemy::~BossEnemy()
{
}

void BossEnemy::Init()
{
	//敵のHP初期化
	m_hp = 1000.0f;

	//敵の攻撃力初期化
	m_attack = 30.0f;

	//敵のスピード強化
	m_speed = 0.01f;

	m_posX = -600.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;

	//コア初期化
	m_core = 2500;

	//死亡判定を初期化する
	m_death = false;

	m_pos = VGet(m_posX, m_posY, m_posZ);

	m_bossBattle = false;

	m_bossMoveAttack = false;
	m_bossAttack = -1;

	m_bossAttack1 = false;
	m_bossAttack2 = false;
	m_bossAttack3 = false;
	patternOne = false;

	//当たり判定
	m_colPos = Pos3(m_pos.x - 2.0f, m_pos.y + 35.0f, m_pos.z);
	m_colBossAttackPos1 = Pos3(m_pos.x - 50.0f, m_pos.y + 35.0f, m_pos.z);
	m_colBossAttackPos2 = Pos3(m_pos.x - 50.0f, m_pos.y + 35.0f, m_pos.z);
	m_colBossAttackPos3 = Pos3(m_pos.x, m_pos.y + 35.0f, m_pos.z);
	m_initializationPos = Pos3(1000.0f, -1000.0f, 1000.0f);
	m_vec = Vec3(0.0f, m_pos.y + 2.0f, 0.0f);
	m_len = 40.0f;
	m_capsuleRadius = 35.0f;
	m_sphereRadius = 120.0f;
	m_bossAttackRadius1 = 60.0f;
	m_bossAttackRadius2 = 40.0f;
	m_bossAttackRadius3 = 130.0f;
	m_capsuleCol.Init(m_colPos, m_vec, m_len, m_capsuleRadius);
	m_bossColDistance.Init(m_colPos, m_sphereRadius);
	m_colBossAttackSphere1.Init(m_initializationPos, m_bossAttackRadius1);
	m_colBossAttackSphere2.Init(m_initializationPos, m_bossAttackRadius2);
	m_colBossAttackSphere3.Init(m_initializationPos, m_bossAttackRadius3);

	m_effectActivation = false;

	walkTime = 0;

	//一回だけ初期化する
	if (m_one == false)
	{
		effect->BossInit();

		se->BossInit();

		m_one = true;
		
	}
	
	attack = false;

	//se->Init();
}

void BossEnemy::Update(Player& player, Map& map, int volume)
{
	m_colPos = Pos3(m_pos.x - 2.0f, m_pos.y + 35.0f, m_pos.z);
	m_bossColDistance.Update(m_colPos);

	//敵とプレイヤーの相対距離
	m_playerDif = VSub(player.GetPos(), m_pos);
	//敵と盾の相対距離
	m_shieldDif = VSub(player.GetShieldPos(), m_pos);

	difPSize = VSize(m_playerDif);
	difSSize = VSize(m_shieldDif);

	//アニメーション再生速度
	if (m_bossAttack1 == true)
	{
		m_playTime += 0.3f;

	}
	else if (m_bossAttack2 == true)
	{
		m_playTime += 0.2f;

	}
	else
	{
		m_playTime += 0.5f;
	}

	//プレイヤーを押し出す方向算出
	float bounceX = m_pos.x - player.GetPosX();
	float bounceZ = m_pos.z - player.GetPosZ();

	m_bounceAngle = atan2f(bounceX, bounceZ);


	//ボスの部屋に入った
	if (map.GetRoomEntered() == true)
	{
		//敵がプレイヤーの位置によって方向を補正する
		float Cx = m_pos.x - player.GetPosX();
		float Cz = m_pos.z - player.GetPosZ();

		correctionAngle = atan2f(Cx, Cz);

		
		if (m_bossMoveAttack == false)
		{
			//左に回転する
			if (m_angle > correctionAngle + 0.8f)
			{
				m_turnLeft = true;
				m_turnRight = false;
			}
			//else if (0.0f <= correctionAngle && correctionAngle <= 4.0f && m_angle <= 0.0f)
			//{
			//	m_turnLeft = true;
			//	m_turnRight = false;
			//}
			//右に回転する
			if (m_angle < correctionAngle - 0.8f)
			{
				m_turnRight = true;
				m_turnLeft = false;
			}
			//else if (0.0f > correctionAngle && correctionAngle >= -4.0f && m_angle > 0.0f)
			//{
			//	m_turnRight = true;
			//	m_turnLeft = false;
			//}
		}

		if (m_bossDistance == false || m_bossMoveAttackPattern == true)
		{
			float X = m_pos.x - player.GetPosX();
			float Z = m_pos.z - player.GetPosZ();

			//攻撃パターン1の時はプレイヤーの方を向く
			if (m_bossBattle == true && m_bossMoveAttack == false || m_bossMoveAttackPattern == true)
			{
				if (m_turnLeft == false && m_turnRight == false)
				{
					//プレイヤーの方を向く
					m_angle = atan2f(X, Z);
				}
			}

			//ボスの戦闘状態移行
			m_bossBattle = true;
		}
	}
	if (m_bossDistance == false && m_bossBattle == true && m_bossMoveAttack == false && m_turnLeft == false && m_turnRight == false)
	{
		walkTime++;

		//敵が移動する
		m_pos = VAdd(m_pos, m_move);

		if (walkTime >= 30.0f)
		{
			PlaySoundMem(se->GetBossWalkSE(), DX_PLAYTYPE_BACK, true);

			walkTime = 0;
		}
	}
	else
	{
		walkTime = 0;
	}

	for (int i = 7; i < 9; i++)
	{
		//モーション終了後アングルを入れる
		if (m_playTime >= m_bossTotalAnimTime[i] && m_bossAnimOne[i] == true)
		{
			if (i == 7)
			{
				m_angle = correctionAngle;
			}
			if (i == 8)
			{
				m_angle = correctionAngle;
			}
		}
	}

	//敵が死亡したら
	if (m_hp <= 0.0f)
	{
		//一回だけ実行
		if (m_death == false)
		{
			m_baseCore = m_baseCore + m_core;

			m_death = true;
		}
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

	//盾よりプレイヤーの方が近かったら
	if (difPSize < difSSize)
	{
		m_playerHit = true;
	}
	else
	{
		m_playerHit = false;
	}


	//マップとの当たり判定用
	m_mapHitColl = VGet(m_colPos.x, m_colPos.y, m_colPos.z);

	//攻撃判定を正面に持っていく
	m_colBossAttackPos1.x = m_pos.x + sinf(m_angle) * -75.0f;
	m_colBossAttackPos1.z = m_pos.z - cosf(m_angle) * 75.0f;
	m_colBossAttackPos2.x = m_pos.x + sinf(m_angle) * -75.0f;
	m_colBossAttackPos2.z = m_pos.z - cosf(m_angle) * 75.0f;
	m_colBossAttackPos3 = Pos3(m_pos.x, m_pos.y + 35.0f, m_pos.z);

	Action(player);

	Animation(m_playTime);

	se->Update(volume);
}

void BossEnemy::Action(Player& player)
{
	//プレイヤーと敵の相対距離を算出
	VECTOR tracking = VSub(player.GetPos(), m_pos);

	//ボスの戦闘状態
	if (m_bossBattle == true && m_bossDistance == false && m_bossMoveAttack == false && m_turnLeft == false && m_turnRight == false)
	{
		m_speed = 0.01f;

		m_move = VScale(tracking, m_speed);
	}
	//射程距離に入った
	if (m_bossDistance == true && m_turnLeft == false && m_turnRight == false)
	{
		//行動が終わるまで一回実行
		if (m_bossMoveAttack == false)
		{
			//攻撃の当たり判定を初期化
			m_colBossAttackSphere1.Update(m_initializationPos);
			m_colBossAttackSphere2.Update(m_initializationPos);
			m_colBossAttackSphere3.Update(m_initializationPos);

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

			if (m_playTime >= 38.0f && m_playTime <= 45.0f)
			{
				if (attack == false)
				{
					PlaySoundMem(se->GetBossAttackSE1(), DX_PLAYTYPE_BACK, true);

					attack = true;
				}

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

			if (m_playTime >= 7.0f && m_playTime <= 12.0f)
			{
				if (attack == false)
				{
					PlaySoundMem(se->GetBossAttackSE2(), DX_PLAYTYPE_BACK, true);

					attack = true;
				}

				m_colBossAttackSphere2.Update(m_colBossAttackPos2);
			}	
			else
			{
				m_colBossAttackSphere2.Update(m_initializationPos);
			}
		}
		if (m_bossAttack == 2 && m_bossAttack3 == true)
		{	

			if (m_playTime >= 5.0f)
			{

				if (m_effectActivation == false)
				{
					m_effect = PlayEffekseer3DEffect(effect->GetBossAttackEffect3());

					m_effectActivation = true;
				}
			}
			if (m_playTime >= 25.0f)
			{

					if (attack == false)
					{
						PlaySoundMem(se->GetBossAttackSE3(), DX_PLAYTYPE_BACK, true);

						attack = true;
					}
	
			}
			if (m_playTime >= 58.0f && m_playTime <= 68.0f)
			{
				m_colBossAttackSphere3.Update(m_colBossAttackPos3);
			}
			else
			{
				m_colBossAttackSphere3.Update(m_initializationPos);
			}
		}
	}

	//エフェクトポジション更新
	SetPosPlayingEffekseer3DEffect(m_effect, m_pos.x, 0.0f, m_pos.z);

	//エフェクト更新
	//effect->Update();
}

void BossEnemy::Animation(float& time)
{
	if (m_bossAnimBlend < 1.0f)
	{
		m_bossAnimBlend += 0.1f;
	}
	//敵が死んだときのアニメーション
	if (m_hp <= 0.0f)
	{
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[2], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[3], m_bossAnimBlend, m_bossAnimOne[3], m_bossAnimOne[2], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[2], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[2], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[2], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[7], m_bossAnimBlend, m_bossAnimOne[7], m_bossAnimOne[2], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[2], m_bossAnimation[8], m_bossAnimBlend, m_bossAnimOne[8], m_bossAnimOne[2], m_bossAnimBlendOne);
	}
	if (m_bossBattle == true)
	{
		//敵が攻撃してない時
		if (m_bossMoveAttack == false && m_turnRight == false && m_turnLeft == false)
		{

			m_bossAttack1 = false;
			m_bossAttack2 = false;
			m_bossAttack3 = false;

			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[3], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[3], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[3], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[3], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[3], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[3], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[3], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[3], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[3], m_bossAnimation[7], m_bossAnimBlend, m_bossAnimOne[7], m_bossAnimOne[3], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[3], m_bossAnimation[8], m_bossAnimBlend, m_bossAnimOne[8], m_bossAnimOne[3], m_bossAnimBlendOne);
		}
		//右回る
		if (m_turnRight == true)
		{
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[7], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[7], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[7], m_bossAnimation[3], m_bossAnimBlend, m_bossAnimOne[3], m_bossAnimOne[7], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[7], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[7], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[7], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[7], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[7], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[7], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[7], m_bossAnimation[8], m_bossAnimBlend, m_bossAnimOne[8], m_bossAnimOne[7], m_bossAnimBlendOne);

		}
		//左回る
		if (m_turnLeft == true)
		{
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[8], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[8], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[8], m_bossAnimation[3], m_bossAnimBlend, m_bossAnimOne[3], m_bossAnimOne[8], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[8], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[8], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[8], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[8], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[8], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[8], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[8], m_bossAnimation[7], m_bossAnimBlend, m_bossAnimOne[7], m_bossAnimOne[8], m_bossAnimBlendOne);

		}
		//攻撃パターン1
		if (m_bossAttack == 0 && m_bossMoveAttack == true && m_turnRight == false && m_turnLeft == false)
		{

			m_bossAttack1 = true;
			m_bossAttack2 = false;
			m_bossAttack3 = false;

			if (patternOne == false)
			{
				m_bossMoveAttackPattern = true;

				patternOne = true;
			}

			//攻撃力
			m_attack = 50.0f;

			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[4], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[4], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[4], m_bossAnimation[3], m_bossAnimBlend, m_bossAnimOne[3], m_bossAnimOne[4], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[4], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[4], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[4], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[4], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[4], m_bossAnimation[7], m_bossAnimBlend, m_bossAnimOne[7], m_bossAnimOne[4], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[4], m_bossAnimation[8], m_bossAnimBlend, m_bossAnimOne[8], m_bossAnimOne[4], m_bossAnimBlendOne);

		}
		//攻撃パターン2
		if (m_bossAttack == 1 && m_bossMoveAttack == true && m_turnRight == false && m_turnLeft == false)
		{
			m_bossAttack1 = false;
			m_bossAttack2 = true;
			m_bossAttack3 = false;

			if (patternOne == false)
			{
				m_bossMoveAttackPattern = true;

				patternOne = true;
			}

			//攻撃力
			m_attack = 30.0f;

			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[5], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[5], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[5], m_bossAnimation[3], m_bossAnimBlend, m_bossAnimOne[3], m_bossAnimOne[5], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[5], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[5], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[5], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[5], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[5], m_bossAnimation[7], m_bossAnimBlend, m_bossAnimOne[7], m_bossAnimOne[5], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[5], m_bossAnimation[8], m_bossAnimBlend, m_bossAnimOne[8], m_bossAnimOne[5], m_bossAnimBlendOne);

		}
		//攻撃パターン3
		if (m_bossAttack == 2 && m_bossMoveAttack == true && m_turnRight == false && m_turnLeft == false)
		{
			m_bossAttack1 = false;
			m_bossAttack2 = false;
			m_bossAttack3 = true;

			//攻撃力
			m_attack = 80.0f;

			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[6], m_bossAnimation[0], m_bossAnimBlend, m_bossAnimOne[0], m_bossAnimOne[6], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[6], m_bossAnimation[3], m_bossAnimBlend, m_bossAnimOne[3], m_bossAnimOne[6], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[6], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[6], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[6], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[6], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[6], m_bossAnimation[7], m_bossAnimBlend, m_bossAnimOne[7], m_bossAnimOne[6], m_bossAnimBlendOne);
			pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[6], m_bossAnimation[8], m_bossAnimBlend, m_bossAnimOne[8], m_bossAnimOne[6], m_bossAnimBlendOne);

		}
		
	}
	//バグ修正用
	if (m_bossMoveAttack == true && m_bossAttack1 == false && m_bossAttack2 == false && m_bossAttack3 == false)
	{
		m_bossAttack = -1;

		PlaySoundMem(se->GetBossVoiceSE(), DX_PLAYTYPE_BACK, true);

		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[0], m_bossAnimation[4], m_bossAnimBlend, m_bossAnimOne[4], m_bossAnimOne[0], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[0], m_bossAnimation[5], m_bossAnimBlend, m_bossAnimOne[5], m_bossAnimOne[0], m_bossAnimBlendOne);
		pAnim->AnimationBlend(time, m_bossModelHandle, m_bossAnimation[0], m_bossAnimation[6], m_bossAnimBlend, m_bossAnimOne[6], m_bossAnimOne[0], m_bossAnimBlendOne);

	}


	//再生時間がアニメーションの総再生時間に達したら再生時間を0に戻す

	for (int i = 0; i < 9; i++)
	{
		if (time >= m_bossTotalAnimTime[i] && m_bossAnimOne[i] == true)
		{
			if (i == 0)
			{
				m_bossMoveAttack = false;

				time = 0.0f;
			}
			if (i == 2)
			{
				//ボスを倒したらゲームクリア
				m_gameClear = true;

				time = 120.0f;
			}
			if (i == 3)
			{
				time = 0.0f;
			}
			if (i == 4)
			{
				m_bossMoveAttack = false;

				m_bossAttack1 = false;

				attack = false;

				time = 0.0f;
			}
			if (i == 5)
			{
				m_bossMoveAttack = false;

				m_bossAttack2 = false;

				attack = false;

				time = 0.0f;
			}
			if (i == 6)
			{
				m_bossMoveAttack = false;

				m_bossAttack3 = false;

				m_effectActivation = false;

				attack = false;

				time = 0.0f;
			}
			if (i == 7)
			{
				if (correctionAngle > m_angle + 0.8f)
				{
					m_turnRight = true;

					time = 0.0f;
				}
				else if (0.0f >= correctionAngle && correctionAngle >= -4.0f && m_angle >= 0.0f)
				{
					m_turnRight = true;

					time = 0.0f;
				}
				else   //右回転しなくなる
				{
					m_turnRight = false;
				}
			}
			if (i == 8)
			{
				if (correctionAngle < m_angle - 0.8f)
				{
					m_turnLeft = true;

					time = 0.0f;
				}
				//アングルが負の数から正の数になった時用
				else if (0.0f <= correctionAngle && correctionAngle <= 4.0f && m_angle <= 0.0f)
				{
					m_turnLeft = true;

					time = 0.0f;
				}
				else   //左回転しなくなる
				{
					m_turnLeft = false;
				}
			}

			patternOne = false;
		}
	}
	//再生時間をセットする
	for (int i = 0; i < 9; i++)
	{
		if (m_bossAnimOne[i] == true)
		{
			MV1SetAttachAnimTime(m_bossModelHandle, m_bossAnimation[i], time);

			//右回り
			if (i == 7)
			{
				if (m_angle < correctionAngle - 0.8f)
				{
					m_angle += 0.05f;
				}
			}
			//左回り
			if (i == 8)
			{
				if (m_angle > correctionAngle + 0.8f)
				{
					m_angle -= 0.05f;
				}
			}
		}
	}
}

void BossEnemy::MapHit(Map& map)
{
	int j;

	//プレイヤーの周囲にあるコリジョンのポリゴンを取得する
	HitDim = MV1CollCheck_Sphere(map.GetCollisionMap(), -1, map.GetVectorMapPos(), 1500.0f);

	//検出されたポリゴンが壁ポリゴン(XZ平面に垂直なポリゴン)か床ポリゴン(XZ平面に垂直ではないポリゴン)かを判断する
	for (int i = 0; i < HitDim.HitNum; i++)
	{
		//XZ平面に垂直かどうかはポリゴンの法線のY成分が0に限りなく近いかどうかで判断する
		if (HitDim.Dim[i].Normal.y < 0.000001f && HitDim.Dim[i].Normal.y > -0.0000001f)
		{
			if (HitDim.Dim[i].Position[0].y > m_pos.y + 1.0f ||
				HitDim.Dim[i].Position[1].y > m_pos.y + 1.0f ||
				HitDim.Dim[i].Position[2].y > m_pos.y + 1.0f)
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
		m_HitFlag = false;

		//移動したかどうかで処理を分岐
		if (m_moveflag == true)
		{
			//壁ポリゴンの数だけ繰り返し
			for (int i = 0; i < m_WallNum; i++)
			{
				//i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				m_Poly = m_Wall[i];

				//ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
				if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == false) continue;

				//ここにきたらポリゴンとプレイヤーが当たっているということなので、ポリゴンに当たったフラグを立てる
				m_HitFlag = true;

				//新たな移動座標で壁ポリゴンと当たっていないかどうかを判定する
				for (j = 0; j < m_WallNum; j++)
				{
					//j番目の壁ポリゴンと当たっていないかどうかを判定する
					m_Poly = m_Wall[j];

					//当たっていたらループから抜ける
					if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true) break;
				}

				//jがm_WallNumだった場合はどのポリゴンとも当たらなかったということなので
				//壁に当たったフラグを倒したうえでループから抜ける
				if (j == m_WallNum)
				{
					m_HitFlag = false;
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
				if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true)
				{
					m_HitFlag = true;
					break;
				}

			}
		}

		//壁に当たっていたら壁から押し出す処理を行う
		if (m_HitFlag == true)
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
					if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == false) continue;

					//当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
					m_pos = VAdd(m_pos, VScale(m_Poly->Normal, 1.0f));

					//移動した上で壁ポリゴンと接触しているかどうかを判定
					for (j = 0; j < m_WallNum; j++)
					{
						//当たっていたらループを抜ける
						m_Poly = m_Wall[j];
						if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true) break;

					}

					//すべてのポリゴンと当たっていなかったらループ終了
					if (j == m_WallNum) break;
				}

				//iがm_WallNumではない場合は全部のポリゴンで押し出しを試みる前にすべての壁ポリゴンと接触しなくなったということなのでループから抜ける
				if (i != m_WallNum) break;
			}
		}
	}

	//検出したプレイヤーの周囲のポリゴン情報を解放する
	MV1CollResultPolyDimTerminate(HitDim);
}

void BossEnemy::Draw()
{
	//方向ベクトル
	Vec3 vec = m_vec.GetNormalized() * m_len * 0.5f;

	Pos3 pos1 = m_colPos + vec;
	Pos3 pos2 = m_colPos - vec;

#if false

	//敵が生きている時は描画
	if (m_hp > 0.0f)
	{
		DrawCapsule3D(pos1.GetVector(), pos2.GetVector(), m_capsuleRadius, 16, m_color, 0, false);

		//攻撃の範囲描画
		DrawSphere3D(m_colPos.GetVector(), m_sphereRadius, 16, m_distanceColor, m_distanceColor, false);

		//攻撃判定描画
		DrawSphere3D(m_colBossAttackPos1.GetVector(), m_bossAttackRadius1, 16, 0xffffff, 0xffffff, false);
		DrawSphere3D(m_colBossAttackPos2.GetVector(), m_bossAttackRadius2, 16, 0xffffff, 0xffffff, false);
		DrawSphere3D(m_colBossAttackPos3.GetVector(), m_bossAttackRadius3, 16, 0xffffff, 0xffffff, false);
	}

#endif
#if false

	DrawFormatString(0, 120, 0xffffff, "m_moveAttack1 : %d", m_bossAttack1);
	DrawFormatString(0, 180, 0xffffff, "m_moveAttack1 : %d", m_bossAttack2);
	DrawFormatString(0, 240, 0xffffff, "m_moveAttack1 : %d", m_bossAttack3);
	DrawFormatString(0, 300, 0xffffff, "m_BossAttack : %d", m_bossAttack);
	DrawFormatString(0, 360, 0xffffff, "m_PlayTime : %f", m_playTime);
	//DrawFormatString(0, 400, 0xffffff, "m_Attack : %f", m_attack);

	
#endif

#if true
	//プレイヤーがボスより左にいると-がかかるし、差がー１くらいで１アニメーション
	//プレイヤーがボスより右にいると+がかかるし、差が+1くらいで1アニメーション
	DrawFormatString(0, 320, 0xffffff, "m_angle : %f", m_angle);
	DrawFormatString(0, 380, 0xffffff, "correctionAngle : %f", correctionAngle);
	DrawFormatString(0, 440, 0xffffff, "right : %d", m_turnRight);
	DrawFormatString(0, 500, 0xffffff, "left : %d", m_turnLeft);
	DrawFormatString(100, 560, 0xffffff, "blend : %f", m_bossAnimBlend);
	DrawFormatString(100, 620, 0xffffff, "pattern : %d", m_bossMoveAttackPattern);
#endif

#if false
	DrawFormatString(100, 500, 0xffffff, "anim0 : %d", m_bossAnimOne[0]);
	DrawFormatString(100, 560, 0xffffff, "anim1 : %d", m_bossAnimOne[1]);
	DrawFormatString(100, 620, 0xffffff, "anim2 : %d", m_bossAnimOne[2]);
	DrawFormatString(100, 680, 0xffffff, "anim3 : %d", m_bossAnimOne[3]);
	DrawFormatString(100, 740, 0xffffff, "anim4 : %d", m_bossAnimOne[4]);
	DrawFormatString(100, 800, 0xffffff, "anim5 : %d", m_bossAnimOne[5]);
	DrawFormatString(100, 860, 0xffffff, "anim6 : %d", m_bossAnimOne[6]);
	DrawFormatString(100, 920, 0xffffff, "anim7 : %d", m_bossAnimOne[7]);
	DrawFormatString(100, 980, 0xffffff, "anim8 : %d", m_bossAnimOne[8]);

#endif

	//3Dモデルポジション設定
	MV1SetPosition(m_bossModelHandle, m_pos);

	//3Dモデル描画
	MV1DrawModel(m_bossModelHandle);

	//3Dモデルの回転地をセットする
	MV1SetRotationXYZ(m_bossModelHandle, VGet(0.0f, m_angle, 0.0f));

	//攻撃された時のエフェクトのポジション
	SetPosPlayingEffekseer3DEffect(m_effectHit, m_pos.x, m_pos.y + 70.0f, m_pos.z);

	//エフェクトの描画
	//effect->Draw();
}

void BossEnemy::End()
{
	//メモリ解放
	effect->End();
}

bool BossEnemy::isSphereHit(const SphereCol& col, float damage, Effect& ef)
{
	bool isHit = m_capsuleCol.IsHitSphere(col);

	//ダメージを受けた判定
	if (isHit)
	{
		m_color = 0xffff00;

		//ダメージを一回だけ与える
		if (m_damageReceived == false)
		{
			m_effectHit = PlayEffekseer3DEffect(ef.GetHitEffect());

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

	MATRIX mts = MGetRotY(D2R(m_bounceAngle));

	//プレイヤーと当たった時
	if (isHit)
	{
		m_color = 0xffff00;

		m_outPush = VScale(vec, 0.1f);

		m_outPush = VTransform(m_outPush, mts);
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
	bool isHit = m_bossColDistance.IsHitCapsule(col);

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
