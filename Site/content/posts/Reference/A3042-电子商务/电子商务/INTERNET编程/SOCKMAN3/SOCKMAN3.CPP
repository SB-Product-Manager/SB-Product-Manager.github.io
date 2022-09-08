// SockMan.CPP
// Winsock Program Manager
// A programming template and shell for Windows Sockets programmers.

#include "..\winsock.h"													// Winsock header file
#include "sockman3.h"														// Prototypes and constants

//	Global Sockman variables
HWND hwndSockman;																// Sockman window handle
HANDLE hInstanceSockman;												// Sockman instance handle
char szAppName[9];															// Application name
char szPrintBuffer[MAX_PRINT_BUFFER+1];					// Buffer for text to paint
char szScratchBuffer[MAX_PRINT_BUFFER+1];				// General purpose buffer

// Global variables for DNS lookup operations
char szHostName[MAX_HOST_NAME+1];								// Host name
char szIPAddress[MAX_IP_ADDRESS+1];							// Dotted-decimal address
char szLookupText[MAX_HOST_NAME+1];							// Buffer for lookup text
char szLookupBuffer[MAXGETHOSTSTRUCT];					// Buffer for host data
HTASK hAsyncLookupTask;													// Asynchronous task handle
DWORD dwLookupAddr;															// 32-bit binary IP address

// Global variables for the Finger utility
HTASK hFingerTask;															// Finger task handle
DWORD dwFingerAddr;															// 32-bit binary IP address
int nFingerPort;																// The finger protocol port
char szFingerHost[MAX_HOST_NAME+1];							// Host to query
char szFingerUser[MAX_USER_NAME+1];							// User ID for the query
char szFingerBuffer[MAXGETHOSTSTRUCT];					// Buffer for host data

int PASCAL WinMain(HANDLE	hInstance, HANDLE	hPrevInstance,
			LPSTR lpszCmdLine, int nCmdShow)
	{
		MSG msg;
		WNDCLASS wndclass;
				
		hInstanceSockman = hInstance;
		lstrcpy(szAppName, "SockMan");
		szPrintBuffer[0] = '\0';
		hFingerTask = 0;
						
		if (!hPrevInstance) 
			{
				wndclass.style					= CS_HREDRAW | CS_VREDRAW;
				wndclass.lpfnWndProc		= WndProc;
				wndclass.cbClsExtra			= 0;
				wndclass.cbWndExtra			= 0;
				wndclass.hInstance			= hInstance;
				wndclass.hIcon					= LoadIcon(hInstance, szAppName);
				wndclass.hCursor				= LoadCursor(NULL, IDC_ARROW);
				wndclass.hbrBackground 	= GetStockObject(WHITE_BRUSH);
				wndclass.lpszMenuName		= szAppName;
				wndclass.lpszClassName 	= szAppName;
				
				if (!RegisterClass(&wndclass))
					return FALSE;
			}
			
		hwndSockman = CreateWindow
					(
						szAppName, 
						"SockMan rev. 3",
						WS_OVERLAPPEDWINDOW	| WS_VSCROLL | WS_HSCROLL,	
						CW_USEDEFAULT, 
						CW_USEDEFAULT,
						CW_USEDEFAULT, 
						CW_USEDEFAULT,
						NULL, 
						NULL, 
						hInstance, 
						NULL
					);
				
		if (!hwndSockman)
			return FALSE;
				
		ShowWindow(hwndSockman, nCmdShow);
		UpdateWindow(hwndSockman);
		if( StartWinsock())
			{
				while(GetMessage(&msg, NULL, 0, 0))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
			}
		WSACleanup();			
		return(msg.wParam);
	}

long FAR PASCAL _export WndProc(HWND hwnd, UINT iMessage, UINT wParam,
			LONG lParam)
	{
		switch (iMessage)
			{				
				case WM_PAINT:
					PAINTSTRUCT ps;
					HDC hdc;
					RECT rect;
					
					hdc = BeginPaint( hwnd, &ps);
					
					GetClientRect(hwndSockman, &rect);
					DrawText(hdc, szPrintBuffer, -1, &rect,
								DT_EXPANDTABS|DT_WORDBREAK);
					EndPaint(hwnd, &ps);
					return(0);
				
				case WM_COMMAND:
					if (DoMenuCommand(hwnd, iMessage, wParam, lParam))
						return(0);
					else
						break;
		
				case WM_DESTROY :
					PostQuitMessage(0);
					return(0);

				case WM_GOT_SERVICE:
					if (wParam == hFingerTask)
						LookupFingerHost(lParam);
					return(0);
					
				case WM_ASYNC_LOOKUP_DONE:
					if (wParam == hAsyncLookupTask)
						DisplayHostEntry(lParam);

					if (wParam == hFingerTask)
						{
							PaintWindow("Asynchronous lookup for Finger completed.");
							FingerHostAsync(lParam);
							hFingerTask = 0;
						}
					return(0);

				case WM_BLOCK_LOOKUP_DONE:
					if (wParam == TASK_BLOCK_LOOKUP)
						DisplayHostEntry(lParam);
						
					if (wParam == TASK_BLOCK_FINGER)
						PaintWindow("Blocking lookup for Finger completed.");
					return(0);
			}
			
		return(DefWindowProc(hwnd, iMessage, wParam, lParam));
	}
					
