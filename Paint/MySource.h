#pragma once

#include "framework.h"
#include "Paint.h"

HWND InitMainWindowSet(HINSTANCE hInstance, WNDPROC WndProc, const WCHAR* name);

void CreateButton(const WCHAR* name, LONG x, LONG y, LONG width, LONG height, HMENU id, HWND hWnd, HINSTANCE hInst);

void CreateRGBTable(const WCHAR* name, LONG left, LONG top, LONG right, LONG bottom, HMENU id, HWND hWnd, HINSTANCE hInst);
void SetColor(HWND hWnd);