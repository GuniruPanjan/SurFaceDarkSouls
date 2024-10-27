#include "NewPlayer.h"
#include "External/CsvLoad.h"
#include "Object/RectObject.h"

namespace
{
	//���f���T�C�Y
	constexpr float cModelSizeScale = 0.4f;

	//�A�j���[�V�����̐؂�ւ��ɂ�����t���[����
	constexpr float cAnimChangeFrame = 5.0f;
	constexpr float cAnimChangeSpeed = 1.0f / cAnimChangeFrame;

	//�A�j���[�V������ς��邽�߂̕�����������
	int cAnX = 0;
	int cAnY = 0;

	//�{�^���̒�����
	int cA;

	//�A�j���[�V�����u�����h���̍ő�
	constexpr float cAnimBlendRateMax = 1.0f;

	//�V���O���g��
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
	//�����蔻��ݒ�
	auto collider = Collidable::AddCollider(MyLibrary::CollidableData::Kind::Capsule, false);
	auto capsuleCol = dynamic_cast<MyLibrary::CollidableDataCapsule*>(collider.get());
	capsuleCol->m_len = 40.0f;
	capsuleCol->m_radius = 12.0f;
	capsuleCol->m_vec = MyLibrary::LibVec3(0.0f, m_vec.y + 2.0f, 0.0f);

	//�v���C���[�̔���
	InitHitBox(capsuleCol->m_radius, capsuleCol->m_len, capsuleCol->m_vec, false);
	//InitAttackBox(m_attackRadius, )

	//���f���ǂݍ���
	m_handle = handle.GetModelHandle("Data/Player/PlayerModel.mv1");

	//���f���̃T�C�Y�ݒ�
	MV1SetScale(m_handle, VGet(cModelSizeScale, cModelSizeScale, cModelSizeScale));

	//�G�t�F�N�g�ǂݍ���
	effect.EffectLoad("Rest", "Data/Effect/Benediction.efkefc", 210, 10.0f);
	effect.EffectLoad("Heal", "Data/Effect/AnotherEffect/Sylph13.efkefc", 160, 20.0f);
	effect.EffectLoad("Imapct", "Data/Effect/HitEffect.efkefc", 30, 7.0f);

	//���x���̏�����
	m_levelStatus.sl_hp = 1;
	m_levelStatus.sl_stamina = 1;
	m_levelStatus.sl_muscle = 1;
	m_levelStatus.sl_skill = 1;

	CsvLoad::GetInstance().AnimDataLoad("Player", m_animIdx);
}

NewPlayer::~NewPlayer()
{
	//���������
	MV1DeleteModel(m_handle);
}

/// <summary>
/// ����������
/// </summary>
/// <param name="physics">�����N���X�̃|�C���^</param>
void NewPlayer::Init(std::shared_ptr<MyLibrary::Physics> physics)
{
	m_pPhysics = physics;

	Collidable::Init(m_pPhysics);


	//�v���C���[�̏����ʒu�ݒ�
	rigidbody.Init(true);
	rigidbody.SetPos(MyLibrary::LibVec3(0.0f, 1.0f * cModelSizeScale, 0.0f));
	rigidbody.SetNextPos(rigidbody.GetPos());
	m_collisionPos = rigidbody.GetPos();
	SetModelPos();
	MV1SetPosition(m_handle, m_modelPos.ConversionToVECTOR());

	//�ҋ@�A�j���[�V������ݒ�
	m_nowAnimNo = MV1AttachAnim(m_handle, m_animIdx["Idle"]);
	m_nowAnimIdx = m_animIdx["Idle"];

	
}

void NewPlayer::Finalize()
{
	Collidable::Finalize(m_pPhysics);
}

