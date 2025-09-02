#include "MySource.h"


/* ������ â ���� */
HWND InitMainWindowSet(HINSTANCE hInstance, WNDPROC WndProc, const WCHAR* name) {

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
