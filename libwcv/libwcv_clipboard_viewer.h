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
		}
	private:
		ref class WindowsClipboardViewerForm
			: public System::Windows::Forms::Form
		{
		private:
			System::IntPtr	_nextClipboardViewer;
			System::Int32	_lastError;
			System::Int32 set_clipboard_viewer([out]System::IntPtr% next_clipboard_viewer_handle);
		protected:
			void WndProc(System::Windows::Forms::Message % msg) override;
			
		public:
			System::Int32 get_last_error();
			System::IntPtr get_next_clipboard_viewer_handle();
		};
	private:
		WindowsClipboardViewerForm^ _form;
		System::IntPtr				_nextClipboardViewerHandle;
		System::String^				_clipboardViewerName;

		
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
				return this->_form->get_next_clipboard_viewer_handle();
			}
		}

		property
			System::Int32 LastError
		{
			System::Int32 get()
			{
				return this->_form->get_last_error();
			}
		}

		property
			System::String^ ClipboardViewerName
		{
			System::String^ get()
			{
				return _clipboardViewerName;
			}
			void set(System::String^ name)
			{
				_clipboardViewerName = name;
			}
		}
		void ShowViewer();
		System::String^ ToString() override;
	};

}
