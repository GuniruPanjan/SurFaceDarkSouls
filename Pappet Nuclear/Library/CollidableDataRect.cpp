#include "CollidableDataRect.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="isTrigger"></param>
MyLibrary::CollidableDataRect::CollidableDataRect(bool isTrigger):
	CollidableData(CollidableData::Kind::Rect, isTrigger),
	m_size()
{
}
