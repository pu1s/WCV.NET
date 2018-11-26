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


wcvlib::UniHandle::UniHandle()
{
	this->m_managed_Handle = IntPtr::Zero;
	this->m_unmanaged_Handle = NULL;
}

wcvlib::UniHandle::UniHandle(wcvlib::UniHandle% unihandle)
{
	this->m_managed_Handle = unihandle.m_managed_Handle;
	this->m_unmanaged_Handle = unihandle.m_unmanaged_Handle;
}


System::String ^ wcvlib::UniHandle::ToString()
{
	System::String^ tmp = gcnew System::String("");
	tmp += "Unmanaged Handle: ";
	tmp += gcnew String(std::to_string((long long)m_unmanaged_Handle).c_str());
	tmp += " ";
	tmp += "Managed Handle: ";
	tmp += m_managed_Handle.ToString();
	return tmp;
}
