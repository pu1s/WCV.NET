#pragma once

#include "wcv_custom_marshaler.h"

#include <Windows.h>
#include <WinUser.h>
#include "libwcv_type_converter.h"
#include "wcv_window_form.h"

#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;

namespace libwcv
{
	public ref class testclass
	{
	public:
		
		System::IntPtr mh;
		HWND uh;
		MSG* msg = new MSG();
		void testfunc(void)
		{
			uh = libwcv::interop::convert<HWND>(mh);
			mh = libwcv::interop::convert<IntPtr>(uh);
			WindowsClipboardViewerForm^ form = gcnew WindowsClipboardViewerForm();
			form->Show();
		}

	};
}
