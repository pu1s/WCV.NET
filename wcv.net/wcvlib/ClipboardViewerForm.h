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
	public:
		HWND unmanaged_handle;
		IntPtr managed_handle;
		UniHandle(const HWND&, const IntPtr%);
		System::String^ ToString() override;
	};
	public ref class ClipboardViewerForm :
		public System::Windows::Forms::Form
	{
	private:
		//UniHandle _uniHandle;
		//void CrossHandleUpdate(void);
	public:
		ClipboardViewerForm();
	protected:
		void WndProc(System::Windows::Forms::Message% m) override;
	};
}


