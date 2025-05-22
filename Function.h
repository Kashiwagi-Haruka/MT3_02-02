﻿#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cstdint>

struct Line /*直線*/ {
	Vector3 origin; //!< 始点
	Vector3 diff;   //!< 終点への差分ベクトル
};
struct Ray /*半直線*/ {

	Vector3 origin; //!< 始点
	Vector3 diff;   //!< 終点への差分ベクトル
};
struct Segment /*線分*/ {

	Vector3 origin; //!< 始点
	Vector3 diff;   //!< 終点への差分ベクトル
};

class Function {

	public:

		
	

	void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

	Matrix4x4 MakeRotateXMatrix(float radian);
	Matrix4x4 MakeRotateYMatrix(float radian);
	Matrix4x4 MakeRotateZMatrix(float radian);
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
	float InnerProduct(const Vector3& v1, const Vector3& v2);
	Vector3 Cross(const Vector3& v1, const Vector3& v2);
	void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix4x4);
	Matrix4x4 Inverse(const Matrix4x4& m);
	Matrix4x4 MakeTranslateMatrix(Vector3 translate);
	Matrix4x4 MakeScaleMatrix(Vector3 scale);
	Matrix4x4 MakeAffineMatrix(Vector3 scale, Vector3 rotate, Vector3 translate);

	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

	Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
	Matrix4x4 Transpose(const Matrix4x4& m);
	Matrix4x4 MakeIdentity();

	Vector3 Project(const Vector3& v1,const Vector3& v2);
	Vector3 ClossPoint(const Vector3& point, const Segment& segment);
};