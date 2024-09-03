#include "Camera.h"
//度をラジアンに変換
#define D2R(deg) ((deg)*DX_PI_F/180.0f)

Camera::Camera():
	m_cameraAngle(VGet(0.0f,0.0f,0.0f)),
	m_cameraPos(VGet(0.0f,0.0f,0.0f)),
	m_cameraTarget(VGet(0.0f,0.0f,0.0f)),
	input()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	//基準となるカメラの座標
	m_cameraPos = VGet(0.0f, 50.0f, -100.0f);

	//カメラのターゲット座標初期化
	m_cameraTarget = VGet(0.0f, 5.0f, 0.0f);

	//カメラのアングル初期設定
	m_cameraAngle = VGet(D2R(-20.0f), 0.0f, 0.0f);

	SetCameraNearFar(1.0f, 1000.0f);
}

void Camera::Update(Player& player, Enemy& enemy)
{
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	//敵をロックオンしてないとき
	if (player.GetLock() == false)
	{
		//左キー
		if (input.Rx < 0)
		{
			m_cameraAngle.y += D2R(1.0f);
		}
		//右キー
		if (input.Rx > 0)
		{
			m_cameraAngle.y -= D2R(1.0f);
		}
		//上キー
		if (input.Ry < 0)
		{
			//カメラがプレイヤーを超えないくらいまで
			if (m_cameraAngle.x <= 0.7f)
			{
				m_cameraAngle.x += D2R(1.0f);
			}

		}
		//下キー
		if (input.Ry > 0)
		{
			//カメラが地面にめりこまないように
			if (m_cameraPos.y >= 15.2f + player.GetPosY())
			{
				m_cameraAngle.x -= D2R(1.0f);
			}

		}

		//基準のベクトル
		VECTOR Direction = VGet(0.0f, 100.0f, -100.0f);

		//X軸回転行列
		MATRIX matrixX = MGetRotX(m_cameraAngle.x);
		//Y軸回転行列
		MATRIX matrixY = MGetRotY(m_cameraAngle.y);

		//行列の合成
		MATRIX matrix = MMult(matrixX, matrixY);

		//基準ベクトルを行列で変換
		Direction = VTransform(Direction, matrix);

		//カメラ座標はプレイヤー座標から少しはなれたところ
		m_cameraPos = VAdd(player.GetPos(), Direction);

		//注視点の座標はプレイヤー座標の少し上
		m_cameraTarget = VAdd(player.GetPos(), VGet(0.0f, 50.0f, 0.0f));
	}
	//ロックオンしたとき
	else if (player.GetLock() == true)
	{
		//ボス戦の時のカメラ
		if (enemy.GetBattale() == true)
		{
			//注視点は敵の座標にする
			m_cameraTarget = VAdd(enemy.GetBossPos(), VGet(0.0f, 20.0f, 0.0f));

			//プレイヤーとエネミーのX座標の差を求める
			float X = enemy.GetBossPosX() - player.GetPosX();

			//プレイヤーとエネミーのZ座標の差を求める
			float Z = enemy.GetBossPosZ() - player.GetPosZ();

			//角度を出す
			float angle = atan2f(X, Z);

			m_x = X;
			m_z = Z;

			//敵からプレイヤーに伸びる基準のベクトルを求める
			VECTOR pos = VSub(player.GetPos(), enemy.GetBossPos());

			//ベクトルの正規化
			VECTOR posTarget = VNorm(pos);

			posTarget.x *= 130.0f;
			posTarget.z *= 130.0f;

			//カメラがどれだけプレイヤーの座標より高いかを設定
			posTarget.y = 80.0f;

			m_cameraAngle.y = angle;

			//プレイヤーの座標に求めたベクトルを足して、カメラの座標とする
			m_cameraPos = VAdd(player.GetPos(), posTarget);
		}
		//ボス戦以外のターゲット
		if (enemy.GetBattale() == false)
		{
			//注視点は敵の座標にする
			m_cameraTarget = VAdd(enemy.GetPos(), VGet(0.0f, 20.0f, 0.0f));

			//プレイヤーとエネミーのX座標の差を求める
			float X = enemy.GetPosX() - player.GetPosX();

			//プレイヤーとエネミーのZ座標の差を求める
			float Z = enemy.GetPosZ() - player.GetPosZ();

			//角度を出す
			float angle = atan2f(X, Z);

			m_x = X;
			m_z = Z;

			//敵からプレイヤーに伸びる基準のベクトルを求める
			VECTOR pos = VSub(player.GetPos(), enemy.GetPos());

			//ベクトルの正規化
			VECTOR posTarget = VNorm(pos);

			posTarget.x *= 130.0f;
			posTarget.z *= 130.0f;

			//カメラがどれだけプレイヤーの座標より高いかを設定
			posTarget.y = 80.0f;

			m_cameraAngle.y = angle;

			//プレイヤーの座標に求めたベクトルを足して、カメラの座標とする
			m_cameraPos = VAdd(player.GetPos(), posTarget);
		}
	}

	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);
}

void Camera::Draw()
{
}

void Camera::End()
{
}
