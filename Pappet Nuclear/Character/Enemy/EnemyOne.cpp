#include "EnemyOne.h"

namespace
{
	//キャラクター名
	constexpr const char* cCharacterName = "Immortal";
	//モデルパス
	constexpr const char* cModelPath = "Data/Enemy/EnemyModel.mv1";
	//モデルの拡大率
	constexpr float cModelSizeScale = 0.4f;
	//押し出し当たり判定の半径
	constexpr float cCollisionRadius = 14.0f;
	//押し出し当たり判定の長さ
	constexpr float cCollisionLen = 40.0f;
	//押し出し当たり判定の長さ
	MyLibrary::LibVec3 cCollisionVec = MyLibrary::LibVec3(0.0f, 2.0f, 0.0f);
	//索敵範囲
	constexpr float cSearchRadius = 120.0f;
}

/// <summary>
/// コンストラクタ
/// </summary>
EnemyOne::EnemyOne() :
	EnemyBase(Collidable::Priority::Middle)
{
	//当たり判定の設定
	InitCollision(cCollisionVec, cCollisionLen, cCollisionRadius);
	//モデルの読み込み
	LoadModel(cModelPath);
	//索敵範囲の設定
	m_searchRadius = cSearchRadius;
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyOne::~EnemyOne()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="physics">物理クラスのポインタ</param>
void EnemyOne::Init(std::shared_ptr<MyLibrary::Physics> physics)
{
	//代入
	m_pPhysics = physics;

	Collidable::Init(m_pPhysics);

	//物理クラスの初期化
	InitRigidbody();

	//中心座標の設定
	CenterPos(1.0f, cModelSizeScale);

	//当たり判定の座標を設定
	m_collisionPos = rigidbody.GetPos();

	//モデルの座標を設定
	SetModelPos(cModelSizeScale);
	MV1SetPosition(m_handle, m_modelPos.ConversionToVECTOR());

	//索敵判定をする当たり判定を作成
	InitSearch(m_searchRadius);

	//モデルのサイズ設定
	MV1SetScale(m_handle, VGet(cModelSizeScale, cModelSizeScale, cModelSizeScale));

}

void EnemyOne::Update(MyLibrary::LibVec3 playerPos, bool isChase)
{
}

void EnemyOne::Draw()
{
}
