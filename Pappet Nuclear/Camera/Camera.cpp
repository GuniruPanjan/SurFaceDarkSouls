#include "Camera.h"
#include "Map/Map.h"
//度をラジアンに変換
#define D2R(deg) ((deg)*DX_PI_F/180.0f)

namespace
{
	//敵とプレイヤーの座標の差を求める
	float difX[ENEMY_NOW];
	float difZ[ENEMY_NOW];

}


Camera::Camera():
	m_cameraAngle(VGet(0.0f,0.0f,0.0f)),
	m_cameraPos(VGet(0.0f,0.0f,0.0f)),
	m_cameraTarget(VGet(0.0f,0.0f,0.0f)),
	input(),
	m_radius(0.0f),
	m_HitFlag(false),
	m_WallNum(0),
	m_FloorNum(0),
	m_HitDimNum(0)
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

	m_radius = 3.0f;

	//基準となるカメラの座標
	m_cameraPos = VGet(0.0f, 50.0f, 100.0f);

	//カメラのターゲット座標初期化
	m_cameraTarget = VGet(0.0f, 5.0f, 0.0f);

	//カメラのアングル初期設定
	m_cameraAngle = VGet(D2R(-20.0f), 97.4f, 0.0f);

	SetCameraNearFar(1.0f, 1000.0f);
}

