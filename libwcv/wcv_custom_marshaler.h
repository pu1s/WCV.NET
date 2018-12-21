#pragma once

#include <cstdlib>
#include <cstdio>

#include <Windows.h>
#include <WinUser.h>
#include <msclr/marshal_windows.h>
#include "wcv_custom_marshal_windows.h"

#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Windows::Forms;

typedef IntPtr^	MHWND;
typedef HWND	UHWND;
typedef	System::Windows::Forms::Message	MMSG;
typedef MSG*	UMSG;

namespace libwcv
{
	template<typename From, typename To>
	void MarshalAs(From, To){}

	template<>
	void MarshalAs<UHWND, MHWND>(UHWND hWnd, MHWND handle)
	{
		handle = IntPtr(hWnd);
	}

	template<>
	void MarshalAs<UHWND&, MHWND>(UHWND& hWnd, MHWND handle)
	{
		handle = IntPtr(hWnd);
	}


	template<>
	void MarshalAs<MHWND, UHWND>(MHWND handle, UHWND hWnd)
	{
		hWnd = static_cast<UHWND>(handle->ToPointer());
	}

	template<>
	void MarshalAs<MHWND%, UHWND>(MHWND% handle, UHWND hWnd)
	{
		hWnd = static_cast<UHWND>(handle->ToPointer());
	}

	template<typename From, typename To>
	To MarshalAs(From) {}
	
	template<>
	HWND MarshalAs<MHWND, UHWND>(MHWND handle)
	{
		UHWND hwnd;
		hwnd = static_cast<UHWND>(handle->ToPointer());
		return hwnd;
	}

	template<>
	HWND MarshalAs<MHWND%, UHWND>(MHWND% handle)
	{
		UHWND hwnd;
		hwnd = static_cast<UHWND>(handle->ToPointer());
		return hwnd;
	}

	template<>
	MHWND MarshalAs<UHWND, MHWND>(UHWND hWnd)
	{
		return gcnew IntPtr(hWnd);
	}

	template<>
	MHWND MarshalAs<UHWND&, MHWND>(UHWND& hWnd)
	{
		return gcnew IntPtr(hWnd);
	}

	template<>
	void MarshalAs<MMSG, UMSG>(MMSG m1, UMSG m2)
	{
		m2->hwnd = (HWND)m1.HWnd.ToPointer();
		m2->message = (UINT)m1.Msg;
		m2->lParam = (LPARAM)m1.LParam.ToPointer();
		m2->wParam = (WPARAM)m1.WParam.ToPointer();
	}

	template<>
	void MarshalAs<UMSG, MMSG>(UMSG m1, MMSG m2)
	{
		m2.Create(IntPtr(m1->hwnd), m1->message, IntPtr((LONG)m1->wParam), IntPtr((LONG)m1->lParam));
	}


#define TO_MHWND(h) MarshalAs<UHWND, MHWND>(h)
#define TO_UHWND(h) MarshalAs<MHWND, UHWND>(h)

	
}




