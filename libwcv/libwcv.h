#pragma once

#include "wcv_custom_marshaler.h"

using namespace System;

namespace libwcv
{
	public ref class testclass
	{
	public:
		
		System::IntPtr^ mh;
		HWND uh;
		void testfunc(void)
		{
			/*mh = gcnew IntPtr();
			uh = (HWND)MarshalAs<IntPtr^, HWND>(mh);
			mh = MarshalAs<HWND, IntPtr^>(uh);
			MarshalAs<IntPtr^, HWND>(mh, uh);
			MarshalAs<HWND, IntPtr^>(uh, mh);*/
			mh = TO_MHWND(uh);
			//mh = MarshalAs<UHWND, MHWND>(uh);
		}

	};
}