void Camera::Update(Player& player)
{
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	//敵をロックオンしてないとき
	if (player.GetLock() == false)
	{
		//左キー
		if (input.Rx < 0)
		{
			if (m_HitFlag == true)
			{
				m_cameraAngle.y -= D2R(1.0f);
			}
			else
			{
				m_cameraAngle.y += D2R(1.0f);
			}
			
		}
		//右キー
		if (input.Rx > 0)
		{
			if (m_HitFlag == true)
			{
				m_cameraAngle.y += D2R(1.0f);
			}
			else
			{
				m_cameraAngle.y -= D2R(1.0f);
			}
			
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

	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);
}

void Camera::LockUpdate(Player& player, Enemy& enemy, int max)
{
	//ロックオンしたとき
	if (player.GetLock() == true)
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
			//敵の距離がプレイヤーに近いやつをロックするようにする

			//注視点は敵の座標にする
			m_cameraTarget = VAdd(enemy.GetPos(max), VGet(0.0f, 20.0f, 0.0f));

			//プレイヤーとエネミーのX座標の差を求める
			float X = enemy.GetPosX(max) - player.GetPosX();

			//プレイヤーとエネミーのZ座標の差を求める
			float Z = enemy.GetPosZ(max) - player.GetPosZ();

			//角度を出す
			float angle = atan2f(X, Z);

			m_x = X;
			m_z = Z;

			//敵からプレイヤーに伸びる基準のベクトルを求める
			VECTOR pos = VSub(player.GetPos(), enemy.GetPos(max));

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

	difX[max] = enemy.GetPos(max).x - player.GetPos().x;
	difZ[max] = enemy.GetPos(max).z - player.GetPos().z;
}

void Camera::HitObj(Map& map)
{
	int j;

	//プレイヤーの周囲にあるコリジョンのポリゴンを取得する
	HitDim = MV1CollCheck_Sphere(map.GetCollisionMap(), -1, map.GetVectorMapPos(), 1500.0f);

	//検出されたポリゴンが壁ポリゴン(XZ平面に垂直なポリゴン)か床ポリゴン(XZ平面に垂直ではないポリゴン)かを判断する
	for (int i = 0; i < HitDim.HitNum; i++)
	{
		//XZ平面に垂直かどうかはポリゴンの法線のY成分が0に限りなく近いかどうかで判断する
		if (HitDim.Dim[i].Normal.y < 0.000001f && HitDim.Dim[i].Normal.y > -0.0000001f)
		{

			//ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
			if (m_WallNum < PLAYER_MAX_HITCOLL)
			{
				//ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
				m_Wall[m_WallNum] = &HitDim.Dim[i];

				//壁ポリゴンの数を加算する
				m_WallNum++;
			}

			if (HitDim.Dim[i].Position[0].y > m_cameraPos.y + 1.0f ||
				HitDim.Dim[i].Position[1].y > m_cameraPos.y + 1.0f ||
				HitDim.Dim[i].Position[2].y > m_cameraPos.y + 1.0f)
			{
				
			}
		}
	}

	//壁ポリゴンと当たり判定処理
	if (m_WallNum != 0)
	{
		//壁に当たったかどうかのフラグは初期状態では「当たっていない」にしておく
		m_HitFlag = false;

		//壁ポリゴンの数だけ繰り返し
		for (int i = 0; i < m_WallNum; i++)
		{
			//i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
			m_Poly = m_Wall[i];

			//ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
			if (HitCheck_Sphere_Triangle(m_cameraPos, m_radius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == false) continue;

			//ここにきたらポリゴンとプレイヤーが当たっているということなので、ポリゴンに当たったフラグを立てる
			m_HitFlag = true;

			//新たな移動座標で壁ポリゴンと当たっていないかどうかを判定する
			for (j = 0; j < m_WallNum; j++)
			{
				//j番目の壁ポリゴンと当たっていないかどうかを判定する
				m_Poly = m_Wall[j];

				//当たっていたらループから抜ける
				if (HitCheck_Sphere_Triangle(m_cameraPos, m_radius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true) break;
			}

			//jがm_WallNumだった場合はどのポリゴンとも当たらなかったということなので
			//壁に当たったフラグを倒したうえでループから抜ける
			if (j == m_WallNum)
			{
				m_HitFlag = false;
				break;
			}

		}

		//移動していない場合の処理

			//壁ポリゴンの数だけ繰り返し
		for (int i = 0; i < m_WallNum; i++)
		{
			//i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
			m_Poly = m_Wall[i];

			//ポリゴンに当たっていたら当たったフラグを立てた上でループから抜ける
			if (HitCheck_Sphere_Triangle(m_cameraPos, m_radius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true)
			{
				m_HitFlag = true;
				break;
			}

		}

		//移動したかどうかで処理を分岐
		//if (m_moveflag == true)
		//{
		//	
		//}
		//else
		//{
	
		//}

		//壁に当たっていたら壁から押し出す処理を行う
		if (m_HitFlag == true)
		{
			//壁からの押し出し処理を試みる最大数だけ繰り返す
			for (int i = 0; i < PLAYER_MAX_HITCOLL; i++)
			{
				//壁ポリゴンの数だけ繰り返し
				for (int k = 0; k < m_WallNum; k++)
				{
					//j番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					m_Poly = m_Wall[k];

					//プレイヤーと当たっているか判定
					if (HitCheck_Sphere_Triangle(m_cameraPos, m_radius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == false) continue;

					//当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
					m_cameraPos = VAdd(m_cameraPos, VScale(m_Poly->Normal, 1.0f));

					//移動した上で壁ポリゴンと接触しているかどうかを判定
					for (j = 0; j < m_WallNum; j++)
					{
						//当たっていたらループを抜ける
						m_Poly = m_Wall[j];
						if (HitCheck_Sphere_Triangle(m_cameraPos, m_radius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true) break;

					}

					//すべてのポリゴンと当たっていなかったらループ終了
					if (j == m_WallNum) break;
				}

				//iがm_WallNumではない場合は全部のポリゴンで押し出しを試みる前にすべての壁ポリゴンと接触しなくなったということなのでループから抜ける
				if (i != m_WallNum) break;
			}
		}
	}

	//検出したプレイヤーの周囲のポリゴン情報を解放する
	MV1CollResultPolyDimTerminate(HitDim);
}

void Camera::Draw()
{
	DrawFormatString(0, 240, 0xffffff, "dif1.x : %f,dif1.z : %f", difX[0], difZ[0]);
	DrawFormatString(0, 260, 0xffffff, "dif2.x : %f,dif2.z : %f", difX[1], difZ[1]);
	DrawFormatString(0, 280, 0xffffff, "dif3.x : %f,dif3.z : %f", difX[2], difZ[2]);
	DrawFormatString(0, 300, 0xffffff, "dif4.x : %f,dif4.z : %f", difX[3], difZ[3]);
	DrawFormatString(0, 320, 0xffffff, "dif5.x : %f,dif5.z : %f", difX[4], difZ[4]);

}

void Camera::End()
{
}
