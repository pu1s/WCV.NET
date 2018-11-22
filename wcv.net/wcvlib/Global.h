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

namespace wcvlib
{
	public ref class TypeConverter
	{
	public:
		template<typename To, typename From>
		static To Convert(From){}
		template<>
		static MHANDLE Convert<MHANDLE, UHANDLE>(UHANDLE h) {
			return System::IntPtr(h);
		}
		template<>
		static UHANDLE Convert<UHANDLE, MHANDLE>(MHANDLE h) {
			return (UHANDLE)h.ToPointer();
		}
		//
		template<typename UType, typename MType>
		static UType ToUnmanaged(MType mt){}
		template<>
		static UHANDLE ToUnmanaged(MHANDLE% mt)
		{
			return (UHANDLE)mt.ToPointer();
		}
		//
		template<typename MType, typename UType>
		static MType ToManaged(UType& ut) {}
		template<>
		static MHANDLE ToManaged(UHANDLE& ut)
		{
			return MHANDLE(ut);
		}
		//
		static MMSG ToManagedMessage(const UMSG& umsg)
		{
			MMSG tmp;
			tmp.Create(MHANDLE(umsg.hwnd), System::Int32(umsg.message), System::IntPtr((long)umsg.wParam), System::IntPtr(umsg.lParam));
			return tmp;
		}
		static UMSG ToUnmanagedMessage(MMSG% const mmsg)
		{
			UMSG tmp;
			tmp.hwnd = (HWND)mmsg.HWnd.ToPointer(); //TODO: to be cont
		}
	};
}