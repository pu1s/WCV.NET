#pragma once
#include <Windows.h>
#include <WinUser.h>

#using <system.dll>
#using <system.drawing.dll>
#using <system.windows.forms.dll>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Reflection;

#define MHANDLE System::IntPtr
#define UHANDLE HWND
#define MMSG	System::Windows::Forms::Message
#define UMSG	MSG

#define ToUM(x) wcvlib::TypeConverter::ConvertMessage<UMSG, MMSG%>(x)
#define ToMM(x) wcvlib::TypeConverter::ConvertMessage<MMSG, UMSG&>(x)
#define ToMH(x) wcvlib::TypeConverter::ConvertHandle<MHANDLE, UHANDLE&>(x)
#define ToUH(x) wcvlib::TypeConverter::ConvertHandle<UHANDLE, MHANDLE%>(x)

namespace wcvlib
{
	public ref class TypeConverter
	{
	public:
		template<typename To, typename From>
		static To ConvertHandle(From) {}

		template<>
		static MHANDLE ConvertHandle<MHANDLE, UHANDLE&>(UHANDLE& h) 
		{
			return System::IntPtr(h);
		}

		template<>
		static UHANDLE ConvertHandle<UHANDLE, MHANDLE%>(MHANDLE% h) 
		{
			return (UHANDLE)h.ToPointer();
		}

		template<typename To, typename From>
		static To ConvertMessage(From) {}

		template<>
		static MMSG ConvertMessage<MMSG, UMSG&>(UMSG& um)
		{
			MMSG mm;
			mm.Create(MHANDLE(um.hwnd), System::Int32(um.message), System::IntPtr((long)um.wParam), System::IntPtr(um.lParam));
			return mm;
		}

		template<>
		static UMSG ConvertMessage(MMSG% mm)
		{
			UMSG um;
			um.hwnd = (HWND)mm.HWnd.ToPointer();
			return um;
		}
	};
}

