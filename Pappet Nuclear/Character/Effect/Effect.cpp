#include "Effect.h"

Effect::Effect():
	m_effectJump(0)
{
}

Effect::~Effect()
{
	//���������
	DeleteEffekseerEffect(m_effectJump);
	DeleteEffekseerEffect(m_effectRest);
	DeleteEffekseerEffect(m_effectHeel);
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

void Effect::Update()
{
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
}
