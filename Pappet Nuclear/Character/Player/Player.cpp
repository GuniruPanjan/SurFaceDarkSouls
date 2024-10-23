#include "Player.h"
#include "Map/Map.h"
#include "Character/Player/Item/ItemManager.h"
#include "Character/Effect/Effect.h"
#include "UI/Setting.h"
#include<math.h>

namespace
{
	int walkTime;       //����SE���Đ������鎞��
	int dashTime;       //����SE���Đ������鎞��
	bool attack;        //�U��SE���Đ������鎞
	int a;
	float angleShield;   //�����\�����������̂���𒼂��ϐ�

	float anX;         //�A�i���O�X�e�B�b�N���i�[����ϐ�
	float anY;         //�A�i���O�X�e�B�b�N���i�[����ϐ�

	MATRIX AvoidancePos;    //��������Ƃ��̃|�W�V����

	int Button;        //��񂾂����͂��邽�߂̕ϐ�

	//�V���O���g��
	auto& handle = HandleManager::GetInstance();
	auto& effect = Effect::GetInstance();
}

/// <summary>
/// �R���X�g���N�^
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

	//�v���C���[�̃J�v�Z���^
	auto collider = Collidable::AddCollider(MyLibrary::CollidableData::Kind::Capsule, false);
	auto capsuleCol = dynamic_cast<MyLibrary::CollidableDataCapsule*>(collider.get());
	capsuleCol->m_len = 40.0f;
	capsuleCol->m_radius = 12.0f;
	capsuleCol->m_vec = MyLibrary::LibVec3(0.0f, m_vec.y + 2.0f, 0.0f);

	//���x���̏�����
	m_levelStatus.sl_hp = 1;
	m_levelStatus.sl_stamina = 1;
	m_levelStatus.sl_muscle = 1;
	m_levelStatus.sl_skill = 1;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	//���������
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

	//�������폜
	handle.Clear();
}

