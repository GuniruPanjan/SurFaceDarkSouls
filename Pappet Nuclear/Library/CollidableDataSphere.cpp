#include "CollidableDataSphere.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="isTrigger"></param>
MyLibrary::CollidableDataSphere::CollidableDataSphere(bool isTrigger):
	CollidableData(CollidableData::Kind::Sphere, isTrigger),
	m_radius(0.0f)
{
}
