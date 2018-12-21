#pragma once

#include "wcv_custom_marshaler.h"

#include <Windows.h>
#include <WinUser.h>
#include <msclr/marshal_windows.h>
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
			/*mh = gcnew IntPtr();
			uh = (HWND)MarshalAs<IntPtr^, HWND>(mh);
			mh = MarshalAs<HWND, IntPtr^>(uh);
			MarshalAs<IntPtr^, HWND>(mh, uh);
			MarshalAs<HWND, IntPtr^>(uh, mh);*/
			
			//mh = MarshalAs<UHWND, MHWND>(uh);
			uh = msclr::interop::marshal_as<HWND>(mh);
			System::Windows::Forms::Message m;
			*msg = msclr::interop::marshal_as<MSG>(m);
			uh = msclr::interop::marshal_as<HWND>(mh);
			m = msclr::interop::marshal_as<System::Windows::Forms::Message>(*msg);
			WindowsClipboardViewerForm^ form = gcnew WindowsClipboardViewerForm();
			form->Show();
		}

	};
}
