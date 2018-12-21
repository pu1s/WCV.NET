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
		inline _To Convert(System::IntPtr){}

		template<>
		inline HWND Convert(System::IntPtr p)
		{
			return (HWND)p.ToPointer();
		}

		template<typename _To>
		inline _To Convert(HWND h) {}

		template<>
		inline System::IntPtr Convert(HWND h)
		{
			return IntPtr(h);
		}
	}
}