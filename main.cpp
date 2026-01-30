#include <Novice.h>
#include <Math.h>
#define _USE_MATH_DEFINES
#include <algorithm>
#include <String.h>
#include "Vector2.h"
#include "Player.h"
#include "stageData.h"

const char kWindowTitle[] = "GC1A_11_ヨ_カンリン_インターセプター";

//struct Drag
//{
//	Vector2 position;
//	int texture;
//	unsigned int color;
//};

Player interceptor[5];
int interceptorInCharge = 0;
int interceptorTimer = 240;
const int interceptorTime = 240;

struct Target
{
	Vector2 position;
	Vector2 prePosition;
	Vector2 texturePosition;
	int size=10;
	int hp=3;
	int texture;
	unsigned int color=BLACK;
};
Target target;

struct PreTarget
{
	Vector2 position = { -100,-100 };
};
PreTarget preTarget[5];

Stage stage[10];
int currentStage = 0;

struct Block {
	Vector2 pos; //位置.
	float size; //大きさ.
	Vertex vertex; //頂点.
	Vector2 moveVec; //移動する向き.
	float moveLength; //移動の長さ
	int moveSpeed; //速さ.
	Vector2 newPos; //移動後の位置.
	unsigned int color; //色.
};

struct ChooseIcon {
	Vector2 pos; //位置.
	float size; //大きさ.
	Vertex vertex; //頂点.
	unsigned int color; //色.
	bool isIconChoosed; //そのアイコンが選択されてるか
	bool isIconDecided; //そのアイコンの決定がされたか
	int number;
};

struct RangerUI {
	int x; //位置.
	int textureX; //テクスチャ位置.
	int status; //0=未啟用  1=啟用未使用  1=incharge  2=攔截中  3=待機(可選) 
};
RangerUI rangerUI[5];

//struct ControlUI {
//	int x; //位置.
//	int textureX; //テクスチャ位置.
//	int status; //0=未啟用  1=啟用未使用  1=incharge  2=攔截中  3=待機(可選) 
//};
//ControlUI replaybutton;
//ControlUI trackbutton;
//ControlUI helpbutton;
//ControlUI retreatbutton;

