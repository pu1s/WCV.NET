#pragma once

#include <Windows.h>
#include "libwcv_type_converter.h"


#using <System.dll>
#using <System.Windows.Forms.dll>

#pragma comment(lib, "user32.lib")


using namespace System;

namespace libwcv
{
	public ref class ClipboardViewer
	{
	public:
		ClipboardViewer()
		{
			_form = gcnew WindowsClipboardViewerForm();
			_form->Show();
		}
	private:
		ref class WindowsClipboardViewerForm
			: public System::Windows::Forms::Form
		{
		private:
			System::IntPtr	_nextClipboardViewer;
			System::Int32	_lastError;
		
		protected:
			void WndProc(System::Windows::Forms::Message % msg) override
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

		};
	private:
		WindowsClipboardViewerForm^ _form;
		System::IntPtr				_nextClipboardViewerHandle;
	public:
		property
			System::IntPtr ClipboardViewerHandle
		{
			System::IntPtr get()
			{
				return this->_form->Handle;

			}
		}

		property
			System::IntPtr NextClipboardViewerHandle
		{
			System::IntPtr get()
			{
				return this->_nextClipboardViewerHandle;

			}
		}


	};

}
