#pragma once



#include <Windows.h>
#include <WinUser.h>
#include "libwcv_type_converter.h"
#include "libwcv_clipboard_viewer.h"
#include "libwcv_native_clipboard_viewer.h"

#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;


namespace libwcv
{
	public ref class testclass
	{
	public:
		
		System::IntPtr mh;
		HWND uh, uh1;
		MSG* msg = new MSG();
		void testfunc(void)
		{
			/*uh = libwcv::interop::clr_cast<HWND>(mh);
			mh = libwcv::interop::clr_cast<IntPtr>(uh);
			ClipboardViewer ^a = gcnew ClipboardViewer();
			a->ShowViewer();*/
			create_clipboard_viewer(L"clWindow", L" ", L"WOW");
			//A::WindowsClipboardViewerForm^ form = gcnew A::WindowsClipboardViewerForm();
			//form->Show();
		}

	};
}
