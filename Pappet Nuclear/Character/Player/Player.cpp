#include "Player.h"
#include "Map/Map.h"
#include "Character/Player/Item/ItemManager.h"
#include "Character/Effect/Effect.h"
#include "UI/Setting.h"
#include<math.h>

namespace
{
	int walkTime;       //歩くSEを再生させる時間
	int dashTime;       //走るSEを再生させる時間
	bool attack;        //攻撃SEを再生させる時
	int a;
	float angleShield;   //盾を構えた時少しのずれを直す変数

	float anX;         //アナログスティックを格納する変数
	float anY;         //アナログスティックを格納する変数

	MATRIX AvoidancePos;    //回避したときのポジション

	int Button;        //一回だけ入力するための変数

	//シングルトン
	auto& handle = HandleManager::GetInstance();
	auto& effect = Effect::GetInstance();
}

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player():
	CharacterBase(Collidable::Priority::High, ObjectTag::Player),
	m_cameraAngle(0.0f),
	m_updatePosX(485.0f),
	m_updatePosY(0.0f),
	m_updatePosZ(-800.0f),
	m_lockAngle(0.0f),
	m_lockonTarget(false),
	m_moveAnimFrameIndex(0),
	m_moveAnimFrameRight(0),
	m_moveAnimFrameRigthPosition(VGet(0.0f,0.0f,0.0f)),
	m_moveAnimShieldFrameHandIndex(0),
	m_moveAnimShieldFrameIndex(0),
	m_a(0),
	m_pad(0),
	m_animRollAttack(-1),
	m_avoidance(false),
	m_nextAttack1(false),
	m_nextAttack2(false),
	m_pushButton(false),
	m_avoidanceNow(false),
	m_restAction(false),
	m_dashMove(false),
	m_staminaBroke(false),
	m_nowPos(VGet(0.0f,0.0f,0.0f)),
	m_bounceMove(VGet(0.0f,0.0f,0.0f)),
	m_coreAllLevel(0),
	m_hpLevel(0),
	m_staminaLevel(0),
	m_animHeel(0),
	m_recoveryNumber(0),
	m_recoberyAmount(0.0f),
	m_heel(0.0f),
	m_recoberyAction(false),
	m_effectHeel(0),
	m_effectOneHeel(false),
	m_a1(false),
	m_bug(false),
	m_menuOpen(false),
	m_button(0),
	m_one(false),
	m_bugTime(0),
	m_notWeapon(false),
	m_notShield(false),
	m_swordRadius(0.0f),
	m_fistCol(false),
	m_swordCol(false),
	m_targetRadius(0.0f),
	m_animShield(0),
	m_shield(false),
	m_shieldNow(false),
	m_rate(0.0f),
	m_oneShield(false),
	m_moveAnimFrameLeftPosition(VGet(0.0f,0.0f,0.0f)),
	m_animLeft(0),
	m_animRight(0),
	m_animShieldImpact(0),
	m_animShieldStand(0),
	m_animWeaponWalk(0),
	m_animWeaponLeftWalk(0),
	m_animWeaponRun(0),
	m_animTaking(0),
	m_animTouch(0),
	m_weaponMoveRight(false),
	m_hitImpact(false),
	m_weaponAnimOne(false),
	m_notWeaponAnimOne(false),
	m_oneAvoidance(false),
	m_hit(false),
	m_itemTaking(false),
	m_itemTakingNow(false),
	m_moveShieldFrameMatrix(),
	m_moveWeaponFrameMatrix(),
	m_xpad()
{
	for (int i = 0; i < ENEMY_NOW; i++)
	{
		m_targetNumber[i] = false;
	}

	//プレイヤーのカプセル型
	auto collider = Collidable::AddCollider(MyLibrary::CollidableData::Kind::Capsule, false);
	auto capsuleCol = dynamic_cast<MyLibrary::CollidableDataCapsule*>(collider.get());
	capsuleCol->m_len = 40.0f;
	capsuleCol->m_radius = 12.0f;
	capsuleCol->m_vec = MyLibrary::LibVec3(0.0f, m_vec.y + 2.0f, 0.0f);

	//レベルの初期化
	m_levelStatus.sl_hp = 1;
	m_levelStatus.sl_stamina = 1;
	m_levelStatus.sl_muscle = 1;
	m_levelStatus.sl_skill = 1;
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	//メモリ解放
	MV1DeleteModel(m_handle);
	MV1DeleteModel(m_animStand);
	MV1DeleteModel(m_animWalk);
	MV1DeleteModel(m_animRun);
	MV1DeleteModel(m_animRoll);
	MV1DeleteModel(m_animAttack1);
	MV1DeleteModel(m_animAttack2);
	MV1DeleteModel(m_animAttack3);
	MV1DeleteModel(m_animDeath);
	MV1DeleteModel(m_animHeel);
	MV1DeleteModel(m_animLeft);
	MV1DeleteModel(m_animRight);
	weapon->End();
	se->End();

	//メモリ削除
	handle.Clear();
}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Init()
{
	m_button = 0;
	m_one = false;
	m_oneAvoidance = false;

	//プレイヤーHPの初期化
	m_status.s_hp = 150.0f;
	m_status.s_hp = m_status.s_hp * m_levelStatus.sl_hp;

	//プレイヤーのスタミナ初期化
	m_status.s_stamina = 100.0f;
	m_status.s_stamina = m_status.s_stamina * m_levelStatus.sl_stamina;

	//プレイヤースピード初期化
	m_status.s_speed = 2.0f;

	//プレイヤーを押し出す距離
	m_bounceDis = 3.0f;

	//プレイヤーの攻撃力初期化
	m_status.s_attack = 10.0f;

	//プレイヤーのロックオン初期化
	m_lockonTarget = false;
	m_lockAngle = 0.0f;

	//回復関係の初期化
	m_recoberyAmount = 100.0f;
	m_heel = 0.0f;
	m_recoveryNumber = 5;
	m_recoberyAction = false;

	//アニメ関係の初期化
	m_hitImpact = false;
	m_weaponAnimOne = false;
	m_notWeaponAnimOne = false;
	m_itemTaking = false;
	m_itemTakingNow = false;

	//一回だけ初期化
	if (m_oneInit == false)
	{
		//武器初期化
		weapon->Init();

		//レベル初期化
		m_coreAllLevel = 0;
		m_hpLevel = 1;
		m_staminaLevel = 1;

		m_modelSize = 0.4f;

		//エフェクト読み込み
		effect.EffectLoad("Rest", "Data/Effect/Benediction.efkefc", 210, 10.0f);
		effect.EffectLoad("Heal", "Data/Effect/AnotherEffect/Sylph13.efkefc", 160, 20.0f);
		effect.EffectLoad("Imapct", "Data/Effect/HitEffect.efkefc", 30, 7.0f);

		//プレイヤーもモデル読み込み
		//m_handle = MV1LoadModel("Data/Player/PuppetPlayerModel.mv1");
		m_handle = handle.GetModelHandle("Data/Player/PuppetPlayerModel.mv1");

		//プレイヤーの大きさを変える
		MV1SetScale(m_handle, VGet(m_modelSize, m_modelSize, m_modelSize));

		//プレイヤーのアニメーション読み込み
		m_animStand = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimStand.mv1");
		m_animWalk = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimWalk.mv1");
		m_animRun = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimRun.mv1");
		m_animRoll = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimRoll.mv1");
		m_animAttack1 = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimAttack1.mv1");
		m_animAttack2 = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimAttack2.mv1");
		m_animAttack3 = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimAttack3.mv1");
		m_animRollAttack = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimRollAttack.mv1");
		m_animDeath = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimDeath.mv1");
		m_animHeel = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimRecovery.mv1");
		m_animHit = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimHit.mv1");
		m_animShield = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimShield.mv1");
		m_animShieldImpact = handle.GetModelHandle("Data/PlayerAnimation/WeaponAnim/PlayerAnimShieldImpact.mv1");
		m_animShieldStand = handle.GetModelHandle("Data/PlayerAnimation/WeaponAnim/PlayerAnimShieldStand.mv1");
		m_animWeaponWalk = handle.GetModelHandle("Data/PlayerAnimation/WeaponAnim/PlayerAnimWeaponWalk.mv1");
		m_animWeaponRun = handle.GetModelHandle("Data/PlayerAnimation/WeaponAnim/PlayerAnimWeaponRun.mv1");
		m_animLeft = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimLeftWalk.mv1");
		m_animRight = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimRightWalk.mv1");
		m_animWeaponLeftWalk = handle.GetModelHandle("Data/PlayerAnimation/WeaponAnim/PlayerAnimWeaponLeftWalk.mv1");
		m_animTaking = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimTaking.mv1");
		m_animTouch = handle.GetModelHandle("Data/PlayerAnimation/PlayerAnimTouch.mv1");

		//アニメーションアタッチ
		m_animation[0] = MV1AttachAnim(m_handle, 1, m_animStand, TRUE);
		m_animation[1] = MV1AttachAnim(m_handle, 1, m_animWalk, TRUE);
		m_animation[2] = MV1AttachAnim(m_handle, 1, m_animRun, TRUE);
		m_animation[3] = MV1AttachAnim(m_handle, 1, m_animRoll, TRUE);
		m_animation[4] = MV1AttachAnim(m_handle, 1, m_animAttack1, TRUE);
		m_animation[5] = MV1AttachAnim(m_handle, 1, m_animAttack2, TRUE);
		m_animation[6] = MV1AttachAnim(m_handle, 1, m_animAttack3, TRUE);
		m_animation[7] = MV1AttachAnim(m_handle, 1, m_animRollAttack, TRUE);
		m_animation[8] = MV1AttachAnim(m_handle, 1, m_animDeath, TRUE);
		m_animation[9] = MV1AttachAnim(m_handle, 1, m_animHeel, TRUE);
		m_animation[10] = MV1AttachAnim(m_handle, 1, m_animHit, TRUE);
		m_animation[11] = MV1AttachAnim(m_handle, 0, m_animShield, TRUE);
		m_animation[12] = MV1AttachAnim(m_handle, 0, m_animShieldImpact, TRUE);
		m_animation[13] = MV1AttachAnim(m_handle, 0, m_animShieldStand, TRUE);
		m_animation[14] = MV1AttachAnim(m_handle, 0, m_animWeaponWalk, TRUE);
		m_animation[15] = MV1AttachAnim(m_handle, 0, m_animWeaponRun, TRUE);
		m_animation[16] = MV1AttachAnim(m_handle, 0, m_animLeft, TRUE);
		m_animation[17] = MV1AttachAnim(m_handle, 0, m_animRight, TRUE);
		m_animation[18] = MV1AttachAnim(m_handle, 0, m_animWeaponLeftWalk, TRUE);
		m_animation[19] = MV1AttachAnim(m_handle, 1, m_animTaking, TRUE);
		m_animation[20] = MV1AttachAnim(m_handle, 0, m_animTouch, TRUE);


		//アタッチしたアニメーションの総再生時間を取得する
		for (int i = 0; i < 21; i++)
		{
			m_totalAnimTime[i] = MV1GetAttachAnimTotalTime(m_handle, m_animation[i]);

		}

		se->CharaInit();

		m_oneInit = true;
	}

	//アニメーションブレンド
	MV1SetAttachAnimBlendRate(m_handle, m_animation[0], 1.0f);

	for (int i = 1; i < 20; i++)
	{
		MV1SetAttachAnimBlendRate(m_handle, m_animation[i], 0.0f);
	}

	m_playTime = 0.0f;
	
	//当たり判定
	m_colPos = Pos3(m_pos.x - 2.0f, m_pos.y + 35.0f, m_pos.z);
	m_colAttackPos = Pos3(m_pos.x - 50.0f, m_pos.y + 35.0f, m_pos.z);
	m_initializationPos = Pos3(0.0f, -1000.0f, 0.0f);
	m_targetColPos = Pos3(m_pos.x, m_pos.y + 35.0f, m_pos.z);
	m_rectPos = Pos3(m_pos.x - 50.0f, m_pos.y + 35.0f, m_pos.z);
	m_rectSize = Size(20.0f, 60.0f, 10.0f);
	m_vec = Vec3(0.0f, m_vec.y + 2.0f, 0.0f);
	m_len = 40.0f;
	m_capsuleRadius = 12.0f;
	m_sphereRadius = 18.0f;
	m_swordRadius = 30.0f;
	m_targetRadius = 200.0f;
	m_capsuleCol.Init(m_colPos, m_vec, m_len, m_capsuleRadius);
	m_sphereCol.Init(m_colAttackPos, m_sphereRadius);
	m_targetCunCol.Init(m_targetColPos, m_targetRadius);
	m_rectCol.Init(m_rectPos, m_rectSize);

	m_posX = m_updatePosX;
	m_posY = m_updatePosY;
	m_posZ = m_updatePosZ;

	//プレイヤーのポジション設定
	m_pos = VGet(m_posX, m_posY, m_posZ);
	m_drawPos = m_pos;

	//死亡アニメーションが入っていたら
	if (m_animOne[8] == true)
	{
		//アニメーションブレンドを0にする
		MV1SetAttachAnimBlendRate(m_handle, m_animation[8], 0.0f);

		//アニメーションアタッチ
		MV1SetAttachAnimBlendRate(m_handle, m_animation[0], 1.0f);

		m_playTime = 0.0f;

		m_animOne[8] = false;
		m_animOne[0] = true;
	}

	m_bug = 0;

	m_avoidance = false;

	attack = false;

	m_effectOneHeel = false;

	m_death = false;

	m_hit = false;

	m_bug = false;

	m_shield = false;

	m_oneShield = false;

	Button = 0;

	m_animOne[0] = true;

	for (int i = 1; i < 20; i++)
	{
		m_animOne[i] = false;
	}
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
	m_colPos = Pos3(m_pos.x - 2.0f, m_pos.y + 35.0f, m_pos.z);
	m_targetColPos = Pos3(m_pos.x, m_pos.y + 35.0f, m_pos.z);

	//初期化
	if (m_notWeapon == false)
	{
		if (m_fistCol == false && m_swordCol == false)
		{
			m_sphereCol.Init(m_colAttackPos, m_sphereRadius);

			m_fistCol = true;
		}

		//素手の攻撃力
		m_status.s_attack = 10.0f;
		m_status.s_attack = m_status.s_attack + (m_status.s_attack * (m_levelStatus.sl_muscle / 10));
	}

	//アニメーションで移動しているフレームの番号を検索する
	m_moveAnimFrameIndex = MV1SearchFrame(m_handle, "mixamorig:Hips");
	//m_moveAnimFrameIndex = MV1GetPosition(m_handle);
	m_moveAnimFrameRight = MV1SearchFrame(m_handle, "mixamorig:RightHandThumb2");

	//武器をアタッチするフレームのローカル→ワールド変換行列を取得する
	m_moveWeaponFrameMatrix = MV1GetFrameLocalWorldMatrix(m_handle, m_moveAnimFrameRight);

	//盾を構えるときのアニメーションのフレーム所得
	m_moveAnimShieldFrameIndex = MV1SearchFrame(m_handle, "mixamorig:LeftShoulder");
	m_moveAnimShieldFrameHandIndex = MV1SearchFrame(m_handle, "mixamorig:LeftHand");

	//武器をアタッチするフレームのローカル→ワールド変換行列を取得する
	m_moveShieldFrameMatrix = MV1GetFrameLocalWorldMatrix(m_handle, m_moveAnimShieldFrameHandIndex);


	//パッド入力所得
	m_pad = GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

	//アナログスティックを使って移動
	int analogX = 0;
	int analogY = 0;

	float SetAngleX = 0.0f;
	float SetAngleY = 0.0f;

	if (m_avoidance == false && m_moveAttack == false && m_recoberyAction == false &&
		m_hit == false && m_status.s_hp >= 0.0f && m_hitImpact == false && m_itemTakingNow == false)
	{
		GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);

		m_oneAvoidance = false;
	}

	//プレイヤーが回避する方向の前に最初に向いてる方向に回避をしてしまうためバグが発生している
	//プレイヤーが向いている方向じゃないと回避がバグる
	//↓が間違っているため修正
	//回避の移動先を入力するため
	if (m_avoidance == true && m_oneAvoidance == false)
	{
		GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);

		m_oneAvoidance = true;
	}

	//アナログスティックの入力を格納
	anX = analogX;
	anY = analogY;


	m_move = VGet(static_cast<float>(-analogX), 0.0f, static_cast<float>(analogY));  //ベクトルの長さ
	m_bounceMove = VGet(static_cast<float>(analogX), 0.0f, static_cast<float>(-analogY));  //ベクトルの長さ

	//ベクトルの長さを取得する
	float len = VSize(m_move);
	float bounceLen = VSize(m_bounceMove);
	//ベクトル長さを0.0～1.0の割合に変換する
	float rate = len / 1000.0f;
	float bounceRate = bounceLen / 1000.0f;

	//アナログスティック無効な範囲を除外する
	rate = (rate - 0.1f) / (0.8f - 0.1f);
	rate = min(rate, 1.0f);
	rate = max(rate, 0.0f);

	bounceRate = (bounceRate - 0.1f) / (0.8f - 0.1f);
	bounceRate = min(bounceRate, 1.0f);
	bounceRate = max(bounceRate, 0.0f);


	//速度が決定できるので移動ベクトルに反映する
	m_move = VNorm(m_move);
	float speed = m_status.s_speed * rate;

	m_move = VScale(m_move, speed);

	m_bounceMove = VNorm(m_bounceMove);
	float bounceDis = m_status.s_speed * bounceRate;

	m_bounceMove = VScale(m_bounceMove, bounceDis);

	//cameraの角度から
	//コントローラーによる移動方向を決定する
	MATRIX mtx = MGetRotY(m_cameraAngle + DX_PI_F);
	m_move = VTransform(m_move, mtx);
	MATRIX reverseMtx = MGetRotY(m_cameraAngle + DX_PI_F);
	m_bounceMove = VTransform(m_bounceMove, reverseMtx);

	//移動方向からプレイヤーへの向く方向を決定する
	//移動していない場合(ゼロベクトル)の場合は変更しない
	if (VSquareSize(m_move) > 0.0f && m_moveAttack == false && m_recoberyAction == false &&
		m_hit == false && m_status.s_hp >= 0.0f && m_hitImpact == false && m_itemTakingNow == false)
	{
		//ロックオンしてない時と走った時のアングル
		if (m_lockonTarget == false || m_dashMove == true && m_avoidance == false)
		{
			//アングルを決定
			m_angle = atan2f(-m_move.z, m_move.x) - DX_PI_F / 2;
		}
		//ロックオンした時のアングル
		else if (m_lockonTarget == true && m_avoidance == false)
		{
			//アングルを決定
			m_angle = m_lockAngle;
			
		}
		else if (m_avoidance == true)
		{
			//アングルを決定
			m_angle = atan2f(-m_move.z, m_move.x) - DX_PI_F / 2;
		}
		


		//プレイヤーが動いたら
		m_moveflag = true;

		//SE
		//走っていなかったら
		if (m_dashMove == false)
		{
			walkTime++;

			if (walkTime >= 30)
			{
				walkTime = 0;
			}
			
			dashTime = 0;
		}
		//走ったら
		else if (m_dashMove == true)
		{
			dashTime++;

			if (dashTime >= 20)
			{
				dashTime = 0;
			}
			
			walkTime = 0;
		}
	}
	//プレイヤーが動いてなかったら
	else if (VSquareSize(m_move) <= 0.0f)
	{
		m_moveflag = false;

		walkTime = 0;
		dashTime = 0;
	}

	//プレイヤーが生きている時だけ
	if (m_status.s_hp > 0.0f)
	{
		m_pos = VAdd(m_pos, m_move);

		m_targetCunCol.Update(m_targetColPos);

		//メニューが開かれてたら行動できない
		if (m_menuOpen == false)
		{
			Action();
		}
		
	}


	//武器を持ってない時
	if (m_notWeapon == false)
	{
		//攻撃の当たり判定をプレイヤーの正面に持ってくる
		m_colAttackPos.x = m_pos.x + sinf(m_angle) * -25.0f;
		m_colAttackPos.z = m_pos.z - cosf(m_angle) * 25.0f;
	}
	
	m_rectPos.x = m_pos.x + sinf(m_angle) * -15.0f;
	m_rectPos.z = m_pos.z - cosf(m_angle) * 15.0f;


	//sinでX軸のwidthのサイズを出す
	if (sinf(m_angle) > 0)
	{
		m_rectSize.width = 30.0f + sinf(m_angle) * -15.0f;

	}
	else if (sinf(m_angle) < 0)
	{
		m_rectSize.width = 30.0f - sinf(m_angle) * -15.0f;
	}

	//cosでZ軸のdepthのサイズを出す
	if (cosf(m_angle) > 0)
	{
		m_rectSize.depth = 30.0f + cosf(m_angle) * -15.0f;

	}
	else if (cosf(m_angle) < 0)
	{
		m_rectSize.depth = 30.0f - cosf(m_angle) * -15.0f;

	}

	m_rectCol.Update(m_rectPos, m_rectSize);



	//アニメーション時間を進める前のアニメーションで移動をしているフレームの座標取得
	m_prevPos = MV1GetFramePosition(m_handle, m_moveAnimFrameIndex);

	AvoidancePos = MV1GetFrameLocalWorldMatrix(m_handle, m_moveAnimFrameIndex);

	//アタッチするモデルのフレーム座標を取得する
	m_moveAnimFrameRigthPosition = MV1GetFramePosition(m_handle, m_moveAnimFrameRight);

	//攻撃していない時のアニメーション速度
	//ターゲットしてない時のアニメーション速度
	if(m_moveAttack == false && m_lockonTarget == false)
	{
		//再生時間を進める
		m_playTime += 0.5f;
	}
	//右に歩かせる
	else if (m_lockonTarget == true && m_weaponMoveRight == true)
	{
		//再生時間を進める
		m_playTime -= 0.5f;
	}
	//後ろ歩き
	else if (m_lockonTarget == true && m_dashMove == false && anY > 0 && anX < 500 && anX > -500)
	{
		//再生時間を進める
		m_playTime -= 0.5f;
	}
	else
	{
		if (m_moveAttack == false)
		{
			//再生時間を進める
			m_playTime += 0.5f;
		}
		
	}


	//Aボタンが押されたら
	//メニューが開かれてたら行動できない
	if (m_menuOpen == false)
	{
		if (m_xpad.Buttons[12] == 1 && m_staminaBroke == false && m_recoberyAction == false &&
			m_moveAttack == false && m_hit == false && m_hitImpact == false)
		{
			if (m_a > 50 && m_status.s_stamina >= 0.1f)
			{
				m_avoidance = false;

				//ダッシュ中
				m_dashMove = true;

				m_status.s_speed = 3.0f;

				//スタミナ消費
				m_status.s_stamina -= 0.1f;
			}
			//回避する
			else if (m_status.s_stamina >= 10.0f && m_avoidance == false)
			{
				m_playTime = 0.0f;

				m_status.s_stamina = m_status.s_stamina - 10.0f;

				m_avoidance = true;
			}

			if (m_a < 51)
			{
				m_a++;
			}
		}
		else
		{
			m_dashMove = false;

			m_status.s_speed = 2.0f;

			m_a = 0;
		}
	}
	


	//回避や攻撃していない時に座標を入れる
	if (m_avoidance == false && m_moveAttack == false)
	{
		m_drawPos = m_pos;
	}
	//回避行動中
	if (m_playTime <= m_totalAnimTime[3] && m_avoidance == true)
	{
		//フレーム回避
		if (m_playTime >= 0.0f && m_playTime <= 20.0f)
		{
			m_avoidanceNow = true;
		}
		else
		{
			m_avoidanceNow = false;
		}
	}
	if (m_playTime >= m_totalAnimTime[3] && m_animOne[3] == true)
	{
		m_drawPos = m_pos;

		m_avoidance = false;

	}

	//攻撃が当たった時モーションや判定を初期化する
	if (m_hit == true && m_hitImpact == false)
	{
		m_drawPos = m_pos;
		m_avoidance = false;
		m_moveAttack = false;
		m_recoberyAction = false;
	}

	//スタミナ切れ
	if (m_status.s_stamina <= 0.1f)
	{
		m_staminaBroke = true;
	}
	//動けるようになる
	else if (m_status.s_stamina >= 20.0f)
	{
		m_staminaBroke = false;
	}
	//スタミナ回復
	if (m_dashMove == false && m_moveAttack == false && m_avoidance == false)
	{
		if (m_shieldNow == true)
		{
			if (m_status.s_stamina <= 100.0f)
			{
				m_status.s_stamina += 0.1f;
			}
		}
		else
		{
			if (m_status.s_stamina <= 100.0f)
			{
				m_status.s_stamina += 0.3f;
			}
		}
		
	}

	//武器を持ってない時のアニメーション
	if (m_notWeapon == false && m_notShield == false)
	{
		NotWeaponAnimation(m_playTime);
	}

	Animation(m_playTime, m_pos);

	//武器を持った時のアニメーション
	if (m_notWeapon == true || m_notShield == true)
	{
		WeaponAnimation(m_playTime);
	}

	m_capsuleCol.Update(m_colPos, m_vec);

	//マップとの当たり判定用
	m_mapHitColl = VGet(m_colPos.x, m_colPos.y, m_colPos.z);

	//メニューを開く
	if (m_xpad.Buttons[4] == 1)
	{
		m_menuOpen = true;
	}
}

