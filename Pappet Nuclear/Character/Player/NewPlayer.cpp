#include "NewPlayer.h"

namespace
{
	//���f���T�C�Y
	constexpr float cModelSizeScale = 0.4f;

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

	//���f���ǂݍ���
	m_handle = handle.GetModelHandle("Data/Player/PuppetPlayerModel.mv1");

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
}

void NewPlayer::Finalize()
{
}

void NewPlayer::Update(std::shared_ptr<Equipment> eq)
{
}

void NewPlayer::Animation()
{
}

void NewPlayer::Draw(std::shared_ptr<Equipment> eq)
{
}

void NewPlayer::OnCollideEnter(const std::shared_ptr<Collidable>& collidable)
{
}

void NewPlayer::OnTriggerEnter(const std::shared_ptr<Collidable>& collidable)
{
}

void NewPlayer::SetModelPos()
{
}
