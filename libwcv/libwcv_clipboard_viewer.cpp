#include "libwcv_clipboard_viewer.h"

inline void libwcv::ClipboardViewer::ClipboardViewerForm::WndProc(System::Windows::Forms::Message % msg)
{
	MSG m;
	m = libwcv::interop::clr_cast<MSG>(msg);
	switch (msg.Msg)
	{
	
	case WM_CREATE:
		this->Text = this->Handle.ToString();
		if (0 !=(_clipboardViewerForm_lastError = _clipboardViewerForm_set_clipboard_viewer(_clipboardViewerForm_nextClipboardViewer)))
		{
			_clipboardViewerForm_is_enabled = true;
		}
		DIAG_OUT(this->Handle.ToString() + 
			"\n" + _clipboardViewerForm_nextClipboardViewer.ToString() + 
			"\n" + _clipboardViewerForm_lastError.ToString());
		break;
	case WM_DRAWCLIPBOARD:
		//
		
		//
		if (_clipboardViewerForm_nextClipboardViewer!= System::IntPtr::Zero)
		{
			SendMessage(libwcv::interop::clr_cast<HWND>(_clipboardViewerForm_nextClipboardViewer), m.message, m.wParam, m.lParam);
		}
		break;
	case WM_DESTROY:
		ChangeClipboardChain(libwcv::interop::clr_cast<HWND>(this->Handle), libwcv::interop::clr_cast<HWND>(_clipboardViewerForm_nextClipboardViewer));
		DIAG_OUT("Destroy Window");
		break;
	default:
		DefWndProc(msg);
		break;
	}
}

System::Int32 libwcv::ClipboardViewer::ClipboardViewerForm::ClipboardViewerForm_get_last_error()
{
	return _clipboardViewerForm_lastError;
}

System::IntPtr libwcv::ClipboardViewer::ClipboardViewerForm::ClipboardViewerForm_get_next_clipboard_viewer_handle()
{
	return _clipboardViewerForm_nextClipboardViewer;
}

bool libwcv::ClipboardViewer::ClipboardViewerForm::ClipboardViewerForm_get_is_enabled()
{
	return _clipboardViewerForm_is_enabled;
}

System::Int32 libwcv::ClipboardViewer::ClipboardViewerForm::_clipboardViewerForm_set_clipboard_viewer(System::IntPtr % next_clipboard_viewer_handle)
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

libwcv::ClipboardViewer::ClipboardViewer()
{
	_clipboardViewerForm = gcnew ClipboardViewerForm();
	_clipboardViewerForm->Visible = true;
	if (_clipboardViewerForm->IsHandleCreated)
	{
		OnCreate();
	}
}

libwcv::ClipboardViewer::~ClipboardViewer()
{
	delete _clipboardViewerForm;
}

void libwcv::ClipboardViewer::ShowViewer()
{
	if (_clipboardViewerForm->Handle != System::IntPtr::Zero)
	{
		_clipboardViewerForm->Show();
		OnShow();
	}
}

void libwcv::ClipboardViewer::HideViewer()
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

BOOL __stdcall std::IsProcMainWindow(HWND hWnd) noexcept
{
	DWORD pid1, pid2;
	HWND fgw_hWnd;
	fgw_hWnd = (HWND)GetForegroundWindow();
	if (fgw_hWnd == NULL || hWnd == NULL) return 0;
	GetWindowThreadProcessId(hWnd, &pid1);
	GetWindowThreadProcessId(fgw_hWnd, &pid2);
	//
	if (pid1 == pid2)
		return 1;
	else
		return 0;
}

HWND std::GetProcMainWindow(HWND hWnd) noexcept
{
	DWORD pid1, pid2;
	HWND fgw_hWnd;
	fgw_hWnd = (HWND)GetForegroundWindow();
	if (fgw_hWnd == NULL || hWnd == NULL) return NULL;
	GetWindowThreadProcessId(hWnd, &pid1);
	GetWindowThreadProcessId(fgw_hWnd, &pid2);
	//
	if (pid1 == pid2)
		return fgw_hWnd;
	else
		return NULL;
}



