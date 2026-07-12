#include "stageData.h"
#include "Vector2.h"

Stage gStageData[10]; 
//{   {5,{{ 200.0f,200.0f }       //0
//	 ,{ 640.0f,360.0f }
//	 ,{ 600.0f,400.0f }
//	 ,{ 1000.0f,100.0f }
//	 ,{ 600.0f,500.0f }}},
//	{4,{{ 300.0f,500.0f }        //1
//	 , { 700.0f,200.0f }
//	 , { 500.0f,400.0f }
//	 , { 900.0f,100.0f }
//	 , { 400.0f,300.0f }}},
//	{4,{{ 300.0f,500.0f }        //2
//	 , { 700.0f,200.0f }
//	 , { 500.0f,400.0f }
//	 , { 900.0f,100.0f }
//	 , { 400.0f,300.0f }}},
//	{4,{{ 300.0f,500.0f }        //3
//	 , { 700.0f,200.0f }
//	 , { 500.0f,400.0f }
//	 , { 900.0f,100.0f }
//	 , { 400.0f,300.0f }}},
//	{4,{{ 300.0f,500.0f }        //4
//	 , { 700.0f,200.0f }
//	 , { 500.0f,400.0f }
//	 , { 900.0f,100.0f }
//	 , { 400.0f,300.0f }}},
//	{4,{{ 300.0f,500.0f }        //5
//	 , { 700.0f,200.0f }
//	 , { 500.0f,400.0f }
//	 , { 900.0f,100.0f }
//	 , { 400.0f,300.0f }}},
//	{4,{{ 300.0f,500.0f }        //6
//	 , { 700.0f,200.0f }
//	 , { 500.0f,400.0f }
//	 , { 900.0f,100.0f }
//	 , { 400.0f,300.0f }}},
//	{3,{{ 300.0f,500.0f }        //7
//	 , { 700.0f,200.0f }
//	 , { 500.0f,400.0f }
//	 , { 900.0f,100.0f }
//	 , { 400.0f,300.0f }}},
//	{4,{{ 700.0f,900.0f }        //8
//	 , { 700.0f,200.0f }
//	 , { 500.0f,400.0f }
//	 , { 900.0f,100.0f }
//	 , { 400.0f,300.0f }}},
//	{5,{{ 600.0f,300.0f }        //9
//	 , { 700.0f,200.0f }
//	 , { 500.0f,400.0f }
//	 , { 900.0f,100.0f }
//	 , { 400.0f,300.0f }}} };


