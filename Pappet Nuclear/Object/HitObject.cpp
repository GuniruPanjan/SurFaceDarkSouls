#include "HitObject.h"
#include "AttackObject.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="radius">半径</param>
/// <param name="len">長さ</param>
/// <param name="vec">ベクトル</param>
HitObject::HitObject(float radius, float len, MyLibrary::LibVec3 vec) :
	ObjectBase(Priority::Low, ObjectTag::Hit),
	m_pPhysics(),
	m_lastHitObjectAttack(0),
	m_hitObjectTag(),
	m_isEnemy(false),
	m_isHit(false)
{
	//当たり判定の設定
	auto collider = Collidable::AddCollider(MyLibrary::CollidableData::Kind::Capsule, true);
	auto capsuleCol = dynamic_cast<MyLibrary::CollidableDataCapsule*>(collider.get());
	capsuleCol->m_radius = radius;
	capsuleCol->m_len = len;
	capsuleCol->m_vec = vec;
}

/// <summary>
/// デストラクタ
/// </summary>
HitObject::~HitObject()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="physics">物理クラスのポインタ</param>
/// <param name="pos">設定座標</param>
/// <param name="isEnemy">持ち主がEnemyがどうか</param>
void HitObject::Init(std::shared_ptr<MyLibrary::Physics> physics, MyLibrary::LibVec3 pos, bool isEnemy)
{
	m_pPhysics = physics;
	m_isEnemy = isEnemy;

	Collidable::Init(m_pPhysics);

	rigidbody.Init();
	rigidbody.SetPos(pos);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="pos">設定座標</param>
void HitObject::Update(MyLibrary::LibVec3 pos)
{
	rigidbody.SetPos(pos);
}

/// <summary>
/// 当たり判定を削除
/// </summary>
/// <param name="physics">物理クラスのポインタ</param>
void HitObject::Finalize(std::shared_ptr<MyLibrary::Physics> physics)
{
	Collidable::Finalize(physics);
}

/// <summary>
/// 他のオブジェクトに当たった時
/// </summary>
/// <param name="collidable"></param>
void HitObject::OnTriggerEnter(const std::shared_ptr<Collidable>& collidable)
{
	m_hitObjectTag = collidable->GetTag();
	if (m_isEnemy)
	{
		if (m_hitObjectTag == ObjectTag::Attack)
		{
			AttackObject* col = dynamic_cast<AttackObject*>(collidable.get());
			m_lastHitObjectAttack = col->GetAttack();
		}
		m_isHit = true;
	}
	else
	{
		if (m_hitObjectTag == ObjectTag::Attack)
		{
			AttackObject* col = dynamic_cast<AttackObject*>(collidable.get());
			m_lastHitObjectAttack = col->GetAttack();
		}
		m_isHit = true;

	}
}

/// <summary>
/// 当たったオブジェクトの攻撃力を取得
/// </summary>
/// <returns></returns>
int HitObject::GetIsAttackNum()
{
	return m_lastHitObjectAttack;
}

/// <summary>
/// 他のオブジェクトに当たったかどうか
/// </summary>
/// <returns></returns>
bool HitObject::GetIsHit()
{
	//trueを返したときだけfalseにする
	if (m_isHit)
	{
		m_isHit = false;
		return true;
	}

	return false;
}