long	DoMenuCommand(HWND hwnd, UINT iMessage, UINT wParam, LONG lParam)
	{
		switch (wParam)
			{
				case IDM_FILE_CLEAR:
					szPrintBuffer[0]='\0';
					InvalidateRect(hwndSockman, NULL, TRUE);
					UpdateWindow(hwndSockman);
					return(TRUE);
					
				case IDM_FILE_PRINT:
				case IDM_FILE_SAVEAS:
					PaintWindow((LPSTR) "File functions are not yet implemented!");
					MessageBeep(0);
					MessageBox(hwnd, "File functions are not yet implemented!",
								szAppName, MB_ICONEXCLAMATION | MB_OK);
					return(TRUE);
								
				case IDM_FILE_EXIT:
					SendMessage(hwnd, WM_CLOSE, 0, 0L);
					return(TRUE);
								
				case IDM_HELP_HELP:
					MessageBeep(0);
					MessageBox(hwnd, "Help is not yet implemented!", szAppName,
								MB_ICONEXCLAMATION | MB_OK);
					return(TRUE);
								
				case IDM_HELP_ABOUT:
					MessageBox(hwnd,
								"A programming shell for Windows Sockets programmers.",
								"SockMan - Winsock Program Manager rev. 3", 
								MB_ICONINFORMATION | MB_OK);
					return(TRUE);
							
				default:
					return(DoWinsockProgram(hwnd, wParam, lParam));
			}
	}

long DoWinsockProgram(HWND hwnd, UINT wParam, LONG lParam)
	{
		switch (wParam)
			{
				case IDM_APP_MAIL:
				case IDM_APP_FTP:
					MessageBeep(0);
					MessageBox(hwnd, "No APPLICATIONS are currently implemented!",
								szAppName, MB_ICONEXCLAMATION | MB_OK);
					return(TRUE);
					
				case IDM_LOOKUP_ASYNC:
				case IDM_LOOKUP_BLOCKING:
					if (LookupHostDialog())
						{
							if (wParam == IDM_LOOKUP_ASYNC)
								hAsyncLookupTask = LookupHostAsync(hwnd, szLookupText,
											szLookupBuffer, (LPDWORD)&dwLookupAddr);
							else
								LookupHostBlocking(hwnd, szLookupText, szLookupBuffer,
											TASK_BLOCK_LOOKUP);
						}
					return(TRUE);
					
				case IDM_FINGER_ASYNC:
				case IDM_FINGER_BLOCKING:
					if (hFingerTask)	// Sockman only allows 1 Finger call at a time
						{
							MessageBeep(0);
							MessageBox(hwnd,
										"Finger utility is already in use. Please wait...",
										"SockMan - FINGER", MB_ICONSTOP | MB_OK);
						}
					else if (FingerDialog())
						{
							if (wParam == IDM_FINGER_ASYNC)
								hFingerTask = AsyncGetServiceInfo(hwnd, TASK_ASYNC_FINGER);
							else
								{
									hFingerTask = TASK_BLOCK_FINGER;
									FingerHostBlocking();
									hFingerTask = 0;
								}
						}
					return(TRUE);
					
				case IDM_TIME_UTIL:
					MessageBeep(0);
					MessageBox(hwnd, "The TIME utility is not yet implemented!",
								szAppName, MB_ICONEXCLAMATION | MB_OK);
					return(TRUE);
					
				case IDM_PING_UTIL:
					MessageBeep(0);
					MessageBox(hwnd, "The PING utility is not yet implemented!",
								szAppName, MB_ICONEXCLAMATION | MB_OK);
					return(TRUE);
			}
		return(FALSE);
	}

HTASK AsyncGetServiceInfo(HWND hwnd, HTASK hService)
	{
		// Store the task handle from WSAAsyncGetServByName
		HTASK hTask = WSAAsyncGetServByName(hwnd,WM_GOT_SERVICE,
					(LPSTR)IPSERVICE_FINGER, NULL, (LPSTR)szFingerBuffer, 
					sizeof(szFingerBuffer));
				
		if (!hTask)
			{
				LPARAM	lParam;
				
				hTask = hService;														// Return the service ID
				lParam = MAKELONG(0, WSAGetLastError());	// Log the error code
				PostMessage(hwnd, WM_GOT_SERVICE, hService, lParam);
			}
		return(hTask);
	}
