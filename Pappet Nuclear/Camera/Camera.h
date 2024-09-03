#pragma once
#include "Character/Player/Player.h"
#include "Character/Enemy/Enemy.h"
#include <cmath>

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void Init();
	void Update(Player& player, Enemy& enemy);
	void Draw();
	void End();

	float GetAngleX() { return m_cameraAngle.x; }
	float GetAngleY() { return m_cameraAngle.y; }
	float GetAngleZ() { return m_cameraAngle.z; }
	VECTOR GetAngle() { return m_cameraAngle; }

private:
	DINPUT_JOYSTATE input;

	//カメラのポジション
	VECTOR m_cameraPos = VGet(0.0f, 0.0f, 0.0f);

	//カメラのターゲット
	VECTOR m_cameraTarget = VGet(0.0f, 0.0f, 0.0f);

	//カメラのアングル
	VECTOR m_cameraAngle = VGet(0.0f, 0.0f, 0.0f);

	float m_x, m_z;
};

