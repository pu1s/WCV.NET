#pragma once


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

		}
	};
}

