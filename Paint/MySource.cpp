#include "MySource.h"


/* 윈도우 창 설정 */
HWND InitMainWindowSet(HINSTANCE hInstance, WNDPROC WndProc, const WCHAR* name) {

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

	return CreateWindowW(name, name, WS_MAXIMIZE|WS_SYSMENU, 100, 100, 750, 750, nullptr, nullptr, hInstance, nullptr);
}
