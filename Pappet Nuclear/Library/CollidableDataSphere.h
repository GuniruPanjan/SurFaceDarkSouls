#pragma once
#include "CollidableData.h"

namespace MyLibrary
{
	class CollidableDataSphere : public CollidableData
	{
	public:
		//�R���X�g���N�^
		CollidableDataSphere(bool isTrigger);

		//���a
		float m_radius;
	};
}



