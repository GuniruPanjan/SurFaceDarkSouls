#include "Effect.h"

Effect::Effect():
	m_effectJump(0),
	m_effectHeel(0),
	m_effectRest(0),
	m_effectHit(0)
{
}

Effect::~Effect()
{
	//メモリ解放
	DeleteEffekseerEffect(m_effectJump);
	DeleteEffekseerEffect(m_effectRest);
	DeleteEffekseerEffect(m_effectHeel);
	DeleteEffekseerEffect(m_effectHit);
}

void Effect::PlayerInit()
{
	m_effectRest = LoadEffekseerEffect("Data/Effect/Benediction.efkefc", 10.0f);
	m_effectHeel = LoadEffekseerEffect("Data/Effect/AnotherEffect/Sylph13.efkefc", 20.0f);
	m_effectHit = LoadEffekseerEffect("Data/Effect/AnotherEffect/HitEffect.efkefc", 1.0f);
}

void Effect::BossInit()
{
	m_effectJump = LoadEffekseerEffect("Data/Effect/BloodLance.efkefc", 10.0f);
}

void Effect::Update()
{
	//3D表示の設定をDXライブラリとEffekseer3D表示の設定に同期させる
	Effekseer_Sync3DSetting();

	//エフェクト更新
	UpdateEffekseer3D();
}

void Effect::Draw()
{
	//エフェクトの描画
	DrawEffekseer3D();
}

void Effect::End()
{
	//メモリ解放
	DeleteEffekseerEffect(m_effectJump);
	DeleteEffekseerEffect(m_effectRest);
	DeleteEffekseerEffect(m_effectHeel);
	DeleteEffekseerEffect(m_effectHit);
}
