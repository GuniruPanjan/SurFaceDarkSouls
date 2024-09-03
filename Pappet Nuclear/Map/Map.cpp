#include "Map.h"

Map::Map():
	m_handle(0),
	m_collisionHandle(0),
	m_size(0.0f),
	m_Xposition(0.0f),
	m_Yposition(0.0f),
	m_Zposition(0.0f),
	m_XCollisionposition(0.0f),
	m_YCollisionposition(0.0f),
	m_ZCollisionposition(0.0f),
	m_bossRoomEntered(false),
	m_saveSpot(false),
	m_oneInit(false),
	m_sphereRadius(0.0f)
{
	m_MapPosition = VGet(0.0f, 0.0, 0.0f);
	m_collisionMapPosition = VGet(0.0f, 0.0f, 0.0f);
}

Map::~Map()
{
	//メモリ解放
	MV1DeleteModel(m_handle);
}

void Map::Init()
{
	m_bossRoomEntered = false;

	if (m_oneInit == false)
	{
		//モデル読み込み
		m_handle = MV1LoadModel("Data/Map/Map.mv1");
		m_collisionHandle = MV1LoadModel("Data/Map/Collision.mv1");

		//モデルのサイズ
		m_size = 0.12f;

		//ポジション初期化
		m_Xposition = 0.0f;
		m_Yposition = 250.0f;
		m_Zposition = 0.0f;

		m_XCollisionposition = -241.0f;
		m_YCollisionposition = -277.0f;
		m_ZCollisionposition = -173.0f;

		//モデルのサイズ変更
		MV1SetScale(m_handle, VGet(m_size, m_size, m_size));
		MV1SetScale(m_collisionHandle, VGet(m_size, m_size, m_size));

		//マップのポジション設定
		m_MapPosition = VGet(m_Xposition, m_Yposition, m_Zposition);
		m_collisionMapPosition = VGet(m_XCollisionposition, m_YCollisionposition, m_ZCollisionposition);

		//RectColの設定
		m_rectPos = Pos3(-10.0f, 50.0f, 0.0f);
		m_spherePos = Pos3(100.0f, 50.0f, -75.0f);
		m_rectSize = Size(5.0f, 50.0f, 70.0f);
		m_sphereRadius = 50.0f;
		m_rectCol.Init(m_rectPos, m_rectSize);
		m_sphereCol.Init(m_spherePos, m_sphereRadius);

		m_oneInit = true;
	}

	
}

void Map::Update()
{
	
}

void Map::Draw()
{
	float halfW = m_rectSize.width * 0.5f;
	float halfH = m_rectSize.height * 0.5f;
	float halfD = m_rectSize.depth * 0.5f;

	float right = m_rectPos.x + halfW;
	float left = m_rectPos.x - halfW;
	float top = m_rectPos.y + halfH;
	float bottom = m_rectPos.y - halfH;
	float front = m_rectPos.z - halfD;
	float back = m_rectPos.z + halfD;

	// 横の線
	DrawLine3D(VGet(left, bottom, front), VGet(right, bottom, front), m_color);
	DrawLine3D(VGet(left, top, front), VGet(right, top, front), m_color);
	DrawLine3D(VGet(left, bottom, back), VGet(right, bottom, back), m_color);
	DrawLine3D(VGet(left, top, back), VGet(right, top, back), m_color);
	// 縦の線
	DrawLine3D(VGet(left, top, front), VGet(left, bottom, front), m_color);
	DrawLine3D(VGet(right, top, front), VGet(right, bottom, front), m_color);
	DrawLine3D(VGet(left, top, back), VGet(left, bottom, back), m_color);
	DrawLine3D(VGet(right, top, back), VGet(right, bottom, back), m_color);
	// 前後の線
	DrawLine3D(VGet(left, top, front), VGet(left, top, back), m_color);
	DrawLine3D(VGet(left, bottom, front), VGet(left, bottom, back), m_color);
	DrawLine3D(VGet(right, top, front), VGet(right, top, back), m_color);
	DrawLine3D(VGet(right, bottom, front), VGet(right, bottom, back), m_color);

	DrawSphere3D(m_spherePos.GetVector(), m_sphereRadius, 16, m_sphereColor, m_sphereColor, false);

	//3Dモデルのポジション設定
	MV1SetPosition(m_handle, m_MapPosition);
	MV1SetPosition(m_collisionHandle, m_collisionMapPosition);

	//モデル描画
	MV1DrawModel(m_handle);
	//MV1DrawModel(m_collisionHandle);
}

void Map::End()
{
	//メモリ解放
	MV1DeleteModel(m_handle);
	MV1DeleteModel(m_collisionHandle);
}

bool Map::CapsuleIsHit(const CapsuleCol& col)
{
	bool isHit = m_rectCol.IsHitCapsule(col);

	if (isHit)
	{
		m_color = 0xff00ff;

		m_bossRoomEntered = true;
	}
	else
	{
		m_color = 0xffffff;
	}

	return isHit;
}

bool Map::CapsuleSaveHit(const CapsuleCol& col)
{
	bool isHit = m_sphereCol.IsHitCapsule(col);

	if (isHit)
	{
		m_sphereColor = 0xff00ff;

		m_saveSpot = true;
	}
	else
	{
		m_sphereColor = 0xffffff;

		m_saveSpot = false;
	}

	return isHit;
}
