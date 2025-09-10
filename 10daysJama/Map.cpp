#include "Map.h"
#include <algorithm> // clamp を使うために必要！

void Map::Initialize(){

	
	player->player = {
		{64,200},
		{0,0},
		16
	};

	scrolX = 0;
	line = { 3000, 550, 1000, 400, 5 }; // Xは同じ、Yが上に向かって減る


}

void Map::Update(char* keys, char* prekeys)
{
	const int screenCenterX = 640;
	const int mapWidth = 100 * BLOCKsize;
	const int screenWidth = 1280;

	int maxScroll = mapWidth - screenWidth;

	scrolX = std::clamp(static_cast<int>(player->player.position.X - screenCenterX), 0, maxScroll);

	if (player->player.position.X < 0) {
		player->player.position.X = 0;
	}
	//右に動く
	if (keys[DIK_A])
	{
		player->player.velocity.X = -5;
		//if (player->player.position.X >= 1500 && player->player.position.X <= 4500)
		//{
		//
		//	scrolX += player->player.velocity.X;
		//
		//}
	}
	if (keys[DIK_A] == 0 && prekeys[DIK_A])
	{
		player->player.velocity.X = 0;
		//if (player->player.position.X >= 1500 && player->player.position.X <= 4500)
		//{
		//
		//	scrolX += player->player.velocity.X;
		//
		//}
	}

	//左に動く
	if (keys[DIK_D])
	{
		player->player.velocity.X = 5;
		//if (player->player.position.X >= 800 && player->player.position.X <= 4500)
		//{
		//
		//	scrolX += player->player.velocity.X;
		//
		//}
	}

	if (keys[DIK_D] == 0 && prekeys[DIK_D])
	{
		player->player.velocity.X = 0;
		//if (player->player.position.X >= 800 && player->player.position.X <= 4500)
		//{
		//
		//	scrolX += player->player.velocity.X;
		//
		//}
	}
	if (keys[DIK_SPACE] == 0 && prekeys[DIK_SPACE])
	{
		if (jampFlag == false)
		{
			jampFlag = true;
			player->player.velocity.Y -= 20;
		}
	}
	//重力
	player->player.velocity.Y += gravity;
	//4頂点の座標
	
	float top = player->player.position.Y - player->player.radius;
	float down = player->player.position.Y + player->player.radius - 1;
	float right = player->player.position.X + player->player.radius - 1;
	float left = player->player.position.X - player->player.radius;

	//左右の判定
	if (map[(int)(top / 32)][(int)((left + player->player.velocity.X) / 32)] != 0 ||
		map[(int)(top / 32)][(int)((right + player->player.velocity.X) / 32)] != 0 ||
		map[(int)(down / 32)][(int)((left + player->player.velocity.X) / 32)] != 0 ||
		map[(int)(down / 32)][(int)((right + player->player.velocity.X) / 32)] != 0)
	{
		if (player->player.velocity.X > 0)
		{
			while (map[(int)(top / 32)][(int)((left + 1) / 32)] == 0 &&
				map[(int)(top / 32)][(int)((right + 1) / 32)] == 0 &&
				map[(int)(down / 32)][(int)((left + 1) / 32)] == 0 &&
				map[(int)(down / 32)][(int)((right + 1) / 32)] == 0)
			{
				player->player.position.Y += 1;
				left += 1;
				right += 1;
			}
		}

		if (player->player.velocity.X < 0)
		{
			while (map[(int)(top / 32)][(int)((left - 1) / 32)] == 0 &&
				map[(int)(top / 32)][(int)((right - 1) / 32)] == 0 &&
				map[(int)(down / 32)][(int)((left - 1) / 32)] == 0 &&
				map[(int)(down / 32)][(int)((right - 1) / 32)] == 0)
			{
				player->player.position.X -= 1;
				left -= 1;
				right -= 1;
			}
		}

		player->player.velocity.X = 0;

	}

	//上下の判定
	top = player->player.position.Y - player->player.radius;
	down = player->player.position.Y + player->player.radius - 1;
	right = player->player.position.X + player->player.radius - 1;
	left = player->player.position.X - player->player.radius;

	//ブロッが0以外の時に判定を取る
	//ブロックが0以外の時に判定を取る
	if (map[(int)((top + player->player.velocity.Y) / 32)][(int)((left) / 32)] != 0 ||
		map[(int)((top + player->player.velocity.Y) / 32)][(int)((right) / 32)] != 0 ||
		map[(int)((down + player->player.velocity.Y) / 32)][(int)((left) / 32)] != 0 ||
		map[(int)((down + player->player.velocity.Y) / 32)][(int)((right) / 32)] != 0)
	{

		if (player->player.velocity.Y > 0)
		{
			while (map[(int)((top + 1) / 32)][(int)((left) / 32)] == 0 &&
				map[(int)((top + 1) / 32)][(int)((right) / 32)] == 0 &&
				map[(int)((down + 1) / 32)][(int)((left) / 32)] == 0 &&
				map[(int)((down + 1) / 32)][(int)((right) / 32)] == 0)
			{
				player->player.position.Y += 1;
				top += 1;
				down += 1;
			}

		}


		//1回しかジャンプしない↓
		if (map[(int)((down + 1) / 32)][(int)((left) / 32)] == 1 ||
			map[(int)((down + 1) / 32)][(int)((right) / 32)] == 1)
		{
			jampFlag = false;//貯めジャンプ
			
		}
		//1回しかジャンプしない↑


		if (player->player.velocity.Y < 0)
		{
			while (map[(int)((top - 1) / 32)][(int)((left) / 32)] == 0 &&
				map[(int)((top - 1) / 32)][(int)((right) / 32)] == 0 &&
				map[(int)((down - 1) / 32)][(int)((left) / 32)] == 0 &&
				map[(int)((down - 1) / 32)][(int)((right) / 32)] == 0)
			{
				player->player.position.Y -= 1;
				top -= 1;
				down -= 1;
			}
		}

		player->player.velocity.Y = 0;

	}

	player->player.position.X += player->player.velocity.X;
	player->player.position.Y += player->player.velocity.Y;
	
	
}
bool Map::IsPlayerOnLine(object player, Line line) {
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
void Map::Draw()
{
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);
	//Novice::DrawBox(400 - scrolX, 500, 25, 25, 0.0f, RED, kFillModeSolid);
	//Novice::DrawBox(400 - scrolX, 550, 25, 25, 0.0f, BLUE, kFillModeSolid);
	//Novice::DrawBox(250 - scrolX, 500, 25, 25, 0.0f, GREEN, kFillModeSolid);
	Novice::DrawBox(
		(int)line.x1 - scrolX, (int)line.y2,                     // 上の方から描画
		(int)line.thickness, (int)(line.y1 - line.y2),           // 高さは y1 - y2
		0.0f,
		BLUE,
		kFillModeSolid
	);

	Novice::DrawSprite(player->player.position.X - player->player.radius - scrolX, player->player.position.Y - player->player.radius, irasuto, 1, 1, 0.0f, WHITE);
	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			if (map[y][x] == BLOCK)//普通のブロック
			{
				Novice::DrawSprite(x * BLOCKsize - scrolX, y * BLOCKsize, irasuto, 1, 1, 0.0f, WHITE);
			}
		}
	}
}

//void Map::acquireItem(const Item& item)
//{
//
//
//}
//
//void Map::showInventory()
//{
//
//}
