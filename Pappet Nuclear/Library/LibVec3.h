#pragma once
#include "DxLib.h"
#include <cassert>
#include <cmath>

namespace MyLibrary
{
	//3�����x�N�g���������N���X
	class LibVec3
	{
	public:
		float x, y, z;

		//�����Ȃ��R���X�g���N�^
		LibVec3() :
			x(0.0f),
			y(0.0f),
			z(0.0f)
		{

		}
		//��������R���X�g���N�^
		LibVec3(float X, float Y, float Z) :
			x(X),
			y(Y),
			z(Z)
		{

		}

		//�P�����Z�q
		LibVec3 Reverse()
		{
			return LibVec3(-x, -y, -z);
		}
		//�����Z
		LibVec3 operator+(const LibVec3& vec) const
		{
			return LibVec3(x + vec.x, y + vec.y, z + vec.z);
		}
		//Vec3 += Vec3
		void operator+=(const LibVec3& vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
		}
		//�����Z
		LibVec3 operator-(const LibVec3& vec) const
		{
			return LibVec3(x - vec.x, y - vec.y, z - vec.z);
		}
		//Vec3 -= Vec3
		void operator-=(const LibVec3& vec)
		{
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
		}
		//�|���Z
		LibVec3 operator*(float scale) const
		{
			return LibVec3(x * scale, y * scale, z * scale);
		}
		//Vec3 *= scale
		void operator*=(float scale)
		{
			x *= scale;
			y *= scale;
			z *= scale;
		}
		//����Z
		LibVec3 operator/(float scale) const
		{
			return LibVec3(x / scale, y / scale, z / scale);
		}
		//Vec3 /= scale
		void operator/=(float scale)
		{
			x /= scale;
			y /= scale;
			z /= scale;
		}
		//Vec3 == Vec3�������ꍇ
		bool operator==(const LibVec3& vec) const
		{
			return x == vec.x && y == vec.y && z == vec.z;
		}
		//Vec3 != Vec3�������ꍇ
		bool operator!=(const LibVec3& vec) const
		{
			return !(*this == vec);
		}

		//Dxlib�̊֐����g���ۂɁAVECTOR�^�ɕϊ�����֐�
		VECTOR GetVector() const { return VGet(x, y, z); }

		//�������擾
		float Length() const
		{
			return sqrtf(SqLength());
		}

		//������2����擾
		float SqLength() const
		{
			return x * x + y * y + z * z;
		}

		//���g�̐��K��
		LibVec3 Normalize()
		{
			float len = Length();
			//����0�̏ꍇ
			if (len == 0.0f)
			{
				assert(false);
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
				return;
			}

			*this /= len;
		}

		//���K���������ʂ��擾
		LibVec3 GetNormalized() const
		{
			float len = Length();
			//����0�̏ꍇ
			if (len == 0.0f)
			{
				return LibVec3();
			}

			return LibVec3(x / len, y / len, z / len);
		}

		/// <summary>
		/// �T�C�Y�\����
		/// </summary>
		struct Size
		{
			//��
			float width = 0.0f;
			//����
			float height = 0.0f;
			//���s
			float depth = 0.0f;

			Size() :
				width(0.0f),
				height(0.0f),
				depth(0.0f)
			{
			}
			Size(float inwidth, float inheight, float indepth) :
				width(inwidth),
				height(inheight),
				depth(indepth)
			{

			}
			//�����Z
			Size operator+(const Size& size) const
			{
				return Size(width + size.width, height + size.height, depth + size.depth);
			}
			//�|���Z
			Size operator*(float scale) const
			{
				return Size(width * scale, height * scale, depth * scale);
			}
		};


		/// <summary>
        /// ���`���
        /// </summary>
        /// <param name="start">�X�^�[�g</param>
        /// <param name="end">�I��</param>
        /// <param name="t">����</param>
        /// <returns>��Ԍ�</returns>
		LibVec3 Lerp(const LibVec3& start, const LibVec3& end, float t)
		{
			float x = start.x + t * (end.x - start.x);
			float y = start.y + t * (end.y - start.y);
			float z = start.z + t * (end.z - start.z);

			return LibVec3(x, y, z);
		}

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="vec1">�x�N�g��1</param>
		/// <param name="vec2">�x�N�g��2</param>
		/// <returns></returns>
		float Dot(const LibVec3& vec1, const LibVec3& vec2)
		{
			return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
		}

		/// <summary>
		/// �O��
		/// </summary>
		/// <param name="vec1">�x�N�g��1</param>
		/// <param name="vec2">�x�N�g��2</param>
		/// <returns></returns>
		LibVec3 Cross(const LibVec3& vec1, const LibVec3& vec2)
		{
			LibVec3 vec;

			vec.x = vec1.y * vec2.z - vec1.z * vec2.y;
			vec.y = vec1.z * vec2.x - vec1.x * vec2.z;
			vec.z = vec1.x * vec2.y - vec1.y * vec2.x;

			return vec;
		}

		//VECTOR�^�ɕϊ�
		VECTOR ConversionToVECTOR()
		{
			VECTOR ret = VGet(0.0f, 0.0f, 0.0f);
			ret.x = this->x;
			ret.y = this->y;
			ret.z = this->z;
			return ret;
		}

		using Pos3 = LibVec3;
	};
}


