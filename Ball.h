#pragma once
#include <Novice.h>
#include "Function.h"
#include "imgui.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "VectorMath.h"
class Ball {

	struct Sphere {
		Vector3 center;
		float radius;
	};

	struct Plane {
		Vector3 normal;
		float distance;
	};

	Function fn;
	VectorMath VM;

	Vector3 cameraRotate = {0.6f, 0.6f, 0.0f};
	Vector3 cameraTranslate = {-6.0f, 7.0f, -5.0f};

public:
	Sphere sphere;
	Plane plane_;
	Ball();
	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
	void Imgui();
	bool IsCollision( const Plane& plane);
	bool IsCollision(const Sphere s1, const Sphere s2);
	Vector3 GetCameraTranslate() { return cameraTranslate; };
	Vector3 GetCameraRotate() { return cameraRotate; };
	void SetCenter(Vector3 v);
	Vector3 Perpendicular(const Vector3& vector);
	void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
};