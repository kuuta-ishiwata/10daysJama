#include "Player.h"

#include <stdio.h>
#include <windows.h>
#include <algorithm> 



bool IsPlayerOnLine(object player, Line line) {
	float px = player.position.X;
	float py = player.position.Y;

	// 横線の判定
	if (line.y1 == line.y2) {
		if (abs(py - line.y1) <= line.thickness &&
			px >= line.x1 && px <= line.x2) {
			return true;
		}
	}

	// 縦線の判定
	if (line.x1 == line.x2) {
		if (abs(px - line.x1) <= line.thickness &&
			py >= line.y2 && py <= line.y1) {
			return true;
		}
	}

	return false;
}

Player::~Player()
{

}

void Player::Initialize()
{
	//プレイヤー
	player =
	{
		{64,64},
		{0,0},
		16
	};
	line = { 1000, 600, 1000, 400, 5 }; // Xは同じ、Yが上に向かって減る
	

}

void Player::Update(char* keys, char* prekeys)
{
	
	const int screenCenterX = 640;
	const int mapWidth = 50 * BLOCKsize;
	const int screenWidth = 1280;

	int maxScroll = mapWidth - screenWidth;

	scrolX = std::clamp(static_cast<int>(player.position.X - screenCenterX), 0, maxScroll);

	if (player.position.X < 0) {
		player.position.X = 0;
	}

	//右に動く
	if (keys[DIK_A])
	{
		player.velocity.X = -5;
		//if (player.position.X >= 1500 && player.position.X > 0)
		//{
		//
		//	scrolX += player.velocity.X;
		//
		//}
	}
	if (keys[DIK_A] == 0 && prekeys[DIK_A])
	{
		player.velocity.X = 0;
		//if (player.position.X >= 1500 && player.position.X > 0)
		//{
		//
		//	scrolX += player.velocity.X;
		//
		//}
	}

	//左に動く
	if (keys[DIK_D])
	{
		player.velocity.X = 5;
		//if (player.position.X >= 800 )
		//{
		//
		//	scrolX += player.velocity.X;
		//
		//}
	}

	if (keys[DIK_D] == 0 && prekeys[DIK_D])
	{
		player.velocity.X = 0;
		//if (player.position.X >= 800)
		//{
		//
		//	scrolX += player.velocity.X;
		//
		//}
	}
	if (keys[DIK_SPACE] == 0 && prekeys[DIK_SPACE])
	{
		if (jampFlag == false)
		{
			jampFlag = true;
			player.velocity.Y -= 20;
		}
	}
	//重力
	player.velocity.Y += gravity;

#pragma region マップチップ判定(プレイヤー)
	//4頂点の座標
	float top = player.position.Y - player.radius;
	float down = player.position.Y + player.radius - 1;
	float right = player.position.X + player.radius - 1;
	float left = player.position.X - player.radius;

	//左右の判定
	if (map[(int)(top / 32)][(int)((left + player.velocity.X) / 32)] != 0 ||
		map[(int)(top / 32)][(int)((right + player.velocity.X) / 32)] != 0 ||
		map[(int)(down / 32)][(int)((left + player.velocity.X) / 32)] != 0 ||
		map[(int)(down / 32)][(int)((right + player.velocity.X) / 32)] != 0)
	{
		if (player.velocity.X > 0)
		{
			while (map[(int)(top / 32)][(int)((left + 1) / 32)] == 0 &&
				map[(int)(top / 32)][(int)((right + 1) / 32)] == 0 &&
				map[(int)(down / 32)][(int)((left + 1) / 32)] == 0 &&
				map[(int)(down / 32)][(int)((right + 1) / 32)] == 0)
			{
				player.position.Y += 1;
				left += 1;
				right += 1;
			}
		}

		if (player.velocity.X < 0)
		{
			while (map[(int)(top / 32)][(int)((left - 1) / 32)] == 0 &&
				map[(int)(top / 32)][(int)((right - 1) / 32)] == 0 &&
				map[(int)(down / 32)][(int)((left - 1) / 32)] == 0 &&
				map[(int)(down / 32)][(int)((right - 1) / 32)] == 0)
			{
				player.position.X -= 1;
				left -= 1;
				right -= 1;
			}
		}

		player.velocity.X = 0;

	}

	//上下の判定
	top = player.position.Y - player.radius;
	down = player.position.Y + player.radius - 1;
	right = player.position.X + player.radius - 1;
	left = player.position.X - player.radius;

	//ブロッが0以外の時に判定を取る
	//ブロックが0以外の時に判定を取る
	if (map[(int)((top + player.velocity.Y) / 32)][(int)((left) / 32)] != 0 ||
		map[(int)((top + player.velocity.Y) / 32)][(int)((right) / 32)] != 0 ||
		map[(int)((down + player.velocity.Y) / 32)][(int)((left) / 32)] != 0 ||
		map[(int)((down + player.velocity.Y) / 32)][(int)((right) / 32)] != 0)
	{

		if (player.velocity.Y > 0)
		{
			while (map[(int)((top + 1) / 32)][(int)((left) / 32)] == 0 &&
				map[(int)((top + 1) / 32)][(int)((right) / 32)] == 0 &&
				map[(int)((down + 1) / 32)][(int)((left) / 32)] == 0 &&
				map[(int)((down + 1) / 32)][(int)((right) / 32)] == 0)
			{
				player.position.Y += 1;
				top += 1;
				down += 1;
			}

		}


		//1回しかジャンプしない↓
		if (map[(int)((down + 1) / 32)][(int)((left) / 32)] == 1 ||
			map[(int)((down + 1) / 32)][(int)((right) / 32)] == 1)
		{
			jampFlag = false;//貯めジャンプ
			//wallflag = false;//壁キック
		}
		//1回しかジャンプしない↑


		if (player.velocity.Y < 0)
		{
			while (map[(int)((top - 1) / 32)][(int)((left) / 32)] == 0 &&
				map[(int)((top - 1) / 32)][(int)((right) / 32)] == 0 &&
				map[(int)((down - 1) / 32)][(int)((left) / 32)] == 0 &&
				map[(int)((down - 1) / 32)][(int)((right) / 32)] == 0)
			{
				player.position.Y -= 1;
				top -= 1;
				down -= 1;
			}
		}

		player.velocity.Y = 0;

	}

	player.position.X += player.velocity.X;
	player.position.Y += player.velocity.Y;

#pragma endregion
}
bool Player::IsPlayerOnLine(object player, Line line) {
	float px = player.position.X;
	float py = player.position.Y;

	// 横線の判定
	if (line.y1 == line.y2) {
		if (abs(py - line.y1) <= line.thickness &&
			px >= line.x1 && px <= line.x2) {
			return true;
		}
	}

	// 縦線の判定
	if (line.x1 == line.x2) {
		if (abs(px - line.x1) <= line.thickness &&
			py >= line.y2 && py <= line.y1) {
			return true;
		}
	}

	return false;
}

void Player::Draw()
{
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, WHITE, kFillModeSolid);
	
	
	Novice::DrawBox(
		(int)line.x1 - scrolX, (int)line.y2,                     // 上の方から描画
		(int)line.thickness, (int)(line.y1 - line.y2),           // 高さは y1 - y2
		0.0f,
		RED,
		kFillModeSolid
	);
	Novice::DrawSprite(player.position.X - player.radius - scrolX , player.position.Y - player.radius, irasuto, 1, 1, 0.0f, WHITE);
	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			if (map[y][x] == BLOCK)//普通のブロック
			{
				Novice::DrawSprite(x * BLOCKsize- scrolX, y * BLOCKsize, irasuto, 1, 1, 0.0f, WHITE);
			}
		}
	}
}