/// <summary>
/// 武器を持った時の更新処理
/// </summary>
/// <param name="eq">装備クラスを返す</param>
void Player::WeaponUpdate(Equipment& eq)
{

	//右手装備
	//剣を持った時
	if (eq.GetSword() == true)
	{
		m_notWeapon = true;

		weapon->RightUpdate(m_moveWeaponFrameMatrix);


		//一回だけ初期化
		if (m_swordCol == false)
		{
			m_sphereCol.Init(m_initializationPos, m_swordRadius);

			//剣の攻撃力
			m_status.s_attack = 30.0f;
			m_status.s_attack = m_status.s_attack + (m_status.s_attack * (m_levelStatus.sl_muscle / 10) + (m_levelStatus.sl_skill / 10));

			m_swordCol = true;
		}

		//攻撃の当たり判定をプレイヤーの正面に持ってくる
		m_colAttackPos.x = m_pos.x + sinf(m_angle) * -35.0f;
		m_colAttackPos.z = m_pos.z - cosf(m_angle) * 35.0f;


		if (m_swordCol == true)
		{
			m_fistCol = false;
		}
	}
	else
	{
		m_notWeapon = false;

		m_swordCol = false;
	}


	//左手装備
	//盾を持った時
	if (eq.GetShield() == true)
	{
		m_notShield = true;

		weapon->LeftUpdate(m_moveShieldFrameMatrix);
	}
	else
	{
		m_notShield = false;
	}

	//盾を持った上で盾を構えた時
	if (eq.GetShield() == true && m_shield == true)
	{
		m_shieldNow = true;
	}
	else
	{
		m_shieldNow = false;
	}

}

