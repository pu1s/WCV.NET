#pragma once


#include <Windows.h>
#include <WinUser.h>

#using <System.dll>
#using <System.Windows.Forms.dll>

namespace libwcv
{
	namespace interop
	{
		template<typename _To>
		inline _To convert(System::IntPtr){}

		template<>
		inline HWND convert(System::IntPtr p)
		{
			return (HWND)p.ToPointer();
		}

		template<typename _To>
		inline _To convert(HWND h) {}

		template<>
		inline System::IntPtr convert(HWND h)
		{
			return System::IntPtr(h);
		}

		template<typename _To>
		inline _To convert(MSG m) {}

		template<>
		inline System::Windows::Forms::Message convert(MSG m) 
		{
			System::Windows::Forms::Message msg;
			msg.Create(System::IntPtr(m.hwnd), m.message, System::IntPtr((LONG)m.wParam), System::IntPtr((LONG)m.lParam));
			return msg;
		}

		template<typename _To>
		inline _To convert(System::Windows::Forms::Message% m) {}

		template<>
		inline MSG convert(System::Windows::Forms::Message% m)
		{
			MSG msg;
			msg.hwnd = static_cast<HWND>(m.HWnd.ToPointer());
			msg.message = static_cast<UINT>(m.Msg);
			msg.wParam = (WPARAM)m.WParam.ToPointer();
			msg.lParam = (LPARAM)m.LParam.ToPointer();
			return msg;
		}
	}
}