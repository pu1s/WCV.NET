#include "libwcv_native_clipboard_viewer.h"



HWND __stdcall create_clipboard_viewer(LPCWSTR class_name, LPCWSTR window_name, LPCWSTR window_title, WNDPROC alt_wnd_proc) noexcept
{
	if (class_name == L"")
	{
		MessageBox(NULL, L"Window Class Name is Requred!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	windowClassName = class_name;
	MSG msg;
	//
	hInstance = GetModuleHandle(NULL);
	//
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	if (alt_wnd_proc == NULL)
	{
		wc.lpfnWndProc = clipboard_viewer_proc;
	}
	else
	{
		wc.lpfnWndProc = alt_wnd_proc;
	}
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = windowClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	//
	clipboardViewer = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		windowClassName,
		window_title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, NULL, hInstance, NULL);

	if (clipboardViewer == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
#ifdef _DEBUG
	ShowWindow(clipboardViewer, SW_SHOW);
#else
	ShowWindow(cvhwnd, NULL);
#endif // _DEBUG
	UpdateWindow(clipboardViewer);

	// Step 3: The Message Loop
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return clipboardViewer;
}

BOOL __stdcall destroy_clipboard_viewer() noexcept
{
	return DestroyWindow(clipboardViewer);
}

LRESULT CALLBACK clipboard_viewer_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
#ifdef _DEBUG
		//MessageBox(NULL, L"Window create", L"Attention", NULL);
#endif // _
		if (!(nextClipboardViewer = (HWND)SetClipboardViewer(clipboardViewer)))
		{
			lastError = GetLastError();
		}
		break;
	case WM_DRAWCLIPBOARD:
		//TODO: Основной код
		if (nextClipboardViewer)
		{
			SendMessage(nextClipboardViewer, uMsg, wParam, lParam);
		}
#ifdef _DEBUG
		MessageBox(NULL, L"Clipboard Updated", NULL, NULL);
#endif // _DEBUG
		break;
	case WM_CHANGECBCHAIN:
		if ((HWND)wParam == nextClipboardViewer)
		{
			nextClipboardViewer = (HWND)lParam;
		}
		else if (!nextClipboardViewer)
		{
			SendMessage(nextClipboardViewer, uMsg, wParam, lParam);
		}
#ifdef _DEBUG
		MessageBox(NULL, L"Chain Change", NULL, NULL);
#endif // _DEBUG
		break;
	case WM_DESTROY:
		ChangeClipboardChain(clipboardViewer, nextClipboardViewer);
		
#ifdef _DEBUG
		MessageBox(NULL, L"Destruct Window", NULL, NULL);
#endif // _DEBUG
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
		
	}
	return 0;
}
