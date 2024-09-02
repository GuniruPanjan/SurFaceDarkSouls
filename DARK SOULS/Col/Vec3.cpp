#include "Vec3.h"
#include <cassert>
#include <cmath>

Size Size::operator+(const Size& size) const
{
	return Size(width + size.width, height + size.height, depth + size.depth);
}

Size Size::operator*(float scale) const
{
	return Size(width * scale, height * scale, depth * scale);
}

Vec3::Vec3() :
	x(0.0f),
	y(0.0f),
	z(0.0f)
{
}

Vec3::Vec3(float X, float Y, float Z) :
	x(X),
	y(Y),
	z(Z)
{
}
Vec3 Vec3::Reverse()
{
	return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator+(const Vec3& vec) const
{
	return Vec3(x + vec.x, y + vec.y, z + vec.z);
}

void Vec3::operator+=(const Vec3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
}

Vec3 Vec3::operator-(const Vec3& vec) const
{
	return Vec3(x - vec.x, y - vec.y, z - vec.z);
}

void Vec3::operator-=(const Vec3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
}

Vec3 Vec3::operator*(float scale) const
{
	return Vec3(x * scale, y * scale, z * scale);
}

void Vec3::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;

}

Vec3 Vec3::operator/(float scale) const
{
	return Vec3(x / scale, y / scale, z / scale);
}

void Vec3::operator/=(float scale)
{
	x /= scale;
	y /= scale;
	z /= scale;
}

bool Vec3::operator==(const Vec3& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z;
}

bool Vec3::operator!=(const Vec3& vec) const
{
	return !(*this == vec);
}

float Vec3::Length() const
{
	return sqrtf(SqLength());
}

float Vec3::SqLength() const
{
	return x * x + y * y + z * z;
}

void Vec3::Normalize()
{
	float len = Length();
	//í∑Ç≥0ÇÃèÍçá
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

Vec3 Vec3::GetNormalized() const
{
	float len = Length();
	//í∑Ç≥0ÇÃèÍçá
	if (len == 0.0f)
	{
		return Vec3();
	}

	return Vec3(x / len, y / len, z / len);
}

Vec3 Lerp(const Vec3& start, const Vec3& end, float t)
{
	float x = start.x + t * (end.x - start.x);
	float y = start.y + t * (end.y - start.y);
	float z = start.z + t * (end.z - start.z);

	return Vec3(x, y, z);
}

float Dot(const Vec3& vec1, const Vec3& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

Vec3 Cross(const Vec3& vec1, const Vec3& vec2)
{
	Vec3 vec;

	vec.x = vec1.y * vec2.z - vec1.z * vec2.y;
	vec.y = vec1.z * vec2.x - vec1.x * vec2.z;
	vec.z = vec1.x * vec2.y - vec1.y * vec2.x;

	return vec;
}
