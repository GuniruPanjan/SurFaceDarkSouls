#include "EnemyBase.h"

EnemyBase::EnemyBase():
	m_enemySearchFlag(false),
	m_enemyWait(false),
	m_enemyWaitseeRandom(0),
	m_randomAction(0),
	m_bossModelHandle(0),
	m_bossSize(0.0f),
	m_searchRadius(0.0f),
	m_distanceRadius(0.0f),
	m_moveTurning(0.0f),
	m_moveReverseTurning(0.0f),
	m_randomNextActionTime(0.0f),
	m_attackRadius(0.0f)
{
	//敵のモデル読み込み
	m_handle = MV1LoadModel("Data/Enemy/EnemyModel.mv1");
	m_bossModelHandle = MV1LoadModel("Data/Enemy/BossEnemy.mv1");

	//敵のアニメーション読み込み
	m_animStand = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyStand1.mv1");
	m_animWalk = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyAnimWalking.mv1");
	m_animHit = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyAnimHit.mv1");
	m_animDeath = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyAnimDeath.mv1");
	m_animLeftWalking = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyWalkingLeft.mv1");
	m_animRightWalking = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyWalkingRight.mv1");
	m_animAttack1 = MV1LoadModel("Data/EnemyAnimation/WeakEnemyAnimation/WeakEnemyAnimAttack1.mv1");
	m_bossAnimStand = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimStand.mv1");
	m_bossAnimDeath = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimDeath.mv1");
	m_bossAnimWalk = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimWalk.mv1");
	m_bossAnimAttack1 = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimAttack1.mv1");
	m_bossAnimAttack2 = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimAttack2.mv1");
	m_bossAnimAttack3 = MV1LoadModel("Data/EnemyAnimation/BossEnemyAnimation/BossEnemyAnimAttack3.mv1");

	//アニメーションアタッチ
	m_animation[0] = MV1AttachAnim(m_handle, 0, m_animStand, TRUE);
	m_animation[1] = MV1AttachAnim(m_handle, 0, m_animHit, TRUE);
	m_animation[2] = MV1AttachAnim(m_handle, 0, m_animDeath, TRUE);
	m_animation[3] = MV1AttachAnim(m_handle, 0, m_animWalk, TRUE);
	m_animation[4] = MV1AttachAnim(m_handle, 0, m_animLeftWalking, TRUE);
	m_animation[5] = MV1AttachAnim(m_handle, 0, m_animRightWalking, TRUE);
	m_animation[6] = MV1AttachAnim(m_handle, 0, m_animAttack1, TRUE);
	m_bossAnimation[0] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimStand, TRUE);
	m_bossAnimation[1] = MV1AttachAnim(m_bossModelHandle, 0, m_bossModelHandle, TRUE);
	m_bossAnimation[2] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimDeath, TRUE);
	m_bossAnimation[3] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimWalk, TRUE);
	m_bossAnimation[4] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack1, TRUE);
	m_bossAnimation[5] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack2, TRUE);
	m_bossAnimation[6] = MV1AttachAnim(m_bossModelHandle, 0, m_bossAnimAttack3, TRUE);

	//アタッチしたアニメーションの総再生時間を取得する
	m_totalAnimTime[0] = MV1GetAttachAnimTotalTime(m_handle, m_animation[0]);
	m_totalAnimTime[1] = MV1GetAttachAnimTotalTime(m_handle, m_animation[1]);
	m_totalAnimTime[2] = MV1GetAttachAnimTotalTime(m_handle, m_animation[2]);
	m_totalAnimTime[3] = MV1GetAttachAnimTotalTime(m_handle, m_animation[3]);
	m_totalAnimTime[4] = MV1GetAttachAnimTotalTime(m_handle, m_animation[4]);
	m_totalAnimTime[5] = MV1GetAttachAnimTotalTime(m_handle, m_animation[5]);
	m_totalAnimTime[6] = MV1GetAttachAnimTotalTime(m_handle, m_animation[6]);
	m_bossTotalAnimTime[0] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[0]);
	m_bossTotalAnimTime[1] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[1]);
	m_bossTotalAnimTime[2] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[2]);
	m_bossTotalAnimTime[3] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[3]);
	m_bossTotalAnimTime[4] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[4]);
	m_bossTotalAnimTime[5] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[5]);
	m_bossTotalAnimTime[6] = MV1GetAttachAnimTotalTime(m_bossModelHandle, m_bossAnimation[6]);



	//一旦待機以外のアニメーションをデタッチする
	MV1DetachAnim(m_handle, m_animation[1]);
	MV1DetachAnim(m_handle, m_animation[2]);
	MV1DetachAnim(m_handle, m_animation[3]);
	MV1DetachAnim(m_handle, m_animation[4]);
	MV1DetachAnim(m_handle, m_animation[5]);
	MV1DetachAnim(m_handle, m_animation[6]);
	m_animation[1] = -1;
	m_animation[2] = -1;
	m_animation[3] = -1;
	m_animation[4] = -1;
	m_animation[5] = -1;
	m_animation[6] = -1;
	MV1DetachAnim(m_bossModelHandle, m_bossAnimation[1]);
	MV1DetachAnim(m_bossModelHandle, m_bossAnimation[2]);
	MV1DetachAnim(m_bossModelHandle, m_bossAnimation[3]);
	MV1DetachAnim(m_bossModelHandle, m_bossAnimation[4]);
	MV1DetachAnim(m_bossModelHandle, m_bossAnimation[5]);
	MV1DetachAnim(m_bossModelHandle, m_bossAnimation[6]);
	m_bossAnimation[1] = -1;
	m_bossAnimation[2] = -1;
	m_bossAnimation[3] = -1;
	m_bossAnimation[4] = -1;
	m_bossAnimation[5] = -1;
	m_bossAnimation[6] = -1;


	//敵のサイズ変更
	m_modelSize = 0.4f;
	m_bossSize = 0.7f;
	MV1SetScale(m_handle, VGet(m_modelSize, m_modelSize, m_modelSize));
	MV1SetScale(m_bossModelHandle, VGet(m_bossSize, m_bossSize, m_bossSize));
}

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

}

void EnemyBase::End()
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

}
