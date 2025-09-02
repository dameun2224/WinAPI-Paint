#include "MySource.h"

HWND InitMainWindowSet(HINSTANCE hInstance, WNDPROC WndProc, const WCHAR* name) {

	// ������ â ���� �� �����ϱ�
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

	return CreateWindowW(name, name, WS_MAXIMIZE|WS_SYSMENU, 100, 100, 750, 750, nullptr, nullptr, hInstance, nullptr);
}