int Hit(Player a,Target b)
{
	float dx = a.position.x - b.position.x;
	float dy = a.position.y - b.position.y;
	float distance = sqrtf(dx * dx + dy * dy);
	if(target.hp<=1)
	{
		if (distance < (a.size + b.size))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (distance < (a.range + b.size))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
}

void moveToNextPosition(Vector2& texturePosition, Vector2 APosition, Vector2 BPosition, int frame,int totalFrame)
{
	float t = 1.0f * (totalFrame-frame)/ totalFrame ;
	texturePosition.x = APosition.x*(1-t) + BPosition.x * t;
	texturePosition.y = APosition.y * (1 - t) + BPosition.y * t;
	
}

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
		if ((distance < player.size +5))
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
		if ((distance < player.size+5))
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
		if ((distance < player.size + 5))
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
		if ((distance < player.size + 5))
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

Vector2I mouse;
Vector2I premouse;
Vector2I startpoint = { 640,320 };

float shotLineLength;
int targetMoveTime = 60;
int targetMoveTimer = targetMoveTime;
//int missionResultTimer = 0;
//int streakTimer = 0;
int dragActive = true;
int chargeRange = 100;
int mouseIsPressed = 0;
int shotTrigger = 0;
int gamePhase = 0;
int inPhaseControll = 0;
int IPC3_2Status = 0; //0:瞄準 1:發射 飛行 2:reset to 0 3:着弾
int backendData = true;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	Novice::AllowWindowSizeChanged(1);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	
	Block block = {
	{0.0f, 0.0f}, //位置.
	0.0f, //大きさ.
	{block.pos.x - block.size, block.pos.y - block.size, //左上.
	block.pos.x + block.size, block.pos.y - block.size, //右上.
	block.pos.x - block.size, block.pos.y + block.size, //左下.
	block.pos.x + block.size, block.pos.y + block.size,}, //右下.
	{0.0f, 0.0f}, //移動する向き.
	0.0f, //移動の長さ
	0, //速さ.
	{0.0f,0.0f}, //移動後の位置.
	0xFFFFFFFF //色.
	};
	ChooseIcon chooseIcon[2][5];

	interceptor[interceptorInCharge].position.x = (float)startpoint.x;
	interceptor[interceptorInCharge].position.y = (float)startpoint.y;
	interceptor[0].color = RED;
	interceptor[1].color = BLUE;
	interceptor[2].color = 0xFFFF37FF;
	interceptor[3].color = GREEN;
	interceptor[4].color = WHITE;

	//stage[0].targetPosition[0] = { 200.0f,200.0f };
	//stage[0].targetPosition[1] = { 640.0f,360.0f };
	//stage[0].targetPosition[2] = { 600.0f,400.0f };
	//stage[0].targetPosition[3] = { 1000.0f,100.0f };
	//stage[0].targetPosition[4] = { 600.0f,500.0f };
	initializeStageData();

	for(int i=0;i<10;i++)
	{
		stage[i].maxInterceptorCount = gStageData[i].maxInterceptorCount;
		stage[i].targetPosition[0] = gStageData[i].targetPosition[0];
		stage[i].targetPosition[1] = gStageData[i].targetPosition[1];
		stage[i].targetPosition[2] = gStageData[i].targetPosition[2];
		stage[i].targetPosition[3] = gStageData[i].targetPosition[3];
		stage[i].targetPosition[4] = gStageData[i].targetPosition[4];
		for (int j = 0; j < 10; j++)
		{
			stage[i].wall[j] = gStageData[i].wall[j];
		}
	}

	interceptor[0].speedMax =10;
	interceptor[0].size = 10;
	interceptor[0].rangeMax=30;

	interceptor[1].speedMax =12;
	interceptor[1].size = 8;
	interceptor[1].rangeMax=40;

	interceptor[2].speedMax=8;
	interceptor[2].size = 15;
	interceptor[2].rangeMax=20;

	interceptor[3].speedMax = 15;
	interceptor[3].size = 5;
	interceptor[3].rangeMax = 20;

	interceptor[4].speedMax = 12;
	interceptor[4].size = 6;
	interceptor[4].rangeMax = 50;

	

	int wall101Texture = Novice::LoadTexture("./Resource/image/wall1.png");
	int wall102Texture = Novice::LoadTexture("./Resource/image/wall2.png");

	int titleTexture = Novice::LoadTexture("./Resource/image/template1.png");
	int tutorialTexture = Novice::LoadTexture("./Resource/image/template2.png");
	int stageSelectTexture = Novice::LoadTexture("./Resource/image/template3.png");

	int Ranger01Texture = Novice::LoadTexture("./Resource/image/rangersCard3.png");
	int Ranger02Texture = Novice::LoadTexture("./Resource/image/rangersCard4.png");
	int Ranger03Texture = Novice::LoadTexture("./Resource/image/rangersCard5.png");
	int Ranger04Texture = Novice::LoadTexture("./Resource/image/rangersCard6.png");
	int Ranger05Texture = Novice::LoadTexture("./Resource/image/rangersCard7.png");
	int reCrewUITexture = Novice::LoadTexture("./Resource/image/reCrew.png");
	int reCrewUIUnderTexture = Novice::LoadTexture("./Resource/image/reCrewUnder.png");

	int controlUITexture = Novice::LoadTexture("./Resource/image/controlUI DEMO.png");
	int controlUIrTexture = Novice::LoadTexture("./Resource/image/UI button3.png");
	int controlUItTexture = Novice::LoadTexture("./Resource/image/UI button4.png");
	int controlUIhTexture = Novice::LoadTexture("./Resource/image/UI button5.png");

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			chooseIcon[i][j].pos = { 200.0f + 145.0f * j, 190.0f + 175.0f * i }; //位置.
			chooseIcon[i][j].size = 32; //大きさ.

			chooseIcon[i][j].vertex = {
				chooseIcon[i][j].pos.x - chooseIcon[i][j].size, chooseIcon[i][j].pos.y - chooseIcon[i][j].size, //左上.
				chooseIcon[i][j].pos.x + chooseIcon[i][j].size, chooseIcon[i][j].pos.y - chooseIcon[i][j].size, //右上.
				chooseIcon[i][j].pos.x - chooseIcon[i][j].size, chooseIcon[i][j].pos.y + chooseIcon[i][j].size, //左下.
				chooseIcon[i][j].pos.x + chooseIcon[i][j].size, chooseIcon[i][j].pos.y + chooseIcon[i][j].size //右下.
			};

			chooseIcon[i][j].color = 0xFFFF00FF; //色.

			chooseIcon[i][j].isIconChoosed = false; //そのアイコンが選択されてるか
			chooseIcon[i][j].isIconDecided = false; //そのアイコンの決定がされたか

		}
	}
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
		premouse = mouse;
		Novice::GetMousePosition(&mouse.x, &mouse.y);

		if(gamePhase == 0) //title
		{
			if(inPhaseControll == 0)
			{
				inPhaseControll = 2;
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
				if (Novice::IsTriggerMouse(0))
				{
					gamePhase = 1;
				}
				
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 1) //tutorial
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
				if (Novice::IsTriggerMouse(0))
				{
					gamePhase = 2;
				}
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 2) //stage menu
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 5; j++) {
						chooseIcon[i][j].number = i*5+j;
					}
				}

				block.pos.x = static_cast<float>(mouse.x);
				block.pos.y = static_cast<float>(mouse.y);

				block.vertex = {
				block.pos.x - block.size, block.pos.y - block.size, //左上.
					block.pos.x + block.size, block.pos.y - block.size, //右上.
					block.pos.x - block.size, block.pos.y + block.size, //左下.
					block.pos.x + block.size, block.pos.y + block.size,
				};
			
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 5; j++) {

						////X軸の当たり判定
						if (chooseIcon[i][j].vertex.leftTop.x < block.vertex.rightDown.x &&
							block.vertex.leftTop.x < chooseIcon[i][j].vertex.rightDown.x)
						{
							if (chooseIcon[i][j].vertex.leftTop.y < block.vertex.rightDown.y &&
								block.vertex.leftTop.y < chooseIcon[i][j].vertex.rightDown.y)//Y軸の当たり判定
							{
								chooseIcon[i][j].isIconChoosed = true;
							}
							else
							{
								chooseIcon[i][j].isIconChoosed = false;
							}
						}
						else
						{
							chooseIcon[i][j].isIconChoosed = false;
						}

						//色を変える
						if (chooseIcon[i][j].isIconChoosed)
						{
							currentStage = chooseIcon[i][j].number;
							chooseIcon[i][j].color = RED;
							if ((keys[DIK_SPACE] && !preKeys[DIK_SPACE]) || Novice::IsTriggerMouse(0))
							{
								inPhaseControll = 3;
							}
						}
						else
						{
							chooseIcon[i][j].color = WHITE;
						}

					}
				}
			
				if (Novice::IsTriggerMouse(0))
				{
					target.position = stage[currentStage].targetPosition[0];
					target.hp = stage[currentStage].maxInterceptorCount;
					inPhaseControll = 3;
				}
			}
			else if (inPhaseControll == 3)
			{
				
				gamePhase = 3;
				inPhaseControll = 2;
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 3) //game

		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2) //main
			{
				target.texturePosition = target.position;
				shotLineLength = (float)sqrt((mouse.y - startpoint.y) * (mouse.y - startpoint.y) + (mouse.x - startpoint.x) * (mouse.x - startpoint.x));
				interceptor[interceptorInCharge].direction = atan2f((float)(mouse.y - startpoint.y), (float)(mouse.x - startpoint.x));
				if (IPC3_2Status == 0) //瞄準
				{
					if (shotLineLength > chargeRange && shotTrigger<2)
					{
						shotTrigger = 0;
					}
					else if (shotLineLength <= chargeRange && shotTrigger < 2)
					{
						shotTrigger = 1;
						if (Novice::IsPressMouse(0))
						{
							if (shotTrigger == 1)
							{
								shotTrigger = 2;
							}
						}
					}

					if (shotTrigger == 2&&!Novice::IsPressMouse(0))
					{
						if (shotLineLength > 30)
						{
							interceptor[interceptorInCharge].status = 1;
							interceptor[interceptorInCharge].speed = interceptor[interceptorInCharge].speedMax;
							interceptor[interceptorInCharge].preDirection = interceptor[interceptorInCharge].direction;
							interceptor[interceptorInCharge].velocity.x = interceptor[interceptorInCharge].speed * -cosf(interceptor[interceptorInCharge].direction);
							interceptor[interceptorInCharge].velocity.y = interceptor[interceptorInCharge].speed * -sinf(interceptor[interceptorInCharge].direction);
							interceptor[interceptorInCharge].velocityRecord = interceptor[interceptorInCharge].velocity;
							for (int j = 0; j < 120; j++)
							{
								interceptor[interceptorInCharge].drag[j].position.x = -100;
								interceptor[interceptorInCharge].drag[j].position.y = -100;
							}
							IPC3_2Status = 1;
						}
						shotTrigger = 0;
					}
					
					/*if (Novice::IsPressMouse(0))
					{
						if (shotTrigger == 1)
						{
							shotTrigger = 2;
						}
					}*/

					//UI
					for(int i =0;i< stage[currentStage].maxInterceptorCount;i++)
					{
						rangerUI[i].status = 4;
					}
				
					rangerUI[interceptorInCharge].status = 2; //0=未啟用  1=啟用未使用  2=incharge  3=攔截中 4=待機(可選)

					if (Novice::IsTriggerMouse(1))
					{
						IPC3_2Status = 1;
					}
					if (mouse.x >= 1162 && mouse.x <= 1190 && mouse.y >= 686 && mouse.y <= 714)
					{
						if (Novice::IsTriggerMouse(0))
						{
							IPC3_2Status = 1;
						}
					}
				}
				else if (IPC3_2Status == 1) //發射 飛行
				{
					interceptorTimer -= 1;
					for (int i = 0; i < stage[currentStage].maxInterceptorCount; i++)
					{
						rangerUI[i].status = 3;
					}
					for(int i=0;i< stage[currentStage].maxInterceptorCount;i++)
					{
						
						interceptor[i].position.x += interceptor[i].velocity.x;
						interceptor[i].position.y += interceptor[i].velocity.y;
						interceptor[i].range = interceptor[i].size + interceptor[i].rangeMax*(interceptorTime - interceptorTimer)/ interceptorTime;
						//目標命中判定
						
						if (interceptorTimer % 2 == 0)
						{
							interceptor[i].drag[interceptorTimer / 2].position.x = interceptor[i].position.x;
							interceptor[i].drag[interceptorTimer / 2].position.y = interceptor[i].position.y;
							interceptor[i].drag[interceptorTimer / 2].color = interceptor[i].color;
						}

						if (interceptor[i].status == 1&&Hit(interceptor[i],target))
						{
							IPC3_2Status = 3;
						}
					}
					
					for(int i=0;i< 10;i++)
					{
						for (int j = 0; j < stage[currentStage].maxInterceptorCount; j++)
						{
							WallCollapes(stage[currentStage].wall[i], interceptor[j]);
						}
					}
					

					if (interceptorTimer <= 0)
					{
						IPC3_2Status = 2;
						if (interceptorInCharge + 1 < stage[0].maxInterceptorCount)
						{
							interceptorInCharge += 1;
						}
					}

					if (Novice::IsTriggerMouse(1))
					{
						if (dragActive)
						{
							dragActive = false;
						}
						else
						{
							dragActive = true;
						}
					}
				}
				else if (IPC3_2Status == 2) //時限後  Reset to 0
				{
					interceptor[interceptorInCharge].position.x = (float)startpoint.x;
					interceptor[interceptorInCharge].position.y = (float)startpoint.y;
					for (int i = 0; i < stage[currentStage].maxInterceptorCount; i++)
					{
						if (interceptor[i].status == 1)
						{
							interceptor[i].position.x = (float)startpoint.x;
							interceptor[i].position.y = (float)startpoint.y;
							interceptor[i].velocity = interceptor[i].velocityRecord;
							interceptor[i].range = interceptor[i].size;
						}
					}
					target.hp = stage[currentStage].maxInterceptorCount;
					target.position.x = stage[currentStage].targetPosition[stage[currentStage].maxInterceptorCount - target.hp].x;
					target.position.y = stage[currentStage].targetPosition[stage[currentStage].maxInterceptorCount - target.hp].y;
					interceptorTimer = interceptorTime;
					interceptor[interceptorInCharge].range = interceptor[interceptorInCharge].size;
					IPC3_2Status = 0;
				}
				else if (IPC3_2Status == 3) //命中 
				{
					target.prePosition = target.position;
					target.hp -= 1;
					target.position.x = stage[currentStage].targetPosition[stage[currentStage].maxInterceptorCount- target.hp].x;
					target.position.y = stage[currentStage].targetPosition[stage[currentStage].maxInterceptorCount - target.hp].y;
					if (target.hp <= 0)
					{
						//stage clear
						inPhaseControll = 4;
					}
					else
					{
						IPC3_2Status = 1;
						inPhaseControll = 3;
					}
					
					
				}

				
				for(int i=0;i< stage[currentStage].maxInterceptorCount;i++)
				{
					if (interceptor[i].status != 0)
					{
						if (interceptor[i].position.x < 0)
						{
							interceptor[i].position.x = 1280;
						}
						if (interceptor[i].position.x > 1280)
						{
							interceptor[i].position.x = 0;
						}
						if (interceptor[i].position.y < 0)
						{
							interceptor[i].position.y = 720;
						}
						if (interceptor[i].position.y > 720)
						{
							interceptor[i].position.y = 0;
						}
					}
				}
				Novice::ScreenPrintf(0, 80, "theta:%f length:%f", interceptor[interceptorInCharge].direction, shotLineLength);
			}
			else if (inPhaseControll == 3) //sub
			{
				targetMoveTimer -= 1;
				//UI
				for (int i = 0; i < stage[currentStage].maxInterceptorCount; i++)
				{
					rangerUI[i].status = 3;
				}
				
				moveToNextPosition(target.texturePosition, target.prePosition,target.position , targetMoveTimer, targetMoveTime);
				if(targetMoveTimer==0)
				{
					inPhaseControll = 2;
					targetMoveTimer = targetMoveTime;
					target.texturePosition = target.position;

					preTarget[stage[currentStage].maxInterceptorCount - target.hp].position.x = target.position.x;
					preTarget[stage[currentStage].maxInterceptorCount - target.hp].position.y = target.position.y;
				}
				
				
			}
			else if (inPhaseControll == 4) //result
			{
				if (Novice::IsPressMouse(1))
				{
					inPhaseControll = 2;
					IPC3_2Status = 1;
				}
				if (Novice::IsPressMouse(0))
				{
					gamePhase = 2;
					inPhaseControll = 2;
				}
			}
			else if (inPhaseControll == 5)
			{
			}

			for (int i = 0; i < stage[currentStage].maxInterceptorCount; i++)
			{
				if (mouse.x >= 1108 && mouse.x <= 1280 && mouse.y >= 30 + 128 * i && mouse.y <= 30 + 128 * i + 103)
				{
					rangerUI[i].status = 2;
					if (Novice::IsTriggerMouse(0))
					{
						interceptorInCharge = i;
						IPC3_2Status = 2;
					}
				}
			}
			if(keys[DIK_1]&& !preKeys[DIK_1])
			{
				interceptorInCharge = 0;
				IPC3_2Status = 2;
			}
			if (keys[DIK_2] && !preKeys[DIK_2])
			{
				interceptorInCharge = 1;
				IPC3_2Status = 2;
			}
			if (keys[DIK_3] && !preKeys[DIK_3])
			{
				interceptorInCharge = 2;
				IPC3_2Status = 2;
			}
			if (stage->maxInterceptorCount > 3)
			{
				if (keys[DIK_4] && !preKeys[DIK_4])
				{
					interceptorInCharge = 3;
					IPC3_2Status = 2;
				}
			}
			if (stage->maxInterceptorCount > 4)
			{
				if (keys[DIK_5] && !preKeys[DIK_5])
				{
					interceptorInCharge = 4;
					IPC3_2Status = 2;
				}
			}
			
			if (keys[DIK_B] && !preKeys[DIK_B])
			{
				gamePhase = 2;
				inPhaseControll = 2;
			}

			if (mouse.x >= 1200 && mouse.x <= 1228 && mouse.y >= 686 && mouse.y <= 714)
			{
				if (Novice::IsTriggerMouse(0))
				{
					if (dragActive)
					{
						dragActive = false;
					}
					else
					{
						dragActive = true;
					}
				}
			}
			if (keys[DIK_T] && !preKeys[DIK_T])
			{
				if(dragActive)
				{
					dragActive = false;
				}
				else
				{
					dragActive = true;
				}
			}
		}
		else if (gamePhase == 4)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		if (gamePhase == 0)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
				Novice::DrawSprite(0, 0, titleTexture, 1.0f , 1.0f , 0.0f, WHITE);
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 1)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
				Novice::DrawSprite(0, 0, tutorialTexture, 1.0f, 1.0f, 0.0f, WHITE);
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 2)
		{
			Novice::DrawSprite(0, 0, stageSelectTexture, 1.0f, 1.0f, 0.0f, WHITE);

			Novice::DrawBox(int(block.pos.x - block.size * 2), int(block.pos.y - block.size * 2), (int) block.size, (int)block.size, 0.0f, WHITE,kFillModeWireFrame);

			
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 5; j++) {
					Novice::DrawBox(int(chooseIcon[i][j].pos.x - chooseIcon[i][j].size), int(chooseIcon[i][j].pos.y - chooseIcon[i][j].size), int(chooseIcon[i][j].size * 2), int(chooseIcon[i][j].size * 2), 0.0f, chooseIcon[i][j].color, kFillModeSolid);
					if (chooseIcon[i][j].isIconChoosed)
					{
						Novice::DrawBox(int(chooseIcon[i][j].pos.x - chooseIcon[i][j].size), int(chooseIcon[i][j].pos.y - chooseIcon[i][j].size), int(chooseIcon[i][j].size * 2), int(chooseIcon[i][j].size * 2), 0.0f, BLACK, kFillModeWireFrame);

					}
				}
			}
			
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
				
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 3)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll >= 2)
			{
				for (int i = 0; i < 10; i++)
				{
					Novice::DrawSpriteRect(static_cast<int>(stage[currentStage].wall[i].position.x) - stage[currentStage].wall[i].length / 2, static_cast<int>(stage[currentStage].wall[i].position.y) - stage[currentStage].wall[i].hieght / 2,
						0, 0, 23, stage[currentStage].wall[i].hieght, wall102Texture, 23.0f / 1280, static_cast<float>(stage[currentStage].wall[i].hieght) / 720, 0.0f, WHITE);
					Novice::DrawSpriteRect(static_cast<int>(stage[currentStage].wall[i].position.x) + stage[currentStage].wall[i].length / 2, static_cast<int>(stage[currentStage].wall[i].position.y) + stage[currentStage].wall[i].hieght / 2,
						0, 0, 23, stage[currentStage].wall[i].hieght, wall102Texture, 23.0f / 1280, static_cast<float>(stage[currentStage].wall[i].hieght) / 720, static_cast<float>(M_PI), WHITE);
					Novice::DrawSpriteRect(static_cast<int>(stage[currentStage].wall[i].position.x) - stage[currentStage].wall[i].length / 2, static_cast<int>(stage[currentStage].wall[i].position.y) - stage[currentStage].wall[i].hieght / 2,
						0, 0, stage[currentStage].wall[i].length, 23, wall101Texture, static_cast<float>(stage[currentStage].wall[i].length) / 1280, 23.0f / 720, 0.0f, WHITE);
					Novice::DrawSpriteRect(static_cast<int>(stage[currentStage].wall[i].position.x) + stage[currentStage].wall[i].length / 2, static_cast<int>(stage[currentStage].wall[i].position.y) + stage[currentStage].wall[i].hieght / 2,
						0, 0, stage[currentStage].wall[i].length, 23, wall101Texture, static_cast<float>(stage[currentStage].wall[i].length) / 1280, 23.0f / 720, static_cast<float>(M_PI), WHITE);
					Novice::DrawBox(static_cast<int>(stage[currentStage].wall[i].position.x) - stage[currentStage].wall[i].length / 2 + 23, static_cast<int>(stage[currentStage].wall[i].position.y) - stage[currentStage].wall[i].hieght / 2 + 23, stage[currentStage].wall[i].length - 46, stage[currentStage].wall[i].hieght - 46, 0.0f, RED, kFillModeWireFrame);

				}

				for (int i = 0; i < stage[currentStage].maxInterceptorCount; i++)
				{
					if (dragActive && interceptor[i].status == 1)
					{
						for (int j = 0; j < 120; j++)
						{
							Novice::DrawEllipse((int)interceptor[i].drag[j].position.x, (int)interceptor[i].drag[j].position.y, interceptor[i].size, interceptor[i].size, 0.0f, interceptor[i].drag[j].color - j * 2 - 10, kFillModeSolid);

						}
					}
					if (IPC3_2Status ==1&& interceptor[i].status == 1)
					{
						Novice::DrawEllipse((int)interceptor[i].position.x, (int)interceptor[i].position.y, interceptor[i].size, interceptor[i].size, 0.0f, interceptor[i].color, kFillModeSolid); //インターセプター本体
						Novice::DrawEllipse((int)interceptor[i].position.x, (int)interceptor[i].position.y, interceptor[i].range, interceptor[i].range, 0.0f, interceptor[i].color - 120 - (interceptorTime - interceptorTimer) / 2, kFillModeSolid); //インターセプター範囲
						
					}
					Novice::DrawEllipse((int)preTarget[i].position.x, (int)preTarget[i].position.y,target.size, target.size, 0.0f, target.color, kFillModeWireFrame); //target record
				}
				Novice::DrawEllipse((int)target.texturePosition.x, (int)target.texturePosition.y, target.size, target.size, 0.0f, target.color, kFillModeSolid);



				float theta = atan2f((float)(mouse.y - startpoint.y), (float)(mouse.x - startpoint.x));
				float length = 200;
				
				if (backendData)
				{
					Novice::ScreenPrintf(0, 20, "mouseX:%d mouseY:%d shotTrigger:%d", mouse.x, mouse.y, shotTrigger);
					Novice::ScreenPrintf(0, 40, "mouseIspressed:%d IPC3_2Status:%d", mouseIsPressed, IPC3_2Status);
					Novice::ScreenPrintf(0, 60, "interceptorInCharge:%d X:%f Y:%f", interceptorInCharge, interceptor[interceptorInCharge].position.x, interceptor[interceptorInCharge].position.y);
					Novice::ScreenPrintf(0, 500, "targetHp=%d", target.hp);
				}
				
				if (IPC3_2Status == 0)
				{
					if (interceptor[interceptorInCharge].status != 0)
					{
						Novice::DrawLine(startpoint.x, startpoint.y, startpoint.x - (int)(length * cosf(interceptor[interceptorInCharge].preDirection)), startpoint.y - (int)(length * sinf(interceptor[interceptorInCharge].preDirection)), BLACK);
					}
					
					if (shotTrigger == 2)
					{
						if(shotLineLength>30)
						{
							Novice::DrawLine(startpoint.x, startpoint.y, startpoint.x - (int)(length * cosf(theta)), startpoint.y - (int)(length * sinf(theta)), 0xFFFFFFFF);
						}
					}
					Novice::DrawEllipse(startpoint.x, startpoint.y, chargeRange, chargeRange, 0.0f, 0xFFFFFFFF, kFillModeWireFrame);
					Novice::DrawEllipse(startpoint.x, startpoint.y, 30, 30, 0.0f, 0xFFFFFFFF, kFillModeWireFrame);

					Novice::DrawEllipse((int)interceptor[interceptorInCharge].position.x, (int)interceptor[interceptorInCharge].position.y, interceptor[interceptorInCharge].size, interceptor[interceptorInCharge].size, 0.0f, interceptor[interceptorInCharge].color, kFillModeSolid); //インターセプター本体

				}
				else if (IPC3_2Status == 1)
				{
					
				}
				else if (IPC3_2Status == 2)
				{
				}
				else if (IPC3_2Status == 3)
				{
				}

				Novice::DrawBox(0, 680, 1280, 60, 0.0f, 0x9badb7FF, kFillModeSolid);
				float X = 1 - ((float)interceptorTimer / (float)interceptorTime);
				Novice::DrawSprite(0, 0, controlUITexture, 1.0f, 1.0f, 0.0f, 0xFFFFFF33);
				Novice::DrawBox(50, 695, 1100, 10, 0.0f, 0x847e87FF, kFillModeSolid);
				Novice::DrawBox(50, 695, (int)(1100 * X), 10, 0.0f, WHITE, kFillModeSolid);
				Novice::DrawEllipse(50 + (int)(1100 * X), 695 + 5, 10, 10, 0.0f, BLACK, kFillModeSolid);
				Novice::DrawSprite(0, 0, controlUITexture, 1.0f, 1.0f, 0.0f, WHITE);
				Novice::DrawSprite(0, 0, controlUIrTexture, 1.0f, 1.0f, 0.0f, WHITE);
				if(dragActive)
				{
					Novice::DrawSprite(0, 0, controlUItTexture, 1.0f, 1.0f, 0.0f, WHITE);
				}
				else
				{
					Novice::DrawSprite(0, 0, controlUItTexture, 1.0f, 1.0f, 0.0f, 0xFFFFFF33);
				}
				Novice::DrawSprite(0, 0, controlUIhTexture, 1.0f, 1.0f, 0.0f, WHITE);
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}

			for (int i = 0; i < 5; i++)
			{
				//0=未啟用  1=啟用未使用  2=incharge  3=攔截中 4=待機(可選)
				if (rangerUI[i].status == 0)
				{
					rangerUI[i].x = 175;
				}
				else if (rangerUI[i].status == 1)
				{
					rangerUI[i].x = 155;
				}
				else if (rangerUI[i].status == 2)
				{
					rangerUI[i].x = 0;
				}
				else if (rangerUI[i].status == 3)
				{
					rangerUI[i].x = 103;
				}
				else if (rangerUI[i].status == 4)
				{
					rangerUI[i].x = 15;
				}

				if (rangerUI[i].textureX > rangerUI[i].x)
				{
					rangerUI[i].textureX -= 10;
					if (rangerUI[i].textureX < rangerUI[i].x)
					{
						rangerUI[i].textureX = rangerUI[i].x;
					}
				}
				else if (rangerUI[i].textureX < rangerUI[i].x)
				{
					rangerUI[i].textureX += 10;
					if (rangerUI[i].textureX > rangerUI[i].x)
					{
						rangerUI[i].textureX = rangerUI[i].x;
					}
				}

			}

			Novice::DrawSprite(0, 0, reCrewUIUnderTexture, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(rangerUI[0].textureX, 0, Ranger01Texture, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(rangerUI[1].textureX, 0, Ranger02Texture, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(rangerUI[2].textureX, 0, Ranger03Texture, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(rangerUI[3].textureX, 0, Ranger04Texture, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(rangerUI[4].textureX, 0, Ranger05Texture, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(0, 0, reCrewUITexture, 1.0f, 1.0f, 0.0f, WHITE);
		}
		else if (gamePhase == 4)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}

		if (backendData)
		{
			Novice::ScreenPrintf(0, 0, "GamePhase:%d inPhase:%d inPhase3:%d stage:%d", gamePhase, inPhaseControll, IPC3_2Status, currentStage);
			Novice::ScreenPrintf(300, 80, "target.positionX:%f target.positionY:%f", stage[currentStage].targetPosition[0].x, stage[currentStage].targetPosition[0].y);
			Novice::ScreenPrintf(300, 100, "texture.positionX:%f texture.positionY:%f", target.texturePosition.x, target.texturePosition.y);
			/*for(int i=0;i< stage[currentStage].maxInterceptorCount;i++)
			{
				Novice::DrawBox(1108, 30 + 128 * i, 172, 103, 0.0f, BLUE, kFillModeWireFrame);
				if(mouse.x>=1108 && mouse.x<=1280 && mouse.y>=30 + 128 * i && mouse.y<=30 + 128 * i +103)
				{
					rangerUI[i].status = 3;
				}
				Novice::DrawBox(1093, 30 + 128 * i, 187, 103, 0.0f, RED, kFillModeWireFrame);
				if(mouse.x>=1093 && mouse.x<=1280 && mouse.y>=30 + 128 * i && mouse.y<=30 + 128 * i +103)
				{
					Novice::DrawBox(1093, 30 + 128 * i, 187, 103, 0.0f, WHITE, kFillModeWireFrame);
				}
			}*/
			
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
