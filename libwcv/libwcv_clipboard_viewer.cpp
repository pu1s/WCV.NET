#include "libwcv_clipboard_viewer.h"

inline void libwcv::ClipboardViewer::WindowsClipboardViewerForm::WndProc(System::Windows::Forms::Message % msg)
{
	MSG m;
	m = libwcv::interop::clr_cast<MSG>(msg);
	switch (msg.Msg)
	{

	case WM_CREATE:
		this->Text = this->Handle.ToString();
		_lastError = set_clipboard_viewer(_nextClipboardViewer);
		break;
	case WM_DRAWCLIPBOARD:
		if (IsWindow(libwcv::interop::clr_cast<HWND>(_nextClipboardViewer)) || _nextClipboardViewer!= System::IntPtr::Zero)
		{
			PostMessage(libwcv::interop::clr_cast<HWND>(_nextClipboardViewer), m.message, m.wParam, m.lParam);
		}
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

System::IntPtr libwcv::ClipboardViewer::WindowsClipboardViewerForm::get_next_clipboard_viewer_handle()
{
	return _nextClipboardViewer;
}

System::Int32 libwcv::ClipboardViewer::WindowsClipboardViewerForm::set_clipboard_viewer(System::IntPtr % next_clipboard_viewer_handle)
{
	System::Int32 return_value = 0;
	System::IntPtr _next_clipboard_viewer_handle = System::IntPtr::Zero;
	if ((_next_clipboard_viewer_handle = libwcv::interop::clr_cast<System::IntPtr>(SetClipboardViewer(libwcv::interop::clr_cast<HWND>(this->Handle)))) != System::IntPtr::Zero)
	{
		return_value = System::Int32(GetLastError());
	}
	next_clipboard_viewer_handle = _next_clipboard_viewer_handle;
	return return_value;
}

void libwcv::ClipboardViewer::ShowViewer()
{
	if (_form->Handle != System::IntPtr::Zero)
	{
		_form->Show();
	}
}

System::String ^ libwcv::ClipboardViewer::ToString()
{
	return gcnew System::String("ClipboardViewer. Name: " + this->ClipboardViewerName + "Handle: " + this->ClipboardViewerHandle.ToString());
}
