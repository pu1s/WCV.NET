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

#define ToUM(x) stdcli::TypeConverter::ConvertMessage<UMSG, MMSG%>(x)
#define ToMM(x) stdcli::TypeConverter::ConvertMessage<MMSG, UMSG&>(x)
#define ToMH(x) stdcli::TypeConverter::ConvertHandle<MHANDLE, UHANDLE&>(x)
#define ToUH(x) stdcli::TypeConverter::ConvertHandle<UHANDLE, MHANDLE%>(x)

#define m_str System::String^
#define m_hwnd m_managed_Handle
#define u_hwnd m_unmanaged_Handle
namespace stdcli
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

	public ref struct UniHandle
	{
	private:
		UHANDLE m_unmanaged_Handle;
		MHANDLE m_managed_Handle;
	public:

		m_str ToString() override
		{
			System::String^ tmp = gcnew System::String("");
			tmp += "Unmanaged Handle: ";
			tmp += gcnew String(std::to_string((long long)m_unmanaged_Handle).c_str());
			tmp += " ";
			tmp += "Managed Handle: ";
			tmp += m_managed_Handle.ToString();
			return tmp;
		}

		UniHandle()
		{
			this->m_managed_Handle = IntPtr::Zero;
			this->m_unmanaged_Handle = NULL;
		}
		UniHandle(UniHandle% unihandle) {
			this->m_managed_Handle = unihandle.m_managed_Handle;
			this->m_unmanaged_Handle = unihandle.m_unmanaged_Handle;
		}

		UniHandle(UHANDLE& handle)
		{
			u_hwnd = handle;
			m_hwnd = ToMH(handle);
		}
		UniHandle(MHANDLE% handle)
		{
			u_hwnd = ToUH(handle);
			m_hwnd = handle;
		}
		UniHandle Create(UHANDLE& handle)
		{
			this->u_hwnd = handle;
			this->m_hwnd = ToMH(handle);
			return *this;
		}
		UniHandle Create(MHANDLE% handle)
		{
			this->u_hwnd = ToUH(handle);
			this->m_hwnd = handle;
			return *this;
		}
		bool operator == (UniHandle% other)
		{
			if ((this->m_hwnd == other.m_hwnd) | (this->u_hwnd == other.u_hwnd)) return true;
			else return false;
		}
		bool operator != (UniHandle% other)
		{
			if (this->m_hwnd != other.m_hwnd && this->u_hwnd != other.u_hwnd) return true;
			else return false;
		}
		UniHandle operator =(UniHandle% other)
		{
			this->m_hwnd = other.m_hwnd;
			this->u_hwnd = other.u_hwnd;
			return *this;
		}
		property IntPtr MHandle
		{
			IntPtr get(void)
			{
				return this->m_hwnd;
			}
		}
	};
}

