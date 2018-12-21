#pragma once

#include <Windows.h>
#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;

namespace System
{
	public ref class WindowsClipboardViewerForm 
		: public System::Windows::Forms::Form
	{
	protected:
		void WndProc(System::Windows::Forms::Message % msg) override
		{
			switch (msg.Msg)
			{
			case WM_CREATE:
				this->Text = this->Handle.ToString();
				break;
			default:
				DefWndProc(msg);
				break;
			}
		}
	};
}

