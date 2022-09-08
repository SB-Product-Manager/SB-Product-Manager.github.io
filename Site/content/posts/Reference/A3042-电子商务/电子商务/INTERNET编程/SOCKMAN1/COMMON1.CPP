// COMMON.CPP
// Commonly used application functions.

#include	"..\winsock.h"								// Winsock header file
#include	"sockman1.h"									// Prototypes and constants
#include	"global1.h"										// Global variables

BOOL StartWinsock(VOID)
	{
		WSADATA wsaData;										// Winsock implementation details
  	UINT iErr;													// Error number
    char szErrMessage[MAX_ERR_MESSAGE];	// Error message buffer

    if (iErr = WSAStartup(WINSOCK_VER_11, &wsaData))
    	{
				MessageBeep(0);
				
    		switch(iErr)
    			{
    				case	WSASYSNOTREADY:
    					lstrcpy(szErrMessage, WSASYSNOTREADY_MSG);
    					break;
							
    				case	WSAVERNOTSUPPORTED:
    					lstrcpy(szErrMessage, WSAVERNOTSUPPORTED_MSG);
    					break;
    					
    				case	WSAEINVAL:
							lstrcpy(szErrMessage, WSAEINVAL_MSG);
    					break;
    			}
	      MessageBox(NULL, szErrMessage, "SockMan", MB_OK|MB_ICONSTOP);
		    return(FALSE);
	  	}
	  else
	  	PaintWindow(wsaData.szDescription);
	  	
	  return(TRUE);
	}
	
VOID CenterWindow(HWND hWnd)
	{
		POINT point;												// Structure for x-y coordinates
	  RECT rect;													// Rectangle coordinates structure
	  RECT rectMainWindow;								// Main window rectangle coordinates
	  int nWidth;													// Rectangle width
	  int nHeight;												// Rectangle height
	
	  GetWindowRect(hWnd, &rect);
	  GetClientRect(hwndSockman, &rectMainWindow);
	  nWidth = rect.right - rect.left;
	  nHeight = rect.bottom - rect.top;
	  point.x = (rectMainWindow.right - rectMainWindow.left) / 2;
	  point.y = (rectMainWindow.bottom - rectMainWindow.top) / 2;
	  ClientToScreen(hwndSockman, &point);
	  point.x = point.x - (nWidth / 2);
	  point.y = point.y - (nHeight / 2);
	  MoveWindow(hWnd, point.x, point.y, nWidth, nHeight, FALSE);
	  
		return;
	}

VOID	PaintWindow(LPSTR lpszTxt)
	{
		int	nTxtLen;                        // Length of text to paint
 		
		nTxtLen = lstrlen(lpszTxt);
		
		//	Make sure the text doesn't exceed the buffer's limit 				                        
		if (nTxtLen > MAX_PRINT_BUFFER)
				*(lpszTxt+(MAX_PRINT_BUFFER - 1)) = '\0';
			
		wsprintf(szPrintBuffer, "%s", (LPSTR)lpszTxt);
		
		InvalidateRect(hwndSockman, NULL, TRUE);
		UpdateWindow(hwndSockman);              
		
		return;
	}
