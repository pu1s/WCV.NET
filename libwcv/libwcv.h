#pragma once



#include <Windows.h>
#include <WinUser.h>
#include "libwcv_type_converter.h"
#include "libwcv_clipboard_viewer.h"
#include "libwcv_native_clipboard_viewer.h"

#using <System.dll>
#using <System.Windows.Forms.dll>

#define MASTER_TRACE

using namespace System;


namespace libwcv
{
	public ref class CBWrapper
	{
	public:
		
		System::IntPtr mh;
		HWND uh, uh1;
		MSG* msg = new MSG();
		CLIPBOARDOWNERINFOSTRUCT* data_owner = new CLIPBOARDOWNERINFOSTRUCT();
		void testfunc(void)
		{
			/*uh = libwcv::interop::clr_cast<HWND>(mh);
			mh = libwcv::interop::clr_cast<IntPtr>(uh);
			ClipboardViewer ^a = gcnew ClipboardViewer();
			a->ShowViewer();*/
			
			
			//A::WindowsClipboardViewerForm^ form = gcnew A::WindowsClipboardViewerForm();
			//form->Show();
		}

		void Create() 
		{
			uh = create_clipboard_viewer(L"clWindow", L" ", L"WOW");	
		}
		void Destroy()
		{
			destroy_clipboard_viewer();
		}
		void GetData()
		{
			get_clipboard_owner_info(data_owner);
		}
	};
}
