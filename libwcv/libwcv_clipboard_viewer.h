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
			
		
		protected:
			void WndProc(System::Windows::Forms::Message % msg) override;
		public:
			System::Int32 get_last_error();
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

		property
			System::Int32 LastError
		{
			System::Int32 get()
			{
				return this->_form->get_last_error();
			}
		}

		void ShowViewer();
	};

}