/// <summary>
/// プレイヤーのSEの音量を変える
/// </summary>
/// <param name="volume">音量</param>
void Player::PlaySE(int volume)
{
	se->Update(volume);
}

/// <summary>
/// 他のキャラクターなどの影響を受ける
/// </summary>
/// <param name="outpush">エネミーがプレイヤーを押し出す距離</param>
/// <param name="weakoutpush">ボスがプレイヤーを押し出す距離</param>
void Player::OtherInfluence(VECTOR outpush, VECTOR weakoutpush)
{
	//他のキャラクターなどの影響を受ける
	m_pos = VAdd(m_pos, outpush);
	m_pos = VAdd(m_pos, weakoutpush);
}

/// <summary>
/// プレイヤーの行動に関する実装をまとめる関数
/// </summary>
void Player::Action()
{	
	//一段階目の攻撃
	if (m_status.s_hp > 0.0f)
	{
		//Rボタンで攻撃
		//一回だけ反応するようにする
		if (m_xpad.Buttons[9] == 1)
		{
			Button++;

			if (Button == 1)
			{
				if (m_staminaBroke == false && m_recoberyAction == false && m_avoidance == false &&
					m_hit == false && m_hitImpact == false)
				{
					if (m_attackNumber == 0 && m_status.s_stamina >= 10.0f)
					{
						//スタミナ消費
						m_status.s_stamina = m_status.s_stamina - 10.0f;

						m_attackNumber = 1;

						m_moveAttack = true;
					}
					else if (m_nextAttack1 == true && m_status.s_stamina >= 10.0f)
					{
						//スタミナ消費
						m_status.s_stamina = m_status.s_stamina - 10.0f;

						m_attackNumber = 2;

						m_moveAttack = true;
					}
					else if (m_nextAttack2 == true && m_status.s_stamina >= 10.0f)
					{
						//スタミナ消費
						m_status.s_stamina = m_status.s_stamina - 10.0f;

						m_attackNumber = 3;

						m_moveAttack = true;
					}
				}
			}
			
		}
		else
		{
			Button = 0;
		}
		
	}
	

	//ZRボタンで必殺技
	if (m_xpad.RightTrigger)
	{
		//DrawFormatString(0, 10, 0xffffff, "強攻撃");
	}


	//行動中は防御できない
	if (m_moveAttack == false && m_avoidance == false && m_staminaBroke == false)
	{
		//Lボタンで防御
		if (m_xpad.Buttons[8] == 1)
		{
			DrawFormatString(0, 10, 0xffffff, "防御");

			m_shield = true;

		}
		else
		{
			m_shield = false;

			m_oneShield = false;

			m_rate = 0.0f;
		}
		
	}
	else
	{
		m_shield = false;

		m_oneShield = false;

		m_rate = 0.0f;
	}

	//攻撃時のアニメーションを速くする
	if (m_moveAttack == true)
	{
		//攻撃１段階目
		if (m_animOne[4] == true)
		{
			if (m_playTime >= 15 && m_playTime < 30.0f)
			{
				m_playTime += 0.9f;

				//攻撃の当たり判定発生
				if (m_playTime >= 25.0f && m_playTime <= 30.0f)
				{
					if (attack == false)
					{
						PlaySoundMem(se->GetAttackSE(), DX_PLAYTYPE_BACK, true);

						attack = true;
					}

					m_sphereCol.Update(m_colAttackPos);
				}
				
			}
			else if (m_playTime >= 30.0f)
			{
				m_playTime += 0.3f;

				//2段階目の攻撃準備
				m_nextAttack1 = true;

				//攻撃の当たり判定を初期化する
				attack = false;

				m_sphereCol.Update(m_initializationPos);
			}
			else
			{
				m_playTime += 0.5f;

				//攻撃の当たり判定を初期化する
				attack = false;

				m_sphereCol.Update(m_initializationPos);
			}
		}
		//攻撃２段階目
		else if (m_animOne[5] == true)
		{

			if (m_playTime >= 5.0f && m_playTime < 15.0f)
			{
				m_playTime += 0.9f;

				//攻撃の当たり判定発生
				if (m_playTime >= 10.0f && m_playTime <= 15.0f)
				{
					if (attack == false)
					{
						PlaySoundMem(se->GetAttackSE(), DX_PLAYTYPE_BACK, true);

						attack = true;
					}

					m_sphereCol.Update(m_colAttackPos);
				}
			}
			else if (m_playTime >= 15.0f)
			{
				m_playTime += 0.3f;

				//3段階目の攻撃準備
				m_nextAttack2 = true;

				attack = false;

				m_sphereCol.Update(m_initializationPos);
			}
			else
			{
				m_playTime += 0.5f;

				//攻撃の当たり判定を初期化する
				attack = false;

				m_sphereCol.Update(m_initializationPos);
			}
			
		}
		//攻撃３段階目
		else if (m_animOne[6] == true)
		{

			if (m_playTime >= 15.0f && m_playTime < 25.0f)
			{
				m_playTime += 0.9f;

				//攻撃の当たり判定発生
				if (m_playTime >= 20.0f && m_playTime <= 25.0f)
				{
					if (attack == false)
					{
						PlaySoundMem(se->GetAttackSE(), DX_PLAYTYPE_BACK, true);

						attack = true;
					}

					m_sphereCol.Update(m_colAttackPos);
				}
			}
			else
			{
				m_playTime += 0.7f;

				//攻撃の当たり判定を初期化する
				attack = false;

				m_sphereCol.Update(m_initializationPos);
			}

		}

	}

	if (m_moveAttack == false)
	{
		//次の攻撃段階の初期化
		m_attackNumber = 0;

		//攻撃準備初期化
		m_nextAttack1 = false;
		m_nextAttack2 = false;

	}


	//敵をロックオンする
	if (m_lockonTarget == false)
	{
		if (m_xpad.Buttons[7] == 1 && m_pushButton == true)
		{
			m_lockonTarget = true;
			m_pushButton = false;
		}
		else if (m_xpad.Buttons[7] == 0)
		{
			m_pushButton = true;
		}
	}
	else if (m_lockonTarget == true)
	{
		if (m_xpad.Buttons[7] == 1 && m_pushButton == true)
		{
			m_lockonTarget = false;
			m_pushButton = false;
		}
		else if (m_xpad.Buttons[7] == 0)
		{
			m_pushButton = true;
		}
	}

	//回復
	//Xボタンが押されたら
	if (m_xpad.Buttons[14] == 1)
	{
		if (m_moveAttack == false && m_avoidance == false)
		{
			//一回だけ実行
			if (m_effectOneHeel == false && m_recoveryNumber > 0)
			{
				effect.EffectCreate("Heal", m_pos);

				PlaySoundMem(se->GetHeelSE(), DX_PLAYTYPE_BACK, true);

				m_recoveryNumber--;

				m_effectOneHeel = true;
			}

			m_recoberyAction = true;
		}
		
	}
	else if(m_recoberyAction == false)
	{
		m_effectOneHeel = false;

		m_heel = 0.0f;
	}

	if (m_recoveryNumber >= 0 && m_recoberyAction == true && m_moveAttack == false && m_avoidance == false)
	{
		//HP回復
		if (m_status.s_hp < 150.0f && m_heel < 100.0f)
		{
			m_heel += 0.1f;

			m_status.s_hp = m_status.s_hp + m_heel;
		}

	}
}

