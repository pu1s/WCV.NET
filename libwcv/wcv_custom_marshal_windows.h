#pragma once

#include <Windows.h>
#include <msclr/marshal_windows.h>

#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Windows::Forms;

namespace msclr
{
	namespace interop
	{
		template<class _To_Type>
		inline _To_Type marshal_as(System::Windows::Forms::Message% m);

		template<>
		inline MSG marshal_as(System::Windows::Forms::Message% m)
		{
			MSG msg;
			msg.hwnd = static_cast<HWND>(m.HWnd.ToPointer());
			msg.message = static_cast<UINT>(m.Msg);
			msg.wParam = (WPARAM)m.WParam.ToPointer();
			msg.lParam = (LPARAM)m.LParam.ToPointer();
			return msg;
		}

		template<class _To_Type>
		inline _To_Type marshal_as(MSG& m);

		template<>
		inline System::Windows::Forms::Message marshal_as(MSG& m)
		{
			System::Windows::Forms::Message msg;
			msg.Create(System::IntPtr(m.hwnd), m.message, System::IntPtr((LONG)m.wParam), System::IntPtr((LONG)m.lParam));
			return msg;
		}

		template<class _To_Type>
		inline _To_Type marshal_as(System::IntPtr p);

		template<>
		inline HWND marshal_as(System::IntPtr p)
		{
			return (HWND)p.ToPointer();
		}

		template<class _To_Type>
		inline _To_Type marshal_as(HWND& p);

		template<>
		inline System::IntPtr marshal_as(HWND& p)
		{
			return System::IntPtr(p);
		}
	}
}
