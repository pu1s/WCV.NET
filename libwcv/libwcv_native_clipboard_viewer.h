#pragma once

#include <Windows.h>
#include <WinUser.h>

//
typedef
struct tagClipboardOwnerInfo
{
	LPCWSTR		ClipboardOwnerWindowTitle;
	HWND		ClipboardOwnerWindowHandle;
	LPCWSTR		ClipboardOwnerProcName;
	HWND		ClipboardOwnerProcHandle;
	LONG		ClipboardOwnerProcId;
	LPCWSTR		ClipboardOwnerModuleName;
}CLIPBOARDOWNERINFOSTRUCT;

//
typedef
struct tagClipboardData
{
	UINT		ClipboardDataFormat;
	void*		ClipboardData;
	size_t		ClipboardDataSize;
}CLIPBOARDDATASTRUCT;

// Global variable
static HWND		nextClipboardViewer;
static HWND		clipboardViewer;
static DWORD	lastError;
//
static CLIPBOARDOWNERINFOSTRUCT	ClipboardOwnerInfo;
static CLIPBOARDDATASTRUCT		ClipboardData;


HWND WINAPI create_clipboard_viewer(LPCWSTR class_name, LPCWSTR window_name = L" ", LPCWSTR window_title = L" ", WNDPROC alt_wnd_proc = NULL) noexcept;
BOOL WINAPI destroy_clipboard_viewer() noexcept;
LRESULT CALLBACK clipboard_viewer_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