void NewPlayer::Update(std::shared_ptr<Equipment> eq)
{
	//�A�j���[�V�����ňړ����Ă���t���[���̔ԍ�����������
	m_moveAnimFrameIndex = MV1SearchFrame(m_handle, "mixamorig:Hips");
	m_moveAnimFrameRight = MV1SearchFrame(m_handle, "mixamorig:RightHandThumb2");

	//������A�^�b�`����t���[���̃��[�J�������[���h�ϊ��s����擾����
	m_moveWeaponFrameMatrix = MV1GetFrameLocalWorldMatrix(m_handle, m_moveAnimFrameRight);

	//�����\����Ƃ��̃A�j���[�V�����̃t���[���擾
	m_moveAnimShieldFrameIndex = MV1SearchFrame(m_handle, "mixamorig:LeftShoulder");
	m_moveAnimShieldFrameHandIndex = MV1SearchFrame(m_handle, "mixamorig:LeftHand");

	//������A�^�b�`����t���[���̃��[�J�������[���h���W���擾����
	m_moveShieldFrameMatrix = MV1GetFrameLocalWorldMatrix(m_handle, m_moveAnimShieldFrameHandIndex);

	//�p�b�h���͎擾
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

	//�A�j���[�V�����̍X�V
	if (!m_isDead)
	{
		//UpdateAnimation()
	}
	m_isAnimationFinish = UpdateAnimation(m_nowAnimNo);

	//�A�j���[�V�����̐؂�ւ�
	if (m_prevAnimNo != -1)
	{
		//�t���[���ŃA�j���[�V������؂�ւ���
		m_animBlendRate += cAnimChangeSpeed;
		if (m_animBlendRate >= cAnimBlendRateMax)
		{
			m_animBlendRate = cAnimBlendRateMax;
		}

		//�A�j���[�V�����̃u�����h����ݒ肷��
		MV1SetAttachAnimBlendRate(m_handle, m_prevAnimNo, cAnimBlendRateMax - m_animBlendRate);
		MV1SetAttachAnimBlendRate(m_handle, m_nowAnimNo, m_animBlendRate);
	}

	//���񂾎��̃A�j���[�V����
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

	//���W���擾����
	m_collisionPos = rigidbody.GetPos();

	//�A�i���O�X�e�B�b�N���g���Ĉړ�
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

	//����̈ړ������͂��邽��
	if (m_avoidance && m_oneAvoidance == false)
	{
		GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);

		m_oneAvoidance = true;
	}

	//�ړ�������ݒ肷��
	auto moveVec =VGet(static_cast<float>(-analogX), 0.0f, static_cast<float>(analogY));    //�x�N�g���̒���

	//�x�N�g���̒������擾����
	float len = VSize(moveVec);
	//�x�N�g���̒�����0.0�`1.0�̊����ɕϊ�����
	float rate = len / 1000.0f;
	//�A�i���O�X�e�B�b�N�����Ȕ͈͂����O����
	rate = (rate - 0.1f) / (0.8f - 0.1f);
	rate = min(rate, 1.0f);
	rate = max(rate, 0.0f);

	//���x������ł���̂ňړ��x�N�g���ɔ��f����
	moveVec = VNorm(moveVec);
	float speed = m_status.s_speed * rate;

	moveVec = VScale(moveVec, speed);

	//camera�̊p�x����
	//�R���g���[���[�ɂ��ړ����������肷��
	MATRIX mtx = MGetRotY(m_cameraAngle + DX_PI_F);
	moveVec = VTransform(moveVec, mtx);

	//���C�u�����̃x�N�^�[�ɕϊ�����
	m_moveVec = MyLibrary::LibVec3(static_cast<float>(moveVec.x), static_cast<float>(moveVec.y), static_cast<float>(moveVec.z));

	//�ړ���������v���C���[�ւ̌������������肷��
	//�ړ����Ă��Ȃ��ꍇ(�[���x�N�g��)�̏ꍇ�͕ύX���Ȃ�
	if (VSquareSize(moveVec) > 0.0f)
	{
		//���b�N�I�����ĂȂ����Ƒ��������̃A���O��
		if (m_lockonTarget == false || m_dashMove && m_avoidance == false)
		{
			//�A���O��������
			m_angle = atan2f(-moveVec.z, moveVec.x) - DX_PI_F / 2;
		}
		//���b�N�I���������̃A���O��
		else if (m_lockonTarget == true && m_avoidance == false)
		{
			//�A���O��������
			m_angle = m_lockAngle;
		}
		else if (m_avoidance)
		{
			//�A���O��������
			m_angle = atan2f(-moveVec.z, moveVec.x) - DX_PI_F / 2;
		}

		//�v���C���[����������
		m_moveflag = true;
	}
	//�v���C���[�������ĂȂ�������
	else if (VSquareSize(moveVec) <= 0.0f)
	{
		m_moveflag = false;
	}

	//�v���C���[�������Ă��鎞����
	if (!m_isDead)
	{
		m_modelPos.ConversionToVECTOR() = VAdd(m_modelPos.ConversionToVECTOR(), moveVec);

		Action();
	}

	//����������ĂȂ����̃A�j���[�V����
	if (m_notWeapon && m_notShield)
	{
		NotWeaponAnimation();
	}

	AllAnimation();

	//��������������̃A�j���[�V����
	if (!m_notWeapon || !m_notShield)
	{
		WeaponAnimation();
	}
	
}

