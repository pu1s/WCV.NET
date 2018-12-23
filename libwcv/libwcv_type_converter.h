#pragma once


#include <Windows.h>
#include <WinUser.h>

#using <System.dll>
#using <System.Windows.Forms.dll>

namespace libwcv
{
	namespace interop
	{
		typedef System::IntPtr					MHANDLE;
		typedef HWND							UHANDLE;
		typedef MSG								UMSG;
		typedef System::Windows::Forms::Message MMSG;


		template<typename _To>
		inline _To clr_cast(System::IntPtr){}

		template<>
		inline HWND clr_cast(System::IntPtr p)
		{
			return (HWND)p.ToPointer();
		}

		template<typename _To>
		inline _To clr_cast(HWND h) {}

		template<>
		inline System::IntPtr clr_cast(HWND h)
		{
			return System::IntPtr(h);
		}

		template<typename _To>
		inline _To clr_cast(MSG m) {
			return _To();
		}

		template<>
		inline System::Windows::Forms::Message clr_cast(MSG m) 
		{
			System::Windows::Forms::Message msg;
			msg.Create(System::IntPtr(m.hwnd), m.message, System::IntPtr((LONG)m.wParam), System::IntPtr((LONG)m.lParam));
			return msg;
		}

		template<typename _To>
		inline _To clr_cast(System::Windows::Forms::Message% m) {}

		template<>
		inline MSG clr_cast(System::Windows::Forms::Message% m)
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