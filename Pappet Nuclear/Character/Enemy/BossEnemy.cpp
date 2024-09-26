#include "BossEnemy.h"
#include "Character/Player/Player.h"
#include "Map/Map.h"

namespace
{
	bool attack;    //攻撃SEの判定
	int walkTime;   //歩くSE間隔
	float difPSize;   //プレイヤーとの距離
	float difSSize;   //盾との距離
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
	m_playerHit(false)
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

	//if (m_bossAttack1 == true)
	//{
	//	m_playTime += 0.5f;
	//}
	//else if (m_bossAttack2 == true)
	//{
	//	m_playTime += 0.5f;
	//}
	//else
	//{
	//	m_playTime += 0.5f;
	//}

	//プレイヤーを押し出す方向算出
	float bounceX = m_pos.x - player.GetPosX();
	float bounceZ = m_pos.z - player.GetPosZ();

	m_bounceAngle = atan2f(bounceX, bounceZ);


	//ボスの部屋に入った
	if (map.GetRoomEntered() == true)
	{
		if (m_bossDistance == false || m_bossMoveAttackPattern == true)
		{

			float X = m_pos.x - player.GetPosX();
			float Z = m_pos.z - player.GetPosZ();

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
			if (m_playTime >= 25.0f)
			{
				if (m_effectActivation == false)
				{
					m_effect = PlayEffekseer3DEffect(effect->GetBossAttackEffect3());

					m_effectActivation = true;
				}

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
	//バグ修正用
	if (m_bossMoveAttack == true && m_bossAttack1 == false && m_bossAttack2 == false && m_bossAttack3 == false)
	{
		if (m_bossAnimation[4] != -1 || m_bossAnimation[5] != -1 || m_bossAnimation[6] != -1)
		{
			//アニメーションデタッチ
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[4]);
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[5]);
			MV1DetachAnim(m_bossModelHandle, m_bossAnimation[6]);

			m_bossAttack = -1;

			PlaySoundMem(se->GetBossVoiceSE(), DX_PLAYTYPE_BACK, true);

			//アニメーションアタッチ
			m_bossAnimation[0] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimStand, TRUE);

			m_playTime = 0.0f;

			m_bossAnimation[4] = -1;
			m_bossAnimation[5] = -1;
			m_bossAnimation[6] = -1;
		}
	}


	//再生時間がアニメーションの総再生時間に達したら再生時間を0に戻す
	if (time >= m_bossTotalAnimTime[0] && m_bossAnimation[0] != -1)
	{
		m_bossMoveAttack = false;

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

		attack = false;

		time = 0.0f;
	}
	if (time >= m_bossTotalAnimTime[5] && m_bossAnimation[5] != -1)
	{
		m_bossMoveAttack = false;

		m_bossAttack2 = false;

		attack = false;

		time = 0.0f;
	}
	if (time >= m_bossTotalAnimTime[6] && m_bossAnimation[6] != -1)
	{
		m_bossMoveAttack = false;

		m_bossAttack3 = false;

		m_effectActivation = false;

		attack = false;

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

	//敵が生きている時は描画
	if (m_hp > 0.0f)
	{
		DrawCapsule3D(pos1.GetVector(), pos2.GetVector(), m_capsuleRadius, 16, m_color, 0, false);

		////攻撃の範囲描画
		//DrawSphere3D(m_colPos.GetVector(), m_sphereRadius, 16, m_distanceColor, m_distanceColor, false);

		//攻撃判定描画
		DrawSphere3D(m_colBossAttackPos1.GetVector(), m_bossAttackRadius1, 16, 0xffffff, 0xffffff, false);
		DrawSphere3D(m_colBossAttackPos2.GetVector(), m_bossAttackRadius2, 16, 0xffffff, 0xffffff, false);
		DrawSphere3D(m_colBossAttackPos3.GetVector(), m_bossAttackRadius3, 16, 0xffffff, 0xffffff, false);
	}

	//DrawFormatString(0, 120, 0xffffff, "m_moveAttack1 : %d", m_bossAttack1);
	//DrawFormatString(0, 140, 0xffffff, "m_moveAttack1 : %d", m_bossAttack2);
	//DrawFormatString(0, 160, 0xffffff, "m_moveAttack1 : %d", m_bossAttack3);
	//DrawFormatString(0, 180, 0xffffff, "m_BossAttack : %d", m_bossAttack);
	//DrawFormatString(0, 400, 0xffffff, "m_Attack : %f", m_attack);

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
