#include "libwcv_clipboard_viewer.h"

inline void libwcv::ClipboardViewer::WindowsClipboardViewerForm::WndProc(System::Windows::Forms::Message % msg)
{
	switch (msg.Msg)
	{

	case WM_CREATE:
		this->Text = this->Handle.ToString();
		_nextClipboardViewer =
			libwcv::interop::clr_cast<System::IntPtr>((HWND)SetClipboardViewer(
				libwcv::interop::clr_cast<HWND>(this->Handle)
			));
		break;
	default:
		DefWndProc(msg);
		break;
	}
}

System::Int32 libwcv::ClipboardViewer::WindowsClipboardViewerForm::get_last_error()
{
	return _lastError;
}

void libwcv::ClipboardViewer::ShowViewer()
{
	if (_form->Handle != System::IntPtr::Zero)
	{
		_form->Show();
	}
}
