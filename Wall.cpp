#include "Wall.h"
#include "Vector2.h"
#include <Math.h>
#define _USE_MATH_DEFINES
#include <algorithm>

void wall101Collapes01(Wall wall101, Player& player)
{
	wall101.a.x = wall101.position.x - wall101.length / 2;
	wall101.a.y = wall101.position.y - wall101.hieght / 2 + 0;
	wall101.b.x = wall101.position.x - wall101.length / 2;
	wall101.b.y = wall101.position.y + wall101.hieght / 2 - 0;
	wall101.d.x = player.position.x - wall101.a.x;
	wall101.d.y = player.position.y - wall101.a.y;
	wall101.ba.x = wall101.b.x - wall101.a.x;
	wall101.ba.y = wall101.b.y - wall101.a.y;
	wall101.e = { wall101.ba.x / sqrtf(wall101.ba.x * wall101.ba.x + wall101.ba.y * wall101.ba.y),wall101.ba.y / sqrtf(wall101.ba.x * wall101.ba.x + wall101.ba.y * wall101.ba.y) };
	float t = ((wall101.d.x * wall101.e.x + wall101.d.y * wall101.e.y) / sqrtf(wall101.ba.x * wall101.ba.x + wall101.ba.y * wall101.ba.y));
	t = std::clamp(t, 0.0f, 1.0f);
	wall101.f.x = (1.0f - t) * wall101.a.x + t * wall101.b.x;
	wall101.f.y = (1.0f - t) * wall101.a.y + t * wall101.b.y;
	float distance = sqrtf((player.position.x - wall101.f.x) * (player.position.x - wall101.f.x) + (player.position.y - wall101.f.y) * (player.position.y - wall101.f.y));

	if (player.position.x + player.size >= wall101.position.x - wall101.length / 2 &&
		player.position.y >= wall101.position.y - wall101.hieght / 2 && player.position.y <= wall101.position.y + wall101.hieght / 2)
	{
		if ((distance < player.size + 0))
		{
			player.position.x = wall101.position.x - wall101.length / 2 - player.size;
			player.velocity.x = -player.velocity.x;
		}
	}
}
void wall101Collapes02(Wall wall101, Player& player)
{
	wall101.a.x = wall101.position.x + wall101.length / 2;
	wall101.a.y = wall101.position.y - wall101.hieght / 2 + 0;
	wall101.b.x = wall101.position.x + wall101.length / 2;
	wall101.b.y = wall101.position.y + wall101.hieght / 2 - 0;
	wall101.d.x = player.position.x - wall101.a.x;
	wall101.d.y = player.position.y - wall101.a.y;
	wall101.ba.x = wall101.b.x - wall101.a.x;
	wall101.ba.y = wall101.b.y - wall101.a.y;
	wall101.e = { wall101.ba.x / sqrtf(wall101.ba.x * wall101.ba.x + wall101.ba.y * wall101.ba.y),wall101.ba.y / sqrtf(wall101.ba.x * wall101.ba.x + wall101.ba.y * wall101.ba.y) };
	float t = ((wall101.d.x * wall101.e.x + wall101.d.y * wall101.e.y) / sqrtf(wall101.ba.x * wall101.ba.x + wall101.ba.y * wall101.ba.y));
	t = std::clamp(t, 0.0f, 1.0f);
	wall101.f.x = (1.0f - t) * wall101.a.x + t * wall101.b.x;
	wall101.f.y = (1.0f - t) * wall101.a.y + t * wall101.b.y;
	float distance = sqrtf((player.position.x - wall101.f.x) * (player.position.x - wall101.f.x) + (player.position.y - wall101.f.y) * (player.position.y - wall101.f.y));

	if (player.position.x - player.size <= wall101.position.x + wall101.length / 2 &&
		player.position.y >= wall101.position.y - wall101.hieght / 2 && player.position.y <= wall101.position.y + wall101.hieght / 2)
	{
		if ((distance < player.size + 0))
		{
			player.position.x = wall101.position.x + wall101.length / 2 + player.size;
			player.velocity.x = -player.velocity.x;
		}
	}
}
void wall101Collapes03(Wall wall101, Player& player)
{
	wall101.a.x = wall101.position.x + wall101.length / 2;
	wall101.a.y = wall101.position.y - wall101.hieght / 2 + 0;
	wall101.b.x = wall101.position.x - wall101.length / 2;
	wall101.b.y = wall101.position.y - wall101.hieght / 2 - 0;
	wall101.d.x = player.position.x - wall101.a.x;
	wall101.d.y = player.position.y - wall101.a.y;
	wall101.ba.x = wall101.b.x - wall101.a.x;
	wall101.ba.y = wall101.b.y - wall101.a.y;
	wall101.e = { wall101.ba.x / sqrtf(wall101.ba.x * wall101.ba.x + wall101.ba.y * wall101.ba.y),wall101.ba.y / sqrtf(wall101.ba.x * wall101.ba.x + wall101.ba.y * wall101.ba.y) };
	float t = ((wall101.d.x * wall101.e.x + wall101.d.y * wall101.e.y) / sqrtf(wall101.ba.x * wall101.ba.x + wall101.ba.y * wall101.ba.y));
	t = std::clamp(t, 0.0f, 1.0f);
	wall101.f.x = (1.0f - t) * wall101.a.x + t * wall101.b.x;
	wall101.f.y = (1.0f - t) * wall101.a.y + t * wall101.b.y;
	float distance = sqrtf((player.position.x - wall101.f.x) * (player.position.x - wall101.f.x) + (player.position.y - wall101.f.y) * (player.position.y - wall101.f.y));

	if (player.position.x >= wall101.position.x - wall101.position.x + wall101.length / 2 &&
		player.position.y + player.size >= wall101.position.y - wall101.hieght / 2)
	{
		if ((distance < player.size + 0))
		{
			player.position.y = wall101.position.y - wall101.hieght / 2 - player.size;
			player.velocity.y = -player.velocity.y;
		}
	}
}
void wall101Collapes04(Wall wall101, Player& player)
{
	wall101.a.x = wall101.position.x + wall101.length / 2;
	wall101.a.y = wall101.position.y + wall101.hieght / 2 + 0;
	wall101.b.x = wall101.position.x - wall101.length / 2;
	wall101.b.y = wall101.position.y + wall101.hieght / 2 - 0;
	wall101.d.x = player.position.x - wall101.a.x;
	wall101.d.y = player.position.y - wall101.a.y;
	wall101.ba.x = wall101.b.x - wall101.a.x;
	wall101.ba.y = wall101.b.y - wall101.a.y;
	wall101.e = { wall101.ba.x / sqrtf(wall101.ba.x * wall101.ba.x + wall101.ba.y * wall101.ba.y),wall101.ba.y / sqrtf(wall101.ba.x * wall101.ba.x + wall101.ba.y * wall101.ba.y) };
	float t = ((wall101.d.x * wall101.e.x + wall101.d.y * wall101.e.y) / sqrtf(wall101.ba.x * wall101.ba.x + wall101.ba.y * wall101.ba.y));
	t = std::clamp(t, 0.0f, 1.0f);
	wall101.f.x = (1.0f - t) * wall101.a.x + t * wall101.b.x;
	wall101.f.y = (1.0f - t) * wall101.a.y + t * wall101.b.y;
	float distance = sqrtf((player.position.x - wall101.f.x) * (player.position.x - wall101.f.x) + (player.position.y - wall101.f.y) * (player.position.y - wall101.f.y));

	if (player.position.x >= wall101.position.x - wall101.length / 2 && player.position.x <= wall101.position.x + wall101.length / 2 &&
		player.position.y - player.size <= wall101.position.y + wall101.hieght / 2)
	{
		if ((distance < player.size + 0))
		{
			player.position.y = wall101.position.y + wall101.hieght / 2 + player.size;
			player.velocity.y = -player.velocity.y;
		}
	}
}

void WallCollapes(Wall wall101, Player& player)
{
	wall101Collapes01(wall101, player);
	wall101Collapes02(wall101, player);
	wall101Collapes03(wall101, player);
	wall101Collapes04(wall101, player);
}
