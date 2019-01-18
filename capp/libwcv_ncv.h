#pragma once
#include "libwcv_includes.h"
#include <WinUser.h>
//typedef WNDPROC 





class libwcv_ncv
{
public:

	libwcv_ncv();
	~libwcv_ncv();
	static VOID bla(HWND, UINT, WPARAM, LPARAM)
	{}
	
};


	//(LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM))&libwcv_ncv::bla;
