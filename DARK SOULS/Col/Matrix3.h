#pragma once

struct Vec3;

struct Matrix3
{
	float Matrix[3][3];

	void Init();
	Matrix3 GetInverse();

	void SetLine(int lineNo, const Vec3& vec);
	void SetRow(int rowNo, const Vec3& vec);

	Vec3 GetLine(int lineNo);
	Vec3 GetRow(int rowNo);
};

