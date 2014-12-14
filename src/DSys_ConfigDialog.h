/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:02 $
	$Id: DSys_ConfigDialog.h,v 1.3 2004/07/31 19:22:02 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___D_STARTUPDIALOG_H
#define ___D_STARTUPDIALOG_H

namespace DSys {

	class ConfigDialog
	{
			static char	*controlsString;

			static BOOL CALLBACK ConfigDialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);
		public:
			static bool Show();
	};

}// end of namespace


#endif // ___D_STARTUPDIALOG_H