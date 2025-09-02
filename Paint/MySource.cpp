#include "MySource.h"

/* 윈도우 창 설정 */
HWND InitMainWindowSet(HINSTANCE hInstance, WNDPROC WndProc, const WCHAR* name) {

	// 윈도우 창 구조체 설정 및 적용하기
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = name;
	wcex.hIconSm = NULL;
	RegisterClassExW(&wcex);

	// 해당 윈도우 창을 가지고와서 윈도우 창 생성하기
	return CreateWindowW(name, name, WS_MAXIMIZE|WS_SYSMENU, 100, 100, 750, 750, nullptr, nullptr, hInstance, nullptr);
}