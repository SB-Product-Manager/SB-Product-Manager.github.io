// server.h : main header file for the SERVER application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

// START CUSTOM CODE: Internet Programming
#include "..\winsock.h"

const int WINSOCK_VERSION = 0x0101;		// Required Winsock version 1.1
const int DEFAULT_PROTOCOL  = 0;			// No protocol specified, use default
const int NO_FLAGS = 0;								// No special flags specified
const int MAX_COLUMNS = 80;						// Maximum columns for text display
const int QUEUE_SIZE = 5;							// Maximum number of incoming 
																			// connections to queue
// Server-defined application messages
const int WM_SERVER_ACCEPT = WM_USER+1;
const int WM_CLIENT_CLOSE = WM_USER+2;
const int WM_CLIENT_READ = WM_USER+3;
// END MODIFICATIONS: Internet Programming

/////////////////////////////////////////////////////////////////////////////
// CServerApp:
// See server.cpp for the implementation of this class
//

class CServerApp : public CWinApp
{
private:
	// START CUSTOM CODE: Internet Programming
 	char chMsgBuffer[100]; 
	// END MODIFICATIONS: Internet Programming

public:
	// START CUSTOM CODE: Internet Programming
	WSADATA wsaData;
	// END MODIFICATIONS: Internet Programming
	CServerApp();

// Overrides

	// START CUSTOM CODE: Internet Programming
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	// END MODIFICATIONS: Internet Programming

// Implementation

	//{{AFX_MSG(CServerApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