/// <summary>
/// 武器を装備してない時のアニメーション関数
/// </summary>
/// <param name="time">アニメーションタイム</param>
void Player::NotWeaponAnimation(float& time)
{
	//武器を持ってる時のアニメーションブレンドを0にする一回だけ実行
	if (m_notWeaponAnimOne == false)
	{
		MV1SetAttachAnimBlendRate(m_handle, m_animation[12], 0.0f);
		MV1SetAttachAnimBlendRate(m_handle, m_animation[13], 0.0f);
		MV1SetAttachAnimBlendRate(m_handle, m_animation[14], 0.0f);
		MV1SetAttachAnimBlendRate(m_handle, m_animation[15], 0.0f);
		MV1SetAttachAnimBlendRate(m_handle, m_animation[18], 0.0f);

		m_animOne[12] = false;
		m_animOne[13] = false;
		m_animOne[14] = false;
		m_animOne[15] = false;
		m_animOne[18] = false;

		m_notWeaponAnimOne = true;
	}

	//武器を持った時用
	m_weaponAnimOne = false;

	//プレイヤーが生きている時
	if (m_status.s_hp >= 0.0f)
	{
		//怯んでないとき
		if (m_hit == false)
		{
			for (int i = 0; i < 20; i++)
			{
				//プレイヤーが動いたら
			    //Aボタン長押し
				if (m_dashMove == true && m_moveflag == true && m_avoidance == false &&
					m_moveAttack == false && m_recoberyAction == false && m_itemTakingNow == false)
				{

					if (i != 2 && i != 8)
					{
						pAnim->AnimationBlend(time, m_handle, m_animation[2], m_animation[i], m_animBlend, m_animOne[i], m_animOne[2], m_animBlendOne);
					}

				}
				//歩きアニメーション
				else if (m_moveflag == true && m_avoidance == false && m_moveAttack == false &&
					m_recoberyAction == false && m_itemTakingNow == false)
				{
					//ターゲットしてない時
					if (m_lockonTarget == false)
					{

						if (i != 1 && i != 8)
						{
							pAnim->AnimationBlend(time, m_handle, m_animation[1], m_animation[i], m_animBlend, m_animOne[i], m_animOne[1], m_animBlendOne);
						}
					}
					//ターゲットしている時
					else if (m_lockonTarget == true)
					{

						//Yが0より上が後ろ歩き
						//Yが0より下が前歩き
						//Xが0より上が右歩き
						//Xが0より下が左歩き

						//左歩き
						if (anX < -500)
						{
							if (i != 16 && i != 8)
							{
								pAnim->AnimationBlend(time, m_handle, m_animation[16], m_animation[i], m_animBlend, m_animOne[i], m_animOne[16], m_animBlendOne);
							}
						}
						//右歩き
						if (anX > 500)
						{
							if (i != 17 && i != 8)
							{
								pAnim->AnimationBlend(time, m_handle, m_animation[17], m_animation[i], m_animBlend, m_animOne[i], m_animOne[17], m_animBlendOne);
							}
						}
						//後ろ歩きor歩き
						if (anX < 500 && anX > -500)
						{

							if (i != 1 && i != 8)
							{
								pAnim->AnimationBlend(time, m_handle, m_animation[1], m_animation[i], m_animBlend, m_animOne[i], m_animOne[1], m_animBlendOne);
							}

						}
					}
				}
			}
		}
	}
}

