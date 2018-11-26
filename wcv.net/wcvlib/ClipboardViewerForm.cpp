#include "stdafx.h"
#include "ClipboardViewerForm.h"


wcvlib::ClipboardViewerForm::ClipboardViewerForm()
{
}

void wcvlib::ClipboardViewerForm::WndProc(System::Windows::Forms::Message % m)
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
		this->Text = this->Handle.ToString() + ":" + mh.ToString();
		break;
	default:
		return this->DefWndProc(m);
		break;
	}
}

wcvlib::UniHandle::UniHandle(const HWND &, const IntPtr %)
{
	throw gcnew System::NotImplementedException();
}

System::String ^ wcvlib::UniHandle::ToString()
{
	throw gcnew System::NotImplementedException();
	// TODO: вставьте здесь оператор return
}
