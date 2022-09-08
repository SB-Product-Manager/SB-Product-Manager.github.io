// SockMan.CPP
// Winsock Program Manager
// A programming template and shell for Windows Sockets programmers.

#include "..\winsock.h"													// Winsock header file
#include "sockman1.h"														// Prototypes and constants

//	Global Sockman variables
HWND hwndSockman;																// Sockman window handle
HANDLE hInstanceSockman;												// Sockman instance handle
char szAppName[9];															// Application name
char szPrintBuffer[MAX_PRINT_BUFFER+1];					// Buffer for text to paint

int PASCAL WinMain(HANDLE	hInstance, HANDLE	hPrevInstance,
			LPSTR lpszCmdLine, int nCmdShow)
	{
		MSG msg ;
		WNDCLASS wndclass ;
                            
		hInstanceSockman = hInstance;
		lstrcpy(szAppName, "SockMan");
		szPrintBuffer[0] = '\0';

		if (!hPrevInstance) 
			{
				wndclass.style					= CS_HREDRAW | CS_VREDRAW;
				wndclass.lpfnWndProc		= WndProc;
				wndclass.cbClsExtra			= 0;
				wndclass.cbWndExtra			= 0;
				wndclass.hInstance			= hInstance;
				wndclass.hIcon					= LoadIcon(hInstance, szAppName);
				wndclass.hCursor				= LoadCursor(NULL, IDC_ARROW);
				wndclass.hbrBackground	= GetStockObject(WHITE_BRUSH);
				wndclass.lpszMenuName		= szAppName;
				wndclass.lpszClassName 	= szAppName;

				if (!RegisterClass(&wndclass))
					return FALSE;
			}

		hwndSockman = CreateWindow
					(
						szAppName, 
						"SockMan rev. 1",
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
					HDC hdc ;
					RECT rect ;

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
					return(0) ;
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
								"SockMan - Winsock Program Manager rev. 1", 
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
					MessageBeep(0);
					MessageBox(hwnd, "The LOOKUP utility is not yet implemented!",
								szAppName, MB_ICONEXCLAMATION | MB_OK);
					return(TRUE);

				case IDM_FINGER_ASYNC:
				case IDM_FINGER_BLOCKING:
					MessageBeep(0);
					MessageBox(hwnd, "The FINGER utility is not yet implemented!",
								szAppName, MB_ICONEXCLAMATION | MB_OK);
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
