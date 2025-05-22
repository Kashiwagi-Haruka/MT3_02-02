#include "Grid.h"


void Grid::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	Function fn; // Function クラスのインスタンス

	for (uint32_t i = 0; i <= kSubdivision; ++i) {
		float offset = -kGridHalfWidth + i * kGridEvery;

		// 横線（Z軸方向）
		Vector3 startX = {-kGridHalfWidth, 0.0f, offset};
		Vector3 endX = {+kGridHalfWidth, 0.0f, offset};

		// 縦線（X軸方向）
		Vector3 startZ = {offset, 0.0f, -kGridHalfWidth};
		Vector3 endZ = {offset, 0.0f, +kGridHalfWidth};

		// 座標変換（ワールド→スクリーン）
		startX = fn.Transform(fn.Transform(startX, viewProjectionMatrix), viewportMatrix);
		endX = fn.Transform(fn.Transform(endX, viewProjectionMatrix), viewportMatrix);
		startZ = fn.Transform(fn.Transform(startZ, viewProjectionMatrix), viewportMatrix);
		endZ = fn.Transform(fn.Transform(endZ, viewProjectionMatrix), viewportMatrix);

		// 描画
		Novice::DrawLine((int)startX.x, (int)startX.y, (int)endX.x, (int)endX.y, 0xAAAAAAFF);
		Novice::DrawLine((int)startZ.x, (int)startZ.y, (int)endZ.x, (int)endZ.y, 0xAAAAAAFF);
	}
}