/// <summary>
/// すべての状態の時に行うアニメーション関数
/// </summary>
/// <param name="time">アニメーションタイム</param>
/// <param name="pos">アニメーションによるポジション移動に使用する</param>
void Player::Animation(float& time, VECTOR& pos)
{
	if (m_animBlend < 1.0f)
	{
		m_animBlend += 0.5f;
	}

	for (int i = 0; i < 20; i++)
	{
		//プレイヤーが死んだ時
		if (m_status.s_hp <= 0.0f)
		{
			if (i != 8)
			{
				pAnim->AnimationBlend(time, m_handle, m_animation[8], m_animation[i], m_animBlend, m_animOne[i], m_animOne[8], m_animBlendOne);
			}

			m_weaponMoveRight = false;
		}
		//プレイヤーが生きていたら
		else if (m_status.s_hp > 0.0f)
		{

			//怯み
			if (m_hit == true)
			{
				if (i != 10 && i != 8)
				{
					pAnim->AnimationBlend(time, m_handle, m_animation[10], m_animation[i], m_animBlend, m_animOne[i], m_animOne[10], m_animBlendOne);
				}

			}
			else if (m_hit == false && m_hitImpact == false)
			{
				//プレイヤーが動いていないなら
				if (m_moveflag == false && m_avoidance == false && m_moveAttack == false &&
					m_recoberyAction == false && m_shieldNow == false && m_itemTakingNow == false)
				{
					if (i != 0 && i != 8)
					{
						pAnim->AnimationBlend(time, m_handle, m_animation[0], m_animation[i], m_animBlend, m_animOne[i], m_animOne[0], m_animBlendOne);
					}

				}
				//回避
				if (m_avoidance == true && m_moveAttack == false && m_recoberyAction == false &&
					m_itemTakingNow == false)
				{
					
					if (i != 3 && i != 8)
					{
						pAnim->AnimationBlend(time, m_handle, m_animation[3], m_animation[i], m_animBlend, m_animOne[i], m_animOne[3], m_animBlendOne);
					}

					m_weaponMoveRight = false;

				}
				if (m_avoidance == false && m_moveAttack == true && m_recoberyAction == false &&
					m_itemTakingNow == false)
				{
					//攻撃１段階目
					if (m_attackNumber == 1)
					{
						if (i != 4 && i != 5 && i != 6 && i != 8)
						{
							//一段階目の攻撃力
							m_status.s_attack = m_status.s_attack * 1.0f;

							pAnim->AnimationBlend(time, m_handle, m_animation[4], m_animation[i], m_animBlend, m_animOne[i], m_animOne[4], m_animBlendOne);
						}

						m_weaponMoveRight = false;

						m_moveAttackEnd = false;
					}
					//攻撃２段階目
					if (m_attackNumber == 2 && m_animOne[4] == true)
					{
						if (i == 4)
						{
							//2段階目の攻撃力
							m_status.s_attack = m_status.s_attack * 1.2f;

							pAnim->AnimationBlend(time, m_handle, m_animation[5], m_animation[i], m_animBlend, m_animOne[i], m_animOne[5], m_animBlendOne);
						}

						m_moveAttackEnd = false;
						
					}
					//攻撃３段階目
					if (m_attackNumber == 3 && m_animOne[5] == true)
					{

						if (i == 5)
						{
							//3段階目の攻撃力
							m_status.s_attack = m_status.s_attack * 1.5f;

							pAnim->AnimationBlend(time, m_handle, m_animation[6], m_animation[i], m_animBlend, m_animOne[i], m_animOne[6], m_animBlendOne);
						}

						m_moveAttackEnd = false;
					}

				}
				//プレイヤーが回復したとき
				if (m_recoberyAction == true && m_itemTakingNow == false)
				{
					
					for (int j = 3; j < 10; j++)
					{
						if (i != j)
						{
							pAnim->AnimationBlend(time, m_handle, m_animation[9], m_animation[i], m_animBlend, m_animOne[i], m_animOne[9], m_animBlendOne);
						}
					}

					m_weaponMoveRight = false;
				}
				//アイテム所得するとき
				if (m_recoberyAction == false && m_itemTaking == true)
				{
					if (i != 19 && i != 8 && i != 3 && i != 4 && i != 5 && i != 6 && i != 10 && i != 12 && i != 13)
					{
						pAnim->AnimationBlend(time, m_handle, m_animation[19], m_animation[i], m_animBlend, m_animOne[i], m_animOne[19], m_animBlendOne);

						m_itemTakingNow = true;
					}
				}

			}
		}


		if (i != 19)
		{
			//再生時間がアニメーションの総再生時間に達したら再生時間を0に戻す
			if (time >= m_totalAnimTime[i] && m_animOne[i] == true)
			{
				if (i != 8 && i != 10 && i != 3)
				{
					time = 0.0f;
				}
				else
				{
					if (i == 10)
					{
						m_hit = false;
					}
					if (i == 8)
					{
						m_death = true;

						time = 120.0f;
					}
				}

				if (i == 4 || i == 5 || i == 6)
				{
					m_drawPos = pos;

					//攻撃終了
					m_moveAttackEnd = true;

					m_moveAttack = false;
				}
				if (i == 9)
				{
					m_recoberyAction = false;
				}
				if (i == 12)
				{
					m_hitImpact = false;
				}
			}
			//後ろ歩き
			if (i == 1)
			{
				if (time < 0.0f && m_animOne[i] == true)
				{
					time = m_totalAnimTime[i];
				}
			}
			if (i == 14)
			{
				//武器を持った時の後ろ歩き
				if (time < 0.0f && m_animOne[i] == true)
				{
					time = m_totalAnimTime[14];
				}
			}
			if (i == 18)
			{
				//右歩き
				if (time < 0.0f && m_weaponMoveRight == true)
				{
					time = m_totalAnimTime[18];
				}
			}

		}
		else if (i == 19)
		{
			//アイテム所得タイム終了
			if (time >= m_totalAnimTime[i] / 2.5f && m_animOne[i] == true)
			{
				m_itemTakingNow = false;
			}
		}

		//再生時間をセットする
		if (m_animOne[i] == true)
		{
			MV1SetAttachAnimTime(m_handle, m_animation[i], time);

			//回避中じゃないとおかしくなる
			if (m_avoidance == true)
			{
				//アニメーションが経過中の座標取得
				m_nowPos = MV1GetFramePosition(m_handle, m_moveAnimFrameIndex);
				m_moveVector = VSub(m_nowPos, m_prevPos);

				pos.x += m_moveVector.x;
				pos.z += m_moveVector.z;
			}
			if (i == 4)
			{
				//アニメーションが経過中の座標取得
				m_nowPos = MV1GetFramePosition(m_handle, m_moveAnimFrameIndex);
				m_moveVector = VSub(m_nowPos, m_prevPos);

				pos.x += m_moveVector.x;
				pos.z += m_moveVector.z;
			}
			if (i == 5)
			{
				//アニメーションが経過中の座標取得
				m_nowPos = MV1GetFramePosition(m_handle, m_moveAnimFrameIndex);
				m_moveVector = VSub(m_nowPos, m_prevPos);

				pos.x += m_moveVector.x;
				pos.z += m_moveVector.z;

				//2段階目の攻撃準備終了
				m_nextAttack1 = false;
			}
			if (i == 6)
			{
				//アニメーションが経過中の座標取得
				m_nowPos = MV1GetFramePosition(m_handle, m_moveAnimFrameIndex);
				m_moveVector = VSub(m_nowPos, m_prevPos);

				pos.x += m_moveVector.x;
				pos.z += m_moveVector.z;

				//3段階目の攻撃準備終了
				m_nextAttack2 = false;
			}

			if (m_shieldNow == true && m_animOne[13] == false && m_animOne[12] == false)
			{

				if (i != 11)
				{
					MV1SetAttachAnimBlendRateToFrame(m_handle, m_animation[i], m_moveAnimShieldFrameIndex, 0.0f);
				}

				MV1SetAttachAnimBlendRateToFrame(m_handle, m_animation[11], m_moveAnimShieldFrameIndex, 1.0f);


				MV1SetAttachAnimTime(m_handle, m_animation[11], time);
			}

		}
		
	}
}

