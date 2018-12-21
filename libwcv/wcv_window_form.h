#pragma once

#include <Windows.h>
#include "libwcv_type_converter.h"


#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;

namespace ClipboardViewer
{
	public ref class WindowsClipboardViewer
	{
	public:
		WindowsClipboardViewer()
		{
			Form_ = gcnew WindowsClipboardViewerForm();
			Form_->Show();
		}
	private:
		ref class WindowsClipboardViewerForm
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
		WindowsClipboardViewerForm^ Form_;
	};

}
