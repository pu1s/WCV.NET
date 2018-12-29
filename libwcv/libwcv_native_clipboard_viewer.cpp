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

BOOL __stdcall get_clipboard_owner_info(CLIPBOARDOWNERINFOSTRUCT * clipboard_owner_info) noexcept
{
	BOOL		result;
	DWORD		proc_id;
	DWORD		thread_id;
	HWND		clipboard_owner_window_handle;
	HWND		next_window;
	HINSTANCE	hinst;
	TCHAR		proc_name[MAX_PATH] = { 0 };
	HANDLE		proc_handle;
	int			window_title_length;
	TCHAR		window_title[MAX_PATH] = { 0 };

	//
	clipboard_owner_window_handle = (HWND)GetClipboardOwner();
	if (!clipboard_owner_window_handle)
	{
		lastError = GetLastError();
		return 0;
	}
	if (!(IsWindow(clipboard_owner_window_handle)))

	{
		SetLastError(1400);
		lastError = GetLastError();
		return 0;
	}

	/*if (!(IsWindowVisible(clipboard_owner_window_handle)))
	{
		wcout << L"Window not visible" << endl;
	}
*/
	
	//
	thread_id = GetWindowThreadProcessId(clipboard_owner_window_handle, &proc_id);

	//
	proc_handle = (HANDLE)OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, proc_id);
	
	GetProcessImageFileName(proc_handle, proc_name, MAX_PATH);
	CloseHandle(proc_handle);
	
	window_title_length = GetWindowTextLength(clipboard_owner_window_handle);

	WINDOWINFO* wi = new WINDOWINFO();

	if (GetWindowText(clipboard_owner_window_handle, window_title, window_title_length + 1) == 0)
	{
		//EnumChildWindows(clipboard_owner_window_handle, clipboard_viewer_enum_child_windows_proc, 0);
	}
	//next_window = (HWND)GetWindowLongPtr(clipboard_owner_window_handle, GWLP_HWNDPARENT);

	next_window = (HWND)GetWindowLong(clipboard_owner_window_handle, GWLP_HWNDPARENT);
	window_title_length = GetWindowTextLength(next_window);

	GetWindowText(next_window, window_title, MAX_PATH);

	//
	clipboard_owner_info->ClipboardOwnerModuleName		= proc_name;
	clipboard_owner_info->ClipboardOwnerProcHandle		= proc_handle;
	clipboard_owner_info->ClipboardOwnerProcId			= proc_id;
	clipboard_owner_info->ClipboardOwnerWindowHandle	= clipboard_owner_window_handle;
	clipboard_owner_info->ClipboardOwnerThreadId		= thread_id;
	clipboard_owner_info->ClipboardOwnerWindowTitle		= window_title;

	//CUSTOMWINDOWINFO* wi = new CUSTOMWINDOWINFO();
	if (EnumWindows(clipboard_viewer_enum_windows_proc, (LPARAM)proc_id))
		wcout << L"Houp" << endl;
	wcout << L"True" << endl;
	return 0;
}

BOOL clipboard_viewer_enum_windows_proc(HWND hWnd, LPARAM lParam) noexcept
{
	DWORD procid, tid, pid;
	pid = (DWORD)lParam;
	GetWindowThreadProcessId(hWnd, &procid);
	if (procid == pid) 
	{ 
		wcout << hWnd <<L" :" << procid << endl;
		wcout << L"Yes" << endl;
		return FALSE; 
	}
	return TRUE;
}

BOOL clipboard_viewer_enum_child_windows_proc(HWND hWnd, LPARAM lParam) noexcept
{
	wcout << L"Call Child Yes" << endl;
	return FALSE;
}
