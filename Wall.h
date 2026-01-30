#pragma once

struct Wall
{
	Vector2 position = { -300,-300 };
	int length = 150;
	int hieght = 150;
	Vector2 posWcs = { 0,0 };
	int blockdirection = 1;
	Vector2 a = { 100,100 };
	Vector2 b = { 1000,400 };
	Vector2 d = { 0,0 };
	Vector2 ba = { 0,0 };
	Vector2 e = { 0,0 };
	Vector2 f = { 0,0 };
	int abr = 10;
};

struct Player
{
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
	int texture;
	unsigned int color;
};

class tWall
{
public:
	tWall();
	~tWall();

	void wall101Collapes01(Wall wall101, Player& player);
	void wall101Collapes02(Wall wall101, Player& player);
	void wall101Collapes03(Wall wall101, Player& player);
	void wall101Collapes04(Wall wall101, Player& player);
};

