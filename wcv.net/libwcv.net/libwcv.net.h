#pragma once

#include <Windows.h>
#include <WinUser.h>

#pragma comment(lib, "user32.lib")

#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Windows::Forms;

extern int d = 10;

namespace libwcvnet
{

	public ref class ClipboardViewerForm : public Form
	{
		// TODO: Добавьте сюда свои методы для этого класса.
	public:
		ClipboardViewerForm() {}
	};
}
