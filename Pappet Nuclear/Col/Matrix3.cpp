#include "Matrix3.h"
#include "Vec3.h"

void Matrix3::Init()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j == i)
			{
				Matrix[i][j] = 1.0f;
			}
			else
			{
				Matrix[i][j] = 0.0f;
			}
		}
	}
}

Matrix3 Matrix3::GetInverse()
{
	//ŠÈˆÕŽÀ‘•
	Matrix3 mat;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mat.Matrix[j][i] = Matrix[i][j];
		}
	}

	return mat;
}

void Matrix3::SetLine(int lineNo, const Vec3& vec)
{
	Matrix[0][lineNo] = vec.x;
	Matrix[1][lineNo] = vec.y;
	Matrix[2][lineNo] = vec.z;

}

void Matrix3::SetRow(int rowNo, const Vec3& vec)
{
	Matrix[rowNo][0] = vec.x;
	Matrix[rowNo][1] = vec.y;
	Matrix[rowNo][2] = vec.z;

}

Vec3 Matrix3::GetLine(int lineNo)
{
	return Vec3(Matrix[0][lineNo], Matrix[1][lineNo], Matrix[2][lineNo]);
}

Vec3 Matrix3::GetRow(int rowNo)
{
	return Vec3(Matrix[rowNo][0], Matrix[rowNo][1], Matrix[rowNo][2]);
}


