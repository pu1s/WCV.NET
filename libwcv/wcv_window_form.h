#pragma once

#include <Windows.h>
#include "libwcv_type_converter.h"


#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;

namespace System
{
	public ref class WindowsClipboardViewerForm 
		: public System::Windows::Forms::Form
	{
	private:
		System::IntPtr	_nextClipboardViewer;
		System::Int32	_lastError;
	public:
		property
			System::IntPtr NextClipboardViewerHandle
		{
			System::IntPtr get()
			{
				return _nextClipboardViewer;
			}
		}
	protected:
		void WndProc(System::Windows::Forms::Message % msg) override;
	};
}

