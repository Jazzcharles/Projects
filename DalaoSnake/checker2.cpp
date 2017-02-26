#include <windows.h>
#include "resource.h"
#include <stdio.h>
#include <vector>
#include <time.h>
#include<mmsystem.h>
using namespace std;
#pragma comment (lib,"winmm.lib");
//游戏区和控制区宽度高度
#define  GAME_WIDE             70     //游戏区宽度70*10
#define  GAME_HEIGHT           60     //游戏区高度60*10
#define  CTRL_WIDE             30     //控制区宽度30*10
#define  CTRL_HEIGHT           60     //控制区高度60*10
#define  BOUNDSIZE             10     //边界厚度10   
//蛇的信息
#define   SNAKESIZE            10     //蛇的宽高都为20的小方块
#define   SNAKEMAX            100     //蛇身长度最大值为100
#define   SNAKESPEED          500     //初始化蛇的速度为500ms
#define   TIMERID_1             1     //定时器ID
#define   PAUSEID               1     //暂停按钮ID
#define   STARTID               2     //开始按钮ID 
#define   SPEEDUPID             3     //加速按钮ID
#define   SPEEDDOWNID           4     //减速按钮ID
vector<POINT> vSnakePoint;       //声明一个蛇的坐标
vector<POINT> vSnakePoint2;
	
UCHAR ucSnakeHead = 4;                //初始化蛇头为4，实际上是vSnakePoint[3];
UCHAR ucSnakeTail = 0;                //初始化蛇尾为0
UCHAR ucSnakekLen = 4;                //初始化蛇身长度为4
UCHAR ucSnakeHead2 = 4;                //初始化蛇头为4，实际上是vSnakePoint[3];
UCHAR ucSnakeTail2 = 0;                //初始化蛇尾为0
UCHAR ucSnakekLen2 = 4;
UINT uiSnakeSpeed = SNAKESPEED;       //初始化蛇的速度为500ms
UINT uiScore = 0;//初始化分数为0
UINT uiScore2 = 0;

POINT ptDirectHead = { 1,0 }; 
POINT ptDirectHead2 = { -1, 0 };	//蛇头的方向,初始化为向右
POINT ptFood = { 20,20 };             //食物坐标

BOOL bIsLoose = TRUE; //判断是否输了
BOOL bIsLoose2 = TRUE;
BOOL bIsWin = FALSE;                  //判断是否赢了
BOOL bIsPause = FALSE;                //判断是否暂停了
BOOL bIsStart = FALSE;                //判断是否开始了
BOOL bFlagStart = FALSE;              //判断是否能开始
HACCEL hAccel;
HBITMAP hBit1,hBit2,hBit3,hBit4,hBit5,hBit6; /* handle of bitmaps */
//HINSTANCE hInst; /* handle to this instance */

FILE* file;
HWND hIdeaDlg = NULL;


