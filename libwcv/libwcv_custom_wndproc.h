#pragma once

#include <Windows.h>
#include <WinUser.h>

namespace libwcv
{
	LRESULT CALLBACK WindowProc(
		_In_ HWND   hwnd,
		_In_ UINT   uMsg,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
	) {}

	LRESULT CALLBACK AltWindowProc(
		MSG msg
	) {}
}

