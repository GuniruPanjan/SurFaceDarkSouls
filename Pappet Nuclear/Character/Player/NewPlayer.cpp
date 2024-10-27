#include "NewPlayer.h"
#include "External/CsvLoad.h"
#include "Object/RectObject.h"

namespace
{
	//モデルサイズ
	constexpr float cModelSizeScale = 0.4f;

	//アニメーションの切り替えにかかるフレーム数
	constexpr float cAnimChangeFrame = 5.0f;
	constexpr float cAnimChangeSpeed = 1.0f / cAnimChangeFrame;

	//アニメーションを変えるための方向を代入する
	int cAnX = 0;
	int cAnY = 0;

	//ボタンの長押し
	int cA;

	//アニメーションブレンド率の最大
	constexpr float cAnimBlendRateMax = 1.0f;

	//シングルトン
	auto& handle = HandleManager::GetInstance();
	auto& effect = Effect::GetInstance();
}

NewPlayer::NewPlayer() :
	CharacterBase(Collidable::Priority::High, ObjectTag::Player),
	m_xpad(),
	m_cameraAngle(0.0f),
	m_lockAngle(0.0f),
	m_recoveryNumber(0),
	m_heel(0.0f),
	m_recoberyAction(false),
	m_lockonTarget(false),
	m_moveAnimFrameIndex(0),
	m_moveAnimFrameRigthPosition(VGet(0.0f,0.0f,0.0f)),
	m_moveAnimShieldFrameIndex(0),
	m_moveAnimShieldFrameHandIndex(0),
	m_moveAnimFrameLeftPosition(VGet(0.0f,0.0f,0.0f)),
	m_moveWeaponFrameMatrix(),
	m_moveShieldFrameMatrix(),
	m_oneAvoidance(false),
	m_nextAttack1(false),
	m_nextAttack2(false),
	m_avoidance(false),
	m_avoidanceNow(false),
	m_restAction(false),
	m_dashMove(false),
	m_staminaBroke(false),
	m_menuOpen(false),
	m_notWeapon(true),
	m_notShield(true),
	m_fistCol(true),
	m_swordCol(false),
	m_hit(false),
	m_isDead(false),
	m_shield(false),
	m_itemTaking(false),
	m_itemTakingNow(false),
	m_nowPos(VGet(0.0f,0.0f,0.0f))
{
	//当たり判定設定
	auto collider = Collidable::AddCollider(MyLibrary::CollidableData::Kind::Capsule, false);
	auto capsuleCol = dynamic_cast<MyLibrary::CollidableDataCapsule*>(collider.get());
	capsuleCol->m_len = 40.0f;
	capsuleCol->m_radius = 12.0f;
	capsuleCol->m_vec = MyLibrary::LibVec3(0.0f, m_vec.y + 2.0f, 0.0f);

	//プレイヤーの判定
	InitHitBox(capsuleCol->m_radius, capsuleCol->m_len, capsuleCol->m_vec, false);
	//InitAttackBox(m_attackRadius, )

	//モデル読み込み
	m_handle = handle.GetModelHandle("Data/Player/PlayerModel.mv1");

	//モデルのサイズ設定
	MV1SetScale(m_handle, VGet(cModelSizeScale, cModelSizeScale, cModelSizeScale));

	//エフェクト読み込み
	effect.EffectLoad("Rest", "Data/Effect/Benediction.efkefc", 210, 10.0f);
	effect.EffectLoad("Heal", "Data/Effect/AnotherEffect/Sylph13.efkefc", 160, 20.0f);
	effect.EffectLoad("Imapct", "Data/Effect/HitEffect.efkefc", 30, 7.0f);

	//レベルの初期化
	m_levelStatus.sl_hp = 1;
	m_levelStatus.sl_stamina = 1;
	m_levelStatus.sl_muscle = 1;
	m_levelStatus.sl_skill = 1;

	CsvLoad::GetInstance().AnimDataLoad("Player", m_animIdx);
}

