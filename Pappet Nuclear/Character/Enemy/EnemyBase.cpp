#include "EnemyBase.h"
#include "WeakEnemy.h"
#include "BossEnemy.h"
#include "Object/AttackObject.h"
#include "Object/SearchObject.h"
#include "Character/Effect/Effect.h"


namespace
{
	//シングルトン
	auto& handle = HandleManager::GetInstance();
	auto& effect = Effect::GetInstance();
}

/// <summary>
/// コンストラクタ
/// </summary>
EnemyBase::EnemyBase(Priority priority):
	CharacterBase(priority, ObjectTag::Enemy),
	m_bossModelHandle(-1),
	m_core(0),
	m_bossSize(0.0f),
	m_searchRadius(0.0f),
	m_distanceRadius(0.0f),
	m_attackRadius(0.0f),
	m_enemyDeath(false)
{
	for (int i = 0; i < ENEMY_NOW; i++)
	{
		m_enemySearchFlag[i] = false;
		m_enemyWait[i] = false;
		m_randomAction[i] = 0;
		m_moveTurning[i] = 0.0f;
		m_moveReverseTurning[i] = 0.0f;
		m_randomNextActionTime[i] = 0.0f;
		m_weakAnimBlend[i] = 1.0f;

		for (int j = 0; j < ANIMATION; j++)
		{
			m_weakAnimOne[j][i] = false;
		}
	}

	m_bossAnimOne[0] = true;

	for (int i = 1; i < ANIMATION; i++)
	{
		if (i == 0)
		{
			m_bossAnimOne[0] = true;
		}
		else
		{
			m_bossAnimOne[i] = false;
		}
	}

	//敵のモデル読み込み
	m_handle = handle.GetModelHandle("Data/Enemy/EnemyModel.mv1");
	m_bossModelHandle = handle.GetModelHandle("Data/Enemy/BossEnemy.mv1");

	//敵のアニメーション読み込み
	m_animStand = handle.GetModelHandle("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyStand1.mv1");
	m_animWalk = handle.GetModelHandle("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyAnimWalking.mv1");
	m_animHit = handle.GetModelHandle("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyAnimHit.mv1");
	m_animDeath = handle.GetModelHandle("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyAnimDeath.mv1");
	m_animLeftWalking = handle.GetModelHandle("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyWalkingLeft.mv1");
	m_animRightWalking = handle.GetModelHandle("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyWalkingRight.mv1");
	m_animAttack1 = handle.GetModelHandle("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyAnimAttack1.mv1");
	m_bossAnimStand = handle.GetModelHandle("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimStand.mv1");
	m_bossAnimDeath = handle.GetModelHandle("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimDeath.mv1");
	m_bossAnimWalk = handle.GetModelHandle("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimWalk.mv1");
	m_bossAnimTurnRight = handle.GetModelHandle("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimRightTurn.mv1");
	m_bossAnimTurnLeft = handle.GetModelHandle("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimLeftTurn.mv1");
	m_bossAnimAttack1 = handle.GetModelHandle("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimAttack1.mv1");
	m_bossAnimAttack2 = handle.GetModelHandle("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimAttack2.mv1");
	m_bossAnimAttack3 = handle.GetModelHandle("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimAttack3.mv1");

	//アニメーションアタッチ
	m_bossAnimation[0] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimStand, TRUE);
	m_bossAnimation[1] = MV1AttachAnim(m_bossModelHandle, 0, m_bossModelHandle, TRUE);
	m_bossAnimation[2] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimDeath, TRUE);
	m_bossAnimation[3] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimWalk, TRUE);
	m_bossAnimation[4] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack1, TRUE);
	m_bossAnimation[5] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack2, TRUE);
	m_bossAnimation[6] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack3, TRUE);
	m_bossAnimation[7] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimTurnRight, TRUE);
	m_bossAnimation[8] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimTurnLeft, TRUE);

	//アタッチしたアニメーションの総再生時間を取得する
	for (int i = 0; i < 9; i++)
	{
		m_bossTotalAnimTime[i] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[i]);
	}


	//アニメーションブレンドを0にする
	for (int i = 0; i < 9; i++)
	{
		if (i == 0)
		{
			MV1SetAttachAnimBlendRate(m_bossModelHandle, m_bossAnimation[i], 1.0f);
		}
		else
		{
			MV1SetAttachAnimBlendRate(m_bossModelHandle, m_bossAnimation[i], 0.0f);
		}
	}

	//敵のサイズ変更
	m_modelSize = 0.4f;
	m_bossSize = 0.7f;
	MV1SetScale(m_bossModelHandle, VGet(m_bossSize, m_bossSize, m_bossSize));
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyBase::~EnemyBase()
{
	//メモリ解放
	MV1DeleteModel(m_handle);
	MV1DeleteModel(m_bossModelHandle);
	MV1DeleteModel(m_animStand);
	MV1DeleteModel(m_animHit);
	MV1DeleteModel(m_animDeath);
	MV1DeleteModel(m_animWalk);
	MV1DeleteModel(m_animLeftWalking);
	MV1DeleteModel(m_animRightWalking);
	MV1DeleteModel(m_animAttack1);
	MV1DeleteModel(m_bossAnimStand);
	MV1DeleteModel(m_bossAnimDeath);
	MV1DeleteModel(m_bossAnimWalk);
	MV1DeleteModel(m_bossAnimAttack1);
	MV1DeleteModel(m_bossAnimAttack2);
	MV1DeleteModel(m_bossAnimAttack3);
	MV1DeleteModel(m_bossAnimTurnRight);
	MV1DeleteModel(m_bossAnimTurnLeft);

	//メモリ削除
	handle.Clear();

}

