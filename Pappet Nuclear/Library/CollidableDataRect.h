#pragma once
#include "CollidableData.h"
#include "LibVec3.h"

namespace MyLibrary
{
	class CollidableDataRect : public CollidableData
	{
	public:
		//�R���X�g���N�^
		CollidableDataRect(bool isTrigger);

		//�T�C�Y
		LibVec3 m_size;
	};
}



