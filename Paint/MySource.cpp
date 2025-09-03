#include "MySource.h"
#include <windowsx.h>


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
void SetFunction(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	// wParam(32Bit) : 컨트롤 ID + 알림 코드
	// lParam(32Bit) : 컨트롤 핸들 (고유한 값, 메시지를 보낸 컨트롤의 핸들)

	// HIWORD: 상위 16Bit, LOWORD: 하위 16Bit
	if (HIWORD(wParam) == BN_CLICKED) // 버튼이 클릭되었을 때
	{
		switch (LOWORD(wParam))
		{
		case 1: // 펜 버튼 (id: 1)
		{
			// 펜이 체크되지 않은 상태에서 클릭: 펜 체크, 지우개 언체크
			if(SendMessageW((HWND)lParam, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessageW((HWND)lParam, BM_SETCHECK, BST_CHECKED, 0);
				SendMessageW(FindWindowEx(hWnd, NULL, L"button", L"Erase"), BM_SETCHECK, BST_UNCHECKED, 0);
			}
			// 펜이 체크된 상태에서 클릭: 펜 언체크
			else {
				SendMessageW((HWND)lParam, BM_SETCHECK, BST_UNCHECKED, 0);
			}
		}
		break;
		case 2: // 지우개 버튼 (id: 2)
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
		break;
		} // 스위치문 종료
	}
	return;
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
void SetColor(HWND hWnd, HDC memDC, HBITMAP memBitmap)
{
	// 스크롤 Bar의 값 받아오기
	int R = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"R"), SB_CTL);
	int G = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"G"), SB_CTL);
	int B = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"B"), SB_CTL);

	HBRUSH newBrush = CreateSolidBrush(RGB(R, G, B));
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, newBrush);

	// 선택된 색상 보여주기
	Rectangle(memDC, 80, 30, 150, 120);

	// 스크롤 Bar의 값 표시해주기
	WCHAR text[10];
	wsprintf(text, L"R : %d", R);
	TextOutW(memDC, 360, 40, text, lstrlenW(text));
	wsprintf(text, L"G : %d", G);
	TextOutW(memDC, 360, 70, text, lstrlenW(text));
	wsprintf(text, L"B : %d", B);
	TextOutW(memDC, 360, 100, text, lstrlenW(text));

	SelectObject(memDC, OldBrush);
	DeleteObject(newBrush);
}

/* 스크롤 동작 */
void SetScrollFunction(WPARAM wParam, LPARAM lParam) 
{
	// WPARAM : 스크롤바의 동작 코드(LOWORD) + 스크롤바가 움직인 새로운 위치(HIWORD)

	switch (LOWORD(wParam))
	{
	case SB_LINELEFT: // 왼쪽 화살표 클릭: 스크롤바 값을 1만큼 감소
		SetScrollPos((HWND)lParam, SB_CTL, max(0, GetScrollPos((HWND)lParam, SB_CTL) - 1), TRUE);
		break;
	case SB_PAGELEFT: // 왼쪽 영역 클릭: 스크롤바 값을 5만큼 감소
		SetScrollPos((HWND)lParam, SB_CTL, max(0, GetScrollPos((HWND)lParam, SB_CTL) - 5), TRUE);
		break;
	case SB_LINERIGHT: // 오른쪽 화살표 클릭: 스크롤바 값을 1만큼 증가
		SetScrollPos((HWND)lParam, SB_CTL, min(255, GetScrollPos((HWND)lParam, SB_CTL) + 1), TRUE);
		break;
	case SB_PAGERIGHT: // 오른쪽 영역 클릭: 스크롤바 값을 5만큼 증가
		SetScrollPos((HWND)lParam, SB_CTL, min(255, GetScrollPos((HWND)lParam, SB_CTL) + 5), TRUE);
		break;
	case SB_THUMBTRACK: // 스크롤바 막대 드래그: 드래그한 위치로 값을 설정
		SetScrollPos((HWND)lParam, SB_CTL, HIWORD(wParam), TRUE);
		break;
	}
}

/* 메모리 DC 및 비트맵에 메모리 할당하기 */ 
void CreateBackPage(HWND hWnd, HINSTANCE hInst, HDC* memDC, HBITMAP* memBitmap) 
{
	// 윈도우의 DC 가져와 화면과 호환되는 메모리 DC 생성
	// DC: 도구 상자. 붓, 펜, 브러시, 색상, 글꼴 등 모든 그리기 도구 정보를 담고 있음
	HDC hdc = GetDC(hWnd);
	*memDC = CreateCompatibleDC(hdc);

	// 사각형 좌표 구조체 생성 및 클라이언트 영역 크기 받아오기
	RECT rect;
	GetClientRect(hWnd, &rect);

	// 빈 비트맵 생성 및 메모리 DC에 비트맵 연결
	// Bitmap: 그림이 그려지는 실제 이미지 데이터
	*memBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	(HBITMAP)SelectObject(*memDC, *memBitmap);

	// 메모리 DC의 배경 흰색으로 채우기
	FillRect(*memDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	// 윈도우 DC 반환 (DC는 시스템 자원이므로 반드시 반환해야 함)
	ReleaseDC(hWnd, hdc);
}

/* 그리기 */
POINT Draw(HWND hWnd, HDC hdc, WPARAM wParam, LPARAM lParam, POINT stPos) 
{
	// 마우스 커서가 1픽셀이라도 움직이면 초당 수십, 수백 번씩 호출됨
	// 매 그리기 작업마다 펜을 새로 생성하고 삭제함

	// 스크롤 Bar의 값 받아오기
	int R = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"R"), SB_CTL);
	int G = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"G"), SB_CTL);
	int B = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"B"), SB_CTL);

	HPEN newPen = CreatePen(PS_SOLID, 10, RGB(R, G, B)); // 스타일: PS_SOLID(실선), 굵기: 10, 색상: RGB(R, G, B)
	HPEN oldPen = (HPEN)SelectObject(hdc, newPen); // newPen의 핸들 저장

	POINT pos;
	pos.x = GET_X_LPARAM(lParam);
	pos.y = GET_Y_LPARAM(lParam);

	// 아주 짧은 시간동안 move와 line이 연달아 실행되면서 연속된 선분을 그림
	MoveToEx(hdc, stPos.x, stPos.y, NULL); // 펜의 위치를 마우스(pos) 위치로 이동
	LineTo(hdc, pos.x, pos.y); // 펜의 위치에서 마우스(pos) 위치까지 선 그리기

	SelectObject(hdc, oldPen); 
	DeleteObject(newPen);

	stPos.x = pos.x;
	stPos.y = pos.y;

	return stPos; // 다음 그리기 시작점 좌표 반환
}

/* 지우기 */
POINT Erase(HWND hWnd, HDC hdc, WPARAM wParam, LPARAM lParam, POINT stPos) 
{
	HPEN newPen = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(hdc, newPen);

	POINT pos;
	pos.x = GET_X_LPARAM(lParam);
	pos.y = GET_Y_LPARAM(lParam);

	MoveToEx(hdc, stPos.x, stPos.y, NULL);
	LineTo(hdc, pos.x, pos.y);

	SelectObject(hdc, oldPen);
	DeleteObject(newPen);

	stPos.x = pos.x;
	stPos.y = pos.y;
	return stPos;
}

// 이미지 씌우기
// 더블버퍼링
// 색상선택
// 버튼 제어
// 등등 기능을 쪼개서 하나씩 추가할 예정