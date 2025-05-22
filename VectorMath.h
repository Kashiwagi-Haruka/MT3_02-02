#pragma once
#include <corecrt_math.h>
#include <Novice.h>
#include "Vector3.h"

class VectorMath {

	private:

	static const int kColumnWidth = 60;
	int kRowheight;
	
	Vector3 resultAdd;
	Vector3 resultSubtract;
	Vector3 resultMultiply;
	float resultDot;
	float resultLength;
	Vector3 resultNormalize;
	
	public:


	Vector3 Add(const Vector3& v1, const Vector3& v2);
		
	Vector3 Subtract(const Vector3& v1, const Vector3& v2);

	Vector3 Multiply(float scalar, const Vector3& v);

	float Dot(const Vector3& v1, const Vector3& v2);

	float Length(const Vector3& v);

	Vector3 Nomalize(const Vector3& v);

	void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

	

	VectorMath();
	~VectorMath();

	void Math(const Vector3& v1,const Vector3& v2,float scalar);
	void Draw();

	

};
