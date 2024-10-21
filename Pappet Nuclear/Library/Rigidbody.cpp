#include "Rigidbody.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
MyLibrary::Rigidbody::Rigidbody():
	m_pos(),
	m_nextPos(),
	m_dir(),
	m_velocity(),
	m_useGravity(true)
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="gravity">�d��</param>
void MyLibrary::Rigidbody::Init(bool gravity)
{
	m_pos = LibVec3();
	m_dir = LibVec3();
	m_velocity = LibVec3();
	this->m_useGravity = gravity;
}

/// <summary>
/// velocity�ɗ͂�������
/// </summary>
/// <param name="force">�������</param>
void MyLibrary::Rigidbody::AddForce(const LibVec3& force)
{
	m_velocity = m_velocity + force;
}

/// <summary>
/// Velocity��Set��Dir�����v�Z
/// </summary>
/// <param name="set">Velocity</param>
/// <param name="mul">����</param>
void MyLibrary::Rigidbody::SetVelocity(LibVec3 set, float mul)
{
	m_velocity = set * mul;

	if (m_velocity.SqLength() > 0)
	{
		m_dir = m_velocity.Normalize();
	}
}
