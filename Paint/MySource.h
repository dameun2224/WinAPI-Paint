#pragma once

#include "framework.h"
#include "Paint.h"

// �ʱ� ���� ���� �Լ�
HWND InitMainWindowSet(HINSTANCE hInstance, WNDPROC WndProc, const WCHAR* name);

// ��ư ���� �Լ�
void CreateButton(const WCHAR* name, LONG x, LONG y, LONG width, LONG height, HMENU id, HWND hWnd, HINSTANCE hInst);
void SetFunction(WPARAM wParam, LPARAM lParam, HWND hWnd);
int GetFunction(WPARAM wParam, LPARAM lParam, HWND hWnd);

// ���� ���̺� ���� �Լ�
void CreateRGBTable(const WCHAR* name, LONG left, LONG top, LONG right, LONG bottom, HMENU id, HWND hWnd, HINSTANCE hInst);
void SetColor(HWND hWnd, HDC memDC, HBITMAP memBitmap);
void SetScrollFunction(WPARAM wParam, LPARAM lParam);

void CreateBackPage(HWND hWnd, HINSTANCE hInst, HDC* memDC, HBITMAP* memBitmap);