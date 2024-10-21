#include "DebugDraw.h"
#include "DxLib.h"

std::list<MyLibrary::DebugDraw::CapsuleInfo> MyLibrary::DebugDraw::m_capsuleInfo;
std::list<MyLibrary::DebugDraw::SphereInfo> MyLibrary::DebugDraw::m_sphereInfo;
std::list<MyLibrary::DebugDraw::RectInfo> MyLibrary::DebugDraw::m_rectInfo;

/// <summary>
/// �`����̍폜
/// </summary>
void MyLibrary::DebugDraw::Clear()
{
	//���ׂĂ̕`���񃊃X�g�̒��g��S�폜
	m_capsuleInfo.clear();
	m_sphereInfo.clear();
	m_rectInfo.clear();
}

/// <summary>
/// �`��
/// </summary>
void MyLibrary::DebugDraw::Draw()
{
#if _DEBUG

	//�J�v�Z���̕`���񃊃X�g�ɂ����񕪕`�悷��
	for (auto& capsule : m_capsuleInfo)
	{
		capsule.vec = capsule.vec.GetNormalized() * capsule.len * 0.5f;

		DrawCapsule3D(VAdd(capsule.center.ConversionToVECTOR(), capsule.vec.ConversionToVECTOR()), VSub(capsule.center.ConversionToVECTOR(), capsule.vec.ConversionToVECTOR()),
			capsule.radius, 16, capsule.color, capsule.color, false);
	}

	//���̂̕`���񃊃X�g�ɂ����񕪕`�悷��
	for (auto& sphere : m_sphereInfo)
	{
		DrawSphere3D(sphere.center.ConversionToVECTOR(), sphere.radius, 16, sphere.color, sphere.color, false);
	}

	//��`�̕`���񃊃X�g�ɂ����񕪕`�悷��
	for (auto& rect : m_rectInfo)
	{
	}

#endif
}

/// <summary>
/// �J�v�Z���^�̕`�惊�X�g�ɒǉ�����
/// </summary>
/// <param name="center">���S���W</param>
/// <param name="vec">�x�N�^�[</param>
/// <param name="radius">���a</param>
/// <param name="len">����</param>
/// <param name="color">�F</param>
void MyLibrary::DebugDraw::AddDrawCapsule(const LibVec3& center, const LibVec3& vec, const float& radius, const float& len, const unsigned int& color)
{
	//�J�v�Z���^�̕`�惊�X�g�ɒǉ�����
	CapsuleInfo addInfo;
	addInfo.center = center;
	addInfo.vec = vec;
	addInfo.radius = radius;
	addInfo.len = len;
	addInfo.color = color;
	m_capsuleInfo.emplace_back(addInfo);
}

/// <summary>
/// ���̂̕`�惊�X�g�ɒǉ�����
/// </summary>
/// <param name="center">���S���W</param>
/// <param name="radius">���a</param>
/// <param name="color">�F</param>
void MyLibrary::DebugDraw::AddDrawSphere(const LibVec3& center, const float& radius, const unsigned int& color)
{
	//���̂̕`�惊�X�g�ɒǉ�����
	SphereInfo addInfo;
	addInfo.center = center;
	addInfo.radius = radius;
	addInfo.color = color;
	m_sphereInfo.emplace_back(addInfo);
}

/// <summary>
/// ��`�̕`�惊�X�g�ɒǉ�����
/// </summary>
/// <param name="center">���S���W</param>
/// <param name="size">�T�C�Y</param>
/// <param name="color">�F</param>
void MyLibrary::DebugDraw::AddDrawRect(const LibVec3& center, const LibVec3& size, const unsigned int& color)
{
	RectInfo addInfo;
	addInfo.center = center;
	addInfo.size = size;
	addInfo.color = color;
	m_rectInfo.emplace_back(addInfo);
}
