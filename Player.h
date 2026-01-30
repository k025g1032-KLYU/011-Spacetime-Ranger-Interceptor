#pragma once
#include "Vector2.h"

class Drag
{
public:
	Vector2 position;
	int texture;
	unsigned int color;
};

class Player
{
public:
	Player();
	~Player();

	Vector2 position = { -100,-100 };
	Vector2 velocity;
	Vector2 velocityRecord;
	float speed;
	float speedMax;
	float direction;
	float preDirection;
	int size = 10;
	int range;
	int rangeMax;
	int status = 0; // 0:初始狀態 1:發射中 2:已發射
	Drag drag[120];
	int texture;
	unsigned int color;
};

