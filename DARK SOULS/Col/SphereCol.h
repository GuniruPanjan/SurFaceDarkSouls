#pragma once
#include "Vec3.h"

class CapsuleCol;

class SphereCol
{
public:
	SphereCol();
	virtual ~SphereCol();

	void Init(const Pos3& pos, float radius);
	void Update(const Pos3& pos);

	bool IsHitCapsule(const CapsuleCol& col);

	const Pos3& GetPos() const { return m_pos; }
	float GetRadius() const { return m_radius; }

private:
	Pos3 m_pos;
	float m_radius;

};

