// Paint.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "Paint.h"
#include "MySource.h"
#include <windowsx.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HDC memDC;										// 메모리 DC(더블 버퍼링을 위한 가상 그림 도구)
HBITMAP memBitmap;								// 메모리 비트맵 (그림을 그릴 실제 종이)
POINT stPos;									// 그리기 시작점 좌표

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


/* WinMain 함수 부분 */

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT));

	MSG msg;

	// 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = InitMainWindowSet(hInstance, &WndProc, L"Paint");

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	// 윈도우 생성 메세지
	case WM_CREATE:
	{
		// 버튼 생성
		CreateButton(L"Pen", 20, 20, 50, 50, (HMENU)1, hWnd, hInst);
		CreateButton(L"Erase", 20, 75, 50, 50, (HMENU)2, hWnd, hInst);
		CreateButtonCustom(L"Hi", 20, 130, 50, 30, (HMENU)3, hWnd, hInst);

		// 버튼 생성 및 이미지 씌우기
		CreateButtonImg(L"Pen", IDI_ICON1, hWnd, hInst);
		CreateButtonImg(L"Erase", IDI_ICON2, hWnd, hInst);

		// 색상 테이블 생성
		CreateRGBTable(L"RGBtable", 80, 30, 150, 120, (HMENU)10, hWnd, hInst);
		
		// 더블 버퍼링을 위한 메모리 세팅
		CreateBackPage(hWnd, hInst, &memDC, &memBitmap);

		break;
	}
	// 각종 버튼에 따른 동작
	case WM_COMMAND:
	{
		int tmp = HIWORD(wParam);
		switch (tmp)
		{
			case BN_CLICKED: // 버튼 클릭
				if (LOWORD(wParam) == 3) { // Hi 버튼 클릭
					DrawGreetingText(hWnd, memDC);
					InvalidateRect(hWnd, NULL, FALSE);
				}
				else {
					SetFunction(wParam, lParam, hWnd);
				}
				break;
		default:
			break;
		}

		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	// 스크롤 기능
	case WM_HSCROLL:
	{
		SetScrollFunction(wParam, lParam);
		InvalidateRect(hWnd, NULL, FALSE);
		UpdateWindow(hWnd);
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (wParam != MK_LBUTTON) break; 
		/* 그리기, 지우기 */
		// memDC에 그리기, 지우기 작업을 수행한 후 윈도우의 DC에 BitBlt로 복사
		if (GetFunction(wParam, lParam, hWnd) == 1) { // Pen
			stPos = Draw(hWnd, memDC, wParam, lParam, stPos);
			HDC hdc = GetDC(hWnd);
			RECT rect;
			GetClientRect(hWnd, &rect);
			BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY); // Bit Block Transfer
			ReleaseDC(hWnd, hdc);
		}
		else if (GetFunction(wParam, lParam, hWnd) == 2) { // Erase
			stPos = Erase(hWnd, memDC, wParam, lParam, stPos);
			HDC hdc = GetDC(hWnd);
			RECT rect;
			GetClientRect(hWnd, &rect);
			BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
			ReleaseDC(hWnd, hdc);
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
		stPos.x = GET_X_LPARAM(lParam);
		stPos.y = GET_Y_LPARAM(lParam);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SetColor(hWnd, memDC, memBitmap);
		RECT rect;
		GetClientRect(hWnd, &rect);
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		DeleteObject(memBitmap);
		DeleteDC(memDC);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
