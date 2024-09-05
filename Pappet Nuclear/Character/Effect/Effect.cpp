#include "Effect.h"

Effect::Effect():
	m_effectJump(0)
{
}

Effect::~Effect()
{
	//���������
	DeleteEffekseerEffect(m_effectJump);
}

void Effect::PlayerInit()
{
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
}
