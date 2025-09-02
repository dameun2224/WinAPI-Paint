#include "MySource.h"


/* 윈도우 창 설정 */
HWND InitMainWindowSet(HINSTANCE hInstance, WNDPROC WndProc, const WCHAR* name)
{
	// 윈도우 창 구조체 설정 및 적용하기
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); // 구조체 크기
	wcex.style = CS_HREDRAW | CS_VREDRAW; // 윈도우 창 스타일, 가로/세로 크기 변경시 다시 그리기
	wcex.lpfnWndProc = WndProc; // 윈도우 프로시저 함수의 포인터 지정, 이 창 클래스에서 발생하는 모든 메시지가 WndProc이라는 함수로 보내져서 처리됨
	wcex.cbClsExtra = 0; // 클래스 구조체에 추가로 확보할 바이트 수
	wcex.cbWndExtra = 0; // 윈도우 인스턴스당 추가로 확보할 바이트 수
	wcex.hInstance = hInstance; // 인스턴스 핸들
	wcex.hIcon = NULL; // 아이콘, 기본값
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // 커서, 기본값
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 배경 브러쉬(배경색), 기본값
	wcex.lpszMenuName = NULL; // 메뉴 이름, 없음
	wcex.lpszClassName = name; // 윈도우 클래스 이름
	wcex.hIconSm = NULL; // 작은 아이콘, 기본값
	RegisterClassExW(&wcex);

	// 해당 윈도우 창을 가지고와서 윈도우 창 생성하기
	return CreateWindowW(name, name, WS_MAXIMIZE | WS_SYSMENU, 100, 100, 750, 750, nullptr, nullptr, hInstance, nullptr);
}

/* 버튼 생성하기 */
void CreateButton(const WCHAR* name, LONG x, LONG y, LONG width, LONG height, HMENU id, HWND hWnd, HINSTANCE hInst)
{
	CreateWindowW(L"button", name, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, x, y, width, height, hWnd, id, hInst, NULL);
}

/* 그리기, 지우기 토글 값 세팅 */
// wParam(32Bit) : 컨트롤 ID + 알림 코드
// lParam(32Bit) : 컨트롤 핸들 (고유한 값, 메시지를 보낸 컨트롤의 핸들)
void SetFunction(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	// HIWORD: 앞의 16Bit, LOWORD: 뒤의 16Bit
	if (HIWORD(wParam) == BN_CLICKED) // 버튼이 클릭되었을 때
	{
		switch (LOWORD(wParam))
		{
		// 펜 버튼 (id: 1)
		case 1:
		{
			// 펜이 체크되지 않은 상태에서 클릭: 펜 체크, 지우개 언체크
			if(SendMessageW((HWND)lParam, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessageW((HWND)lParam, BM_SETCHECK, BST_CHECKED, 0);
				SendMessageW(FindWindowEx(hWnd, NULL, L"button", L"Erase"), BM_SETCHECK, BST_UNCHECKED, 0);
				return;
			}
			// 펜이 체크된 상태에서 클릭: 펜 언체크
			else {
				SendMessageW((HWND)lParam, BM_SETCHECK, BST_UNCHECKED, 0);
			}
		}
		// 지우개 버튼 (id: 2)
		case 2:
		{
			// 지우개가 체크되지 않은 상태에서 클릭: 지우개 체크, 펜 언체크
			if (SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessageW((HWND)lParam, BM_SETCHECK, BST_CHECKED, 0);
				SendMessageW(FindWindowEx(hWnd, NULL, L"button", L"Pen"), BM_SETCHECK, BST_UNCHECKED, 0);
				return;
			}
			// 지우개가 체크된 상태에서 클릭: 지우개 언체크
			else {
				SendMessageW((HWND)lParam, BM_SETCHECK, BST_UNCHECKED, 0);
			}
		}
		} // 스위치문 종료
	}
}

/* 토글 값 받아오기 */
int GetFunction(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	// 1: 펜, 2: 지우개, 0: 아무것도 선택 안됨
	if(SendMessageW(FindWindowExW(hWnd, NULL, L"button", L"Pen"), BM_GETCHECK, 0, 0) == BST_CHECKED) return 1;
	if (SendMessageW(FindWindowExW(hWnd, NULL, L"button", L"Erase"), BM_GETCHECK, 0, 0) == BST_CHECKED) return 2; 
	else return 0;
}

/* 색상 선택 도구 만들기 */
void CreateRGBTable(const WCHAR* name, LONG left, LONG top, LONG right, LONG bottom, HMENU id, HWND hWnd, HINSTANCE hInst)
{
	// RGB의 스크롤 바 생성 및 범위 설정
	CreateWindowW(L"scrollbar", L"R", WS_CHILD | WS_VISIBLE | SBS_HORZ, right + 20, top + 15, right + 30, 15, hWnd, id, hInst, NULL);
	SetScrollRange(FindWindowExW(hWnd, NULL, L"scrollbar", L"R"), SB_CTL, 0, 255, TRUE);
	CreateWindowW(L"scrollbar", L"G", WS_CHILD | WS_VISIBLE | SBS_HORZ, right + 20, top + 45, right + 30, 15, hWnd, id + 1, hInst, NULL);
	SetScrollRange(FindWindowExW(hWnd, NULL, L"scrollbar", L"G"), SB_CTL, 0, 255, TRUE);
	CreateWindowW(L"scrollbar", L"B", WS_CHILD | WS_VISIBLE | SBS_HORZ, right + 20, top + 75, right + 30, 15, hWnd, id + 2, hInst, NULL);
	SetScrollRange(FindWindowExW(hWnd, NULL, L"scrollbar", L"B"), SB_CTL, 0, 255, TRUE);
	//SetColor(hWnd);
}

/* 색상 선택 */
void SetColor(HWND hWnd)
{
	// 장치 컨텍스트 핸들(Handle to a Device Context)
	HDC hdc = GetDC(hWnd);

	// 스크롤 Bar의 값 받아오기
	int R = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"R"), SB_CTL);
	int G = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"G"), SB_CTL);
	int B = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"B"), SB_CTL);

	HBRUSH newBrush = CreateSolidBrush(RGB(R, G, B));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, newBrush);
	// 선택된 색상 보여주기
	Rectangle(hdc, 80, 30, 150, 120);

	// 스크롤 Bar의 값 표시해주기
	WCHAR text[10];
	wsprintf(text, L"R : %d", R);
	TextOutW(hdc, 360, 40, text, lstrlenW(text));
	wsprintf(text, L"G : %d", G);
	TextOutW(hdc, 360, 70, text, lstrlenW(text));
	wsprintf(text, L"B : %d", B);
	TextOutW(hdc, 360, 100, text, lstrlenW(text));
	SelectObject(hdc, OldBrush);
	DeleteObject(newBrush);
	ReleaseDC(hWnd, hdc);
}

// 이미지 씌우기
// 더블버퍼링
// 색상선택
// 버튼 제어
// 등등 기능을 쪼개서 하나씩 추가할 예정