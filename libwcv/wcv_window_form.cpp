#include "wcv_window_form.h"

//void System::WindowsClipboardViewerForm::WndProc(System::Windows::Forms::Message % msg)
//{
//	//throw gcnew System::NotImplementedException();
//}

inline void System::WindowsClipboardViewerForm::WndProc(System::Windows::Forms::Message % msg)
{
	switch (msg.Msg)
	{

	case WM_CREATE:
		this->Text = this->Handle.ToString();
		_nextClipboardViewer =
			libwcv::interop::convert<System::IntPtr>((HWND)SetClipboardViewer(
				libwcv::interop::convert<HWND>(this->Handle)
			));
		break;
	default:
		DefWndProc(msg);
		break;
	}
}
