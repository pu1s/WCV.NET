#include "stdafx.h"
#include "ClipboardViewerForm.h"


wcvlib::ClipboardViewerForm::ClipboardViewerForm()
{
}

void wcvlib::ClipboardViewerForm::WndProc(System::Windows::Forms::Message % m)
{
	switch (m.Msg)
	{
	case WM_CREATE:
		this->Text = this->Handle.ToString();
		break;
	default:
		return this->DefWndProc(m);
		break;
	}
}