static int state = 2;//1向左2向右3向上4向下
static int state1 = 1,choice = 0;
HANDLE hfile;
TCHAR buf[100][100];//存文件


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL  CALLBACK IdeaDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL    CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szAppName[] = TEXT("Snake by DaLao");
//HINSTANCE hInst = nullptr;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	//hInst = hInstance;
	HWND     hwnd;
	MSG      msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	//hInst = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}
	
	hwnd = CreateWindow(szAppName, szAppName,
		WS_DLGFRAME | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hwnd, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

//初始化蛇
VOID InitSnake()
{
	//先清空坐标
	vSnakePoint.clear();
	//给蛇坐标分配空间
	vSnakePoint.resize(SNAKEMAX);
	//游戏结束后再次初始化
	ucSnakeHead = 4;//初始化蛇头为4，实际上是vSnakePoint[3];
	ucSnakeTail = 0;//初始化蛇尾为0
	ucSnakekLen = 4;//初始化蛇身长度为4
	uiSnakeSpeed = SNAKESPEED;//初始化蛇的速度为200ms
	ptDirectHead = { 1,0 };//初始化蛇头方向
	ptFood = { 20,20 };//初始化食物坐标
	uiScore = 0;//初始化分数
				//初始化每一节的蛇身坐标
	uiScore2 = 0;
	for (int i = 0; i < ucSnakekLen; i++)
	{
		vSnakePoint[i].x = i;
		vSnakePoint[i].y = 0;
	}
}


VOID InitSnake2()
{
	//先清空坐标
	vSnakePoint2.clear();
	//给蛇坐标分配空间
	vSnakePoint2.resize(SNAKEMAX << 4);
	//游戏结束后再次初始化
	ucSnakeHead2 = 4;//初始化蛇头为4，实际上是vSnakePoint[3];
	ucSnakeTail2 = 0;//初始化蛇尾为0
	ucSnakekLen2 = 4;//初始化蛇身长度为4
	uiSnakeSpeed = SNAKESPEED;//初始化蛇的速度为200ms
	ptDirectHead2 = { -1, 0 };//初始化蛇头方向
							  //初始化每一节的蛇身坐标
	for (int i = 0; i < ucSnakekLen2; i++)
	{
		vSnakePoint2[i].x = 69 - i;
		vSnakePoint2[i].y = 59;
	}
}

//获取蛇结点位置
//index是一个偏移蛇尾的偏移量
POINT &GetSnakeNode(int index)
{
	int i = ucSnakeTail + index;//蛇身的长度
	if (i >= SNAKEMAX)
	{
		i -= SNAKEMAX;
	}
	return vSnakePoint[i];
}


POINT &GetSnakeNode2(int index)
{
	int i = ucSnakeTail2 + index;//蛇身的长度
	if (i >= SNAKEMAX)
	{
		i -= SNAKEMAX;
	}
	return vSnakePoint2[i];
}

//画蛇身
VOID DrawSnake(HDC hdc,HWND hwnd)
{
	HDC memDC1,memDC2,memDC3;
	char str[30] = "saa";
	//static HBRUSH hBrush = CreateSolidBrush(RGB(0, 243, 222));
	hdc = GetDC(hwnd);
	switch (state)
	{
	case 1:
		hBit1 = (HBITMAP)LoadImage(NULL, "headblueL.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit2 = (HBITMAP)LoadImage(NULL, "bodyblue1.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit3 = (HBITMAP)LoadImage(NULL, "tailblueL.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		break;
	case 2:
		hBit1 = (HBITMAP)LoadImage(NULL, "headblueR.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit2 = (HBITMAP)LoadImage(NULL, "bodyblue1.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit3 = (HBITMAP)LoadImage(NULL, "tailblueR.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		break;
	case 3:
		hBit1 = (HBITMAP)LoadImage(NULL, "headblueU.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit2 = (HBITMAP)LoadImage(NULL, "bodyblue.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit3 = (HBITMAP)LoadImage(NULL, "tailblueU.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		break;
	case 4:
		hBit1 = (HBITMAP)LoadImage(NULL, "headblueD.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit2 = (HBITMAP)LoadImage(NULL, "bodyblue.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit3 = (HBITMAP)LoadImage(NULL, "tailblueD.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		break;
	}
	memDC1 = CreateCompatibleDC(hdc);
	memDC2 = CreateCompatibleDC(hdc);
	memDC3 = CreateCompatibleDC(hdc);
	//SelectObject(hdc, hBrush);
	SelectObject(memDC1, hBit1);
	SelectObject(memDC2, hBit2);
	SelectObject(memDC3, hBit3);
	//当前蛇结点
	POINT ptCurrentNode = { 0 };

	for (int i = 0; i < ucSnakekLen; i++)
	{
		ptCurrentNode = GetSnakeNode(i);
		//Rectangle(hdc, ptCurrentNode.x*SNAKESIZE + BOUNDSIZE, ptCurrentNode.y*SNAKESIZE + BOUNDSIZE,
			//(ptCurrentNode.x + 1)*SNAKESIZE + BOUNDSIZE, (ptCurrentNode.y + 1)*SNAKESIZE + BOUNDSIZE);
		if(i==0)
			BitBlt(hdc, ptCurrentNode.x*SNAKESIZE + BOUNDSIZE, ptCurrentNode.y*SNAKESIZE + BOUNDSIZE,10, 10,memDC3, 0, 0, SRCCOPY);
		else if(i==ucSnakekLen-1)
			BitBlt(hdc, ptCurrentNode.x*SNAKESIZE + BOUNDSIZE, ptCurrentNode.y*SNAKESIZE + BOUNDSIZE, 10, 10, memDC1, 0, 0, SRCCOPY);
		else
			BitBlt(hdc, ptCurrentNode.x*SNAKESIZE + BOUNDSIZE, ptCurrentNode.y*SNAKESIZE + BOUNDSIZE, 10, 10, memDC2, 0, 0, SRCCOPY);

	}

}


VOID DrawSnake2(HDC hdc,HWND hwnd)
{
	HDC memDC4, memDC5, memDC6;
	char str[30] = "saa";
	//static HBRUSH hBrush = CreateSolidBrush(RGB(0, 243, 222));
	hdc = GetDC(hwnd);
	switch (state1)
	{
	case 1:
		hBit4 = (HBITMAP)LoadImage(NULL, "headredL.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit5 = (HBITMAP)LoadImage(NULL, "bodyred.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit6 = (HBITMAP)LoadImage(NULL, "tailredL.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		break;
	case 2:
		hBit4 = (HBITMAP)LoadImage(NULL, "headredR.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit5 = (HBITMAP)LoadImage(NULL, "bodyred.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit6 = (HBITMAP)LoadImage(NULL, "tailredR.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		break;
	case 3:
		hBit4 = (HBITMAP)LoadImage(NULL, "headredU.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit5 = (HBITMAP)LoadImage(NULL, "bodyred1.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit6 = (HBITMAP)LoadImage(NULL, "tailredU.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		break;
	case 4:
		hBit4 = (HBITMAP)LoadImage(NULL, "headredD.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit5 = (HBITMAP)LoadImage(NULL, "bodyred1.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		hBit6 = (HBITMAP)LoadImage(NULL, "tailredD.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
		break;
	}
	memDC4 = CreateCompatibleDC(hdc);
	memDC5 = CreateCompatibleDC(hdc);
	memDC6 = CreateCompatibleDC(hdc);
	//SelectObject(hdc, hBrush);
	SelectObject(memDC4, hBit4);
	SelectObject(memDC5, hBit5);
	SelectObject(memDC6, hBit6);
	//当前蛇结点
	POINT ptCurrentNode = { 0 };

	for (int i = 0; i < ucSnakekLen2; i++)
	{
		ptCurrentNode = GetSnakeNode2(i);
		//Rectangle(hdc, ptCurrentNode.x*SNAKESIZE + BOUNDSIZE, ptCurrentNode.y*SNAKESIZE + BOUNDSIZE,
		//(ptCurrentNode.x + 1)*SNAKESIZE + BOUNDSIZE, (ptCurrentNode.y + 1)*SNAKESIZE + BOUNDSIZE);
		if (i == 0)
			BitBlt(hdc, ptCurrentNode.x*SNAKESIZE + BOUNDSIZE, ptCurrentNode.y*SNAKESIZE + BOUNDSIZE, 10, 10, memDC6, 0, 0, SRCCOPY);
		else if (i == ucSnakekLen2 - 1)
			BitBlt(hdc, ptCurrentNode.x*SNAKESIZE + BOUNDSIZE, ptCurrentNode.y*SNAKESIZE + BOUNDSIZE, 10, 10, memDC4, 0, 0, SRCCOPY);
		else
			BitBlt(hdc, ptCurrentNode.x*SNAKESIZE + BOUNDSIZE, ptCurrentNode.y*SNAKESIZE + BOUNDSIZE, 10, 10, memDC5, 0, 0, SRCCOPY);

	}
}

//设置食物坐标
void SetFood()
{
	POINT ptNow = { 0 };
	int x = 0, y = 0, i = 0;
	while (true)
	{
		srand(time(0));//随机器种子
		x = rand() % GAME_WIDE; //设置食物随机坐标
		y = rand() % GAME_HEIGHT;
		for (i = 0; i < ucSnakekLen; i++)
		{
			ptNow = GetSnakeNode(i);
			if (ptNow.x == x && ptNow.y == y)
				break;//如果食物出现在蛇身，则重新设置食物
		}//如果食物不在蛇身，就退出循环
		if (ucSnakekLen == i) break;
	}
	ptFood.x = x;
	ptFood.y = y;
}

//判断蛇是否撞墙
BOOL IsStrikeWall(POINT ptHead)
{
	if (ptHead.x < 0 || ptHead.x >= GAME_WIDE
		|| ptHead.y < 0 || ptHead.y >= GAME_HEIGHT)
	{
		bIsLoose = FALSE;//撞墙输了
		return FALSE;
	}
	return TRUE;
}

BOOL IsStrikeWall2(POINT ptHead)
{
	if (ptHead.x < 0 || ptHead.x >= GAME_WIDE
		|| ptHead.y < 0 || ptHead.y >= GAME_HEIGHT)
	{
		bIsLoose2 = FALSE;//撞墙输了
		return FALSE;
	}
	return TRUE;
}

//判断是否撞到自己
BOOL IsStrikeSelf(POINT ptHead)
{
	POINT ptNow = { 0 };
	for (int i = 0; i < ucSnakekLen - 1; i++)
	{
		ptNow = GetSnakeNode(i);
		if (ptHead.x == ptNow.x && ptHead.y == ptNow.y)
		{
			bIsLoose = FALSE;//撞自己输了
			return FALSE;
		}

	}
	return TRUE;
}

BOOL IsStrikeSelf2(POINT ptHead)
{
	POINT ptNow = { 0 };
	for (int i = 0; i < ucSnakekLen2 - 1; i++)
	{
		ptNow = GetSnakeNode2(i);
		if (ptHead.x == ptNow.x && ptHead.y == ptNow.y)
		{
			bIsLoose2 = FALSE;//撞自己输了
			return FALSE;
		}

	}
	return TRUE;
}


BOOL IsStrike(POINT ptHead){
	POINT ptNow = { 0 };
	for (int i = 0; i < ucSnakekLen2; i++){
		ptNow = GetSnakeNode2(i);
		if (ptHead.x == ptNow.x && ptHead.y == ptNow.y){
			bIsLoose = FALSE;
			return FALSE;
		}
	}

	return TRUE;
}

BOOL IsStrike2(POINT ptHead2){

	POINT ptNow = { 0 };

	for (int i = 0; i < ucSnakekLen; i++){
		ptNow = GetSnakeNode(i);
		if (ptHead2.x == ptNow.x && ptHead2.y == ptNow.y){
			bIsLoose2 = FALSE;
			return FALSE;
		}
	}
	return TRUE;
}
//判断是否吃到食物
BOOL IsEat(POINT ptHead)
{
	return (ptHead.x == ptFood.x && ptHead.y == ptFood.y) ? TRUE : FALSE;
}

//显示分数
void ShowScore(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	HPEN hPen = CreatePen(PS_SOLID, 4, RGB(255, 255, 0));
	SelectObject(hdc, hPen);
	int iLength = 0;
	TCHAR szBuffer[20] = { 0 };
	iLength = wsprintf(szBuffer, "Player1 Score: %u", uiScore);
	TextOut(hdc, BOUNDSIZE * 2 + GAME_WIDE*SNAKESIZE + 100,
		BOUNDSIZE + 200, szBuffer, iLength);
	if (choice == 2){
		iLength = wsprintf(szBuffer, "Player2 Score: %u", uiScore2);
		TextOut(hdc, BOUNDSIZE * 2 + GAME_WIDE*SNAKESIZE + 100,
			BOUNDSIZE + 300, szBuffer, iLength);
	}
	ReleaseDC(hwnd, hdc);
	DeleteObject(hPen);
}

//判断是否超出范围
void IsOverTake()
{
	if (SNAKEMAX == ucSnakeHead)  ucSnakeHead = 0;   //超出范围往返循环  
	if (SNAKEMAX == ucSnakeTail)  ucSnakeTail = 0;
	//if (SNAKEMAX == ucSnakekLen)  bIsWin = TRUE;//赢了
	if (SNAKEMAX == ucSnakeHead2) ucSnakeHead2 = 0;
	if (SNAKEMAX == ucSnakeTail2) ucSnakeTail2 = 0;
	//if (SNAKEMAX == ucSnakekLen2) bIsWin = TRUE;
}


//增加蛇的长度
void AddSnakeLen(POINT ptHead)
{
	vSnakePoint[ucSnakeHead++] = ptHead;//蛇头增长
	ucSnakekLen++;//长度+1
	IsOverTake();//判断是否超出范围
}

void AddSnakeLen2(POINT ptHead)
{
	vSnakePoint2[ucSnakeHead2++] = ptHead;//蛇头增长
	ucSnakekLen2++;//长度+1
	IsOverTake();//判断是否超出范围
}


//让蛇动起来
BOOL  SnakeMove()
{
	BOOL bRet = FALSE;
	do
	{
		POINT ptNewNode = { 0 };//新的蛇头
		ptNewNode.x = GetSnakeNode(ucSnakekLen - 1).x + ptDirectHead.x;
		ptNewNode.y = GetSnakeNode(ucSnakekLen - 1).y + ptDirectHead.y;
		if (!IsStrikeWall(ptNewNode))//判断新的蛇头是否撞墙
			break;
		if (!IsStrikeSelf(ptNewNode))//判断蛇是否撞到自己
			break;
		if (!IsStrike(ptNewNode))
			break;
		if (IsEat(ptNewNode))//判断是否吃到食物
		{
			SetFood();//重新设置食物坐标
			uiScore += 10;//吃到一个食物加10分
			AddSnakeLen(ptNewNode);//增加蛇的长度
			break;
		}
		vSnakePoint[ucSnakeHead].x = ptNewNode.x;//蛇头移动
		vSnakePoint[ucSnakeHead++].y = ptNewNode.y;
		ucSnakeTail++;
		IsOverTake();
		bRet = TRUE;
	} while (FALSE);
	return bRet;
}


//让蛇动起来
BOOL  SnakeMove2()
{
	BOOL bRet = FALSE;
	do
	{
		POINT ptNewNode = { 0 };//新的蛇头
		ptNewNode.x = GetSnakeNode2(ucSnakekLen2 - 1).x + ptDirectHead2.x;
		ptNewNode.y = GetSnakeNode2(ucSnakekLen2 - 1).y + ptDirectHead2.y;
		if (!IsStrikeWall2(ptNewNode))//判断新的蛇头是否撞墙
			break;
		if (!IsStrikeSelf2(ptNewNode))//判断蛇是否撞到自己
			break;
		if (!IsStrike2(ptNewNode))
			break;
		if (IsEat(ptNewNode))//判断是否吃到食物
		{
			SetFood();//重新设置食物坐标
			if(choice == 2) uiScore2 += 10;//吃到一个食物加10分
			AddSnakeLen2(ptNewNode);//增加蛇的长度
			break;
		}

		vSnakePoint2[ucSnakeHead2].x = ptNewNode.x;//蛇头移动
		vSnakePoint2[ucSnakeHead2++].y = ptNewNode.y;
		ucSnakeTail2++;
		IsOverTake();
		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

//画食物
void DrawFood(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	SelectObject(hdc, hBrush);
	//椭圆食物
	Ellipse(hdc, BOUNDSIZE + ptFood.x*SNAKESIZE, BOUNDSIZE + ptFood.y*SNAKESIZE
		, BOUNDSIZE + (ptFood.x + 1)*SNAKESIZE, BOUNDSIZE + (ptFood.y + 1)*SNAKESIZE);
	ReleaseDC(hwnd, hdc);
	DeleteObject(hBrush);
}

void showrank(HWND hwnd){

	HDC hdc = GetDC(hwnd);

	int i = 0, col = 200;
	TCHAR S[1000] = { 0 };
	int k = 0;
	TCHAR temp[20] = "Score  Name\n\n$";
	for (int i = 0; temp[i] != '$'; i++){
		S[k++] = temp[i];
	}
	file = fopen("Rank.txt", "r");
	for (int i = 0; i < 5; i++){
		fgets(buf[i], 100, file);
		//TextOut(hdc, 200, col, buf[i], strlen(buf[i])-1);
		//col += 20;
		for (int j = 0; j<strlen(buf[i]); j++)
			S[k++] = buf[i][j];
		//S[k++] = '\n';
	}
	MessageBox(hwnd,S, TEXT("Ranklist"), MB_OK);
}

void setrank(){
	SetFilePointer(hfile, 0, 0, FILE_BEGIN);
	



}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rect = { 0 };
	static int  ixWind = 0, iyWind = 0;//窗口大小参数
	static int ixClient = 0, iyClient = 0;//客户区大小参数
	static int started = 0;;
	static int x1 = 0;   //鼠标位置
	static int y1 = 0;
	static HBITMAP      background,background1, bmp, mask;
	static HWND  hPause = nullptr;//暂停按钮句柄
	static HWND  hStart = nullptr;//开始按钮句柄
	static HWND  hSpeedUp = nullptr;//加速按钮句柄
	static HWND  hSpeedDown = nullptr;//减速按钮句柄
	HMENU hmenu;
	DWORD dwError = 0;//错误信息
	HDC DC, memDC;
	static HINSTANCE hInst;
	DWORD dwreadsize = 0;
	switch (message)
	{
	case WM_CREATE:
	{
		DC = GetDC(hwnd);
		hInst = ((LPCREATESTRUCT)lParam)->hInstance;
		//获取窗口大小
		GetWindowRect(hwnd, &rect);
		ixWind = rect.right - rect.left;
		iyWind = rect.bottom - rect.top;
		//获取客户区大小
		GetClientRect(hwnd, &rect);
		ixClient = rect.right - rect.left;
		iyClient = rect.bottom - rect.top;
		//修改窗口大小
		int nWideth = (BOUNDSIZE) * 3 + (GAME_WIDE )*SNAKESIZE + (ixWind - ixClient);
		int nHeight = (BOUNDSIZE*2) + GAME_HEIGHT*SNAKESIZE+ (iyWind - iyClient);
		MoveWindow(hwnd, 50, 50, nWideth, nHeight, TRUE);
		//初始化蛇身
		InitSnake();
		InitSnake2();
		//创建一个暂停按钮,宽100高50
		hPause = CreateWindowW(L"button", L"Pause", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BOUNDSIZE * 2 + GAME_WIDE*SNAKESIZE + 30, BOUNDSIZE + 20,
			100, 50, hwnd, (HMENU)PAUSEID, hInst, 0);
		//创建一个开始按钮,宽100高50
		hStart = CreateWindowW(L"button", L"Start", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BOUNDSIZE * 2 + GAME_WIDE*SNAKESIZE + 170, BOUNDSIZE + 20,
			100, 50, hwnd, (HMENU)STARTID, hInst, 0);
		//创建一个加速按钮,宽100高50
		hSpeedUp = CreateWindowW(L"button", L"SpeedUp", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BOUNDSIZE * 2 + GAME_WIDE*SNAKESIZE + 30, BOUNDSIZE + 90,
			100, 50, hwnd, (HMENU)SPEEDUPID, hInst, 0);
		//创建一个减速按钮,宽100高50
		hSpeedDown = CreateWindowW(L"button", L"SpeedDown", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BOUNDSIZE * 2 + GAME_WIDE*SNAKESIZE + 170, BOUNDSIZE + 90,
			100, 50, hwnd, (HMENU)SPEEDDOWNID, hInst, 0);

		//PlaySound((LPCTSTR)IDR_WAVE1, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		PlaySound(TEXT("Mass.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		//background = (HBITMAP)LoadImage(NULL, "bk.bmp", IMAGE_BITMAP, BOUNDSIZE + GAME_WIDE*SNAKESIZE, BOUNDSIZE + GAME_HEIGHT*SNAKESIZE, LR_LOADFROMFILE);
		memDC = CreateCompatibleDC(DC);
		ReleaseDC(hwnd,DC);
	}

	break;
	case WM_TIMER:

		switch (wParam)
		{
		case TIMERID_1:
		{   //移动蛇
			SnakeMove();
			if(choice == 2) SnakeMove2();
			//判断是否输了
			if (FALSE == bIsLoose)
			{
				KillTimer(hwnd, TIMERID_1);
				MessageBox(hwnd, "Player1 looooooooooooooose!", "", MB_OK);
				InitSnake();//初始化蛇
				state = 2;
				InitSnake2();
				state1 = 1;
				choice = 0;
				int nWideth = BOUNDSIZE * 3 + (GAME_WIDE)*SNAKESIZE + (ixWind - ixClient);
				int nHeight = BOUNDSIZE * 2 + GAME_HEIGHT*SNAKESIZE + (iyWind - iyClient);
				MoveWindow(hwnd, 50, 50, nWideth, nHeight, TRUE);
				bIsLoose = TRUE;
				SetWindowTextW(hStart, L"Start"); //如果输了就把ReStart变为Start
				bIsStart = FALSE;//重置开始
				bFlagStart = FALSE;
				started = 0;
			}
			if (FALSE == bIsLoose2)
			{
				KillTimer(hwnd, TIMERID_1);
				MessageBox(hwnd, "Player2 looooooooooooooose!", "", MB_OK);
				InitSnake();//初始化蛇
				state = 2;
				InitSnake2();
				state1 = 1;
				choice = 0;
				int nWideth = BOUNDSIZE * 3 + (GAME_WIDE)*SNAKESIZE + (ixWind - ixClient);
				int nHeight = BOUNDSIZE * 2 + GAME_HEIGHT*SNAKESIZE + (iyWind - iyClient);
				MoveWindow(hwnd, 50, 50, nWideth, nHeight, TRUE);
				bIsLoose2 = TRUE;
				SetWindowTextW(hStart, L"Start"); //如果输了就把ReStart变为Start
				bIsStart = FALSE;//重置开始
				bFlagStart = FALSE;
				started = 0;
			}
			if (TRUE == bIsWin)//判断是否赢了
			{
				KillTimer(hwnd, TIMERID_1);
				MessageBox(hwnd, "you Win!", "", MB_OK);
				InitSnake();//初始化蛇
				InitSnake2();
				bIsWin = FALSE;
			}
			//重新画蛇
			RECT rect = { 0 };
			SetRect(&rect, 0, 0, BOUNDSIZE + GAME_WIDE*SNAKESIZE,
				BOUNDSIZE + GAME_HEIGHT*SNAKESIZE);
			InvalidateRect(hwnd, &rect, TRUE);
		}
		break;
		default:
			break;
		}

		break;
	case WM_SETFOCUS:
		SetFocus(hwnd);
		break;
	case WM_KEYDOWN://控制方向

		if (FALSE == bIsLoose || FALSE==bIsLoose2 || TRUE == bIsPause)
			return 0;

		switch (wParam)
		{
		case VK_UP:
			state = 3;
			if (ptDirectHead.x != 0 && ptDirectHead.y != 1)
			{
				ptDirectHead.x = 0;
				ptDirectHead.y = -1;
			}
			break;
		case VK_DOWN:
			state = 4;
			if (ptDirectHead.x != 0 && ptDirectHead.y != -1)
			{
				ptDirectHead.x = 0;
				ptDirectHead.y = 1;
			}
			break;
		case VK_LEFT:
			state = 1;
			if (ptDirectHead.y != 0 && ptDirectHead.x != 1)
			{
				ptDirectHead.x = -1;
				ptDirectHead.y = 0;
			}
			break;
		case VK_RIGHT:
			state = 2;
			if (ptDirectHead.y != 0 && ptDirectHead.x != -1)
			{
				ptDirectHead.x = 1;
				ptDirectHead.y = 0;
			}
			break;
		case 87://W
			state1 = 3;
			if (choice == 2){
				if (ptDirectHead2.x != 0 && ptDirectHead2.y != 1)
				{
					ptDirectHead2.x = 0;
					ptDirectHead2.y = -1;

				}
				
			}
			break;
		case 83://S
			state1 = 4;
			if (choice == 2){
				if (ptDirectHead2.x != 0 && ptDirectHead2.y != -1)
				{
					ptDirectHead2.x = 0;
					ptDirectHead2.y = 1;

				}
			}

			break;
		case 65://A
			state1 = 1;
			if (choice == 2){
				if (ptDirectHead2.y != 0 && ptDirectHead2.x != 1)
				{
					ptDirectHead2.x = -1;
					ptDirectHead2.y = 0;

				}
			}

			break;
		case 68://D
			state1 = 2;
			if (choice == 2){
				if (ptDirectHead2.y != 0 && ptDirectHead2.x != -1)
				{
					ptDirectHead2.x = 1;
					ptDirectHead2.y = 0;

				}
			}

			break;
		default:
			break;
		}

		break;
	case WM_LBUTTONUP:
		x1 = LOWORD(lParam);	// 鼠标发生时的x坐标位置
		y1 = HIWORD(lParam);
		if (choice == 0) {
			if (x1>250 && x1<450 && y1>300 && y1<540) {

				if (y1 < 360) {
					choice = 1;
					SendMessage(hwnd, WM_COMMAND, STARTID, 0);
				}
				else if (y1 < 420) {
					choice = 2;
					SendMessage(hwnd, WM_COMMAND, STARTID, 0);
				}
				else if (y1 < 480) {
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTDLG),
						hwnd, AboutDlgProc);
				}
				else {
					choice = 4;
					KillTimer(hwnd, TIMERID_1);
					PostQuitMessage(0);
				}
			}
		}
		else {
		}
		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		hmenu = GetMenu(hwnd);
		// 分析菜单选择: 
		switch (wmId)
		{
		case ID_Speedup:
		case SPEEDUPID://速度加
			if (uiSnakeSpeed >= 10 && bIsStart == TRUE)
			{
				if (100 >= uiSnakeSpeed)
					uiSnakeSpeed -= 10;
				else
					uiSnakeSpeed -= 100;
				SetTimer(hwnd, TIMERID_1, uiSnakeSpeed, nullptr);//重新设置             
			}
			SendMessage(hwnd, WM_SETFOCUS, 0, 0);
			break;
		case ID_Speeddown:
		case SPEEDDOWNID://速度减
		{

			if (uiSnakeSpeed <= 1000 && bIsStart == TRUE)
			{
				if (100 > uiSnakeSpeed)
					uiSnakeSpeed += 10;
				else
					uiSnakeSpeed += 100;
				SetTimer(hwnd, TIMERID_1, uiSnakeSpeed, nullptr);//重新设置             
			}
			SendMessage(hwnd, WM_SETFOCUS, 0, 0);
		}
		break;
		case ID_Start:
		case STARTID://开始
		{
			if (FALSE == bIsStart && FALSE == bFlagStart)
			{
				started = 1;
				int nWideth = BOUNDSIZE * 3 + (GAME_WIDE + CTRL_WIDE)*SNAKESIZE + (ixWind - ixClient);
				int nHeight = BOUNDSIZE * 2 + GAME_HEIGHT*SNAKESIZE + (iyWind - iyClient);
				MoveWindow(hwnd, 50, 50, nWideth, nHeight, TRUE);
				SetTimer(hwnd, TIMERID_1, uiSnakeSpeed, nullptr);//设置定时器
				bIsStart = TRUE;//设置为已经开始
				bFlagStart = TRUE;//第一次开始后就设为TREU 表示不再进入这个函数
				SetWindowTextW(hStart, L"ReStart");
				SendMessage(hwnd, WM_SETFOCUS, 0, 0);//把输入焦点还给游戏区
			}
			else
			{
				if (TRUE == bIsPause)
				{//如果已经暂停了，按下重新开始要记得把暂停按钮恢复原样
					if (!SetWindowTextW(hPause, L"Pause"))
						dwError = GetLastError();
					bIsPause = FALSE;
				}
				InitSnake();//初始化，重新开始
				InitSnake2();
				SetTimer(hwnd, TIMERID_1, uiSnakeSpeed, nullptr);
				SendMessage(hwnd, WM_SETFOCUS, 0, 0);//把焦点还给游戏区
			}
		}
		break;
		case ID_Pause:
		case PAUSEID://暂停
			if (TRUE == bFlagStart)//游戏进行的时候才能暂停
			{
				if (FALSE == bIsPause)//如果没有暂停则将它暂停
				{
					KillTimer(hwnd, TIMERID_1);//关掉定时器就是暂停了
					bIsPause = TRUE;          //把状态设置为暂停
					if (!SetWindowText(hPause, "Go on"))//更改按钮标题
						dwError = GetLastError();

				}
				else
				{//按下继续按钮就重新创建定时器
					SetTimer(hwnd, TIMERID_1, uiSnakeSpeed, nullptr);
					bIsPause = FALSE;//把状态设置为没有被暂停
					if (!SetWindowText(hPause, "Pause"))//更改按钮标题
						dwError = GetLastError();
					SendMessage(hwnd, WM_SETFOCUS, 0, 0);//把焦点还给游戏区
				}
			}
			break;


		case ID_Rank:
			//showrank(hwnd);
			
			//hIdeaDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ABOUTDLG), hwnd, AboutDlgProc);
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTDLG),
				hwnd, AboutDlgProc);
			break;
		case ID_MUSICOFF:
			PlaySound(NULL, NULL, SND_FILENAME);
			break;
		case ID_MUSICON:
			PlaySound(TEXT("Mass.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			break;
		case WM_SETFOCUS:
			SetFocus(hwnd);
			break;
		case ID_About:
			MessageBox(hwnd, TEXT("作者:\n14121802\t霍宏斌\n14121811\t牟舣杨\n14121840\t徐际岚"), TEXT("关于"), MB_OK);
			break;
		case ID_Rules:
			MessageBox(hwnd, TEXT("单人模式:\n控制小蛇去吃到红色的食物，每吃到一个小蛇的长度加一\n若小蛇触碰到墙壁或者自身则游戏失败\n双人模式:\n游戏中左上角和右下角会分别生成一条蓝色和红色小蛇，每次场地内会刷新一个食物，基本规则和单人模式一致\n另外若小蛇的头部触碰到另一条蛇则前者失败"), TEXT("游戏规则"), MB_OK);
			break;
		case ID_Tips:
			MessageBox(hwnd, TEXT("单人模式:\n↑↓←→分别控制蛇的上下左右\n双人模式:\n↑↓←→分别控制蓝蛇的上下左右\nWSAD控制红蛇的上下左右"), TEXT("操作说明"), MB_OK);
			break;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC memDC,hdc = BeginPaint(hwnd, &ps);
		HDC backgroundhdc,backgroundhdc1, bmphdc, maskhdc;
		static HBRUSH hBrush1 = CreateSolidBrush(RGB(58, 206, 66));
		static HBRUSH hBrush2 = CreateSolidBrush(RGB(80, 87, 196));
		if (started == 1) {
			
			//画游戏区
			Rectangle(hdc, BOUNDSIZE, BOUNDSIZE, BOUNDSIZE + GAME_WIDE*SNAKESIZE,
				BOUNDSIZE + GAME_HEIGHT*SNAKESIZE);

			Rectangle(hdc, BOUNDSIZE * 2 + GAME_WIDE*SNAKESIZE, BOUNDSIZE,
				BOUNDSIZE * 2 + (GAME_WIDE + CTRL_WIDE)*SNAKESIZE, BOUNDSIZE + CTRL_HEIGHT*SNAKESIZE);
			//填充控制区颜色
			SetRect(&rect, BOUNDSIZE * 2 + GAME_WIDE*SNAKESIZE, BOUNDSIZE,
				BOUNDSIZE * 2 + (GAME_WIDE + CTRL_WIDE)*SNAKESIZE,
				BOUNDSIZE + CTRL_HEIGHT*SNAKESIZE);
			
			DC = GetDC(hwnd);
			memDC = CreateCompatibleDC(DC);

			background = (HBITMAP)LoadImage(NULL, "bk.bmp", IMAGE_BITMAP, BOUNDSIZE + GAME_WIDE*SNAKESIZE, BOUNDSIZE + GAME_HEIGHT*SNAKESIZE, LR_LOADFROMFILE);
			SelectObject(memDC, background);
			BitBlt(DC, BOUNDSIZE, BOUNDSIZE,  GAME_WIDE*SNAKESIZE, GAME_HEIGHT*SNAKESIZE, memDC, 0, 0, SRCCOPY);
			
			FillRect(hdc, &rect, hBrush2);
			//画蛇身
			DrawSnake(hdc, hwnd);
			if(choice==2) DrawSnake2(hdc, hwnd);
			//画食物
			DrawFood(hwnd);
			//显示分数
			ShowScore(hwnd);
			DeleteDC(memDC);
			ReleaseDC(hwnd, DC);
			EndPaint(hwnd, &ps);
		}
		else {
			background = (HBITMAP)LoadImage(NULL, "Clouds.bmp", IMAGE_BITMAP, ixWind, iyWind, LR_LOADFROMFILE);
			backgroundhdc = CreateCompatibleDC(hdc);
			SelectObject(backgroundhdc, background);


			//------------------- background  ------------------------------------


			bmp = (HBITMAP)LoadImage(NULL, "logo.bmp", IMAGE_BITMAP, 400, 200, LR_LOADFROMFILE);
			bmphdc = CreateCompatibleDC(hdc);
			SelectObject(bmphdc, bmp);

			mask = (HBITMAP)LoadImage(NULL, "logoo.bmp", IMAGE_BITMAP, 400, 200, LR_LOADFROMFILE);
			maskhdc = CreateCompatibleDC(hdc);
			SelectObject(maskhdc, mask);

			BitBlt(hdc, 0, 0, ixWind, iyWind, backgroundhdc, 0, 0, SRCCOPY);
			BitBlt(hdc, 150, 50, 550, 250, maskhdc, 0, 0, SRCPAINT);
			BitBlt(hdc, 150, 50, 550, 250, bmphdc, 0, 0, SRCAND);

			DeleteDC(backgroundhdc);
			DeleteDC(maskhdc);
			DeleteDC(bmphdc);

			//------------------- logo  ------------------------------------
			bmp = (HBITMAP)LoadImage(NULL, "danren.bmp", IMAGE_BITMAP, 200, 50, LR_LOADFROMFILE);
			bmphdc = CreateCompatibleDC(hdc);
			SelectObject(bmphdc, bmp);

			mask = (HBITMAP)LoadImage(NULL, "danrenBP.bmp", IMAGE_BITMAP, 200, 50, LR_LOADFROMFILE);
			maskhdc = CreateCompatibleDC(hdc);
			SelectObject(maskhdc, mask);

			BitBlt(hdc, 0, 0, ixWind, iyWind, backgroundhdc, 0, 0, SRCCOPY);
			BitBlt(hdc, 250, 300, 450, 350, maskhdc, 0, 0, SRCPAINT);
			BitBlt(hdc, 250, 300, 450, 350, bmphdc, 0, 0, SRCAND);

			DeleteDC(backgroundhdc);
			DeleteDC(maskhdc);
			DeleteDC(bmphdc);

			//------------------- 单人游戏  ------------------------------------
			bmp = (HBITMAP)LoadImage(NULL, "duoren.bmp", IMAGE_BITMAP, 200, 50, LR_LOADFROMFILE);
			bmphdc = CreateCompatibleDC(hdc);
			SelectObject(bmphdc, bmp);

			mask = (HBITMAP)LoadImage(NULL, "duorenBP.bmp", IMAGE_BITMAP, 200, 50, LR_LOADFROMFILE);
			maskhdc = CreateCompatibleDC(hdc);
			SelectObject(maskhdc, mask);

			BitBlt(hdc, 250, 360, 450, 410, maskhdc, 0, 0, SRCPAINT);
			BitBlt(hdc, 250, 360, 450, 410, bmphdc, 0, 0, SRCAND);

			DeleteDC(maskhdc);
			DeleteDC(bmphdc);
			//------------------- 多人游戏  ------------------------------------

			bmp = (HBITMAP)LoadImage(NULL, "xuanxiang.bmp", IMAGE_BITMAP, 200, 50, LR_LOADFROMFILE);
			bmphdc = CreateCompatibleDC(hdc);
			SelectObject(bmphdc, bmp);

			mask = (HBITMAP)LoadImage(NULL, "xuanxiangBP.bmp", IMAGE_BITMAP, 200, 50, LR_LOADFROMFILE);
			maskhdc = CreateCompatibleDC(hdc);
			SelectObject(maskhdc, mask);

			BitBlt(hdc, 250, 420, 450, 470, maskhdc, 0, 0, SRCPAINT);
			BitBlt(hdc, 250, 420, 450, 470, bmphdc, 0, 0, SRCAND);

			DeleteDC(maskhdc);
			DeleteDC(bmphdc);
			//------------------- 选项  ------------------------------------

			bmp = (HBITMAP)LoadImage(NULL, "tuichu.bmp", IMAGE_BITMAP, 200, 50, LR_LOADFROMFILE);
			bmphdc = CreateCompatibleDC(hdc);
			SelectObject(bmphdc, bmp);

			mask = (HBITMAP)LoadImage(NULL, "tuichuBP.bmp", IMAGE_BITMAP, 200, 50, LR_LOADFROMFILE);
			maskhdc = CreateCompatibleDC(hdc);
			SelectObject(maskhdc, mask);

			BitBlt(hdc, 250, 480, 450, 530, maskhdc, 0, 0, SRCPAINT);
			BitBlt(hdc, 250, 480, 450, 530, bmphdc, 0, 0, SRCAND);

			DeleteDC(maskhdc);
			DeleteDC(bmphdc);
			//------------------- 退出游戏  ------------------------------------
		}
	}
	break;
	case WM_DESTROY:
		KillTimer(hwnd, TIMERID_1);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

/*
BOOL  CALLBACK IdeaDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	HDC hdc = GetDC(hDlg);
	
	TextOut(hdc, 200, 200, buf[0], strlen(buf[0]) - 1);
	switch (LOWORD(wParam))
	{
	case IDOK:

		break;
	
	case IDCANCEL:

		break; 
	}
	return FALSE;
}
*/




BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){

	HDC hdc = GetDC(hDlg);

	int i = 0, col = 110;
	TCHAR S[1000] = { 0 };
	int k = 0;
	switch (message){
		case WM_PAINT:

			break;
		case WM_COMMAND:
			switch (LOWORD(wParam)){
				case IDC_SHOW:
		
					file = fopen("rank.txt", "r");
					for (int i = 0; i < 5; i++){
						fgets(buf[i], 50, file);
						TextOut(hdc, 150, col, buf[i], strlen(buf[i]) - 1);
						col += 20;
						/*for (int j = 0; j<strlen(buf[i]); j++)
						S[k++] = buf[i][j];
						S[k++] = '\n';*/
					}
					fclose(file);
					//EndDialog(hDlg, FALSE);
					return TRUE;
				case IDOK:
					EndDialog(hDlg, TRUE);
					return TRUE;
				case IDCANCEL:	
					EndDialog(hDlg, TRUE);
					return TRUE;
			}


	}


	

	return FALSE;

}