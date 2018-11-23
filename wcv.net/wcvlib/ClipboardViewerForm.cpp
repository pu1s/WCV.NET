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
	
	um = TypeConverter::ConvertMessage<UMSG, MMSG%>(m);
	switch (m.Msg)
	{
	case WM_CREATE:
		h = (UHANDLE)SetClipboardViewer(um.hwnd);
		mh = TypeConverter::ConvertHandle<MHANDLE, UHANDLE&>(h);
		this->Text = this->Handle.ToString() + ":" + mh.ToString();
		break;
	default:
		return this->DefWndProc(m);
		break;
	}
}
