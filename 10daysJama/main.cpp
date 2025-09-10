#include <Novice.h>
#define _USE_MATH_DEFINES
#include "Vector2.h"

#include "Map.h"
const char kWindowTitle[] = "境界線";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	Player* player;
	player = new Player();
	


	player->Initialize();
	
	Map* map;
	map = new Map();
	map->Initialize();
	int scene = 0;
	Line line = { 1000, 500, 1000, 300, 5 }; // ← 実体でOK！
	Line line2  = { 3000, 550, 1000, 400, 5 };
	int OP = Novice::LoadTexture("./kyoukaisenn.png");

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
		
		//player->Update(keys, preKeys);
		//map->Update(keys, preKeys);
		switch (scene) {

		case 0:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				scene = 1;
				player->Update(keys, preKeys);
			}
			
			break;

		case 1:
			player->Update(keys, preKeys); // ← 毎フレーム呼ぶ！
			if (player->IsPlayerOnLine(player->player,line))
			{
				scene = 2;
				player->player.position = { 64, 64 };
				
			}
			break;

		case 2:

			map->Update(keys, preKeys); // ← 毎フレーム呼ぶ！
			if (map->IsPlayerOnLine(player->player, line2))
			{
				
				scene = 1;
				player->player.position = { 64, 64 };

			}

			break;

		case 3:
			map->Update(keys, preKeys); // ← 毎フレーム呼ぶ！
			if (map->IsPlayerOnLine(player->player, line2))
			{

				scene = 2;
				player->player.position = { 64, 64 };

			}
		break;
		}
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		if (scene == 0)
		{
			Novice::DrawSprite(0, 0, OP, 1, 1, 0.0f, WHITE);
		}
		if (scene == 1)
		{
			player->Draw();
		}
		if (scene == 2)
		{
			map->Draw();
		}
		if(scene == 3)
		{
			player->Draw();
		}
	
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
