#define _WIN32_WINNT 0x0A00
#include <Windows.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE_STR 256
#define RUS 1049
#define ENG 1033


DWORD lKey = 0, rKey = 0, keyScroll, keyPush=0;



LRESULT CALLBACK LogKey(int iCode, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	HHOOK hHook = SetWindowsHookEx(WH_MOUSE_LL,
		LogKey, NULL, NULL);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(hHook);

	return 0;
}

LRESULT CALLBACK LogKey(int iCode, WPARAM wParam, LPARAM lParam)
{
	_wsetlocale(LC_ALL, L".866");
	
	if (wParam == 513)
	{
		LPPOINT ddd;
		ddd = malloc(sizeof(LPPOINT));
		GetCursorPos(ddd);

		//lKey++;
		//wchar_t buf[10];
		//swprintf_s(buf, 100, L"%i", lKey);
		//MessageBox(NULL, buf, L"Кол-во нажатий ЛКМ", NULL);

		wchar_t x[10];
		swprintf_s(x, 10, L"%i", ddd[0].x);
		wchar_t y[10];
		swprintf_s(y, 10, L"%i", ddd[0].y);
#pragma region StrPos
		DWORD counter = 0;
		WCHAR res[30];
		for (int i = 0; i < 30; i++)
		{
			if (x[i] == '\0')break;
			res[i] = x[i];
			counter++;
		}
		DWORD i = 0;
		res[counter] = 'X';
		for (int k = counter + 1; k < 30; k++)
		{
			res[k] = y[i];
			if (y[i] == '\0')break;
			i++;
		}
#pragma endregion

		
		MessageBox(NULL, res, L"Координаты", NULL);
	}
	if (wParam == 516)
	{
		rKey++;
		wchar_t buf[10];
		swprintf_s(buf, 100, L"%i", rKey);
		MessageBox(NULL, buf, L"Кол-во нажатий ПКМ", NULL);
	}

	if (wParam == 516)
	{
		keyPush++;
		wchar_t buf[10];
		swprintf_s(buf, 100, L"%i", keyPush);
		MessageBox(NULL, buf, L"Кол-во нажатий колёсиком мышки", NULL);
	}


	if (wParam == 522) //вниз
	{
		keyScroll++;
		wchar_t buf[10];
		swprintf_s(buf, 100, L"%i", keyScroll);
		MessageBox(NULL, buf, L"Кол-во нажатий скролов мыши", NULL);
	}

	return CallNextHookEx(NULL, iCode, wParam, lParam);
}

