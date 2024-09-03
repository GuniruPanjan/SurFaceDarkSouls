#pragma once
#include "Vec3.h"

class SphereCol;

class CapsuleCol
{
public:
	CapsuleCol();
	virtual ~CapsuleCol();

	void Init(const Pos3& pos, const Vec3& vec, float len, float radius);
	void Update(const Pos3& pos, const Vec3 vec);

	bool IsHitCapsule(const CapsuleCol& col);
	bool IsHitSphere(const SphereCol& col);

	const Pos3& GetPos() const { return m_pos; }
	const Vec3& GetVec() const { return m_vec; }
	float GetLength() const { return m_len; }
	float GetRadius() const { return m_radius; }

private:
	Pos3 m_pos;
	Vec3 m_vec;
	float m_len;
	float m_radius;
};

