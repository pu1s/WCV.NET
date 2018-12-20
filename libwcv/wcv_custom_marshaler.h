#pragma once

#include <cstdlib>
#include <cstdio>

#include <Windows.h>
#include <WinUser.h>

#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Windows::Forms;

namespace libwcv
{
	template<typename From, typename To>
	void MarshalAs(From, To){}

	template<>
	void MarshalAs<HWND&, IntPtr%>(HWND& hWnd, IntPtr% handle)
	{
		handle = IntPtr(hWnd);
	}

	template<>
	void MarshalAs<IntPtr%, HWND&>(IntPtr% handle, HWND& hWnd)
	{
		hWnd = static_cast<HWND>(handle.ToPointer());
	}

	template<typename From, typename To>
	To MarshalAs(From) {}

	template<>
	HWND MarshalAs<IntPtr%, HWND>(IntPtr% handle)
	{

	}
}


