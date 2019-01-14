#pragma once

#include <Windows.h>
#include "libwcv_type_converter.h"


#using <System.dll>
#using <System.Windows.Forms.dll>

#pragma comment(lib, "user32.lib")

#define DIAG_OUT(x) System::Windows::Forms::MessageBox::Show(x)
using namespace System;

namespace std
{
	/*
	Возвращает ложь, если окно в котором изменен буфер обмена не принадлежит процессу "верхнего" окна Windows
	*/
	BOOL WINAPI IsProcMainWindow(
		HWND hWnd // Дескриптор окна
	) noexcept;

	/*
	Возвращает дескриптор "Главного" окна процесса.
	Функция возвращает NULL, если не найдено окно в данном процессе
	*/
	HWND WINAPI GetProcMainWindow(
		HWND hWnd // Дескриптор окна
	) noexcept;

	/*
	Возвращает дескриптор "Главного" окна процесса.
	Функция возвращает NULL, если не найдено окно в данном процессе
	*/
	HWND WINAPI GetProcMainWindow(
		LPDWORD pid // Дескриптор процесса
	) noexcept;
}
namespace libwcv
{

	public ref class AEventArgs : public System::EventArgs
	{
	public:
		AEventArgs()
		{
			obj = gcnew System::Object();
		}
		System::Object^ obj;
	};
	
	public ref class ClipboardViewer
	{
	public:
		ClipboardViewer();
		~ClipboardViewer();
	private:
		ref class ClipboardViewerForm
			: public System::Windows::Forms::Form
		{
		private:
			System::IntPtr	_clipboardViewerForm_nextClipboardViewer;
			System::Int32	_clipboardViewerForm_lastError;
			System::Int32	_clipboardViewerForm_set_clipboard_viewer([out]System::IntPtr% next_clipboard_viewer_handle);
			bool			_clipboardViewerForm_is_enabled;

		protected:
			void WndProc(System::Windows::Forms::Message % msg) override;
			
		public:
			System::Int32	ClipboardViewerForm_get_last_error();
			System::IntPtr	ClipboardViewerForm_get_next_clipboard_viewer_handle();
			bool			ClipboardViewerForm_get_is_enabled();
			
		};
	private:
		ClipboardViewerForm^		_clipboardViewerForm;
		System::IntPtr				_nextClipboardViewerHandle;
		System::String^				_clipboardViewerName;
		
		
	public:
		property
			bool IsCreated
		{
			bool get()
			{
				return this->_clipboardViewerForm->ClipboardViewerForm_get_is_enabled();
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
				return this->_clipboardViewerForm->ClipboardViewerForm_get_next_clipboard_viewer_handle();
			}
		}

		property
			System::Int32 LastError
		{
			System::Int32 get()
			{
				return this->_clipboardViewerForm->ClipboardViewerForm_get_last_error();
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
		
		// Show Clipboard Viewer
		void ShowViewer();

		// Hide Clipboard Viewer
		void HideViewer();

		// Clipboard Viewer String Representation
		System::String^ ToString() override;
	public:

		// Event on create Clipboard Viewer Form
		static event System::EventHandler^ Create;

		// Event on show Clipboard Viewer Form
		event System::EventHandler<AEventArgs^>^ Shown;

	protected:
		// Event on create Clipboard Viewer Form
		static void OnCreate()
		{
			Create(nullptr, gcnew System::EventArgs());
		}

		// Event on show Clipboard Viewer Form
		void OnShow()
		{
			Shown(this, gcnew AEventArgs());
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
