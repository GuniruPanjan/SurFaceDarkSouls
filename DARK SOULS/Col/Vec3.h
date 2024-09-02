#pragma once
#include "DxLib.h"

/// <summary>
/// サイズ構造体
/// </summary>
struct Size
{
	//幅
	float width = 0.0f;
	//高さ
	float height = 0.0f;
	//奥行
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
	//足し算
	Size operator+(const Size& size) const;
	//掛け算
	Size operator*(float scale) const;
};

/// <summary>
/// ベクター構造体
/// </summary>
struct Vec3
{
	float x, y, z;

	Vec3();
	Vec3(float X, float Y, float Z);

	//単項演算子
	Vec3 Reverse();
	//足し算
	Vec3 operator+(const Vec3& vec) const;
	//Vec3 += Vec3
	void operator+=(const Vec3& vec);
	//引き算
	Vec3 operator-(const Vec3& vec) const;
	//Vec3 -= Vec3
	void operator-=(const Vec3& vec);
	//掛け算
	Vec3 operator*(float scale) const;
	//Vec3 *= scale
	void operator*=(float scale);
	//割り算
	Vec3 operator/(float scale) const;
	//Vec3 /= scale
	void operator/=(float scale);
	//Vec3 == Vec3だった場合
	bool operator==(const Vec3& vec) const;
	//Vec3 != Vec3だった場合
	bool operator!=(const Vec3& vec) const;

	//Dxlibの関数を使う際に、VECTOR型に変換する関数
	VECTOR GetVector() const { return VGet(x, y, z); }

	//長さを取得
	float Length() const;

	//長さの2乗を取得
	float SqLength() const;

	//自身の正規化
	void Normalize();

	//正規化した結果を取得
	Vec3 GetNormalized() const;
};
/// <summary>
/// 線形補間
/// </summary>
/// <param name="start">スタート</param>
/// <param name="end">終了</param>
/// <param name="t">割合</param>
/// <returns>補間後</returns>
Vec3 Lerp(const Vec3& start, const Vec3& end, float t);

/// <summary>
/// 内積
/// </summary>
/// <param name="vec1">ベクトル1</param>
/// <param name="vec2">ベクトル2</param>
/// <returns></returns>
float Dot(const Vec3& vec1, const Vec3& vec2);

/// <summary>
/// 外積
/// </summary>
/// <param name="vec1">ベクトル1</param>
/// <param name="vec2">ベクトル2</param>
/// <returns></returns>
Vec3 Cross(const Vec3& vec1, const Vec3& vec2);

using Pos3 = Vec3;