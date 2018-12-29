#pragma once

#include <Windows.h>
#include "libwcv_type_converter.h"


#using <System.dll>
#using <System.Windows.Forms.dll>

#pragma comment(lib, "user32.lib")

#define DIAG_OUT(x) System::Windows::Forms::MessageBox::Show(x)
using namespace System;

namespace libwcv
{
	
	public ref class ClipboardViewer
	{
	public:
		ClipboardViewer()
		{
			_clipboardViewerForm = gcnew Win32CVF();
			//DIAG_OUT(_clipboardViewerForm->Handle.ToString());
		}
	private:
		ref class Win32CVF
			: public System::Windows::Forms::Form
		{
		private:
			System::IntPtr	_Win32CVF_nextClipboardViewer;
			System::Int32	_Win32CVF_lastError;
			System::Int32	_Win32CVF_set_clipboard_viewer([out]System::IntPtr% next_clipboard_viewer_handle);
			bool			_Win32CVF_is_enabled;

		protected:
			void WndProc(System::Windows::Forms::Message % msg) override;
			
		public:
			System::Int32	Win32CVF_get_last_error();
			System::IntPtr	Win32CVF_get_next_clipboard_viewer_handle();
			bool			Win32CVF_get_is_enabled();
			
		};
	private:
		Win32CVF^					_clipboardViewerForm;
		System::IntPtr				_nextClipboardViewerHandle;
		System::String^				_clipboardViewerName;
		
		
	public:
		property
			bool IsCreated
		{
			bool get()
			{
				return this->_clipboardViewerForm->Win32CVF_get_is_enabled();
			}
		}
		property
			System::IntPtr ClipboardViewerHandle
		{
			System::IntPtr get()
			{
				return this->_clipboardViewerForm->Handle;
			}
		}

		property
			System::IntPtr NextClipboardViewerHandle
		{
			System::IntPtr get()
			{
				return this->_clipboardViewerForm->Win32CVF_get_next_clipboard_viewer_handle();
			}
		}

		property
			System::Int32 LastError
		{
			System::Int32 get()
			{
				return this->_clipboardViewerForm->Win32CVF_get_last_error();
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
		void HideViewer();
		System::String^ ToString() override;
	public:
		event System::EventHandler^ ClipboardViewerCreated
		{
			void add(System::EventHandler^ d)
			{
				ClipboardViewerCreated += d;
			}
			void remove(System::EventHandler^ d)
			{
				ClipboardViewerCreated -= d;
			}
			void raise(System::EventHandler^ d, System::EventArgs^ a)
			{
				
				if (d)
				{
					d->Invoke(this, &a);
				}
			}
		}
		
	protected:
		
	};

	public value struct ClipboardOwnerInfo
	{
		System::IntPtr		ClipboardOwnerWindowHandle;
		System::String^		ClipboardOwnerWindowTitle;
		System::String^		ClipboardOwnerProcessName;
		System::Int32		ClipboardOwnerProcessID;
		System::String^		ClipboardOwnerModuleName;
	};
}