NewPlayer::~NewPlayer()
{
	//メモリ解放
	MV1DeleteModel(m_handle);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="physics">物理クラスのポインタ</param>
void NewPlayer::Init(std::shared_ptr<MyLibrary::Physics> physics)
{
	m_pPhysics = physics;

	Collidable::Init(m_pPhysics);


	//プレイヤーの初期位置設定
	rigidbody.Init(true);
	rigidbody.SetPos(MyLibrary::LibVec3(0.0f, 1.0f * cModelSizeScale, 0.0f));
	rigidbody.SetNextPos(rigidbody.GetPos());
	m_collisionPos = rigidbody.GetPos();
	SetModelPos();
	MV1SetPosition(m_handle, m_modelPos.ConversionToVECTOR());

	//待機アニメーションを設定
	m_nowAnimNo = MV1AttachAnim(m_handle, m_animIdx["Idle"]);
	m_nowAnimIdx = m_animIdx["Idle"];

	
}

void NewPlayer::Finalize()
{
	Collidable::Finalize(m_pPhysics);
}

void NewPlayer::Update(std::shared_ptr<Equipment> eq)
{
	//アニメーションで移動しているフレームの番号を検索する
	m_moveAnimFrameIndex = MV1SearchFrame(m_handle, "mixamorig:Hips");
	m_moveAnimFrameRight = MV1SearchFrame(m_handle, "mixamorig:RightHandThumb2");

	//武器をアタッチするフレームのローカル→ワールド変換行列を取得する
	m_moveWeaponFrameMatrix = MV1GetFrameLocalWorldMatrix(m_handle, m_moveAnimFrameRight);

	//盾を構えるときのアニメーションのフレーム取得
	m_moveAnimShieldFrameIndex = MV1SearchFrame(m_handle, "mixamorig:LeftShoulder");
	m_moveAnimShieldFrameHandIndex = MV1SearchFrame(m_handle, "mixamorig:LeftHand");

	//武器をアタッチするフレームのローカル→ワールド座標を取得する
	m_moveShieldFrameMatrix = MV1GetFrameLocalWorldMatrix(m_handle, m_moveAnimShieldFrameHandIndex);

	//パッド入力取得
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

	//アニメーションの更新
	if (!m_isDead)
	{
		//UpdateAnimation()
	}
	m_isAnimationFinish = UpdateAnimation(m_nowAnimNo);

	//アニメーションの切り替え
	if (m_prevAnimNo != -1)
	{
		//フレームでアニメーションを切り替える
		m_animBlendRate += cAnimChangeSpeed;
		if (m_animBlendRate >= cAnimBlendRateMax)
		{
			m_animBlendRate = cAnimBlendRateMax;
		}

		//アニメーションのブレンド率を設定する
		MV1SetAttachAnimBlendRate(m_handle, m_prevAnimNo, cAnimBlendRateMax - m_animBlendRate);
		MV1SetAttachAnimBlendRate(m_handle, m_nowAnimNo, m_animBlendRate);
	}

	//死んだ時のアニメーション
	if (m_status.s_hp <= 0)
	{
		if (!m_isDead)
		{
			m_isDead = true;

			m_nowAnimIdx = m_animIdx["Death"];
			ChangeAnimation(m_nowAnimIdx);

			Finalize();
		}
	}

	//座標を取得する
	m_collisionPos = rigidbody.GetPos();

	//アナログスティックを使って移動
	int analogX = 0;
	int analogY = 0;

	cAnX = analogX;
	cAnY = analogY;

	float SetAngleX = 0.0f;
	float SetAngleY = 0.0f;

	if (!m_isDead && m_hit == false && m_moveAttack == false && m_recoberyAction == false &&
		m_hitImpact == false && m_itemTakingNow == false && m_avoidance == false)
	{
		GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);

		m_oneAvoidance = false;
	}

	//回避の移動先を入力するため
	if (m_avoidance && m_oneAvoidance == false)
	{
		GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);

		m_oneAvoidance = true;
	}

	//移動方向を設定する
	auto moveVec =VGet(static_cast<float>(-analogX), 0.0f, static_cast<float>(analogY));    //ベクトルの長さ

	//ベクトルの長さを取得する
	float len = VSize(moveVec);
	//ベクトルの長さを0.0～1.0の割合に変換する
	float rate = len / 1000.0f;
	//アナログスティック無効な範囲を除外する
	rate = (rate - 0.1f) / (0.8f - 0.1f);
	rate = min(rate, 1.0f);
	rate = max(rate, 0.0f);

	//速度が決定できるので移動ベクトルに反映する
	moveVec = VNorm(moveVec);
	float speed = m_status.s_speed * rate;

	moveVec = VScale(moveVec, speed);

	//cameraの角度から
	//コントローラーによる移動方向を決定する
	MATRIX mtx = MGetRotY(m_cameraAngle + DX_PI_F);
	moveVec = VTransform(moveVec, mtx);

	//ライブラリのベクターに変換する
	m_moveVec = MyLibrary::LibVec3(static_cast<float>(moveVec.x), static_cast<float>(moveVec.y), static_cast<float>(moveVec.z));

	//移動方向からプレイヤーへの向く方向を決定する
	//移動していない場合(ゼロベクトル)の場合は変更しない
	if (VSquareSize(moveVec) > 0.0f)
	{
		//ロックオンしてない時と走った時のアングル
		if (m_lockonTarget == false || m_dashMove && m_avoidance == false)
		{
			//アングルを決定
			m_angle = atan2f(-moveVec.z, moveVec.x) - DX_PI_F / 2;
		}
		//ロックオンした時のアングル
		else if (m_lockonTarget == true && m_avoidance == false)
		{
			//アングルを決定
			m_angle = m_lockAngle;
		}
		else if (m_avoidance)
		{
			//アングルを決定
			m_angle = atan2f(-moveVec.z, moveVec.x) - DX_PI_F / 2;
		}

		//プレイヤーが動いたら
		m_moveflag = true;
	}
	//プレイヤーが動いてなかったら
	else if (VSquareSize(moveVec) <= 0.0f)
	{
		m_moveflag = false;
	}

	//プレイヤーが生きている時だけ
	if (!m_isDead)
	{
		m_modelPos.ConversionToVECTOR() = VAdd(m_modelPos.ConversionToVECTOR(), moveVec);

		Action();
	}

	//武器を持ってない時のアニメーション
	if (m_notWeapon && m_notShield)
	{
		NotWeaponAnimation();
	}

	AllAnimation();

	//武器を持った時のアニメーション
	if (!m_notWeapon || !m_notShield)
	{
		WeaponAnimation();
	}
	
}

