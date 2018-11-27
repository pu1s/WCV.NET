#include "stdafx.h"
#include "ClipboardViewerForm.h"


stdcli::ClipboardViewerForm::ClipboardViewerForm()
{
	
}

void stdcli::ClipboardViewerForm::WndProc(System::Windows::Forms::Message % m)
{
	UHANDLE h;
	UMSG um;
	MHANDLE mh;

	um = ToUM(m);
	switch (m.Msg)
	{
	/*case WM_NCCREATE:

		break;*/
	case WM_CREATE:
		h = (UHANDLE)SetClipboardViewer(um.hwnd);
		mh = ToMH(h);
		
		
	
		
		break;
	default:
		return this->DefWndProc(m);
		break;
	}
}





System::String ^ stdcli::UniHandle::ToString()
{
	System::String^ tmp = gcnew System::String("");
	tmp += "Unmanaged Handle: ";
	tmp += gcnew String(std::to_string((long)UnmanagedHandle).c_str());
	tmp += " ";
	tmp += "Managed Handle: ";
	tmp += ManagedHandle.ToString();
	return tmp;
}
