#include "Effect.h"

Effect::Effect():
	m_effectJump(0),
	m_effectHeel(0),
	m_effectRest(0),
	m_effectHit(0),
	m_effectItem(0)
{
}

Effect::~Effect()
{
	//���������
	DeleteEffekseerEffect(m_effectJump);
	DeleteEffekseerEffect(m_effectRest);
	DeleteEffekseerEffect(m_effectHeel);
	DeleteEffekseerEffect(m_effectHit);
	DeleteEffekseerEffect(m_effectItem);
}

void Effect::PlayerInit()
{
	m_effectRest = LoadEffekseerEffect("Data/Effect/Benediction.efkefc", 10.0f);
	m_effectHeel = LoadEffekseerEffect("Data/Effect/AnotherEffect/Sylph13.efkefc", 20.0f);
}

void Effect::BossInit()
{
	m_effectJump = LoadEffekseerEffect("Data/Effect/BloodLance.efkefc", 10.0f);
}

void Effect::AllInit()
{
	m_effectHit = LoadEffekseerEffect("Data/Effect/HitEffect.efkefc", 7.0f);
	m_effectItem = LoadEffekseerEffect("Data/Effect/Item.efkefc", 5.0f);
}

void Effect::Update()
{
	//Position������������
	SetPosPlayingEffekseer3DEffect(m_effectItem, -10000.0f, -10000.0f, -10000.0f);

	//3D�\���̐ݒ��DX���C�u������Effekseer3D�\���̐ݒ�ɓ���������
	Effekseer_Sync3DSetting();

	//�G�t�F�N�g�X�V
	UpdateEffekseer3D();
}

void Effect::Draw()
{
	//�G�t�F�N�g�̕`��
	DrawEffekseer3D();
}

void Effect::End()
{
	//���������
	DeleteEffekseerEffect(m_effectJump);
	DeleteEffekseerEffect(m_effectRest);
	DeleteEffekseerEffect(m_effectHeel);
	DeleteEffekseerEffect(m_effectHit);
	DeleteEffekseerEffect(m_effectItem);
}
