#include "SphereCol.h"
#include "CapsuleCol.h"

SphereCol::SphereCol()
{
}

SphereCol::~SphereCol()
{
}

void SphereCol::Init(const Pos3& pos, float radius)
{
	m_pos = pos;
	m_radius = radius;
}

void SphereCol::Update(const Pos3& pos)
{
	m_pos = pos;
}

bool SphereCol::IsHitCapsule(const CapsuleCol& col)
{
	//向いている方向に伸びているベクトルを作成
	Vec3 dirVec = col.GetVec().GetNormalized() * col.GetLength() * 0.5f;

	//相対ベクトル
	Vec3 vec = col.GetPos() - m_pos;

	//相対ベクトルと正面ベクトルの内積
	float dot = Dot(vec, dirVec);
	//方向ベクトルの大きさを取得(2乗)
	float sqLen = dirVec.SqLength();

	//線分上のどこにあるかを確かめる
	float t = dot / sqLen;
	//範囲の制限
	if (t < -1.0f) t = -1.0f;  //下限
	if (t > 1.0f) t = 1.0f;  //上限

	//線分上での点までの最短距離
	Pos3 minPos = dirVec * t + m_pos;

	//最短距離と円の座標のベクトル大きさ(2乗)を取得
	sqLen = (minPos - col.GetPos()).SqLength();
	//半径の合計の2乗
	float radius = m_radius + col.GetRadius();
	radius = radius * radius;

	return sqLen < radius;
}
