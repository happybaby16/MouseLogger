
#include <Windows.h>
//#include <Winuser.h> //��, ����� WinMain �������� �� ����
#include <malloc.h>
#include <locale.h>
#include <string.h>
#include <stdio.h>
//����� ���: https://youtu.be/IHSrJuSCjeA
#define SIZE_STR 256
#define PATH L"keylog.txt"
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
		lKey++;
		wchar_t buf[10];
		swprintf_s(buf, 100, L"%i", lKey);
		MessageBox(NULL, buf, L"���-�� ������� ���", NULL);
	}
	if (wParam == 516)
	{
		rKey++;
		wchar_t buf[10];
		swprintf_s(buf, 100, L"%i", rKey);
		MessageBox(NULL, buf, L"���-�� ������� ���", NULL);
	}

	if (wParam == 516)
	{
		keyPush++;
		wchar_t buf[10];
		swprintf_s(buf, 100, L"%i", keyPush);
		MessageBox(NULL, buf, L"���-�� ������� �������� �����", NULL);
	}


	if (wParam == 522) //����
	{
		keyScroll++;
		wchar_t buf[10];
		swprintf_s(buf, 100, L"%i", keyScroll);
		MessageBox(NULL, buf, L"���-�� ������� ������� ����", NULL);
	}

	return CallNextHookEx(NULL, iCode, wParam, lParam);
}