/// <summary>
/// ����������
/// </summary>
void Player::Init()
{
	m_button = 0;
	m_one = false;
	m_oneAvoidance = false;

	//�v���C���[HP�̏�����
	m_status.s_hp = 150.0f;
	m_status.s_hp = m_status.s_hp * m_levelStatus.sl_hp;

	//�v���C���[�̃X�^�~�i������
	m_status.s_stamina = 100.0f;
	m_status.s_stamina = m_status.s_stamina * m_levelStatus.sl_stamina;

	//�v���C���[�X�s�[�h������
	m_status.s_speed = 2.0f;

	//�v���C���[�������o������
	m_bounceDis = 3.0f;

	//�v���C���[�̍U���͏�����
	m_status.s_attack = 10.0f;

	//�v���C���[�̃��b�N�I��������
	m_lockonTarget = false;
	m_lockAngle = 0.0f;

	//�񕜊֌W�̏�����
	m_recoberyAmount = 100.0f;
	m_heel = 0.0f;
	m_recoveryNumber = 5;
	m_recoberyAction = false;

	//�A�j���֌W�̏�����
	m_hitImpact = false;
	m_weaponAnimOne = false;
	m_notWeaponAnimOne = false;
	m_itemTaking = false;
	m_itemTakingNow = false;

	//��񂾂�������
	if (m_oneInit == false)
	{
		//���평����
		weapon->Init();

		//���x��������
		m_coreAllLevel = 0;
		m_hpLevel = 1;
		m_staminaLevel = 1;

		m_modelSize = 0.4f;

		//�G�t�F�N�g�ǂݍ���
		effect.EffectLoad("Rest", "Data/Effect/Benediction.efkefc", 210, 10.0f);
		effect.EffectLoad("Heal", "Data/Effect/AnotherEffect/Sylph13.efkefc", 160, 20.0f);
		effect.EffectLoad("Imapct", "Data/Effect/HitEffect.efkefc", 30, 7.0f);

		//�v���C���[�����f���ǂݍ���
		//m_handle = MV1LoadModel("Data/Player/PuppetPlayerModel.mv1");
		m_handle = handle.GetModelHandle("Data/Player/PuppetPlayerModel.mv1");

		//�v���C���[�̑傫����ς���
		MV1SetScale(m_handle, VGet(m_modelSize, m_modelSize, m_modelSize));

		//�v���C���[�̃A�j���[�V�����ǂݍ���
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

		//�A�j���[�V�����A�^�b�`
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


		//�A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		for (int i = 0; i < 21; i++)
		{
			m_totalAnimTime[i] = MV1GetAttachAnimTotalTime(m_handle, m_animation[i]);

		}

		se->CharaInit();

		m_oneInit = true;
	}

	//�A�j���[�V�����u�����h
	MV1SetAttachAnimBlendRate(m_handle, m_animation[0], 1.0f);

	for (int i = 1; i < 20; i++)
	{
		MV1SetAttachAnimBlendRate(m_handle, m_animation[i], 0.0f);
	}

	m_playTime = 0.0f;
	
	//�����蔻��
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

	//�v���C���[�̃|�W�V�����ݒ�
	m_pos = VGet(m_posX, m_posY, m_posZ);
	m_drawPos = m_pos;

	//���S�A�j���[�V�����������Ă�����
	if (m_animOne[8] == true)
	{
		//�A�j���[�V�����u�����h��0�ɂ���
		MV1SetAttachAnimBlendRate(m_handle, m_animation[8], 0.0f);

		//�A�j���[�V�����A�^�b�`
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
/// �X�V����
/// </summary>
void Player::Update()
{
	m_colPos = Pos3(m_pos.x - 2.0f, m_pos.y + 35.0f, m_pos.z);
	m_targetColPos = Pos3(m_pos.x, m_pos.y + 35.0f, m_pos.z);

	//������
	if (m_notWeapon == false)
	{
		if (m_fistCol == false && m_swordCol == false)
		{
			m_sphereCol.Init(m_colAttackPos, m_sphereRadius);

			m_fistCol = true;
		}

		//�f��̍U����
		m_status.s_attack = 10.0f;
		m_status.s_attack = m_status.s_attack + (m_status.s_attack * (m_levelStatus.sl_muscle / 10));
	}

	//�A�j���[�V�����ňړ����Ă���t���[���̔ԍ�����������
	m_moveAnimFrameIndex = MV1SearchFrame(m_handle, "mixamorig:Hips");
	//m_moveAnimFrameIndex = MV1GetPosition(m_handle);
	m_moveAnimFrameRight = MV1SearchFrame(m_handle, "mixamorig:RightHandThumb2");

	//������A�^�b�`����t���[���̃��[�J�������[���h�ϊ��s����擾����
	m_moveWeaponFrameMatrix = MV1GetFrameLocalWorldMatrix(m_handle, m_moveAnimFrameRight);

	//�����\����Ƃ��̃A�j���[�V�����̃t���[������
	m_moveAnimShieldFrameIndex = MV1SearchFrame(m_handle, "mixamorig:LeftShoulder");
	m_moveAnimShieldFrameHandIndex = MV1SearchFrame(m_handle, "mixamorig:LeftHand");

	//������A�^�b�`����t���[���̃��[�J�������[���h�ϊ��s����擾����
	m_moveShieldFrameMatrix = MV1GetFrameLocalWorldMatrix(m_handle, m_moveAnimShieldFrameHandIndex);


	//�p�b�h���͏���
	m_pad = GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

	//�A�i���O�X�e�B�b�N���g���Ĉړ�
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

	//�v���C���[�������������̑O�ɍŏ��Ɍ����Ă�����ɉ�������Ă��܂����߃o�O���������Ă���
	//�v���C���[�������Ă����������Ȃ��Ɖ�����o�O��
	//�����Ԉ���Ă��邽�ߏC��
	//����̈ړ������͂��邽��
	if (m_avoidance == true && m_oneAvoidance == false)
	{
		GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);

		m_oneAvoidance = true;
	}

	//�A�i���O�X�e�B�b�N�̓��͂��i�[
	anX = analogX;
	anY = analogY;


	m_move = VGet(static_cast<float>(-analogX), 0.0f, static_cast<float>(analogY));  //�x�N�g���̒���
	m_bounceMove = VGet(static_cast<float>(analogX), 0.0f, static_cast<float>(-analogY));  //�x�N�g���̒���

	//�x�N�g���̒������擾����
	float len = VSize(m_move);
	float bounceLen = VSize(m_bounceMove);
	//�x�N�g��������0.0�`1.0�̊����ɕϊ�����
	float rate = len / 1000.0f;
	float bounceRate = bounceLen / 1000.0f;

	//�A�i���O�X�e�B�b�N�����Ȕ͈͂����O����
	rate = (rate - 0.1f) / (0.8f - 0.1f);
	rate = min(rate, 1.0f);
	rate = max(rate, 0.0f);

	bounceRate = (bounceRate - 0.1f) / (0.8f - 0.1f);
	bounceRate = min(bounceRate, 1.0f);
	bounceRate = max(bounceRate, 0.0f);


	//���x������ł���̂ňړ��x�N�g���ɔ��f����
	m_move = VNorm(m_move);
	float speed = m_status.s_speed * rate;

	m_move = VScale(m_move, speed);

	m_bounceMove = VNorm(m_bounceMove);
	float bounceDis = m_status.s_speed * bounceRate;

	m_bounceMove = VScale(m_bounceMove, bounceDis);

	//camera�̊p�x����
	//�R���g���[���[�ɂ��ړ����������肷��
	MATRIX mtx = MGetRotY(m_cameraAngle + DX_PI_F);
	m_move = VTransform(m_move, mtx);
	MATRIX reverseMtx = MGetRotY(m_cameraAngle + DX_PI_F);
	m_bounceMove = VTransform(m_bounceMove, reverseMtx);

	//�ړ���������v���C���[�ւ̌������������肷��
	//�ړ����Ă��Ȃ��ꍇ(�[���x�N�g��)�̏ꍇ�͕ύX���Ȃ�
	if (VSquareSize(m_move) > 0.0f && m_moveAttack == false && m_recoberyAction == false &&
		m_hit == false && m_status.s_hp >= 0.0f && m_hitImpact == false && m_itemTakingNow == false)
	{
		//���b�N�I�����ĂȂ����Ƒ��������̃A���O��
		if (m_lockonTarget == false || m_dashMove == true && m_avoidance == false)
		{
			//�A���O��������
			m_angle = atan2f(-m_move.z, m_move.x) - DX_PI_F / 2;
		}
		//���b�N�I���������̃A���O��
		else if (m_lockonTarget == true && m_avoidance == false)
		{
			//�A���O��������
			m_angle = m_lockAngle;
			
		}
		else if (m_avoidance == true)
		{
			//�A���O��������
			m_angle = atan2f(-m_move.z, m_move.x) - DX_PI_F / 2;
		}
		


		//�v���C���[����������
		m_moveflag = true;

		//SE
		//�����Ă��Ȃ�������
		if (m_dashMove == false)
		{
			walkTime++;

			if (walkTime >= 30)
			{
				walkTime = 0;
			}
			
			dashTime = 0;
		}
		//��������
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
	//�v���C���[�������ĂȂ�������
	else if (VSquareSize(m_move) <= 0.0f)
	{
		m_moveflag = false;

		walkTime = 0;
		dashTime = 0;
	}

	//�v���C���[�������Ă��鎞����
	if (m_status.s_hp > 0.0f)
	{
		m_pos = VAdd(m_pos, m_move);

		m_targetCunCol.Update(m_targetColPos);

		//���j���[���J����Ă���s���ł��Ȃ�
		if (m_menuOpen == false)
		{
			Action();
		}
		
	}


	//����������ĂȂ���
	if (m_notWeapon == false)
	{
		//�U���̓����蔻����v���C���[�̐��ʂɎ����Ă���
		m_colAttackPos.x = m_pos.x + sinf(m_angle) * -25.0f;
		m_colAttackPos.z = m_pos.z - cosf(m_angle) * 25.0f;
	}
	
	m_rectPos.x = m_pos.x + sinf(m_angle) * -15.0f;
	m_rectPos.z = m_pos.z - cosf(m_angle) * 15.0f;


	//sin��X����width�̃T�C�Y���o��
	if (sinf(m_angle) > 0)
	{
		m_rectSize.width = 30.0f + sinf(m_angle) * -15.0f;

	}
	else if (sinf(m_angle) < 0)
	{
		m_rectSize.width = 30.0f - sinf(m_angle) * -15.0f;
	}

	//cos��Z����depth�̃T�C�Y���o��
	if (cosf(m_angle) > 0)
	{
		m_rectSize.depth = 30.0f + cosf(m_angle) * -15.0f;

	}
	else if (cosf(m_angle) < 0)
	{
		m_rectSize.depth = 30.0f - cosf(m_angle) * -15.0f;

	}

	m_rectCol.Update(m_rectPos, m_rectSize);



	//�A�j���[�V�������Ԃ�i�߂�O�̃A�j���[�V�����ňړ������Ă���t���[���̍��W�擾
	m_prevPos = MV1GetFramePosition(m_handle, m_moveAnimFrameIndex);

	AvoidancePos = MV1GetFrameLocalWorldMatrix(m_handle, m_moveAnimFrameIndex);

	//�A�^�b�`���郂�f���̃t���[�����W���擾����
	m_moveAnimFrameRigthPosition = MV1GetFramePosition(m_handle, m_moveAnimFrameRight);

	//�U�����Ă��Ȃ����̃A�j���[�V�������x
	//�^�[�Q�b�g���ĂȂ����̃A�j���[�V�������x
	if(m_moveAttack == false && m_lockonTarget == false)
	{
		//�Đ����Ԃ�i�߂�
		m_playTime += 0.5f;
	}
	//�E�ɕ�������
	else if (m_lockonTarget == true && m_weaponMoveRight == true)
	{
		//�Đ����Ԃ�i�߂�
		m_playTime -= 0.5f;
	}
	//������
	else if (m_lockonTarget == true && m_dashMove == false && anY > 0 && anX < 500 && anX > -500)
	{
		//�Đ����Ԃ�i�߂�
		m_playTime -= 0.5f;
	}
	else
	{
		if (m_moveAttack == false)
		{
			//�Đ����Ԃ�i�߂�
			m_playTime += 0.5f;
		}
		
	}


	//A�{�^���������ꂽ��
	//���j���[���J����Ă���s���ł��Ȃ�
	if (m_menuOpen == false)
	{
		if (m_xpad.Buttons[12] == 1 && m_staminaBroke == false && m_recoberyAction == false &&
			m_moveAttack == false && m_hit == false && m_hitImpact == false)
		{
			if (m_a > 50 && m_status.s_stamina >= 0.1f)
			{
				m_avoidance = false;

				//�_�b�V����
				m_dashMove = true;

				m_status.s_speed = 3.0f;

				//�X�^�~�i����
				m_status.s_stamina -= 0.1f;
			}
			//�������
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
	


	//�����U�����Ă��Ȃ����ɍ��W������
	if (m_avoidance == false && m_moveAttack == false)
	{
		m_drawPos = m_pos;
	}
	//����s����
	if (m_playTime <= m_totalAnimTime[3] && m_avoidance == true)
	{
		//�t���[�����
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

	//�U�����������������[�V�����┻�������������
	if (m_hit == true && m_hitImpact == false)
	{
		m_drawPos = m_pos;
		m_avoidance = false;
		m_moveAttack = false;
		m_recoberyAction = false;
	}

	//�X�^�~�i�؂�
	if (m_status.s_stamina <= 0.1f)
	{
		m_staminaBroke = true;
	}
	//������悤�ɂȂ�
	else if (m_status.s_stamina >= 20.0f)
	{
		m_staminaBroke = false;
	}
	//�X�^�~�i��
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

	//����������ĂȂ����̃A�j���[�V����
	if (m_notWeapon == false && m_notShield == false)
	{
		NotWeaponAnimation(m_playTime);
	}

	Animation(m_playTime, m_pos);

	//��������������̃A�j���[�V����
	if (m_notWeapon == true || m_notShield == true)
	{
		WeaponAnimation(m_playTime);
	}

	m_capsuleCol.Update(m_colPos, m_vec);

	//�}�b�v�Ƃ̓����蔻��p
	m_mapHitColl = VGet(m_colPos.x, m_colPos.y, m_colPos.z);

	//���j���[���J��
	if (m_xpad.Buttons[4] == 1)
	{
		m_menuOpen = true;
	}
}

/// <summary>
/// ��������������̍X�V����
/// </summary>
/// <param name="eq">�����N���X��Ԃ�</param>
void Player::WeaponUpdate(Equipment& eq)
{

	//�E�葕��
	//������������
	if (eq.GetSword() == true)
	{
		m_notWeapon = true;

		weapon->RightUpdate(m_moveWeaponFrameMatrix);


		//��񂾂�������
		if (m_swordCol == false)
		{
			m_sphereCol.Init(m_initializationPos, m_swordRadius);

			//���̍U����
			m_status.s_attack = 30.0f;
			m_status.s_attack = m_status.s_attack + (m_status.s_attack * (m_levelStatus.sl_muscle / 10) + (m_levelStatus.sl_skill / 10));

			m_swordCol = true;
		}

		//�U���̓����蔻����v���C���[�̐��ʂɎ����Ă���
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


	//���葕��
	//������������
	if (eq.GetShield() == true)
	{
		m_notShield = true;

		weapon->LeftUpdate(m_moveShieldFrameMatrix);
	}
	else
	{
		m_notShield = false;
	}

	//������������ŏ����\������
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
/// �v���C���[��SE�̉��ʂ�ς���
/// </summary>
/// <param name="volume">����</param>
void Player::PlaySE(int volume)
{
	se->Update(volume);
}

/// <summary>
/// ���̃L�����N�^�[�Ȃǂ̉e�����󂯂�
/// </summary>
/// <param name="outpush">�G�l�~�[���v���C���[�������o������</param>
/// <param name="weakoutpush">�{�X���v���C���[�������o������</param>
void Player::OtherInfluence(VECTOR outpush, VECTOR weakoutpush)
{
	//���̃L�����N�^�[�Ȃǂ̉e�����󂯂�
	m_pos = VAdd(m_pos, outpush);
	m_pos = VAdd(m_pos, weakoutpush);
}

/// <summary>
/// �v���C���[�̍s���Ɋւ���������܂Ƃ߂�֐�
/// </summary>
void Player::Action()
{	
	//��i�K�ڂ̍U��
	if (m_status.s_hp > 0.0f)
	{
		//R�{�^���ōU��
		//��񂾂���������悤�ɂ���
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
						//�X�^�~�i����
						m_status.s_stamina = m_status.s_stamina - 10.0f;

						m_attackNumber = 1;

						m_moveAttack = true;
					}
					else if (m_nextAttack1 == true && m_status.s_stamina >= 10.0f)
					{
						//�X�^�~�i����
						m_status.s_stamina = m_status.s_stamina - 10.0f;

						m_attackNumber = 2;

						m_moveAttack = true;
					}
					else if (m_nextAttack2 == true && m_status.s_stamina >= 10.0f)
					{
						//�X�^�~�i����
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
	

	//ZR�{�^���ŕK�E�Z
	if (m_xpad.RightTrigger)
	{
		//DrawFormatString(0, 10, 0xffffff, "���U��");
	}


	//�s�����͖h��ł��Ȃ�
	if (m_moveAttack == false && m_avoidance == false && m_staminaBroke == false)
	{
		//L�{�^���Ŗh��
		if (m_xpad.Buttons[8] == 1)
		{
			DrawFormatString(0, 10, 0xffffff, "�h��");

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

	//�U�����̃A�j���[�V�����𑬂�����
	if (m_moveAttack == true)
	{
		//�U���P�i�K��
		if (m_animOne[4] == true)
		{
			if (m_playTime >= 15 && m_playTime < 30.0f)
			{
				m_playTime += 0.9f;

				//�U���̓����蔻�蔭��
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

				//2�i�K�ڂ̍U������
				m_nextAttack1 = true;

				//�U���̓����蔻�������������
				attack = false;

				m_sphereCol.Update(m_initializationPos);
			}
			else
			{
				m_playTime += 0.5f;

				//�U���̓����蔻�������������
				attack = false;

				m_sphereCol.Update(m_initializationPos);
			}
		}
		//�U���Q�i�K��
		else if (m_animOne[5] == true)
		{

			if (m_playTime >= 5.0f && m_playTime < 15.0f)
			{
				m_playTime += 0.9f;

				//�U���̓����蔻�蔭��
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

				//3�i�K�ڂ̍U������
				m_nextAttack2 = true;

				attack = false;

				m_sphereCol.Update(m_initializationPos);
			}
			else
			{
				m_playTime += 0.5f;

				//�U���̓����蔻�������������
				attack = false;

				m_sphereCol.Update(m_initializationPos);
			}
			
		}
		//�U���R�i�K��
		else if (m_animOne[6] == true)
		{

			if (m_playTime >= 15.0f && m_playTime < 25.0f)
			{
				m_playTime += 0.9f;

				//�U���̓����蔻�蔭��
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

				//�U���̓����蔻�������������
				attack = false;

				m_sphereCol.Update(m_initializationPos);
			}

		}

	}

	if (m_moveAttack == false)
	{
		//���̍U���i�K�̏�����
		m_attackNumber = 0;

		//�U������������
		m_nextAttack1 = false;
		m_nextAttack2 = false;

	}


	//�G�����b�N�I������
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

	//��
	//X�{�^���������ꂽ��
	if (m_xpad.Buttons[14] == 1)
	{
		if (m_moveAttack == false && m_avoidance == false)
		{
			//��񂾂����s
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
		//HP��
		if (m_status.s_hp < 150.0f && m_heel < 100.0f)
		{
			m_heel += 0.1f;

			m_status.s_hp = m_status.s_hp + m_heel;
		}

	}
}

/// <summary>
/// ����𑕔����ĂȂ����̃A�j���[�V�����֐�
/// </summary>
/// <param name="time">�A�j���[�V�����^�C��</param>
void Player::NotWeaponAnimation(float& time)
{
	//����������Ă鎞�̃A�j���[�V�����u�����h��0�ɂ����񂾂����s
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

	//��������������p
	m_weaponAnimOne = false;

	//�v���C���[�������Ă��鎞
	if (m_status.s_hp >= 0.0f)
	{
		//����łȂ��Ƃ�
		if (m_hit == false)
		{
			for (int i = 0; i < 20; i++)
			{
				//�v���C���[����������
			    //A�{�^��������
				if (m_dashMove == true && m_moveflag == true && m_avoidance == false &&
					m_moveAttack == false && m_recoberyAction == false && m_itemTakingNow == false)
				{

					if (i != 2 && i != 8)
					{
						pAnim->AnimationBlend(time, m_handle, m_animation[2], m_animation[i], m_animBlend, m_animOne[i], m_animOne[2], m_animBlendOne);
					}

				}
				//�����A�j���[�V����
				else if (m_moveflag == true && m_avoidance == false && m_moveAttack == false &&
					m_recoberyAction == false && m_itemTakingNow == false)
				{
					//�^�[�Q�b�g���ĂȂ���
					if (m_lockonTarget == false)
					{

						if (i != 1 && i != 8)
						{
							pAnim->AnimationBlend(time, m_handle, m_animation[1], m_animation[i], m_animBlend, m_animOne[i], m_animOne[1], m_animBlendOne);
						}
					}
					//�^�[�Q�b�g���Ă��鎞
					else if (m_lockonTarget == true)
					{

						//Y��0���オ������
						//Y��0��艺���O����
						//X��0���オ�E����
						//X��0��艺��������

						//������
						if (anX < -500)
						{
							if (i != 16 && i != 8)
							{
								pAnim->AnimationBlend(time, m_handle, m_animation[16], m_animation[i], m_animBlend, m_animOne[i], m_animOne[16], m_animBlendOne);
							}
						}
						//�E����
						if (anX > 500)
						{
							if (i != 17 && i != 8)
							{
								pAnim->AnimationBlend(time, m_handle, m_animation[17], m_animation[i], m_animBlend, m_animOne[i], m_animOne[17], m_animBlendOne);
							}
						}
						//������or����
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
/// ���ׂĂ̏�Ԃ̎��ɍs���A�j���[�V�����֐�
/// </summary>
/// <param name="time">�A�j���[�V�����^�C��</param>
/// <param name="pos">�A�j���[�V�����ɂ��|�W�V�����ړ��Ɏg�p����</param>
void Player::Animation(float& time, VECTOR& pos)
{
	if (m_animBlend < 1.0f)
	{
		m_animBlend += 0.5f;
	}

	for (int i = 0; i < 20; i++)
	{
		//�v���C���[�����񂾎�
		if (m_status.s_hp <= 0.0f)
		{
			if (i != 8)
			{
				pAnim->AnimationBlend(time, m_handle, m_animation[8], m_animation[i], m_animBlend, m_animOne[i], m_animOne[8], m_animBlendOne);
			}

			m_weaponMoveRight = false;
		}
		//�v���C���[�������Ă�����
		else if (m_status.s_hp > 0.0f)
		{

			//����
			if (m_hit == true)
			{
				if (i != 10 && i != 8)
				{
					pAnim->AnimationBlend(time, m_handle, m_animation[10], m_animation[i], m_animBlend, m_animOne[i], m_animOne[10], m_animBlendOne);
				}

			}
			else if (m_hit == false && m_hitImpact == false)
			{
				//�v���C���[�������Ă��Ȃ��Ȃ�
				if (m_moveflag == false && m_avoidance == false && m_moveAttack == false &&
					m_recoberyAction == false && m_shieldNow == false && m_itemTakingNow == false)
				{
					if (i != 0 && i != 8)
					{
						pAnim->AnimationBlend(time, m_handle, m_animation[0], m_animation[i], m_animBlend, m_animOne[i], m_animOne[0], m_animBlendOne);
					}

				}
				//���
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
					//�U���P�i�K��
					if (m_attackNumber == 1)
					{
						if (i != 4 && i != 5 && i != 6 && i != 8)
						{
							//��i�K�ڂ̍U����
							m_status.s_attack = m_status.s_attack * 1.0f;

							pAnim->AnimationBlend(time, m_handle, m_animation[4], m_animation[i], m_animBlend, m_animOne[i], m_animOne[4], m_animBlendOne);
						}

						m_weaponMoveRight = false;

						m_moveAttackEnd = false;
					}
					//�U���Q�i�K��
					if (m_attackNumber == 2 && m_animOne[4] == true)
					{
						if (i == 4)
						{
							//2�i�K�ڂ̍U����
							m_status.s_attack = m_status.s_attack * 1.2f;

							pAnim->AnimationBlend(time, m_handle, m_animation[5], m_animation[i], m_animBlend, m_animOne[i], m_animOne[5], m_animBlendOne);
						}

						m_moveAttackEnd = false;
						
					}
					//�U���R�i�K��
					if (m_attackNumber == 3 && m_animOne[5] == true)
					{

						if (i == 5)
						{
							//3�i�K�ڂ̍U����
							m_status.s_attack = m_status.s_attack * 1.5f;

							pAnim->AnimationBlend(time, m_handle, m_animation[6], m_animation[i], m_animBlend, m_animOne[i], m_animOne[6], m_animBlendOne);
						}

						m_moveAttackEnd = false;
					}

				}
				//�v���C���[���񕜂����Ƃ�
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
				//�A�C�e����������Ƃ�
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
			//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ�0�ɖ߂�
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

					//�U���I��
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
			//������
			if (i == 1)
			{
				if (time < 0.0f && m_animOne[i] == true)
				{
					time = m_totalAnimTime[i];
				}
			}
			if (i == 14)
			{
				//��������������̌�����
				if (time < 0.0f && m_animOne[i] == true)
				{
					time = m_totalAnimTime[14];
				}
			}
			if (i == 18)
			{
				//�E����
				if (time < 0.0f && m_weaponMoveRight == true)
				{
					time = m_totalAnimTime[18];
				}
			}

		}
		else if (i == 19)
		{
			//�A�C�e�������^�C���I��
			if (time >= m_totalAnimTime[i] / 2.5f && m_animOne[i] == true)
			{
				m_itemTakingNow = false;
			}
		}

		//�Đ����Ԃ��Z�b�g����
		if (m_animOne[i] == true)
		{
			MV1SetAttachAnimTime(m_handle, m_animation[i], time);

			//��𒆂���Ȃ��Ƃ��������Ȃ�
			if (m_avoidance == true)
			{
				//�A�j���[�V�������o�ߒ��̍��W�擾
				m_nowPos = MV1GetFramePosition(m_handle, m_moveAnimFrameIndex);
				m_moveVector = VSub(m_nowPos, m_prevPos);

				pos.x += m_moveVector.x;
				pos.z += m_moveVector.z;
			}
			if (i == 4)
			{
				//�A�j���[�V�������o�ߒ��̍��W�擾
				m_nowPos = MV1GetFramePosition(m_handle, m_moveAnimFrameIndex);
				m_moveVector = VSub(m_nowPos, m_prevPos);

				pos.x += m_moveVector.x;
				pos.z += m_moveVector.z;
			}
			if (i == 5)
			{
				//�A�j���[�V�������o�ߒ��̍��W�擾
				m_nowPos = MV1GetFramePosition(m_handle, m_moveAnimFrameIndex);
				m_moveVector = VSub(m_nowPos, m_prevPos);

				pos.x += m_moveVector.x;
				pos.z += m_moveVector.z;

				//2�i�K�ڂ̍U�������I��
				m_nextAttack1 = false;
			}
			if (i == 6)
			{
				//�A�j���[�V�������o�ߒ��̍��W�擾
				m_nowPos = MV1GetFramePosition(m_handle, m_moveAnimFrameIndex);
				m_moveVector = VSub(m_nowPos, m_prevPos);

				pos.x += m_moveVector.x;
				pos.z += m_moveVector.z;

				//3�i�K�ڂ̍U�������I��
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
/// ����𑕔��������̃A�j���[�V�����֐�
/// </summary>
/// <param name="time">�A�j���[�V�����^�C��</param>
void Player::WeaponAnimation(float& time)
{
	//����������ĂȂ����̃A�j���[�V�����u�����h��0�ɂ���
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

	//����������ĂȂ����p
	m_notWeaponAnimOne = false;

	//�v���C���[�������Ă��鎞
	if (m_status.s_hp >= 0.0f)
	{
		for (int i = 0; i < 20; i++)
		{
			//���󂯂����Ƃ�
			if (m_hitImpact == true)
			{

				if (i != 12 && i != 8 && i != 10)
				{
					pAnim->AnimationBlend(time, m_handle, m_animation[12], m_animation[i], m_animBlend, m_animOne[i], m_animOne[12], m_animBlendOne);
				}

				m_weaponMoveRight = false;

			}
			//����łȂ��Ƃ����󂯂��ĂȂ���
			if (m_hit == false && m_hitImpact == false)
			{
				//�����\���ė����Ă鎞
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

				//�v���C���[����������
				//A�{�^��������
				if (m_dashMove == true && m_moveflag == true && m_avoidance == false &&
					m_moveAttack == false && m_recoberyAction == false && m_itemTakingNow == false)
				{
					//�������o�O

					if (i != 15 && i != 8)
					{
						pAnim->AnimationBlend(time, m_handle, m_animation[15], m_animation[i], m_animBlend, m_animOne[i], m_animOne[15], m_animBlendOne);
					}

					m_weaponMoveRight = false;

				}
				//�����A�j���[�V����
				else if (m_moveflag == true && m_avoidance == false && m_moveAttack == false && 
					m_recoberyAction == false && m_itemTakingNow == false)
				{
					//�^�[�Q�b�g���ĂȂ���
					if (m_lockonTarget == false)
					{
						if (i != 14 && i != 8)
						{
							pAnim->AnimationBlend(time, m_handle, m_animation[14], m_animation[i], m_animBlend, m_animOne[i], m_animOne[14], m_animBlendOne);
						}
					}
					//�^�[�Q�b�g���Ă鎞
					else if (m_lockonTarget == true)
					{
						//������or�E����
						if (anX < -500 || anX > 500)
						{
							if (i != 18 && i != 8)
							{
								pAnim->AnimationBlend(time, m_handle, m_animation[18], m_animation[i], m_animBlend, m_animOne[i], m_animOne[18], m_animBlendOne);
							}

							//������
							if (anX < -500)
							{
								m_weaponMoveRight = false;
							}
							//�E����
							if (anX > 500)
							{
								m_weaponMoveRight = true;
							}
						}

						//����
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
				//�h��
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
/// �}�b�v�̓����蔻��
/// </summary>
/// <param name="map">�}�b�v�Ăяo��</param>
/// <param name="item">�A�C�e���Ăяo��</param>
void Player::HitObj(Map& map, ItemManager& item)
{
	int j;

	//�v���C���[�̎��͂ɂ���R���W�����̃|���S�����擾����
	HitDim = MV1CollCheck_Sphere(map.GetCollisionMap(), -1, map.GetVectorMapPos(), 1500.0f);

	//���o���ꂽ�|���S�����ǃ|���S��(XZ���ʂɐ����ȃ|���S��)�����|���S��(XZ���ʂɐ����ł͂Ȃ��|���S��)���𔻒f����
	for (int i = 0; i < HitDim.HitNum; i++)
	{
		//XZ���ʂɐ������ǂ����̓|���S���̖@����Y������0�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
		if (HitDim.Dim[i].Normal.y < 0.000001f && HitDim.Dim[i].Normal.y > -0.0000001f)
		{
			if (HitDim.Dim[i].Position[0].y > m_pos.y + 1.0f ||
				HitDim.Dim[i].Position[1].y > m_pos.y + 1.0f ||
				HitDim.Dim[i].Position[2].y > m_pos.y + 1.0f)
			{
				//�|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
				if (m_WallNum < PLAYER_MAX_HITCOLL)
				{
					//�|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
					m_Wall[m_WallNum] = &HitDim.Dim[i];

					//�ǃ|���S���̐������Z����
					m_WallNum++;
				}
			}
		}
	}

	//�ǃ|���S���Ɠ����蔻�菈��
	if (m_WallNum != 0)
	{
		//�ǂɓ����������ǂ����̃t���O�͏�����Ԃł́u�������Ă��Ȃ��v�ɂ��Ă���
		m_HitFlag = false;

		//�ړ��������ǂ����ŏ����𕪊�
		if (m_moveflag == true)
		{
			//�ǃ|���S���̐������J��Ԃ�
			for (int i = 0; i < m_WallNum; i++)
			{
				//i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				m_Poly = m_Wall[i];

				//�|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
				if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == false) continue;

				//�����ɂ�����|���S���ƃv���C���[���������Ă���Ƃ������ƂȂ̂ŁA�|���S���ɓ��������t���O�𗧂Ă�
				m_HitFlag = true;

				//�V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
				for (j = 0; j < m_WallNum; j++)
				{
					//j�Ԗڂ̕ǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
					m_Poly = m_Wall[j];

					//�������Ă����烋�[�v���甲����
					if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true) break;
				}

				//j��m_WallNum�������ꍇ�͂ǂ̃|���S���Ƃ�������Ȃ������Ƃ������ƂȂ̂�
				//�ǂɓ��������t���O��|���������Ń��[�v���甲����
				if (j == m_WallNum)
				{
					m_HitFlag = false;
					break;
				}
			
			}
		}
		else
		{
			//�ړ����Ă��Ȃ��ꍇ�̏���

			//�ǃ|���S���̐������J��Ԃ�
			for (int i = 0; i < m_WallNum; i++)
			{
				//i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				m_Poly = m_Wall[i];

				//�|���S���ɓ������Ă����瓖�������t���O�𗧂Ă���Ń��[�v���甲����
				if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true)
				{
					m_HitFlag = true;
					break;
				}

			}
		}

		//�ǂɓ������Ă�����ǂ��牟���o���������s��
		if (m_HitFlag == true)
		{
			//�ǂ���̉����o�����������݂�ő吔�����J��Ԃ�
			for (int i = 0; i < PLAYER_MAX_HITCOLL; i++)
			{
				//�ǃ|���S���̐������J��Ԃ�
				for (int k = 0; k < m_WallNum; k++)
				{
					//j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					m_Poly = m_Wall[k];

					//�v���C���[�Ɠ������Ă��邩����
					if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == false) continue;

					//�������Ă�����K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
					m_pos = VAdd(m_pos, VScale(m_Poly->Normal, m_status.s_speed / 2));

					//����s���������ꍇ
					if (m_avoidance == true)
					{
						//�������Ă�����K�苗�����v���C���[��@�������Ɉړ�������
						m_drawPos = VAdd(m_drawPos, VScale(m_Poly->Normal, m_bounceDis));
						m_pos = VAdd(m_pos, VScale(m_Poly->Normal, m_status.s_speed));
					}
					//�U�����������ꍇ
					if (m_moveAttack == true)
					{
						//�������Ă�����K�苗�����v���C���[��@�������Ɉړ�������
						m_drawPos = VAdd(m_drawPos, VScale(m_Poly->Normal, m_bounceDis));
						m_pos = VAdd(m_pos, VScale(m_Poly->Normal, m_status.s_speed));

					}

					//�ړ�������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
					for (j = 0; j < m_WallNum; j++)
					{
						//�������Ă����烋�[�v�𔲂���
						m_Poly = m_Wall[j];
						if (HitCheck_Capsule_Triangle(m_mapHitColl, VAdd(m_mapHitColl, VGet(0.0f, m_len, 0.0f)), m_capsuleRadius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true) break;

					}

					//���ׂẴ|���S���Ɠ������Ă��Ȃ������烋�[�v�I��
					if (j == m_WallNum) break;
				}

				//i��m_WallNum�ł͂Ȃ��ꍇ�͑S���̃|���S���ŉ����o�������݂�O�ɂ��ׂĂ̕ǃ|���S���ƐڐG���Ȃ��Ȃ����Ƃ������ƂȂ̂Ń��[�v���甲����
				if (i != m_WallNum) break;
			}
		}
	}

	MapAction(map, item);

	//���o�����v���C���[�̎��͂̃|���S�������������
	MV1CollResultPolyDimTerminate(HitDim);

}

/// <summary>
/// �}�b�v�̃M�~�b�N�Ǘ�
/// </summary>
/// <param name="map">�}�b�v���Ăяo��</param>
/// <param name="item">�A�C�e�����Ăяo��</param>
void Player::MapAction(Map& map, ItemManager& item)
{

	//�x�����\��������
	if (map.GetSavePossible() == true)
	{	
		//Y�{�^���������ꂽ��
		if (m_xpad.Buttons[15] == 1)
		{
			m_updatePosX = 95.0f;
			m_updatePosY = 0.0f;
			m_updatePosZ = -40.0f;

			//��񂾂����s
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
		//�A�C�e���������\��������
		if (map.GetItem(i) == true)
		{
			//Y�{�^���������ꂽ��
			if (m_xpad.Buttons[15] == 1)
			{
				m_itemTaking = true;

				//�A�C�e������������(�A�C�e���}�l�[�W���[�ɕԂ�)
				item.SetGetItem(i, true);
				//���������A�C�e���X�|�b�g������
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
/// �`�揈��
/// </summary>
void Player::Draw()
{
	//�����x�N�g��
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


	// ���̐�
	DrawLine3D(VGet(left, bottom, front), VGet(right, bottom, front), m_rectColor);
	DrawLine3D(VGet(left, top, front), VGet(right, top, front), m_rectColor);
	DrawLine3D(VGet(left, bottom, back), VGet(right, bottom, back), m_rectColor);
	DrawLine3D(VGet(left, top, back), VGet(right, top, back), m_rectColor);
	// �c�̐�
	DrawLine3D(VGet(left, top, front), VGet(left, bottom, front), m_rectColor);
	DrawLine3D(VGet(right, top, front), VGet(right, bottom, front), m_rectColor);
	DrawLine3D(VGet(left, top, back), VGet(left, bottom, back), m_rectColor);
	DrawLine3D(VGet(right, top, back), VGet(right, bottom, back), m_rectColor);
	// �O��̐�
	DrawLine3D(VGet(left, top, front), VGet(left, top, back), m_rectColor);
	DrawLine3D(VGet(left, bottom, front), VGet(left, bottom, back), m_rectColor);
	DrawLine3D(VGet(right, top, front), VGet(right, top, back), m_rectColor);
	DrawLine3D(VGet(right, bottom, front), VGet(right, bottom, back), m_rectColor);
#endif

#if false

	//��������ԗ��R�͂����炭m_drawPos����������

	//�J�v�Z��3D�̕`��
	DrawCapsule3D(pos1.GetVector(), pos2.GetVector(), m_capsuleRadius, 16, m_color, 0, false);

	//�~��3D�`��
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
	//	DrawFormatString(0, 100, 0xffffff, "�ǂɓ�������");
	//}
	//if (m_restAction == true)
	//{
	//	DrawFormatString(0, 80, 0xffffff, "�񕜂ł���");
	//}

	////DrawFormatString(0, 120, 0xffffff, "HitPoly : %d", HitDim.HitNum);
	//DrawFormatString(0, 0, 0xffffff, "playTime : %f", m_playTime);
	////�o�O�ōU����ԂɂȂ邪���[�V����������Ȃ�
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

	//Y��1000����-1000����
	//X��1000���E-1000����

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


	//���x�����グ�邽�߂̕ϐ��`��
	DrawFormatString(1400, 950, 0x000000, "%d", m_coreAllLevel);

	//3D���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_handle, m_drawPos);

	//3D���f���̉�]�n���Z�b�g����
	MV1SetRotationXYZ(m_handle, VGet(0.0f, m_angle - angleShield, 0.0f));

	//3D���f���`��
	MV1DrawModel(m_handle);
}

/// <summary>
/// ����`��
/// </summary>
/// <param name="eq">�����Ăяo��</param>
void Player::WeaponDraw(Equipment& eq)
{
	//������������
	if (eq.GetSword() == true)
	{
		weapon->RightDraw();
	}
	//������������
	if (eq.GetShield() == true)
	{
		weapon->LeftDraw();
	}
}

/// <summary>
/// �I������
/// </summary>
void Player::End()
{
	//���������
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

	//�������폜
	handle.Clear();
}

void Player::OnCollideEnter(const std::shared_ptr<Collidable>& collidable)
{
#if _DEBUG
	std::string message = "�v���C���[��";
#endif
	auto tag = collidable->GetTag();
	switch (tag)
	{
	case ObjectTag::Enemy:
#if _DEBUG
		message += "�G";
#endif
		break;
	case ObjectTag::Attack:
#if _DEBUG
		message += "�U��";
#endif
		break;
	case ObjectTag::Search:
#if _DEBUG
		message += "���G";
#endif
		break;
	case ObjectTag::Item:
#if _DEBUG
		message += "�A�C�e��";
#endif
		break;
	case ObjectTag::BossEnter:
#if _DEBUG
		message += "�{�X�����̓���";
#endif
		break;
	}

#if _DEBUG
	message += "�Ɠ�������\n";
	printfDx(message.c_str());
#endif
}

void Player::OnTriggerEnter(const std::shared_ptr<Collidable>& collidable)
{
#if _DEBUG
	std::string message = "�v���C���[��";
#endif
	auto tag = collidable->GetTag();
	switch (tag)
	{
	case ObjectTag::Enemy:
#if _DEBUG
		message += "�G";
#endif
		break;
	case ObjectTag::Attack:
	{
		//�G�̍U��������������HP�����炷

	}
		break;
	case ObjectTag::Search:
	{
		//�G�̍��G������������
	}
		break;
	case ObjectTag::Item:
	{
		//�A�C�e��������������
	}
		break;
	case ObjectTag::BossEnter:
	{
		//�{�X�̕����̓����ɓ���������
	}
		break;
	}

#if _DEBUG
	message += "�Ɠ�������\n";
	printfDx(message.c_str());
#endif
}

/// <summary>
/// �J�v�Z�������̓����蔻��
/// </summary>
/// <param name="col">�J�v�Z���^�P</param>
/// <param name="col1">�J�v�Z���^2</param>
/// <returns></returns>
bool Player::IsCapsuleHit(const CapsuleCol& col, const CapsuleCol& col1)
{
	bool isHit = m_capsuleCol.IsHitCapsule(col);
	bool isHitBoss = m_capsuleCol.IsHitCapsule(col1);

	m_a1 = isHit;

	if (isHit)
	{
		m_color = 0xffff00;

		//�������Ă�����K�苗�����v���C���[��@�������Ɉړ�������
		m_pos = VAdd(m_pos, VScale(m_bounceMove, m_status.s_speed / 2));

		//����s���������ꍇ
		//m_pos�������Ă���
		if (m_avoidance == true)
		{
			//�������Ă�����K�苗�����v���C���[��@�������Ɉړ�������
			m_pos.x -= m_moveVector.x * 3.5f;
			m_pos.z -= m_moveVector.z * 3.5f;
			m_drawPos.x -= m_moveVector.x * 3.5f;
			m_drawPos.z -= m_moveVector.z * 3.5f;


		}
		//�U�����������ꍇ
		else if (m_moveAttack == true)
		{
			//�������Ă�����K�苗�����v���C���[��@�������Ɉړ�������
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
		//�������Ă�����K�苗�����v���C���[��@�������Ɉړ�������
		m_pos = VAdd(m_pos, VScale(m_bounceMove, m_status.s_speed / 2));

		//����s���������ꍇ
		//m_pos�������Ă���
		if (m_avoidance == true)
		{
			//�������Ă�����K�苗�����v���C���[��@�������Ɉړ�������
			m_pos.x -= m_moveVector.x * 1.2f;
			m_pos.z -= m_moveVector.z * 1.2f;
			m_drawPos.x -= m_moveVector.x * 1.2f;
			m_drawPos.z -= m_moveVector.z * 1.2f;


		}
		//�U�����������ꍇ
		else if (m_moveAttack == true)
		{
			//�������Ă�����K�苗�����v���C���[��@�������Ɉړ�������
			m_pos.x -= m_moveVector.x * 1.2f;
			m_pos.z -= m_moveVector.z * 1.2f;
			m_drawPos.x -= m_moveVector.x * 1.2f;
			m_drawPos.z -= m_moveVector.z * 1.2f;
		}
	}

	return isHit || isHitBoss;
}

/// <summary>
/// �G�̍U���Ƃ̓����蔻��
/// </summary>
/// <param name="col">����</param>
/// <param name="damage">�_���[�W</param>
/// <returns></returns>
bool Player::isSphereHit(const SphereCol& col, float damage)
{
	bool isHit = m_capsuleCol.IsHitSphere(col);

	//�G���G�̍U���������Ă���

	//�_���[�W���󂯂�����
	if (isHit)
	{
		m_color = 0xffff00;

		//�_���[�W����񂾂��^����
		if (m_damageReceived == false)
		{
			PlaySoundMem(se->GetHitSE(), DX_PLAYTYPE_BACK, true);

			//��𒆂̃t���[�����ƃ_���[�W���󂯂Ȃ�
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
/// �{�X�U���Ƃ̓����蔻��
/// </summary>
/// <param name="col1">���̂P</param>
/// <param name="col2">���̂Q</param>
/// <param name="col3">���̂R</param>
/// <param name="bossdamage">�_���[�W</param>
/// <returns></returns>
bool Player::isBossSphereHit(const SphereCol& col1, const SphereCol& col2, const SphereCol& col3, float bossdamage)
{
	bool isBossAttackHit1 = m_capsuleCol.IsHitSphere(col1);
	bool isBossAttackHit2 = m_capsuleCol.IsHitSphere(col2);
	bool isBossAttackHit3 = m_capsuleCol.IsHitSphere(col3);

	if (isBossAttackHit1 || isBossAttackHit2 || isBossAttackHit3)
	{
		m_color = 0xffff00;

		//�_���[�W����񂾂��^����
		if (m_damageReceived == false)
		{
			PlaySoundMem(se->GetPlayerHitSE(), DX_PLAYTYPE_BACK, true);

			//��𒆂̃t���[�����ƃ_���[�W���󂯂Ȃ�
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
/// ���̂Ƌ�`�Ƃ̓����蔻��
/// </summary>
/// <param name="col">����</param>
/// <param name="damage">�_���[�W</param>
/// <returns></returns>
bool Player::isShieldHit(const SphereCol& col, float damage)
{
	bool isHit = m_rectCol.IsHitSphere(col);

	//�_���[�W���󂯂�����
	if (isHit)
	{

		//�����\������
		if (m_shieldNow == true)
		{
			m_rectColor = 0xffff00;

			//�U������񂾂��^����
			if (m_damageReceived == false)
			{
				m_status.s_stamina = m_status.s_stamina - damage * 1.2f;

				//�X�^�~�i��0�ȉ��ɂ����Ȃ�
				if (m_status.s_stamina < 0.0f)
				{
					m_status.s_stamina = 0.0f;
				}

				//���󂯔���
				m_hitImpact = true;

				m_damageReceived = true;
			}
		}

	}
	else
	{
		//�U�����󂯂ĂȂ����@�@�@�@�@
		if (m_hit == false)
		{
			m_damageReceived = false;
		}

		m_rectColor = 0xffffff;
	}

	return isHit;
}

/// <summary>
/// ���̂Ƌ�`�Ƃ̓����蔻��
/// </summary>
/// <param name="col1">���̂P</param>
/// <param name="col2">���̂Q</param>
/// <param name="col3">���̂R</param>
/// <param name="bossdamage">�_���[�W</param>
/// <returns></returns>
bool Player::isBossShieldHit(const SphereCol& col1, const SphereCol& col2, const SphereCol& col3, float bossdamage)
{
	bool isBossAttackHit1 = m_rectCol.IsHitSphere(col1);
	bool isBossAttackHit2 = m_rectCol.IsHitSphere(col2);
	bool isBossAttackHit3 = m_rectCol.IsHitSphere(col3);

	if (isBossAttackHit1 || isBossAttackHit2 || isBossAttackHit3)
	{
		//�����\������
		if (m_shieldNow == true)
		{
			m_rectColor = 0xffff00;

			//�U������񂾂��^����
			if (m_damageReceived == false)
			{

				m_status.s_stamina = m_status.s_stamina - bossdamage * 1.2f;

				//�X�^�~�i��0�ȉ��ɂ����Ȃ�
				if (m_status.s_stamina < 0.0f)
				{
					m_status.s_stamina = 0.0f;
				}

				//���󂯔���
				m_hitImpact = true;

				m_damageReceived = true;
			}
		}
	}
	else
	{
		//�U�����󂯂ĂȂ����@�@�@�@�@
		if (m_hit == false)
		{
			m_damageReceived = false;
		}

		m_rectColor = 0xffffff;
	}

	return isBossAttackHit1 || isBossAttackHit2 || isBossAttackHit3;
}

/// <summary>
/// ���̂ƃJ�v�Z���Ƃ̓����蔻��
/// </summary>
/// <param name="col">�J�v�Z���^</param>
/// <param name="max">�G�̍ő吔</param>
/// <returns></returns>
bool Player::isTargetHit(const CapsuleCol& col, int max)
{
	bool isHit = m_targetCunCol.IsHitCapsule(col);

	if (isHit)
	{
		//�^�[�Q�b�g�ł���悤�ɂȂ�
		m_targetNumber[max] = true;
	}
	else
	{
		m_targetNumber[max] = false;
	}

	return isHit;
}
