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




		break;
	default:
		return this->DefWndProc(m);
		break;
	}
}