void initializeStageData()
{
	gStageData[0].maxInterceptorCount=3;
	gStageData[0].targetPosition[0]={ 200.0f,200.0f };
	gStageData[0].targetPosition[1]={ 640.0f,360.0f };
	gStageData[0].targetPosition[2]={ 600.0f,400.0f };
	//gStageData[0].targetPosition[3]={ 1000.0f,100.0f };
	//gStageData[0].targetPosition[4]={ 600.0f,500.0f };
	gStageData[0].wall[0].position = { 400,360 };
	gStageData[0].wall[0].length = 200;
	gStageData[0].wall[0].hieght = 90;

	gStageData[1].maxInterceptorCount = 3;
	gStageData[1].targetPosition[0] = { 200.0f,200.0f };
	gStageData[1].targetPosition[1] = { 840.0f,360.0f };
	gStageData[1].targetPosition[2] = { 600.0f,500.0f };
	//gStageData[1].targetPosition[3] = { 1000.0f,100.0f };
	//gStageData[1].targetPosition[4] = { 600.0f,500.0f };
	gStageData[1].wall[0].position = { 400,360 };
	gStageData[1].wall[0].length = 20;
	gStageData[1].wall[0].hieght = 250;
	gStageData[1].wall[1].position = { 800,180 };
	gStageData[1].wall[1].length = 40;
	gStageData[1].wall[1].hieght = 400;
	gStageData[1].wall[2].position = { 600,600 };
	gStageData[1].wall[2].length = 300;
	gStageData[1].wall[2].hieght = 20;

	gStageData[2].maxInterceptorCount = 4;
	gStageData[2].targetPosition[0] = { 600.0f,200.0f };
	gStageData[2].targetPosition[1] = { 1000,600 };
	gStageData[2].targetPosition[2] = { 800.0f,400.0f };
	gStageData[2].targetPosition[3] = { 1000.0f,100.0f };
	//gStageData[2].targetPosition[4] = { 600.0f,500.0f };
	gStageData[2].wall[0].position = { 800,400 };
	gStageData[2].wall[0].length = 60;
	gStageData[2].wall[0].hieght = 60;
	gStageData[2].wall[1].position = { 450,180 };
	gStageData[2].wall[1].length = 40;
	gStageData[2].wall[1].hieght = 40;
	gStageData[2].wall[2].position = { 200,500 };
	gStageData[2].wall[2].length = 50;
	gStageData[2].wall[2].hieght = 50;
	gStageData[2].wall[3].position = { 1000,600 };
	gStageData[2].wall[3].length = 30;
	gStageData[2].wall[3].hieght = 30;
	gStageData[2].wall[4].position = { 300,300 };
	gStageData[2].wall[4].length = 40;
	gStageData[2].wall[4].hieght = 40;
	gStageData[2].wall[5].position = { 500,400 };
	gStageData[2].wall[5].length = 40;
	gStageData[2].wall[5].hieght = 40;

	gStageData[3].maxInterceptorCount = 4;
	gStageData[3].targetPosition[0] = { 200.0f,200.0f };
	gStageData[3].targetPosition[1] = { 1100.0f,200.0f };
	gStageData[3].targetPosition[2] = { 1100.0f,600.0f };
	gStageData[3].targetPosition[3] = { 200.0f,600.0f };
	//gStageData[3].targetPosition[4] = { 600.0f,500.0f };
	gStageData[3].wall[0].position = { 400,360 };
	gStageData[3].wall[0].length = 200;
	gStageData[3].wall[0].hieght = 90;
	gStageData[3].wall[1].position = { 900,600 };
	gStageData[3].wall[1].length = 50;
	gStageData[3].wall[1].hieght = 70;
	
	gStageData[4].maxInterceptorCount = 5;
	gStageData[4].targetPosition[0] = { 1000.0f,100.0f };
	gStageData[4].targetPosition[1] = { 640.0f,600.0f };
	gStageData[4].targetPosition[2] = { 90.0f,400.0f };
	gStageData[4].targetPosition[3] = { 200.0f,360.0f };
	gStageData[4].targetPosition[4] = { 600.0f,500.0f };
	gStageData[4].wall[0].position = { 200,360 };
	gStageData[4].wall[0].length = 90;
	gStageData[4].wall[0].hieght = 90;
	gStageData[4].wall[1].position = { 800,180 };
	gStageData[4].wall[1].length = 70;
	gStageData[4].wall[1].hieght = 40;
	gStageData[4].wall[2].position = { 400,600 };
	gStageData[4].wall[2].length = 100;
	gStageData[4].wall[2].hieght = 50;


	gStageData[5].maxInterceptorCount = 5;
	gStageData[5].targetPosition[0] = { 200.0f,200.0f };
	gStageData[5].targetPosition[1] = { 640.0f,360.0f };
	gStageData[5].targetPosition[2] = { 600.0f,400.0f };
	gStageData[5].targetPosition[3] = { 1000.0f,100.0f };
	gStageData[5].targetPosition[4] = { 600.0f,500.0f };
	gStageData[5].wall[0].position = { 400,360 };
	gStageData[5].wall[0].length = 200;
	gStageData[5].wall[0].hieght = 90;
	gStageData[5].wall[1].position = { 700,180 };
	gStageData[5].wall[1].length = 60;
	gStageData[5].wall[1].hieght = 40;
	gStageData[5].wall[2].position = { 800,600 };
	gStageData[5].wall[2].length = 50;
	gStageData[5].wall[2].hieght = 90;
};