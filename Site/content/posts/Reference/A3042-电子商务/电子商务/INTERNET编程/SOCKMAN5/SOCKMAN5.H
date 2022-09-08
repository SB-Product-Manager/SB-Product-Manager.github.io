// SockMan.h
// Function prototypes and symbolic constants

#include "..\winsock.h"							// Winsock header file

// Function prototypes for SOCKMAN.CPP
LONG DoMenuCommand(HWND, UINT, UINT, LONG);
LONG DoWinsockProgram(HWND, UINT, LONG) ;
LONG FAR PASCAL _export WndProc(HWND, UINT, UINT, LONG);
HTASK AsyncGetServiceInfo(HWND, HTASK);

// Function prototypes for COMMON.CPP
BOOL StartWinsock(VOID);
VOID CenterWindow(HWND);
VOID PaintWindow(LPSTR);

// Function prototypes for LOOKUP.CPP
HTASK LookupHostAsync(HWND, LPSTR, LPSTR, LPDWORD);
LPHOSTENT LookupHostBlocking(HWND, LPSTR, LPSTR, HTASK);
LPSTR LookupHostDialog(VOID);
BOOL __export CALLBACK LookupHostDialogProc(HWND, UINT, WPARAM, LPARAM);
void DisplayHostEntry(LPARAM);

// Function prototypes for FINGER.CPP
BOOL FingerDialog(VOID);
BOOL __export CALLBACK FingerDialogProc(HWND, UINT, WPARAM, LPARAM);
BOOL FingerHostAsync(LPARAM);
BOOL FingerHostBlocking(VOID);
VOID LookupFingerHost(LPARAM);
BOOL DoFingerOperation(VOID);

// Function prototypes for TIME.CPP
BOOL TimeServerDialog(VOID);
BOOL _export CALLBACK TimeServerDialogProc(HWND, UINT, WPARAM, LPARAM);
VOID LookupTimeServer(HWND, LPARAM);
LONG TimeServerQuery(HWND hwnd, LPARAM);

// Function prototypes for PING.CPP
BOOL PingDialog(VOID);
BOOL _export CALLBACK PingDialogProc(HWND, UINT, WPARAM, LPARAM);
BOOL DoPingOperation(HWND, LPSTR, PDWORD);
WORD InternetChksum(LPWORD, WORD);

#define WINSOCK_VER_11 			0x0101	// Winsock Version required by SockMan

#define IDM_FILE 						0x01		// Menu Definitions
#define IDM_FILE_CLEAR 			0x11
#define IDM_FILE_PRINT 			0x12
#define IDM_FILE_SAVEAS			0x13
#define IDM_FILE_EXIT 			0x14

#define IDM_APP 						0x02
#define IDM_APP_MAIL 				0x21
#define IDM_APP_FTP 				0x22
 
#define IDM_LOOKUP 					0x03 
#define IDM_LOOKUP_ASYNC 		0x31
#define IDM_LOOKUP_BLOCKING	0x32
 
#define IDM_FINGER 					0x04 
#define IDM_FINGER_ASYNC 		0x41
#define IDM_FINGER_BLOCKING 0x42

#define IDM_TIME 						0x06 
#define IDM_TIME_UTIL				0x61

#define IDM_PING 						0x07
#define IDM_PING_UTIL 			0x70
 
#define IDM_HELP 						0x0F 
#define IDM_HELP_HELP 			0xF1
#define IDM_HELP_ABOUT			0xF2

// Winsock Error Messages
#define MAX_ERR_MESSAGE 		120			// Maximum length for error messages
#define WSASYSNOTREADY_MSG "Underlying network subsystem is not ready for network communication."
#define WSAVERNOTSUPPORTED_MSG "Version of Windows Sockets API support requested is not provided by this particular implementation."
#define WSAEINVAL_MSG "Windows Sockets version specified by application is not supported by this DLL."

// Miscellaneous Definitions
#define MAX_PRINT_BUFFER 		4096		// Maximum length of text to paint
#define MAX_HOST_NAME 			50			// Sockman limit for host name lengths
#define MAX_IP_ADDRESS 			15			// Maximum dotted-decimal address length
#define AF_INET_LENGTH 			4				// Address length for Internet protocols
#define DEFAULT_PROTOCOL 		0				// No protocol specified, use default
#define NO_FLAGS 						0				// No flags specified
#define MAX_USER_NAME 			50			// Maximum length for user name or ID

#define IDC_STATIC 					-1      // Definitions used by SOCKMAN.RC
#define IDC_TEXTBOX 				1000		
#define IDC_FINGER_HOST 		1001
#define IDC_FINGER_USER 		1002
#define IDC_TIMESERVER 			1000
#define IDC_SERVER_TIME			1001
#define IDC_LOCAL_TIME			1002
#define IDC_DIFFERENCE			1003
#define IDSETTIME 					3
#define IDC_PING_HOST   		1000
#define IDC_PING_TIME   		1001
#define IDEXIT							1004

// Sockman generated messages and symbolic constants for task handles
#define WM_ASYNC_LOOKUP_DONE	WM_USER+1
#define WM_BLOCK_LOOKUP_DONE 	WM_USER+2
#define TASK_BLOCK_LOOKUP 		WM_USER+3
#define WM_GOT_SERVICE 				WM_USER+4
#define TASK_ASYNC_FINGER 		WM_USER+5
#define TASK_BLOCK_FINGER 		WM_USER+6
#define TASK_TIMESERVER 			WM_USER+7
#define TASK_PING 						WM_USER+8

// TCP/IP Network Services
#define IPSERVICE_FINGER 			"finger"
#define IPSERVICE_TIME 				"time"

