#pragma once
#include "Vector2.h"

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

struct Stage
{
	int maxInterceptorCount = 5;
	Vector2 targetPosition[5];
	Wall wall[10];

};

extern Stage gStageData[10];

void initializeStageData();