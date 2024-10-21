#pragma once
#include "CollidableData.h"
#include "LibVec3.h"

namespace MyLibrary
{
	class CollidableDataCapsule : public CollidableData
	{
	public:
		//�R���X�g���N�^
		CollidableDataCapsule(bool isTrigger);

		LibVec3 m_vec;

		//����
		float m_len;

		//���a
		float m_radius;
	};
}



