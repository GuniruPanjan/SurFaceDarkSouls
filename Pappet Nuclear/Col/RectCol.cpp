#include "RectCol.h"
#include<cmath>
#include "CapsuleCol.h"
#include "SphereCol.h"
#include "Matrix3.h"

RectCol::RectCol()
{
}

RectCol::~RectCol()
{
}

void RectCol::Init(const Pos3& pos, const Size& size)
{
	m_pos = pos;
	m_size = size;
}

void RectCol::Update(const Pos3& pos, const Size& size)
{
	m_pos = pos;
	m_size = size;
}

bool RectCol::IsHitCapsule(const CapsuleCol& col)
{

	//相対ベクトル
	Vec3 vec = col.GetPos() - m_pos;

	//値の絶対値化
	vec.x = fabs(vec.x);
	vec.y = fabs(vec.y);
	vec.z = fabs(vec.z);

	float trw = col.GetRadius() + (m_size.width * 0.5f);
	float trh = col.GetRadius() + (m_size.height * 0.5f);
	float trd = col.GetRadius() + (m_size.depth * 0.5f);

	//各成分の判定
	bool isHitX = vec.x < trw;
	bool isHitY = vec.y < trh;
	bool isHitZ = vec.z < trd;

	//判定
	return isHitX && isHitY && isHitZ;
}

bool RectCol::IsHitSphere(const SphereCol& col)
{
	//相対ベクトル
	Vec3 vec = col.GetPos() - m_pos;

	//値の絶対値化
	vec.x = fabs(vec.x);
	vec.y = fabs(vec.y);
	vec.z = fabs(vec.z);

	float trw = col.GetRadius() + (m_size.width * 0.5f);
	float trh = col.GetRadius() + (m_size.height * 0.5f);
	float trd = col.GetRadius() + (m_size.depth * 0.5f);

	//各成分の判定
	bool isHitX = vec.x < trw;
	bool isHitY = vec.y < trh;
	bool isHitZ = vec.z < trd;

	//判定
	return isHitX && isHitY && isHitZ;
}

bool RectCol::IsHItRect(const RectCol& rect)
{
	//相対ベクトルの作成
	auto vec = rect.GetPos() - m_pos;
	//値の絶対値化
	vec.x = fabs(vec.x);
	vec.y = fabs(vec.y);
	vec.z = fabs(vec.z);

	//それぞれのサイズの半分のものを作成
	Size size = (rect.GetSize() + m_size) * 0.5f;

	//各成分の判定
	bool isHitX = vec.x < size.width;
	bool isHitY = vec.y < size.height;
	bool isHitZ = vec.z < size.depth;

	//判定
	return isHitX && isHitY && isHitZ;
}