/// <summary>
/// プレイヤーのアクション行動をまとめる
/// </summary>
void NewPlayer::Action()
{
	//Aボタンが長押しされたらダッシュする
	if (m_xpad.Buttons[12] == 1)
	{
		if (cA >= 50 && m_status.s_stamina >= 0.1f)
		{
			m_avoidance = false;

			//ダッシュ中
			m_dashMove = true;

			m_status.s_speed = 3.0f;

			//スタミナ消費
			m_status.s_stamina -= 0.1f;
		}


		if (cA < 51)
		{
			cA++;
		}
	}
	else
	{
		m_dashMove = false;

		m_status.s_speed = 2.0f;

		cA = 0;
	}
}

/// <summary>
/// 武器を装備していない時のアニメーション
/// </summary>
void NewPlayer::NotWeaponAnimation()
{
	//プレイヤーが生きている時だけ
	if (!m_isDead)
	{
		if (!m_hit)
		{
			//走る
			if (m_dashMove && m_moveflag)
			{
				m_nowAnimIdx = m_animIdx["Run"];
				ChangeAnimation(m_nowAnimIdx);
			}
			else if (m_moveflag)
			{
				//ターゲットしていない時だけ
				if (!m_lockonTarget)
				{
					m_nowAnimIdx = m_animIdx["Walk"];
					ChangeAnimation(m_nowAnimIdx);
				}
				//ターゲットしている時
				else if (m_lockonTarget)
				{
					//左歩き
					if (cAnX < -500)
					{
						m_nowAnimIdx = m_animIdx["LeftWalk"];
						ChangeAnimation(m_nowAnimIdx);
					}
					//右歩き
					else if (cAnX > 500)
					{
						m_nowAnimIdx = m_animIdx["RightWalk"];
						ChangeAnimation(m_nowAnimIdx);
					}
					//後ろ歩きor歩き
					else if (cAnX < 500 && cAnX > -500)
					{
						m_nowAnimIdx = m_animIdx["Walk"];
						ChangeAnimation(m_nowAnimIdx);
					}
				}
				
			}
		}
	}
}