/// <summary>
/// 武器を装備した時のアニメーション関数
/// </summary>
/// <param name="time">アニメーションタイム</param>
void Player::WeaponAnimation(float& time)
{
	//武器を持ってない時のアニメーションブレンドを0にする
	if (m_weaponAnimOne == false)
	{
		//MV1SetAttachAnimBlendRate(m_handle, m_animation[0], 0.0f);
		MV1SetAttachAnimBlendRate(m_handle, m_animation[1], 0.0f);
		MV1SetAttachAnimBlendRate(m_handle, m_animation[2], 0.0f);
		MV1SetAttachAnimBlendRate(m_handle, m_animation[16], 0.0f);
		MV1SetAttachAnimBlendRate(m_handle, m_animation[17], 0.0f);

		m_animOne[1] = false;
		m_animOne[2] = false;
		m_animOne[16] = false;
		m_animOne[17] = false;

		m_weaponAnimOne = true;
	}

	//武器を持ってない時用
	m_notWeaponAnimOne = false;

	//プレイヤーが生きている時
	if (m_status.s_hp >= 0.0f)
	{
		for (int i = 0; i < 20; i++)
		{
			//盾受けしたとき
			if (m_hitImpact == true)
			{

				if (i != 12 && i != 8 && i != 10)
				{
					pAnim->AnimationBlend(time, m_handle, m_animation[12], m_animation[i], m_animBlend, m_animOne[i], m_animOne[12], m_animBlendOne);
				}

				m_weaponMoveRight = false;

			}
			//怯んでないとき盾受けしてない時
			if (m_hit == false && m_hitImpact == false)
			{
				//盾を構えて立ってる時
				if (m_moveflag == false && m_avoidance == false && m_moveAttack == false &&
					m_recoberyAction == false && m_shieldNow == true && m_itemTakingNow == false)
				{

					if (i != 13 && i != 8)
					{
						pAnim->AnimationBlend(time, m_handle, m_animation[13], m_animation[i], m_animBlend, m_animOne[i], m_animOne[13], m_animBlendOne);
					}

					angleShield = 0.1f;

					m_weaponMoveRight = false;
				}
				else
				{
					angleShield = 0.0f;
				}

				//プレイヤーが動いたら
				//Aボタン長押し
				if (m_dashMove == true && m_moveflag == true && m_avoidance == false &&
					m_moveAttack == false && m_recoberyAction == false && m_itemTakingNow == false)
				{
					//ここがバグ

					if (i != 15 && i != 8)
					{
						pAnim->AnimationBlend(time, m_handle, m_animation[15], m_animation[i], m_animBlend, m_animOne[i], m_animOne[15], m_animBlendOne);
					}

					m_weaponMoveRight = false;

				}
				//歩きアニメーション
				else if (m_moveflag == true && m_avoidance == false && m_moveAttack == false && 
					m_recoberyAction == false && m_itemTakingNow == false)
				{
					//ターゲットしてない時
					if (m_lockonTarget == false)
					{
						if (i != 14 && i != 8)
						{
							pAnim->AnimationBlend(time, m_handle, m_animation[14], m_animation[i], m_animBlend, m_animOne[i], m_animOne[14], m_animBlendOne);
						}
					}
					//ターゲットしてる時
					else if (m_lockonTarget == true)
					{
						//左歩きor右歩き
						if (anX < -500 || anX > 500)
						{
							if (i != 18 && i != 8)
							{
								pAnim->AnimationBlend(time, m_handle, m_animation[18], m_animation[i], m_animBlend, m_animOne[i], m_animOne[18], m_animBlendOne);
							}

							//左歩き
							if (anX < -500)
							{
								m_weaponMoveRight = false;
							}
							//右歩き
							if (anX > 500)
							{
								m_weaponMoveRight = true;
							}
						}

						//歩き
						if (anX < 500 && anX > -500)
						{
							
							if (i != 14 && i != 8)
							{
								pAnim->AnimationBlend(time, m_handle, m_animation[14], m_animation[i], m_animBlend, m_animOne[i], m_animOne[14], m_animBlendOne);
							}

							m_weaponMoveRight = false;
						}

					}

				}
				//防御
				if (m_shieldNow == true && m_animOne[13] == false)
				{
					if (m_oneShield == false)
					{

						m_oneShield = true;
					}
				}
				else
				{

					MV1SetAttachAnimBlendRateToFrame(m_handle, m_animation[11], m_moveAnimShieldFrameIndex, 0.0f);

					if (m_animOne[i] == true)
					{
						if (i != 11)
						{
							MV1SetAttachAnimBlendRateToFrame(m_handle, m_animation[i], m_moveAnimShieldFrameIndex, 1.0f);
						}
					}
					
				}
			}
		}
	}

}

/// <summary>
/// マップの当たり判定
/// </summary>
/// <param name="map">マップ呼び出し</param>
/// <param name="item">アイテム呼び出し</param>
void Player::HitObj(Map& map, ItemManager& item)
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
					m_pos = VAdd(m_pos, VScale(m_Poly->Normal, m_status.s_speed / 2));

					//回避行動だった場合
					if (m_avoidance == true)
					{
						//当たっていたら規定距離分プレイヤーを法線方向に移動させる
						m_drawPos = VAdd(m_drawPos, VScale(m_Poly->Normal, m_bounceDis));
						m_pos = VAdd(m_pos, VScale(m_Poly->Normal, m_status.s_speed));
					}
					//攻撃中だった場合
					if (m_moveAttack == true)
					{
						//当たっていたら規定距離分プレイヤーを法線方向に移動させる
						m_drawPos = VAdd(m_drawPos, VScale(m_Poly->Normal, m_bounceDis));
						m_pos = VAdd(m_pos, VScale(m_Poly->Normal, m_status.s_speed));

					}

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

	MapAction(map, item);

	//検出したプレイヤーの周囲のポリゴン情報を解放する
	MV1CollResultPolyDimTerminate(HitDim);

}