void EnemyBase::Init(std::shared_ptr<MyLibrary::Physics> physics)
{
}

void EnemyBase::End(std::shared_ptr<MyLibrary::Physics> physics)
{
	Collidable::Finalize(physics);
	m_pAttack->Finalize(m_pPhysics);
	m_pSearch->Finalize(m_pPhysics);
}

bool EnemyBase::GetIsHit()
{
	bool log = m_isHit;
	m_isHit = false;
	return log;
}

/// <summary>
/// 他のオブジェクトと押し出し判定をする当たり判定を作成
/// </summary>
/// <param name="vec">ベクター</param>
/// <param name="len">長さ</param>
/// <param name="radius">半径</param>
void EnemyBase::InitCollision(MyLibrary::LibVec3 vec, float len, float radius)
{
	auto collider = Collidable::AddCollider(MyLibrary::CollidableData::Kind::Capsule, false);
	auto capsuleCol = dynamic_cast<MyLibrary::CollidableDataCapsule*>(collider.get());
	capsuleCol->m_vec = vec;
	capsuleCol->m_len = len;
	capsuleCol->m_radius = radius;
}

/// <summary>
/// モデルを読み込む
/// </summary>
/// <param name="name">モデルパス</param>
void EnemyBase::LoadModel(std::string name)
{
	m_handle = handle.GetModelHandle(name);
}

/// <summary>
/// 物理クラスの初期化
/// </summary>
/// <param name="isUseGravity">true重力を与えるfalse重力を与えない</param>
void EnemyBase::InitRigidbody(bool isUseGravity)
{
	rigidbody.Init(isUseGravity);
	//rigidbody.SetPos()
	rigidbody.SetNextPos(rigidbody.GetPos());
}

/// <summary>
/// モデルの中心座標を計算
/// </summary>
/// <param name="modeldefaultSize">モデルのもとのサイズ</param>
/// <param name="modelSize">モデルの拡大率</param>
void EnemyBase::CenterPos(float modeldefaultSize, float modelSize)
{
	m_centerPos = rigidbody.GetPos();
	m_centerPos.y += (modeldefaultSize * modelSize) / 2.0f;
}

/// <summary>
/// モデル座標を設定
/// </summary>
/// <param name="offset">差分</param>
void EnemyBase::SetModelPos(float offset)
{
	m_modelPos = m_collisionPos;
	m_modelPos.y -= offset;
}

/// <summary>
/// 索敵判定をする当たり判定を作成
/// </summary>
/// <param name="radius">半径</param>
void EnemyBase::InitSearch(float radius)
{
	m_pSearch = std::make_shared<SearchObject>(radius);
	m_pSearch->Init(m_pPhysics, m_modelPos, true);
}

/// <summary>
/// 攻撃判定をする当たり判定を作成
/// </summary>
/// <param name="radius">半径</param>
/// <param name="pos">ポジション</param>
void EnemyBase::InitAttack(float radius, MyLibrary::LibVec3 pos)
{
	m_pAttack = std::make_shared<AttackObject>(radius);
	m_pAttack->Init(m_pPhysics, pos, true);
}

/// <summary>
/// ダメージを受けた時
/// </summary>
/// <param name="damage"></param>
void EnemyBase::OnDamage(float damage)
{
	//HPを減らす
	m_status.s_hp -= damage - (m_status.s_defense / 10.0f);

	//敵の近くにエフェクトを表示
	auto pos = m_centerPos;
	effect.EffectCreate("Imapct", pos.ConversionToVECTOR());

}

/// <summary>
/// 死亡したとき
/// </summary>
void EnemyBase::Death()
{
	if (!m_death)
	{
		m_death = true;
		EnemyBase::Finalize(m_pPhysics);

		m_allCore += m_core;
	}
}
