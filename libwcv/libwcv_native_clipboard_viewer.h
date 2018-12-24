#pragma once

#include <Windows.h>
#include <WinUser.h>

// Global variable
static HWND nextClipboardViewer;
static HWND clipboardViewer;
static DWORD lastError;


HWND WINAPI create_clipboard_viewer(LPCWSTR class_name, LPCWSTR window_name = L" ", LPCWSTR window_title = L" ", WNDPROC alt_wnd_proc = NULL) noexcept;
BOOL WINAPI delete_clipboard_viewer() noexcept;
LRESULT CALLBACK clipboard_viewer_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