/// <summary>
/// マップのギミック管理
/// </summary>
/// <param name="map">マップを呼び出し</param>
/// <param name="item">アイテムを呼び出し</param>
void Player::MapAction(Map& map, ItemManager& item)
{

	//休息が可能だったら
	if (map.GetSavePossible() == true)
	{	
		//Yボタンが押されたら
		if (m_xpad.Buttons[15] == 1)
		{
			m_updatePosX = 95.0f;
			m_updatePosY = 0.0f;
			m_updatePosZ = -40.0f;

			//一回だけ実行
			if (m_effectActivation == false)
			{
				effect.EffectCreate("Rest", map.GetRestPos());

				PlaySoundMem(se->GetRestSE(), DX_PLAYTYPE_BACK, true);

				m_effectActivation = true;
			}

			m_restAction = true;
		}

	}
	else
	{
		m_effectActivation = false;
	}

	for (int i = 0; i < ITEM_NUMBER; i++)
	{
		//アイテムが所得可能だったら
		if (map.GetItem(i) == true)
		{
			//Yボタンが押されたら
			if (m_xpad.Buttons[15] == 1)
			{
				m_itemTaking = true;

				//アイテムを所得する(アイテムマネージャーに返す)
				item.SetGetItem(i, true);
				//所得したアイテムスポットを消す
				map.SetItemSpot(i, true);
			}
			else
			{
				m_itemTaking = false;
			}
		}
		
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{
	//方向ベクトル
	Vec3 vec = m_vec.GetNormalized() * m_len * 0.5f;

	Pos3 pos1 = m_colPos + vec;
	Pos3 pos2 = m_colPos - vec;

#if false

	float halfW = m_rectSize.width * 0.5f;
	float halfH = m_rectSize.height * 0.5f;
	float halfD = m_rectSize.depth * 0.5f;

	float right = m_rectPos.x + halfW;
	float left = m_rectPos.x - halfW;
	float top = m_rectPos.y + halfH;
	float bottom = m_rectPos.y - halfH;
	float front = m_rectPos.z - halfD;
	float back = m_rectPos.z + halfD;


	// 横の線
	DrawLine3D(VGet(left, bottom, front), VGet(right, bottom, front), m_rectColor);
	DrawLine3D(VGet(left, top, front), VGet(right, top, front), m_rectColor);
	DrawLine3D(VGet(left, bottom, back), VGet(right, bottom, back), m_rectColor);
	DrawLine3D(VGet(left, top, back), VGet(right, top, back), m_rectColor);
	// 縦の線
	DrawLine3D(VGet(left, top, front), VGet(left, bottom, front), m_rectColor);
	DrawLine3D(VGet(right, top, front), VGet(right, bottom, front), m_rectColor);
	DrawLine3D(VGet(left, top, back), VGet(left, bottom, back), m_rectColor);
	DrawLine3D(VGet(right, top, back), VGet(right, bottom, back), m_rectColor);
	// 前後の線
	DrawLine3D(VGet(left, top, front), VGet(left, top, back), m_rectColor);
	DrawLine3D(VGet(left, bottom, front), VGet(left, bottom, back), m_rectColor);
	DrawLine3D(VGet(right, top, front), VGet(right, top, back), m_rectColor);
	DrawLine3D(VGet(right, bottom, front), VGet(right, bottom, back), m_rectColor);
#endif

#if false

	//回避が跳ぶ理由はおそらくm_drawPosがおかしい

	//カプセル3Dの描画
	DrawCapsule3D(pos1.GetVector(), pos2.GetVector(), m_capsuleRadius, 16, m_color, 0, false);

	//円の3D描画
	if (m_fistCol == true)
	{
		DrawSphere3D(m_colAttackPos.GetVector(), m_sphereRadius, 16, 0xffffff, 0xffffff, false);
	}
	if (m_swordCol == true)
	{
		DrawSphere3D(m_colAttackPos.GetVector(), m_swordRadius, 16, 0xffffff, 0xffffff, false);

	}
	//DrawSphere3D(map->GetVectorMapPos(), 1500.0f, 16, 0xffffff, 0xffffff, false);

	DrawSphere3D(m_targetColPos.GetVector(), m_targetRadius, 16, 0xffffff, 0xffffff, false);

	//if (m_HitFlag == true)
	//{
	//	DrawFormatString(0, 100, 0xffffff, "壁に当たった");
	//}
	//if (m_restAction == true)
	//{
	//	DrawFormatString(0, 80, 0xffffff, "回復できる");
	//}

	////DrawFormatString(0, 120, 0xffffff, "HitPoly : %d", HitDim.HitNum);
	//DrawFormatString(0, 0, 0xffffff, "playTime : %f", m_playTime);
	////バグで攻撃状態になるがモーションが入らない
	//DrawFormatString(0, 200, 0xffffff, "m_stamina : %f", m_stamina);
	//DrawFormatString(200, 60, 0xffffff, "m_staminaBroke : %d", m_staminaBroke);
	//DrawFormatString(200, 100, 0xffffff, "m_hit : %d", m_a1);

	//DrawFormatString(200, 180, 0xffffff, "m_angle : %f", cosf(m_angle));
	//DrawFormatString(200, 180, 0xffffff, "m_recoberyAction : %d", m_recoberyAction);
	//DrawFormatString(200, 220, 0xffffff, "m_moveflag : %d", m_moveflag);
	//DrawFormatString(200, 260, 0xffffff, "m_avoidance : %d", m_avoidance);
	//DrawFormatString(200, 300, 0xffffff, "m_attack : %d", m_moveAttack);
	//DrawFormatString(200, 340, 0xffffff, "m_effect: %d", m_effectHit);

#endif

#if false

	//Yの1000が下-1000が上
	//Xの1000が右-1000が左

	DrawFormatString(0, 140, 0xffffff, "posX : %f posY : %f posZ : %f", m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 200, 0xffffff, "DrawposX : %f DrawposY : %f DrawposZ : %f", m_drawPos.x, m_drawPos.y, m_drawPos.z);

#endif

#if false

	DrawFormatString(0, 200, 0xffffff, "item : %d bool : %d", ItemNumber, m_itemTaking);

#endif

#if false
	DrawFormatString(200, 100, 0xffffff, "0 : %d", m_animOne[0]);
	DrawFormatString(200, 160, 0xffffff, "1 : %d", m_animOne[1]);
	DrawFormatString(200, 220, 0xffffff, "2 : %d", m_animOne[2]);
	DrawFormatString(200, 280, 0xffffff, "3 : %d", m_animOne[3]);
	DrawFormatString(200, 340, 0xffffff, "4 : %d", m_animOne[4]);
	DrawFormatString(200, 400, 0xffffff, "5 : %d", m_animOne[5]);
	DrawFormatString(200, 460, 0xffffff, "6 : %d", m_animOne[6]);
	DrawFormatString(200, 520, 0xffffff, "7 : %d", m_animOne[7]);
	DrawFormatString(200, 580, 0xffffff, "8 : %d", m_animOne[8]);
	DrawFormatString(200, 640, 0xffffff, "9 : %d", m_animOne[9]);
	DrawFormatString(200, 700, 0xffffff, "10 : %d", m_animOne[10]);
	DrawFormatString(200, 760, 0xffffff, "11 : %d", m_animOne[11]);
	DrawFormatString(200, 820, 0xffffff, "12 : %d", m_animOne[12]);
	DrawFormatString(200, 880, 0xffffff, "13 : %d", m_animOne[13]);
	DrawFormatString(200, 940, 0xffffff, "14 : %d", m_animOne[14]);
	DrawFormatString(500, 100, 0xffffff, "15 : %d", m_animOne[15]);
	DrawFormatString(500, 160, 0xffffff, "16 : %d", m_animOne[16]);
	DrawFormatString(500, 220, 0xffffff, "17 : %d", m_animOne[17]);
	DrawFormatString(500, 280, 0xffffff, "18 : %d", m_animOne[18]);
	DrawFormatString(500, 340, 0xffffff, "19 : %d", m_animOne[19]);
	DrawFormatString(500, 400, 0xffffff, "m_time : %f", m_playTime);
	DrawFormatString(500, 460, 0xffffff, "m_blend : %f", m_animBlend);

#endif


	//レベルを上げるための変数描画
	DrawFormatString(1400, 950, 0x000000, "%d", m_coreAllLevel);

	//3Dモデルのポジション設定
	MV1SetPosition(m_handle, m_drawPos);

	//3Dモデルの回転地をセットする
	MV1SetRotationXYZ(m_handle, VGet(0.0f, m_angle - angleShield, 0.0f));

	//3Dモデル描画
	MV1DrawModel(m_handle);
}

/// <summary>
/// 武器描画
/// </summary>
/// <param name="eq">装備呼び出し</param>
void Player::WeaponDraw(Equipment& eq)
{
	//剣を持った時
	if (eq.GetSword() == true)
	{
		weapon->RightDraw();
	}
	//盾を持った時
	if (eq.GetShield() == true)
	{
		weapon->LeftDraw();
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Player::End()
{
	//メモリ解放
	MV1DeleteModel(m_handle);
	MV1DeleteModel(m_animStand);
	MV1DeleteModel(m_animWalk);
	MV1DeleteModel(m_animRun);
	MV1DeleteModel(m_animRoll);
	MV1DeleteModel(m_animAttack1);
	MV1DeleteModel(m_animAttack2);
	MV1DeleteModel(m_animAttack3);
	MV1DeleteModel(m_animDeath);
	MV1DeleteModel(m_animHeel);
	MV1DeleteModel(m_animLeft);
	MV1DeleteModel(m_animRight);
	weapon->End();
	se->End();

	//メモリ削除
	handle.Clear();
}

void Player::OnCollideEnter(const std::shared_ptr<Collidable>& collidable)
{
#if _DEBUG
	std::string message = "プレイヤーが";
#endif
	auto tag = collidable->GetTag();
	switch (tag)
	{
	case ObjectTag::Enemy:
#if _DEBUG
		message += "敵";
#endif
		break;
	case ObjectTag::Attack:
#if _DEBUG
		message += "攻撃";
#endif
		break;
	case ObjectTag::Search:
#if _DEBUG
		message += "索敵";
#endif
		break;
	case ObjectTag::Item:
#if _DEBUG
		message += "アイテム";
#endif
		break;
	case ObjectTag::BossEnter:
#if _DEBUG
		message += "ボス部屋の入口";
#endif
		break;
	}

#if _DEBUG
	message += "と当たった\n";
	printfDx(message.c_str());
#endif
}

void Player::OnTriggerEnter(const std::shared_ptr<Collidable>& collidable)
{
#if _DEBUG
	std::string message = "プレイヤーが";
#endif
	auto tag = collidable->GetTag();
	switch (tag)
	{
	case ObjectTag::Enemy:
#if _DEBUG
		message += "敵";
#endif
		break;
	case ObjectTag::Attack:
	{
		//敵の攻撃が当たった時HPを減らす

	}
		break;
	case ObjectTag::Search:
	{
		//敵の索敵が当たった時
	}
		break;
	case ObjectTag::Item:
	{
		//アイテムが当たった時
	}
		break;
	case ObjectTag::BossEnter:
	{
		//ボスの部屋の入口に当たった時
	}
		break;
	}

#if _DEBUG
	message += "と当たった\n";
	printfDx(message.c_str());
#endif
}

/// <summary>
/// カプセル動詞の当たり判定
/// </summary>
/// <param name="col">カプセル型１</param>
/// <param name="col1">カプセル型2</param>
/// <returns></returns>
bool Player::IsCapsuleHit(const CapsuleCol& col, const CapsuleCol& col1)
{
	bool isHit = m_capsuleCol.IsHitCapsule(col);
	bool isHitBoss = m_capsuleCol.IsHitCapsule(col1);

	m_a1 = isHit;

	if (isHit)
	{
		m_color = 0xffff00;

		//当たっていたら規定距離分プレイヤーを法線方向に移動させる
		m_pos = VAdd(m_pos, VScale(m_bounceMove, m_status.s_speed / 2));

		//回避行動だった場合
		//m_posが動いている
		if (m_avoidance == true)
		{
			//当たっていたら規定距離分プレイヤーを法線方向に移動させる
			m_pos.x -= m_moveVector.x * 3.5f;
			m_pos.z -= m_moveVector.z * 3.5f;
			m_drawPos.x -= m_moveVector.x * 3.5f;
			m_drawPos.z -= m_moveVector.z * 3.5f;


		}
		//攻撃中だった場合
		else if (m_moveAttack == true)
		{
			//当たっていたら規定距離分プレイヤーを法線方向に移動させる
			m_pos.x -= m_moveVector.x * 3.5f;
			m_pos.z -= m_moveVector.z * 3.5f;
			m_drawPos.x -= m_moveVector.x * 3.5f;
			m_drawPos.z -= m_moveVector.z * 3.5f;
		}
	}
	else
	{
		m_color = 0xffffff;
	}

	if (isHitBoss)
	{
		//当たっていたら規定距離分プレイヤーを法線方向に移動させる
		m_pos = VAdd(m_pos, VScale(m_bounceMove, m_status.s_speed / 2));

		//回避行動だった場合
		//m_posが動いている
		if (m_avoidance == true)
		{
			//当たっていたら規定距離分プレイヤーを法線方向に移動させる
			m_pos.x -= m_moveVector.x * 1.2f;
			m_pos.z -= m_moveVector.z * 1.2f;
			m_drawPos.x -= m_moveVector.x * 1.2f;
			m_drawPos.z -= m_moveVector.z * 1.2f;


		}
		//攻撃中だった場合
		else if (m_moveAttack == true)
		{
			//当たっていたら規定距離分プレイヤーを法線方向に移動させる
			m_pos.x -= m_moveVector.x * 1.2f;
			m_pos.z -= m_moveVector.z * 1.2f;
			m_drawPos.x -= m_moveVector.x * 1.2f;
			m_drawPos.z -= m_moveVector.z * 1.2f;
		}
	}

	return isHit || isHitBoss;
}

/// <summary>
/// 敵の攻撃との当たり判定
/// </summary>
/// <param name="col">球体</param>
/// <param name="damage">ダメージ</param>
/// <returns></returns>
bool Player::isSphereHit(const SphereCol& col, float damage)
{
	bool isHit = m_capsuleCol.IsHitSphere(col);

	//雑魚敵の攻撃が入っている

	//ダメージを受けた判定
	if (isHit)
	{
		m_color = 0xffff00;

		//ダメージを一回だけ与える
		if (m_damageReceived == false)
		{
			PlaySoundMem(se->GetHitSE(), DX_PLAYTYPE_BACK, true);

			//回避中のフレームだとダメージを受けない
			if (m_avoidanceNow == false)
			{
				//m_effectHit = PlayEffekseer3DEffect(effect->GetHitEffect());
				//m_effectHit = PlayEffekseer3DEffect(ef.GetHitEffect());

				effect.EffectCreate("Imapct", VGet(m_pos.x, m_pos.y + 40.0f, m_pos.z));

				m_status.s_hp = m_status.s_hp - damage;

				m_hit = true;
			}

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

/// <summary>
/// ボス攻撃との当たり判定
/// </summary>
/// <param name="col1">球体１</param>
/// <param name="col2">球体２</param>
/// <param name="col3">球体３</param>
/// <param name="bossdamage">ダメージ</param>
/// <returns></returns>
bool Player::isBossSphereHit(const SphereCol& col1, const SphereCol& col2, const SphereCol& col3, float bossdamage)
{
	bool isBossAttackHit1 = m_capsuleCol.IsHitSphere(col1);
	bool isBossAttackHit2 = m_capsuleCol.IsHitSphere(col2);
	bool isBossAttackHit3 = m_capsuleCol.IsHitSphere(col3);

	if (isBossAttackHit1 || isBossAttackHit2 || isBossAttackHit3)
	{
		m_color = 0xffff00;

		//ダメージを一回だけ与える
		if (m_damageReceived == false)
		{
			PlaySoundMem(se->GetPlayerHitSE(), DX_PLAYTYPE_BACK, true);

			//回避中のフレームだとダメージを受けない
			if (m_avoidanceNow == false)
			{
				//m_effectHit = PlayEffekseer3DEffect(effect->GetHitEffect());
				//m_effectHit = PlayEffekseer3DEffect(ef.GetHitEffect());
				
				effect.EffectCreate("Imapct", VGet(m_pos.x, m_pos.y + 40.0f, m_pos.z));

				m_status.s_hp = m_status.s_hp - bossdamage;

				m_hit = true;
			}

			m_damageReceived = true;
		}
	}
	else
	{
		m_damageReceived = false;

		m_color = 0xffffff;
	}

	return isBossAttackHit1 || isBossAttackHit2 || isBossAttackHit3;
}

/// <summary>
/// 球体と矩形との当たり判定
/// </summary>
/// <param name="col">球体</param>
/// <param name="damage">ダメージ</param>
/// <returns></returns>
bool Player::isShieldHit(const SphereCol& col, float damage)
{
	bool isHit = m_rectCol.IsHitSphere(col);

	//ダメージを受けた判定
	if (isHit)
	{

		//盾を構えた時
		if (m_shieldNow == true)
		{
			m_rectColor = 0xffff00;

			//攻撃を一回だけ与える
			if (m_damageReceived == false)
			{
				m_status.s_stamina = m_status.s_stamina - damage * 1.2f;

				//スタミナを0以下にさせない
				if (m_status.s_stamina < 0.0f)
				{
					m_status.s_stamina = 0.0f;
				}

				//盾受け判定
				m_hitImpact = true;

				m_damageReceived = true;
			}
		}

	}
	else
	{
		//攻撃を受けてない時　　　　　
		if (m_hit == false)
		{
			m_damageReceived = false;
		}

		m_rectColor = 0xffffff;
	}

	return isHit;
}

/// <summary>
/// 球体と矩形との当たり判定
/// </summary>
/// <param name="col1">球体１</param>
/// <param name="col2">球体２</param>
/// <param name="col3">球体３</param>
/// <param name="bossdamage">ダメージ</param>
/// <returns></returns>
bool Player::isBossShieldHit(const SphereCol& col1, const SphereCol& col2, const SphereCol& col3, float bossdamage)
{
	bool isBossAttackHit1 = m_rectCol.IsHitSphere(col1);
	bool isBossAttackHit2 = m_rectCol.IsHitSphere(col2);
	bool isBossAttackHit3 = m_rectCol.IsHitSphere(col3);

	if (isBossAttackHit1 || isBossAttackHit2 || isBossAttackHit3)
	{
		//盾を構えた時
		if (m_shieldNow == true)
		{
			m_rectColor = 0xffff00;

			//攻撃を一回だけ与える
			if (m_damageReceived == false)
			{

				m_status.s_stamina = m_status.s_stamina - bossdamage * 1.2f;

				//スタミナを0以下にさせない
				if (m_status.s_stamina < 0.0f)
				{
					m_status.s_stamina = 0.0f;
				}

				//盾受け判定
				m_hitImpact = true;

				m_damageReceived = true;
			}
		}
	}
	else
	{
		//攻撃を受けてない時　　　　　
		if (m_hit == false)
		{
			m_damageReceived = false;
		}

		m_rectColor = 0xffffff;
	}

	return isBossAttackHit1 || isBossAttackHit2 || isBossAttackHit3;
}

/// <summary>
/// 球体とカプセルとの当たり判定
/// </summary>
/// <param name="col">カプセル型</param>
/// <param name="max">敵の最大数</param>
/// <returns></returns>
bool Player::isTargetHit(const CapsuleCol& col, int max)
{
	bool isHit = m_targetCunCol.IsHitCapsule(col);

	if (isHit)
	{
		//ターゲットできるようになる
		m_targetNumber[max] = true;
	}
	else
	{
		m_targetNumber[max] = false;
	}

	return isHit;
}
