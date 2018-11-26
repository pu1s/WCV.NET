#pragma once
#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <string>

#include "TypeConverter.h"

//#pragma comment(lib, "user32.dll")

#using <system.dll>
#using <system.drawing.dll>
#using <system.windows.forms.dll>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Reflection;

#define m_str System::String^
#define m_hwnd m_managed_Handle
#define u_hwnd m_unmanaged_Handle
namespace wcvlib
{
	public ref struct UniHandle
	{
	private:
		UHANDLE m_unmanaged_Handle;
		MHANDLE m_managed_Handle;
	public:
	
		m_str ToString() override;
		UniHandle();
		
		UniHandle(UniHandle% unihandle);
		
		UniHandle(UHANDLE& handle)
		{
			u_hwnd = handle;
			m_hwnd = ToMH(handle);
		}
		UniHandle(MHANDLE% handle)
		{
			u_hwnd= ToUH(handle);
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



	public ref class ClipboardViewerForm :
		public System::Windows::Forms::Form
	{
	private:
		
		//void CrossHandleUpdate(void);
	public:
		ClipboardViewerForm();
		UniHandle^ pUniHandle;
		
	protected:
		void WndProc(System::Windows::Forms::Message% m) override;
	};
}


