#include "MySource.h"
#include <windowsx.h>


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
	return CreateWindowW(name, name, WS_MAXIMIZE | WS_SYSMENU, 100, 100, 750, 750, nullptr, nullptr, hInstance, nullptr);
}

/* ��ư �����ϱ� */
void CreateButton(const WCHAR* name, LONG x, LONG y, LONG width, LONG height, HMENU id, HWND hWnd, HINSTANCE hInst)
{
	CreateWindowW(L"button", name, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, x, y, width, height, hWnd, id, hInst, NULL);
}

/* �׸���, ����� ��� �� ���� */
void SetFunction(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	// wParam(32Bit) : ��Ʈ�� ID + �˸� �ڵ�
	// lParam(32Bit) : ��Ʈ�� �ڵ� (������ ��, �޽����� ���� ��Ʈ���� �ڵ�)

	// HIWORD: ���� 16Bit, LOWORD: ���� 16Bit
	if (HIWORD(wParam) == BN_CLICKED) // ��ư�� Ŭ���Ǿ��� ��
	{
		switch (LOWORD(wParam))
		{
		case 1: // �� ��ư (id: 1)
		{
			// ���� üũ���� ���� ���¿��� Ŭ��: �� üũ, ���찳 ��üũ
			if(SendMessageW((HWND)lParam, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessageW((HWND)lParam, BM_SETCHECK, BST_CHECKED, 0);
				SendMessageW(FindWindowEx(hWnd, NULL, L"button", L"Erase"), BM_SETCHECK, BST_UNCHECKED, 0);
			}
			// ���� üũ�� ���¿��� Ŭ��: �� ��üũ
			else {
				SendMessageW((HWND)lParam, BM_SETCHECK, BST_UNCHECKED, 0);
			}
		}
		break;
		case 2: // ���찳 ��ư (id: 2)
		{
			// ���찳�� üũ���� ���� ���¿��� Ŭ��: ���찳 üũ, �� ��üũ
			if (SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessageW((HWND)lParam, BM_SETCHECK, BST_CHECKED, 0);
				SendMessageW(FindWindowEx(hWnd, NULL, L"button", L"Pen"), BM_SETCHECK, BST_UNCHECKED, 0);
				return;
			}
			// ���찳�� üũ�� ���¿��� Ŭ��: ���찳 ��üũ
			else {
				SendMessageW((HWND)lParam, BM_SETCHECK, BST_UNCHECKED, 0);
			}
		}
		break;
		} // ����ġ�� ����
	}
	return;
}

/* ��� �� �޾ƿ��� */
int GetFunction(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	// 1: ��, 2: ���찳, 0: �ƹ��͵� ���� �ȵ�
	if(SendMessageW(FindWindowExW(hWnd, NULL, L"button", L"Pen"), BM_GETCHECK, 0, 0) == BST_CHECKED) return 1;
	if (SendMessageW(FindWindowExW(hWnd, NULL, L"button", L"Erase"), BM_GETCHECK, 0, 0) == BST_CHECKED) return 2; 
	else return 0;
}

/* ���� ���� ���� ����� */
void CreateRGBTable(const WCHAR* name, LONG left, LONG top, LONG right, LONG bottom, HMENU id, HWND hWnd, HINSTANCE hInst)
{
	// RGB�� ��ũ�� �� ���� �� ���� ����
	CreateWindowW(L"scrollbar", L"R", WS_CHILD | WS_VISIBLE | SBS_HORZ, right + 20, top + 15, right + 30, 15, hWnd, id, hInst, NULL);
	SetScrollRange(FindWindowExW(hWnd, NULL, L"scrollbar", L"R"), SB_CTL, 0, 255, TRUE);
	CreateWindowW(L"scrollbar", L"G", WS_CHILD | WS_VISIBLE | SBS_HORZ, right + 20, top + 45, right + 30, 15, hWnd, id + 1, hInst, NULL);
	SetScrollRange(FindWindowExW(hWnd, NULL, L"scrollbar", L"G"), SB_CTL, 0, 255, TRUE);
	CreateWindowW(L"scrollbar", L"B", WS_CHILD | WS_VISIBLE | SBS_HORZ, right + 20, top + 75, right + 30, 15, hWnd, id + 2, hInst, NULL);
	SetScrollRange(FindWindowExW(hWnd, NULL, L"scrollbar", L"B"), SB_CTL, 0, 255, TRUE);
	//SetColor(hWnd);
}

/* ���� ���� */
void SetColor(HWND hWnd, HDC memDC, HBITMAP memBitmap)
{
	// ��ũ�� Bar�� �� �޾ƿ���
	int R = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"R"), SB_CTL);
	int G = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"G"), SB_CTL);
	int B = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"B"), SB_CTL);

	HBRUSH newBrush = CreateSolidBrush(RGB(R, G, B));
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, newBrush);

	// ���õ� ���� �����ֱ�
	Rectangle(memDC, 80, 30, 150, 120);

	// ��ũ�� Bar�� �� ǥ�����ֱ�
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

