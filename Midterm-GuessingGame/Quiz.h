#pragma once
#include "Midterm-GuessingGame.h"

using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

class Quiz
{
public:
	int ID;
	WCHAR quiz[MAX_LOADSTRING];
	bool correactAns;
	WCHAR img1[MAX_LOADSTRING];
	WCHAR img2[MAX_LOADSTRING];
public:
	Quiz() {};
	Quiz(int i, HINSTANCE hInst)
	{
		ID = i;
		;
		switch (i)
		{
		case 1: LoadStringW(hInst, IDS_QUIZ1, quiz, MAX_LOADSTRING); correactAns = 0;
			wcscpy_s(img1, L"Manchester United.png"); wcscpy_s(img2, L"Liverpool.png");
			break;
		case 2: LoadStringW(hInst, IDS_QUIZ2, quiz, MAX_LOADSTRING); correactAns = 1;
			wcscpy_s(img1, L"Arsenal.png"); wcscpy_s(img2, L"Manchester United.png");
			break;
		case 3: LoadStringW(hInst, IDS_QUIZ3, quiz, MAX_LOADSTRING); correactAns = 0;
			wcscpy_s(img1, L"Chelsea.png"); wcscpy_s(img2, L"Arsenal.png");
			break;
		case 4: LoadStringW(hInst, IDS_QUIZ4, quiz, MAX_LOADSTRING); correactAns = 1;
			wcscpy_s(img1, L"Southampton.png"); wcscpy_s(img2, L"Everton.png");
			break;
		case 5: LoadStringW(hInst, IDS_QUIZ5, quiz, MAX_LOADSTRING); correactAns = 0;
			wcscpy_s(img1, L"Real Madrid.png"); wcscpy_s(img2, L"AC Milan.png");
			break;
		case 6: LoadStringW(hInst, IDS_QUIZ6, quiz, MAX_LOADSTRING); correactAns = 1;
			wcscpy_s(img1, L"Arsenal.png"); wcscpy_s(img2, L"Liverpool.png");
			break;
		case 7: LoadStringW(hInst, IDS_QUIZ7, quiz, MAX_LOADSTRING); correactAns = 1;
			wcscpy_s(img1, L"Manchester City.png"); wcscpy_s(img2, L"Barcelona.png");
			break;
		case 8: LoadStringW(hInst, IDS_QUIZ8, quiz, MAX_LOADSTRING); correactAns = 0;
			wcscpy_s(img1, L"Manchester United.png"); wcscpy_s(img2, L"Manchester City.png");
			break;
		case 9: LoadStringW(hInst, IDS_QUIZ9, quiz, MAX_LOADSTRING); correactAns = 0;
			wcscpy_s(img1, L"Arsenal.png"); wcscpy_s(img2, L"Chelsea.png");
			break;
		default:LoadStringW(hInst, IDS_QUIZ10, quiz, MAX_LOADSTRING); correactAns = 1;
			wcscpy_s(img1, L"Manchester United.png"); wcscpy_s(img2, L"Liverpool.png");
			break;
		}
	};
};