/// <summary>
/// �v���C���[�̃A�N�V�����s�����܂Ƃ߂�
/// </summary>
void NewPlayer::Action()
{
	//A�{�^�������������ꂽ��_�b�V������
	if (m_xpad.Buttons[12] == 1)
	{
		if (cA >= 50 && m_status.s_stamina >= 0.1f)
		{
			m_avoidance = false;

			//�_�b�V����
			m_dashMove = true;

			m_status.s_speed = 3.0f;

			//�X�^�~�i����
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
/// ����𑕔����Ă��Ȃ����̃A�j���[�V����
/// </summary>
void NewPlayer::NotWeaponAnimation()
{
	//�v���C���[�������Ă��鎞����
	if (!m_isDead)
	{
		if (!m_hit)
		{
			//����
			if (m_dashMove && m_moveflag)
			{
				m_nowAnimIdx = m_animIdx["Run"];
				ChangeAnimation(m_nowAnimIdx);
			}
			else if (m_moveflag)
			{
				//�^�[�Q�b�g���Ă��Ȃ�������
				if (!m_lockonTarget)
				{
					m_nowAnimIdx = m_animIdx["Walk"];
					ChangeAnimation(m_nowAnimIdx);
				}
				//�^�[�Q�b�g���Ă��鎞
				else if (m_lockonTarget)
				{
					//������
					if (cAnX < -500)
					{
						m_nowAnimIdx = m_animIdx["LeftWalk"];
						ChangeAnimation(m_nowAnimIdx);
					}
					//�E����
					else if (cAnX > 500)
					{
						m_nowAnimIdx = m_animIdx["RightWalk"];
						ChangeAnimation(m_nowAnimIdx);
					}
					//������or����
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
/// ���ׂĂ̏�Ԃ̎��ɍs���A�j���[�V�����֐�
/// </summary>
void NewPlayer::AllAnimation()
{
	//�v���C���[�������Ă��鎞����
	if (!m_isDead)
	{
		//�U��������������
		if (m_hit)
		{
			m_nowAnimIdx = m_animIdx["Hit"];
			ChangeAnimation(m_nowAnimIdx);
		}
		//�U�����������ĂȂ���
		else if (!m_hit)
		{
			//�����Ă��Ȃ��Ƃ�
			if (!m_moveflag)
			{
				m_nowAnimIdx = m_animIdx["Idle"];
				ChangeAnimation(m_nowAnimIdx);
			}
			//���������
			else if (m_avoidance && !m_moveAttack && !m_recoberyAction &&
				!m_itemTakingNow)
			{
				m_nowAnimIdx = m_animIdx["Roll"];
				ChangeAnimation(m_nowAnimIdx);
			}
			//�U������A�j���[�V����
			else if (!m_avoidance && m_moveAttack && !m_recoberyAction &&
				!m_itemTakingNow)
			{
				m_nowAnimIdx = m_animIdx["Attack1"];
				ChangeAnimation(m_nowAnimIdx);
			}
			//�v���C���[���񕜂�����
			else if (m_recoberyAction && !m_itemTakingNow)
			{
				m_nowAnimIdx = m_animIdx["Recovery"];
				ChangeAnimation(m_nowAnimIdx);
			}
			//�A�C�e���擾����Ƃ�
			else if (!m_recoberyAction && m_itemTaking)
			{
				m_nowAnimIdx = m_animIdx["Taking"];
				ChangeAnimation(m_nowAnimIdx);
			}
		}
	}
	//�v���C���[�����S����������
	else if (m_isDead)
	{
		m_nowAnimIdx = m_animIdx["Death"];
		ChangeAnimation(m_nowAnimIdx);
	}
	
}

/// <summary>
/// �������������̃A�j���[�V����
/// </summary>
void NewPlayer::WeaponAnimation()
{
	//�v���C���[�������Ă��鎞����
	if (!m_isDead)
	{
		//���󂯂����Ƃ�
		if (m_hitImpact)
		{
			m_nowAnimIdx = m_animIdx["ShieldImpact"];
			ChangeAnimation(m_nowAnimIdx);
		}
		//����ł��Ȃ��Ƃ����󂯂��ĂȂ���
		else if (!m_hit && !m_hitImpact)
		{
			//�����\���ė����Ă�Ƃ�
			if (!m_moveflag && !m_avoidance && !m_moveAttack && !m_recoberyAction &&
				m_shield && !m_itemTakingNow)
			{
				m_nowAnimIdx = m_animIdx["ShieldIdle"];
				ChangeAnimation(m_nowAnimIdx);
			}
			//�v���C���[����������(��������)
			if (m_dashMove && m_moveflag && !m_avoidance && !m_moveAttack &&
				!m_recoberyAction && !m_itemTakingNow)
			{
				m_nowAnimIdx = m_animIdx["ShieldRun"];
				ChangeAnimation(m_nowAnimIdx);
			}
			//����
			else if (m_moveflag && !m_avoidance && !m_moveAttack && !m_recoberyAction &&
				!m_itemTakingNow)
			{
				//�^�[�Q�b�g���Ă��Ȃ��Ƃ�
				if (!m_lockonTarget)
				{
					m_nowAnimIdx = m_animIdx["ShieldWalk"];
					ChangeAnimation(m_nowAnimIdx);
				}
				//�^�[�Q�b�g���Ă���Ƃ�
				else if (m_lockonTarget)
				{
					//������or�E����
					if (cAnX < -500 || cAnX > 500)
					{
						m_nowAnimIdx = m_animIdx["ShieldSideWalk"];
						ChangeAnimation(m_nowAnimIdx);

						//������
						if (cAnX < -500)
						{
							m_weaponMoveRight = false;
						}
						//�E����
						if (cAnX > 500)
						{
							m_weaponMoveRight = true;
						}
					}
					//����
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
	//�`��

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
