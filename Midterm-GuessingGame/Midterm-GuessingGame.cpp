// Midterm-GuessingGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Midterm-GuessingGame.h"
#include <windowsx.h>
#include <objidl.h>
#include <gdiplus.h>
#include "Quiz.h"
#include <algorithm>
#include <time.h>

using namespace std;
using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")
#pragma comment(linker, \
    "\"/manifestdependency:type='Win32' "\
    "name='Microsoft.Windows.Common-Controls' "\
    "version='6.0.0.0' "\
    "processorArchitecture='*' "\
    "publicKeyToken='6595b64144ccf1df' "\
    "language='*'\"")


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
int countQuizes = 0;
int score = 0;
HWND lblShowScore;
HWND lblQuiz;
HWND btnChoose1;
HWND btnChoose2;
HWND lblScore;
HWND lblNotify;
HWND lblFinalScore;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL				OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void				OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void				OnPaint(HWND hwnd);
void				OnDestroy(HWND hwnd);
LRESULT				OnCtlColorStatic(HDC hdc, HWND hCtl);
void				CreateQuizes(Quiz quiz[], int size);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MIDTERMGUESSINGGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MIDTERMGUESSINGGAME));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MIDTERMGUESSINGGAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MIDTERMGUESSINGGAME);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	ULONG_PTR token;
	GdiplusStartupInput input = { 0 };
	input.GdiplusVersion = 1;
	GdiplusStartup(&token, &input, NULL);

	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 584, 450, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
Quiz quiz[10];
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	

	LRESULT  r;
	switch (message)
	{
	case WM_CTLCOLORSTATIC:
		if (r = OnCtlColorStatic((HDC)wParam, (HWND)lParam)) return r;
		break;
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
	
}

void CreateQuizes(Quiz quiz[], int size)
{
	int size_of_permutetation = 1;
	for (int i = 1; i <= size; i++)
	{
		size_of_permutetation *= i;
	}

	srand(time(NULL));
	int a = rand() % size_of_permutetation;
	//int a = 1;
	int pos = 0;
	int myints[] = { 1,2,3,4,5,6,7,8,9,10 };

	while (1)
	{
		if (pos == a) {
			std::next_permutation(myints, myints + 10); 
			break;
		}
		std::next_permutation(myints, myints + 10);
		pos++;
	}

	for (int i = 0; i < size; i++)
	{
		quiz[i] =  Quiz(myints[i], hInst);
	}
}


BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	CreateQuizes(quiz, 10);
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 29;
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, L"Roboto Condensed");

	lblShowScore = CreateWindowEx(0, L"STATIC", L"0",
		WS_CHILD | WS_VISIBLE, 450, 45, 498, 43, hwnd,
		(HMENU)IDC_SHOWSCORE, lpCreateStruct->hInstance, NULL);
	SetWindowFont(lblShowScore, hFont, TRUE);

	lf.lfHeight = 20.5;
	hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, L"Roboto Condensed");

	lblScore = CreateWindowEx(0, L"STATIC", L"Điểm:",
		WS_CHILD | WS_VISIBLE, 394, 50, 50, 43, hwnd,
		(HMENU)IDC_SCORE, lpCreateStruct->hInstance, NULL);
	SetWindowFont(lblScore, hFont, TRUE);

	
	lblQuiz = CreateWindowEx(0, L"STATIC", quiz[countQuizes].quiz ,
		WS_CHILD | WS_VISIBLE , 43, 121, 498, 43, hwnd,
		(HMENU)IDC_QUIZ, lpCreateStruct->hInstance, NULL);
	SetWindowFont(lblQuiz, hFont, TRUE);
	
	btnChoose1 = CreateWindowEx(NULL, L"BUTTON", L"Chọn",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 90, 300, 80, 25, hwnd,
		(HMENU)IDC_BTNCHOOSE1, lpCreateStruct->hInstance, NULL);
	SetWindowFont(btnChoose1, hFont, TRUE);

	btnChoose2 = CreateWindowEx(NULL, L"BUTTON", L"Chọn",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 394, 300, 80, 25, hwnd,
		(HMENU)IDC_BTNCHOOSE2, lpCreateStruct->hInstance, NULL);
	SetWindowFont(btnChoose2, hFont, TRUE);


	lblNotify = CreateWindowEx(0, L"STATIC", L"ĐIỂM CỦA BẠN LÀ",
		WS_CHILD, 220, 121, 498, 43, hwnd,
		(HMENU)IDC_QUIZ, lpCreateStruct->hInstance, NULL);
	SetWindowFont(lblNotify, hFont, TRUE);

	
	hFont = CreateFont(50, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, L"Roboto Condensed");

	lblFinalScore = CreateWindowEx(0, L"STATIC", L"0",
		WS_CHILD, 230, 200, 100, 43, hwnd,
		(HMENU)IDC_QUIZ, lpCreateStruct->hInstance, NULL);
	SetWindowFont(lblFinalScore, hFont, TRUE);

	return TRUE;
}
/*https://www.codeproject.com/Questions/256167/Set-static-background-color-in-cplusplus*/
HWND      texthwnd = 0;
COLORREF  textcol = RGB(0, 0, 0);
LRESULT OnCtlColorStatic(HDC hdc, HWND hCtl)
{
	if (hCtl == texthwnd)
	{
		SetTextColor(hdc, textcol);
		return (LRESULT)GetStockObject(HOLLOW_BRUSH);
	}
	return 0;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id) {
	case IDC_BTNCHOOSE1:
		if (quiz[countQuizes].correactAns == 0)
			score++;
		break;
	case IDC_BTNCHOOSE2:
		if (quiz[countQuizes].correactAns == 1)
			score++;
		break;
	}

	WCHAR buffer[3];
	wsprintf(buffer, L"%d", score);
	SetWindowText(lblShowScore, buffer);

	countQuizes++;
	SetWindowText(lblQuiz, quiz[countQuizes].quiz);

	OnPaint(hwnd);
	InvalidateRect(hwnd, NULL, true);

	if (countQuizes > 9)
	{
		ShowWindow(lblScore, SW_HIDE);
		ShowWindow(lblQuiz, SW_HIDE);
		ShowWindow(lblShowScore, SW_HIDE);
		ShowWindow(btnChoose1, SW_HIDE);
		ShowWindow(btnChoose2, SW_HIDE);

		ShowWindow(lblNotify, SW_SHOW);
		WCHAR buffer[6];
		wsprintf(buffer, L"%d", score);
		wcscat_s(buffer, L"/10");
		SetWindowText(lblFinalScore, buffer);
		ShowWindow(lblFinalScore, SW_SHOW);
		//DestroyWindow(hwnd);
	}
}

void OnPaint(HWND hwnd)
{
	ULONG_PTR gdiplusToken;
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	{/* Scope to ensure Graphics and Image are destructed before GdiplusShutdown */

		Graphics graphics(hdc);
		Image image(quiz[countQuizes].img1);
		graphics.DrawImage(&image, 90, 180);
	}

	{/* Scope to ensure Graphics and Image are destructed before GdiplusShutdown */

		Graphics graphics(hdc);
		Image image(quiz[countQuizes].img2);
		graphics.DrawImage(&image, 394, 180);
	}

	GdiplusShutdown(gdiplusToken);

	EndPaint(hwnd, &ps);
	return;
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
	return;
}
