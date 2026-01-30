#pragma once

struct Vector2
{
	float x;
	float y;
};

struct Vector2I
{
	int x;
	int y;
};

struct Vertex {
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftDown;
	Vector2 rightDown;
};