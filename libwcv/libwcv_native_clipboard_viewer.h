#pragma once

#include <Windows.h>
#include <WinUser.h>
#include <psapi.h>
#include <iostream>

using namespace std;

//
typedef
struct tagCustomWindowInfo
{
	HWND		pWindowHandle;
	LPCWSTR		pWindowCaption;
	LPCWSTR		pWindowClass;
}CUSTOMWINDOWINFO, *LPCUSTOMWINDOWINFO;

typedef
struct tagClipboardOwnerInfo
{
	LPCWSTR		ClipboardOwnerWindowTitle;
	HWND		ClipboardOwnerWindowHandle;
	LPCWSTR		ClipboardOwnerProcName;
	HANDLE		ClipboardOwnerProcHandle;
	LONG		ClipboardOwnerProcId;
	LPCWSTR		ClipboardOwnerModuleName;
	DWORD		ClipboardOwnerThreadId;
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
static HWND			nextClipboardViewer;
static HWND			clipboardViewer;
static DWORD		lastError;
static HINSTANCE	hInstance;
static LPCWSTR		windowClassName;

//
static CLIPBOARDOWNERINFOSTRUCT	ClipboardOwnerInfo;
static CLIPBOARDDATASTRUCT		ClipboardData;



HWND WINAPI create_clipboard_viewer(LPCWSTR class_name, LPCWSTR window_name = L" ", LPCWSTR window_title = L" ", WNDPROC alt_wnd_proc = NULL) noexcept;

BOOL WINAPI destroy_clipboard_viewer() noexcept;

LRESULT CALLBACK clipboard_viewer_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL WINAPI get_clipboard_owner_info(CLIPBOARDOWNERINFOSTRUCT * clipboard_owner_info) noexcept;

BOOL CALLBACK clipboard_viewer_enum_windows_proc(HWND hWnd, LPARAM lParam) noexcept;
//