/// <summary>
/// すべての状態の時に行うアニメーション関数
/// </summary>
void NewPlayer::AllAnimation()
{
	//プレイヤーが生きている時だけ
	if (!m_isDead)
	{
		//攻撃が当たった時
		if (m_hit)
		{
			m_nowAnimIdx = m_animIdx["Hit"];
			ChangeAnimation(m_nowAnimIdx);
		}
		//攻撃が当たってない時
		else if (!m_hit)
		{
			//動いていないとき
			if (!m_moveflag)
			{
				m_nowAnimIdx = m_animIdx["Idle"];
				ChangeAnimation(m_nowAnimIdx);
			}
			//回避した時
			else if (m_avoidance && !m_moveAttack && !m_recoberyAction &&
				!m_itemTakingNow)
			{
				m_nowAnimIdx = m_animIdx["Roll"];
				ChangeAnimation(m_nowAnimIdx);
			}
			//攻撃するアニメーション
			else if (!m_avoidance && m_moveAttack && !m_recoberyAction &&
				!m_itemTakingNow)
			{
				m_nowAnimIdx = m_animIdx["Attack1"];
				ChangeAnimation(m_nowAnimIdx);
			}
			//プレイヤーが回復した時
			else if (m_recoberyAction && !m_itemTakingNow)
			{
				m_nowAnimIdx = m_animIdx["Recovery"];
				ChangeAnimation(m_nowAnimIdx);
			}
			//アイテム取得するとき
			else if (!m_recoberyAction && m_itemTaking)
			{
				m_nowAnimIdx = m_animIdx["Taking"];
				ChangeAnimation(m_nowAnimIdx);
			}
		}
	}
	//プレイヤーが死亡した時だけ
	else if (m_isDead)
	{
		m_nowAnimIdx = m_animIdx["Death"];
		ChangeAnimation(m_nowAnimIdx);
	}
	
}

/// <summary>
/// 装備をした時のアニメーション
/// </summary>
void NewPlayer::WeaponAnimation()
{
	//プレイヤーが生きている時だけ
	if (!m_isDead)
	{
		//盾受けしたとき
		if (m_hitImpact)
		{
			m_nowAnimIdx = m_animIdx["ShieldImpact"];
			ChangeAnimation(m_nowAnimIdx);
		}
		//怯んでいないとき盾受けしてない時
		else if (!m_hit && !m_hitImpact)
		{
			//盾を構えて立ってるとき
			if (!m_moveflag && !m_avoidance && !m_moveAttack && !m_recoberyAction &&
				m_shield && !m_itemTakingNow)
			{
				m_nowAnimIdx = m_animIdx["ShieldIdle"];
				ChangeAnimation(m_nowAnimIdx);
			}
			//プレイヤーが動いたら(走ったら)
			if (m_dashMove && m_moveflag && !m_avoidance && !m_moveAttack &&
				!m_recoberyAction && !m_itemTakingNow)
			{
				m_nowAnimIdx = m_animIdx["ShieldRun"];
				ChangeAnimation(m_nowAnimIdx);
			}
			//歩き
			else if (m_moveflag && !m_avoidance && !m_moveAttack && !m_recoberyAction &&
				!m_itemTakingNow)
			{
				//ターゲットしていないとき
				if (!m_lockonTarget)
				{
					m_nowAnimIdx = m_animIdx["ShieldWalk"];
					ChangeAnimation(m_nowAnimIdx);
				}
				//ターゲットしているとき
				else if (m_lockonTarget)
				{
					//左歩きor右歩き
					if (cAnX < -500 || cAnX > 500)
					{
						m_nowAnimIdx = m_animIdx["ShieldSideWalk"];
						ChangeAnimation(m_nowAnimIdx);

						//左歩き
						if (cAnX < -500)
						{
							m_weaponMoveRight = false;
						}
						//右歩き
						if (cAnX > 500)
						{
							m_weaponMoveRight = true;
						}
					}
					//歩き
					if (cAnX < 500 && cAnX > -500)
					{
						m_nowAnimIdx = m_animIdx["ShieldWalk"];
						ChangeAnimation(m_nowAnimIdx);

						m_weaponMoveRight = false;
					}
				}
			}
		}
	}
}

void NewPlayer::Draw(std::shared_ptr<Equipment> eq)
{
	rigidbody.SetPos(rigidbody.GetNextPos());
	m_collisionPos = rigidbody.GetPos();
	SetModelPos();
	MV1SetPosition(m_handle, m_modelPos.ConversionToVECTOR());
	//描画

	MV1DrawModel(m_handle);
}

void NewPlayer::OnCollideEnter(const std::shared_ptr<Collidable>& collidable)
{
}

void NewPlayer::OnTriggerEnter(const std::shared_ptr<Collidable>& collidable)
{
}

void NewPlayer::SetModelPos()
{
	m_modelPos = m_collisionPos;
}
