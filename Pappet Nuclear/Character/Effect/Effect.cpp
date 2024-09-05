#include "Effect.h"

Effect::Effect():
	m_effectClaw1(0),
	m_effectClaw2(0),
	m_effectJump(0)
{
}

Effect::~Effect()
{
	//メモリ解放
	DeleteEffekseerEffect(m_effectJump);
}

void Effect::PlayerInit()
{
}

void Effect::BossInit()
{
	m_effectClaw1 = LoadEffekseerEffect("Data/Effect/Claw1.efkefc", 10.0f);
	m_effectClaw2 = LoadEffekseerEffect("Data/Effect/Claw2.efkefc", 10.0f);
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
}