/* ��ũ�� ���� */
void SetScrollFunction(WPARAM wParam, LPARAM lParam) 
{
	// WPARAM : ��ũ�ѹ��� ���� �ڵ�(LOWORD) + ��ũ�ѹٰ� ������ ���ο� ��ġ(HIWORD)

	switch (LOWORD(wParam))
	{
	case SB_LINELEFT: // ���� ȭ��ǥ Ŭ��: ��ũ�ѹ� ���� 1��ŭ ����
		SetScrollPos((HWND)lParam, SB_CTL, max(0, GetScrollPos((HWND)lParam, SB_CTL) - 1), TRUE);
		break;
	case SB_PAGELEFT: // ���� ���� Ŭ��: ��ũ�ѹ� ���� 5��ŭ ����
		SetScrollPos((HWND)lParam, SB_CTL, max(0, GetScrollPos((HWND)lParam, SB_CTL) - 5), TRUE);
		break;
	case SB_LINERIGHT: // ������ ȭ��ǥ Ŭ��: ��ũ�ѹ� ���� 1��ŭ ����
		SetScrollPos((HWND)lParam, SB_CTL, min(255, GetScrollPos((HWND)lParam, SB_CTL) + 1), TRUE);
		break;
	case SB_PAGERIGHT: // ������ ���� Ŭ��: ��ũ�ѹ� ���� 5��ŭ ����
		SetScrollPos((HWND)lParam, SB_CTL, min(255, GetScrollPos((HWND)lParam, SB_CTL) + 5), TRUE);
		break;
	case SB_THUMBTRACK: // ��ũ�ѹ� ���� �巡��: �巡���� ��ġ�� ���� ����
		SetScrollPos((HWND)lParam, SB_CTL, HIWORD(wParam), TRUE);
		break;
	}
}

/* �޸� DC �� ��Ʈ�ʿ� �޸� �Ҵ��ϱ� */ 
void CreateBackPage(HWND hWnd, HINSTANCE hInst, HDC* memDC, HBITMAP* memBitmap) 
{
	// �������� DC ������ ȭ��� ȣȯ�Ǵ� �޸� DC ����
	// DC: ���� ����. ��, ��, �귯��, ����, �۲� �� ��� �׸��� ���� ������ ��� ����
	HDC hdc = GetDC(hWnd);
	*memDC = CreateCompatibleDC(hdc);

	// �簢�� ��ǥ ����ü ���� �� Ŭ���̾�Ʈ ���� ũ�� �޾ƿ���
	RECT rect;
	GetClientRect(hWnd, &rect);

	// �� ��Ʈ�� ���� �� �޸� DC�� ��Ʈ�� ����
	// Bitmap: �׸��� �׷����� ���� �̹��� ������
	*memBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	(HBITMAP)SelectObject(*memDC, *memBitmap);

	// �޸� DC�� ��� ������� ä���
	FillRect(*memDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	// ������ DC ��ȯ (DC�� �ý��� �ڿ��̹Ƿ� �ݵ�� ��ȯ�ؾ� ��)
	ReleaseDC(hWnd, hdc);
}

/* �׸��� */
POINT Draw(HWND hWnd, HDC hdc, WPARAM wParam, LPARAM lParam, POINT stPos) 
{
	// ���콺 Ŀ���� 1�ȼ��̶� �����̸� �ʴ� ����, ���� ���� ȣ���
	// �� �׸��� �۾����� ���� ���� �����ϰ� ������

	// ��ũ�� Bar�� �� �޾ƿ���
	int R = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"R"), SB_CTL);
	int G = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"G"), SB_CTL);
	int B = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"B"), SB_CTL);

	HPEN newPen = CreatePen(PS_SOLID, 10, RGB(R, G, B)); // ��Ÿ��: PS_SOLID(�Ǽ�), ����: 10, ����: RGB(R, G, B)
	HPEN oldPen = (HPEN)SelectObject(hdc, newPen); // newPen�� �ڵ� ����

	POINT pos;
	pos.x = GET_X_LPARAM(lParam);
	pos.y = GET_Y_LPARAM(lParam);

	// ���� ª�� �ð����� move�� line�� ���޾� ����Ǹ鼭 ���ӵ� ������ �׸�
	MoveToEx(hdc, stPos.x, stPos.y, NULL); // ���� ��ġ�� ���콺(pos) ��ġ�� �̵�
	LineTo(hdc, pos.x, pos.y); // ���� ��ġ���� ���콺(pos) ��ġ���� �� �׸���

	SelectObject(hdc, oldPen); 
	DeleteObject(newPen);

	stPos.x = pos.x;
	stPos.y = pos.y;

	return stPos; // ���� �׸��� ������ ��ǥ ��ȯ
}

/* ����� */
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

// �̹��� �����
// ������۸�
// ������
// ��ư ����
// ��� ����� �ɰ��� �ϳ��� �߰��� ����