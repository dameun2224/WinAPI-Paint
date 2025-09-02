#include "MySource.h"


/* ������ â ���� */
HWND InitMainWindowSet(HINSTANCE hInstance, WNDPROC WndProc, const WCHAR* name) 
{
	// ������ â ����ü ���� �� �����ϱ�
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); // ����ü ũ��
	wcex.style = CS_HREDRAW | CS_VREDRAW; // ������ â ��Ÿ��, ����/���� ũ�� ����� �ٽ� �׸���
	wcex.lpfnWndProc = WndProc; // ������ ���ν��� �Լ��� ������ ����, �� â Ŭ�������� �߻��ϴ� ��� �޽����� WndProc�̶�� �Լ��� �������� ó����
	wcex.cbClsExtra = 0; // Ŭ���� ����ü�� �߰��� Ȯ���� ����Ʈ ��
	wcex.cbWndExtra = 0; // ������ �ν��Ͻ��� �߰��� Ȯ���� ����Ʈ ��
	wcex.hInstance = hInstance; // �ν��Ͻ� �ڵ�
	wcex.hIcon = NULL; // ������, �⺻��
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // Ŀ��, �⺻��
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ��� �귯��(����), �⺻��
	wcex.lpszMenuName = NULL; // �޴� �̸�, ����
	wcex.lpszClassName = name; // ������ Ŭ���� �̸�
	wcex.hIconSm = NULL; // ���� ������, �⺻��
	RegisterClassExW(&wcex);

	// �ش� ������ â�� ������ͼ� ������ â �����ϱ�
	return CreateWindowW(name, name, WS_MAXIMIZE|WS_SYSMENU, 100, 100, 750, 750, nullptr, nullptr, hInstance, nullptr);
}

/* ��ư �����ϱ� */
void CreateButton(const WCHAR* name, LONG x, LONG y, LONG width, LONG height, HMENU id, HWND hWnd, HINSTANCE hInst) 
{
	CreateWindowW(L"button", name, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, x, y, width, height, hWnd, id, hInst, NULL);
}

/* ���� ���� ���� ����� */
void CreateRGBTable(const WCHAR* name, LONG left, LONG top, LONG right, LONG bottom, HMENU id, HWND hWnd, HINSTANCE hInst)
{
	// RGB�� ��ũ�� �� ���� �� ���� ����
	CreateWindowW(L"scrollbar", L"R", WS_CHILD | WS_VISIBLE | SBS_HORZ, right + 20, top + 15, right + 30, 15, hWnd, id, hInst, NULL);
	SetScrollRange(FindWindowW(L"scrollbar", L"R"), SB_CTL, 0, 255, TRUE);
	CreateWindowW(L"scrollbar", L"G", WS_CHILD | WS_VISIBLE | SBS_HORZ, right + 20, top + 45, right + 30, 15, hWnd, id + 1, hInst, NULL);
	SetScrollRange(FindWindowW(L"scrollbar", L"G"), SB_CTL, 0, 255, TRUE);
	CreateWindowW(L"scrollbar", L"B", WS_CHILD | WS_VISIBLE | SBS_HORZ, right + 20, top + 75, right + 30, 15, hWnd, id + 2, hInst, NULL);
	SetScrollRange(FindWindowW(L"scrollbar", L"B"), SB_CTL, 0, 255, TRUE);
	//SetColor(hWnd);
}

/* ���� ���� */
void SetColor(HWND hWnd)
{
	// ��ġ ���ؽ�Ʈ �ڵ�(Handle to a Device Context)
	HDC hdc = GetDC(hWnd);

	// ��ũ�� Bar�� �� �޾ƿ���
	int R = GetScrollPos(FindWindowW(L"scrollbar", L"R"), SB_HORZ);
	int G = GetScrollPos(FindWindowW(L"scrollbar", L"G"), SB_HORZ);
	int B = GetScrollPos(FindWindowW(L"scrollbar", L"B"), SB_HORZ);

	HBRUSH newBrush = CreateSolidBrush(RGB(R, G, B));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, newBrush);
	// ���õ� ���� �����ֱ�
	Rectangle(hdc, 80, 30, 150, 120);

	// ��ũ�� Bar�� �� ǥ�����ֱ�
	WCHAR text[10];
	wsprintf(text, L"R : %d", R, SB_HORZ);
	TextOutW(hdc, 360, 40, text, lstrlenW(text));
	wsprintf(text, L"G : %d", G, SB_HORZ);
	TextOutW(hdc, 360, 70, text, lstrlenW(text));
	wsprintf(text, L"B : %d", B, SB_HORZ);
	TextOutW(hdc, 360, 100, text, lstrlenW(text));
	SelectObject(hdc, OldBrush);
	DeleteObject(newBrush);
	ReleaseDC(hWnd, hdc);
}