#include "VectorMath.h"

VectorMath::VectorMath() {

	kRowheight = 30;

	resultAdd = {};
	resultSubtract = {};
	resultMultiply = {};
	resultDot = {};
	resultLength = {};
	resultNormalize = {};
}

VectorMath::~VectorMath() {

}

Vector3 VectorMath::Add(const Vector3& v1, const Vector3& v2) {

	return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vector3 VectorMath::Subtract(const Vector3& v1, const Vector3& v2) {

	return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vector3 VectorMath::Multiply(float scalar, const Vector3& v) {

	return {v.x*scalar, v.y*scalar, v.z*scalar};

}

float VectorMath::Dot(const Vector3& v1, const Vector3& v2) { 
	float result=0;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;


	return result;
}

float VectorMath::Length(const Vector3& v) { 
	float result;

	result = sqrtf(float(pow(v.x, 2)) + float(pow(v.y, 2)) + float(pow(v.z, 2)));
	return result;
}

Vector3 VectorMath::Nomalize(const Vector3& v) { 
	Vector3 result;
	float length = Length(v);
	result = {float(v.x / length), float(v.y / length), float(v.z / length)};
	return result;
}

void VectorMath::VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {

	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.2f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.2f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
	
}

void VectorMath::Math(const Vector3& v1, const Vector3& v2,float scalar) {

	resultAdd = Add(v1, v2);
	resultSubtract = Subtract(v1, v2);
	resultMultiply = Multiply(scalar, v1);
	resultDot = Dot(v1, v2);
	resultLength = Length(v1);
	resultNormalize = Nomalize(v2);

}

void VectorMath::Draw() {

	VectorScreenPrintf(0, 0, resultAdd, "  : Add");
	VectorScreenPrintf(0, kRowheight, resultSubtract, "  : Subtract");
	VectorScreenPrintf(0, kRowheight * 2, resultMultiply, "  : Multiply");
	Novice::ScreenPrintf(0, kRowheight * 3, "%.02f  : Dot", resultDot);
	Novice::ScreenPrintf(0, kRowheight * 4, "%.02f  : Length", resultLength);
	VectorScreenPrintf(0, kRowheight * 5, resultNormalize, "  : Normalize");


}