#include <Novice.h>
#include "Ball.h"
#include "Grid.h"
const char kWindowTitle[] = "LE2B_05_カシワギハルカ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	Ball ball;
	Grid grid;
	Function fn;


	ball.sphere.center = {0, 0, 0};
	ball.sphere.radius = 1.0f;

	ball.plane_.distance = 1.0f;
	ball.plane_.normal = {0.2f, 0.2f, 0.2f};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		ball.Update(); // ここで ImGui の描画も走る

		// (2) カメラ＆行列計算
		auto viewMatrix = fn.Inverse(fn.MakeAffineMatrix({1, 1, 1}, ball.GetCameraRotate(), ball.GetCameraTranslate()));
		auto projMatrix = fn.MakePerspectiveFovMatrix(1.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
		auto viewProj = fn.Multiply(viewMatrix, projMatrix);
		auto viewport = fn.MakeViewportMatrix(0, 0, 1280, 720, 0, 1);


		int color = 0xffffffff;

		if (ball.IsCollision(ball.plane_)) {
			color = 0xff0000ff;
		}

		// (3) 描画
		grid.DrawGrid(viewProj, viewport);
		ball.Draw(viewProj, viewport, color);                       // 球
		ball.DrawPlane(ball.plane_, viewProj, viewport, 0xFFFFFFFF); // 平面
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
