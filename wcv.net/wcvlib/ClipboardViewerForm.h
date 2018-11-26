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

namespace wcvlib
{
	public value struct UniHandle
	{
	private:
		UHANDLE UnmanagedHandle;
		MHANDLE ManagedHandle;
	public:
		static UniHandle Empty;
		System::String^ ToString() override;
		UniHandle(UHANDLE& handle)
		{
			UnmanagedHandle = handle;
			ManagedHandle = ToMH(handle);
		}
		UniHandle(MHANDLE% handle)
		{
			UnmanagedHandle = ToUH(handle);
			ManagedHandle = handle;
		}
		UniHandle Create(UHANDLE& handle)
		{
			this->UnmanagedHandle = handle;
			this->ManagedHandle = ToMH(handle);
			return *this;
		}
		UniHandle Create(MHANDLE% handle)
		{
			this->UnmanagedHandle = ToUH(handle);
			this->ManagedHandle = handle;
			return *this;
		}
	};

	

	public ref class ClipboardViewerForm :
		public System::Windows::Forms::Form
	{
	private:
		
		//void CrossHandleUpdate(void);
	public:
		ClipboardViewerForm();
		UniHandle pUniHandle;
		
	protected:
		void WndProc(System::Windows::Forms::Message% m) override;
	};
}


