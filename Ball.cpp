#include "Ball.h"
#include <cmath> // fabsf
Ball::Ball() {



}
void Ball::Imgui() {
	ImGui::Begin("Window");

	// 球,
	ImGui::DragFloat3("Sphere.Center", &sphere.center.x,0.01f);
	ImGui::DragFloat("Sphere.Radius", &sphere.radius,0.01f);

	ImGui::Separator();

	// 平面
	ImGui::DragFloat3("Plane.Normal", &plane_.normal.x,0.01f);
	ImGui::DragFloat("Plane.Distance", &plane_.distance,0.01f);

	ImGui::End();

}
void Ball::SetCenter(Vector3 v) {

	sphere.center = v;


}
	
	void Ball::Update() {

Imgui();
	    plane_.normal = VM.Nomalize(plane_.normal);




}
void Ball::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color) {
	const uint32_t kSubdivision = 20;
	const float kLonEvery = 2.0f * float(M_PI) / float(kSubdivision);
	const float kLatEvery = float(M_PI) / float(kSubdivision);



	Matrix4x4 worldMatrix = fn.MakeTranslateMatrix(sphere.center);

	Matrix4x4 worldViewProjectionMatrix = fn.Multiply(worldMatrix, viewProjectionMatrix);

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex;

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;

			// 球面上の3点をワールド空間で計算
			Vector3 a = {
			    sphere.radius * cosf(lat) * cosf(lon),
			    sphere.radius * sinf(lat),
			    sphere.radius * cosf(lat) * sinf(lon),
			};

			Vector3 b = {
			    sphere.radius * cosf(lat + kLatEvery) * cosf(lon),
			    sphere.radius * sinf(lat + kLatEvery),
			    sphere.radius * cosf(lat + kLatEvery) * sinf(lon),
			};

			Vector3 c = {
			    sphere.radius * cosf(lat + kLatEvery) * cosf(lon + kLonEvery),
			    sphere.radius * sinf(lat + kLatEvery),
			    sphere.radius * cosf(lat + kLatEvery) * sinf(lon + kLonEvery),
			};

			// 画面座標へ変換（ワールド → WVP → ビューポート）
			a = fn.Transform(fn.Transform(a, worldViewProjectionMatrix), viewPortMatrix);
			b = fn.Transform(fn.Transform(b, worldViewProjectionMatrix), viewPortMatrix);
			c = fn.Transform(fn.Transform(c, worldViewProjectionMatrix), viewPortMatrix);

			Novice::DrawLine((int)a.x, (int)a.y, (int)b.x, (int)b.y, color);
			Novice::DrawLine((int)b.x, (int)b.y, (int)c.x, (int)c.y, color);
		}
	}
}
bool Ball::IsCollision(const Sphere s1, const Sphere s2) { 
	float distance = VM.Length(VM.Subtract(s2.center, s1.center));
	if (distance<=s1.radius+s2.radius) {
	
	return true;

	}	
	
	
	return false; 
}





bool Ball::IsCollision(const Plane& plane) {
	float distance = plane.normal.x * sphere.center.x + plane.normal.y * sphere.center.y + plane.normal.z * sphere.center.z - plane.distance;
	return std::abs(distance) <= sphere.radius;
}

Vector3 Ball::Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return {-vector.y, vector.x, 0.0f};
	}
	return {0.0f, -vector.z, vector.y};
}

void Ball::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

    // 平面の中心位置
	Vector3 center = VM.Multiply(plane.distance,plane.normal);

	// u, vを計算
	Vector3 u = Perpendicular(plane.normal);
	Vector3 v = fn.Cross(plane.normal, u);

	// 正規化（Normalizeなしなので手動で）
	float uLen = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z);
	float vLen = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	u = VM.Multiply(1.0f / uLen, u);
	v = VM.Multiply(1.0f / vLen, v);

	// サイズをかける
	float size = 2.0f;
	u = VM.Multiply(size, u);
	v = VM.Multiply(size, v);

	// 4つの頂点を作る
	Vector3 points[4];
	points[0] = VM.Add(center, VM.Add(u, v));                       // +u +v
	points[1] = VM.Add(center, VM.Subtract(u, v));                  // +u -v
	points[2] = VM.Add(center, VM.Subtract(VM.Multiply(-1.0f, u), v)); // -u -v
	points[3] = VM.Add(center, VM.Add(VM.Multiply(-1.0f, u), v));      // -u +v

	// 変換
	for (int i = 0; i < 4; ++i) {
		points[i] = fn.Transform(fn.Transform(points[i], viewProjectionMatrix), viewportMatrix);
	}

	    for (int i = 0; i < 4; ++i) {
		int next = (i + 1) % 4;
		Novice::DrawLine((int)points[i].x, (int)points[i].y, (int)points[next].x, (int)points[next].y, color);
	}
}