#include "libwcv_clipboard_viewer.h"

inline void libwcv::ClipboardViewer::Win32CVF::WndProc(System::Windows::Forms::Message % msg)
{
	MSG m;
	m = libwcv::interop::clr_cast<MSG>(msg);
	switch (msg.Msg)
	{

	case WM_CREATE:
		this->Text = this->Handle.ToString();
		if (0 !=(_Win32CVF_lastError = _Win32CVF_set_clipboard_viewer(_Win32CVF_nextClipboardViewer)))
		{
			_Win32CVF_is_enabled = true;
		}
		DIAG_OUT(this->Handle.ToString() + 
			"\n" + _Win32CVF_nextClipboardViewer.ToString() + 
			"\n" + _Win32CVF_lastError.ToString());
		break;
	case WM_DRAWCLIPBOARD:

		if (IsWindow(libwcv::interop::clr_cast<HWND>(_Win32CVF_nextClipboardViewer)) || _Win32CVF_nextClipboardViewer!= System::IntPtr::Zero)
		{
			PostMessage(libwcv::interop::clr_cast<HWND>(_Win32CVF_nextClipboardViewer), m.message, m.wParam, m.lParam);
		}
		break;
	default:
		DefWndProc(msg);
		break;
	}
}

System::Int32 libwcv::ClipboardViewer::Win32CVF::Win32CVF_get_last_error()
{
	return _Win32CVF_lastError;
}

System::IntPtr libwcv::ClipboardViewer::Win32CVF::Win32CVF_get_next_clipboard_viewer_handle()
{
	return _Win32CVF_nextClipboardViewer;
}

bool libwcv::ClipboardViewer::Win32CVF::Win32CVF_get_is_enabled()
{
	return _Win32CVF_is_enabled;
}

System::Int32 libwcv::ClipboardViewer::Win32CVF::_Win32CVF_set_clipboard_viewer(System::IntPtr % next_clipboard_viewer_handle)
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
	if (_clipboardViewerForm->Handle != System::IntPtr::Zero)
	{
		_clipboardViewerForm->Show();
	}
}

void libwcv::ClipboardViewer::CloseViewer()
{
	if (_clipboardViewerForm->Handle != System::IntPtr::Zero)
	{
		_clipboardViewerForm->Hide();
	}
}

System::String ^ libwcv::ClipboardViewer::ToString()
{
	return gcnew System::String("ClipboardViewer. Name: " + this->ClipboardViewerName + "Handle: " + this->ClipboardViewerHandle.ToString());
}
