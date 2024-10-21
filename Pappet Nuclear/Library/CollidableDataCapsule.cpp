#include "CollidableDataCapsule.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="isTrigger"></param>
MyLibrary::CollidableDataCapsule::CollidableDataCapsule(bool isTrigger):
	CollidableData(CollidableData::Kind::Capsule, isTrigger),
	m_vec(),
	m_len(0.0f),
	m_radius(0.0f)
{
}
