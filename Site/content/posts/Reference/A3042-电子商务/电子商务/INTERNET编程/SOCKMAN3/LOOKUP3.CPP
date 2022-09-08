// LOOKUP.CPP
// These functions resolve Internet (DNS) host names and IP addresses.

#include <memory.h>												// Includes prototype for _fmemcpy()
#include "..\winsock.h"										// Winsock header file
#include "sockman3.h"											// Prototypes and constants
#include "global3.h"											// Global variables

LPSTR LookupHostDialog(VOID)
	{
		// The dialog procedure uses the global static buffer szLookupText
		// to store the user's entry from the text box. Callers should copy
		// this value to their own locally allocated buffer since buffer
		// szLookupText could be immediately reused by another program
		// doing a host lookup.
		
		DLGPROC	lpfnDialogProc;
		BOOL bOkay;

		// Create a dialog box for the user's entry		
		lpfnDialogProc = MakeProcInstance((DLGPROC)LookupHostDialogProc,
					hInstanceSockman);
		bOkay = DialogBox(hInstanceSockman,"IDD_TEXT",	hwndSockman,
					lpfnDialogProc);
		FreeProcInstance(lpfnDialogProc);

    if (bOkay == -1)
    	{
				wsprintf(szScratchBuffer, "Unable to create dialog box!");
				MessageBeep(0);
				MessageBox(hwndSockman, szScratchBuffer,
							"SockMan-HOST LOOKUP", MB_OK|MB_ICONINFORMATION);
    		bOkay = FALSE;
    	}
			
		return(bOkay ? szLookupText : (LPSTR) NULL);
	}

BOOL _export CALLBACK LookupHostDialogProc(HWND hwndDlg, UINT iMessage,
			WPARAM wParam, LPARAM lParam)
	{
		switch (iMessage)
			{
				case WM_INITDIALOG:		// Initialize the dialog box
					SetDlgItemText(hwndDlg, IDC_TEXTBOX, (LPSTR)szLookupText ); 
					SetWindowText(hwndDlg, "Enter HOST Name or IP Address");
					CenterWindow(hwndDlg);
					return(TRUE);
					
				case WM_CLOSE:				// Close the dialog box
					PostMessage(hwndDlg, WM_COMMAND, IDCANCEL, 0L);
					return(TRUE);
					
				case WM_COMMAND:			// Handle command buttons
					switch (wParam)
						{ 
							case IDOK:			// The OK button was clicked
								GetDlgItemText(hwndDlg, IDC_TEXTBOX, (LPSTR)szLookupText,
											MAX_HOST_NAME);
								EndDialog(hwndDlg, TRUE);
								return(TRUE);
								
							case IDCANCEL:	// The Cancel command button was clicked
								EndDialog(hwndDlg, FALSE);
								return(TRUE);
						}
					break;
			}
		return(FALSE);
	}

HTASK	LookupHostAsync(HWND hwnd, LPSTR szUserEntry, LPSTR szHostEntryBuffer,
			LPDWORD	lpdwAddr)
	{
		HTASK hTask;														// Asynchronous task handle
		
		//	Assume a dotted-decimal address and try to convert
		if ((*lpdwAddr = inet_addr(szUserEntry)) == INADDR_NONE)
			{
				lstrcpy(szHostName, szUserEntry);		// Store the host name
				hTask = WSAAsyncGetHostByName(hwnd, WM_ASYNC_LOOKUP_DONE,
							szUserEntry, szHostEntryBuffer, MAXGETHOSTSTRUCT);
			}
		else
			{
				lstrcpy(szIPAddress, szUserEntry);	// Store the host address
				hTask = WSAAsyncGetHostByAddr(hwnd, WM_ASYNC_LOOKUP_DONE,
							(LPCSTR)lpdwAddr, AF_INET_LENGTH, AF_INET,
							szHostEntryBuffer, MAXGETHOSTSTRUCT);
			}
		return(hTask);													// Return the task handle
	}

LPHOSTENT LookupHostBlocking(HWND hwnd, LPSTR szUserEntry, LPSTR szHostEntryBuffer,
			HTASK hTask)
	{
		LPARAM lParam;					// Windows message parameter for error reporting
		DWORD dwIPAddr;					// IP address as an unsigned long
		LPHOSTENT lpHostEntry;	// Pointer to an Internet host data structure
		
		lpHostEntry = NULL;
					
		// Assume a dotted-decimal address and try to convert
		if( (dwIPAddr = inet_addr(szUserEntry)) == INADDR_NONE)
			{
				// If it wasn't a dotted-decimal address, assume it's a host name
				if ((lpHostEntry = gethostbyname(szUserEntry)) == NULL)
					{
						MessageBeep(0);
						MessageBox(NULL, "Could not get host name.", szUserEntry,
									MB_OK|MB_ICONSTOP);
					}
			}
		else	// Resolve the IP address
			{
				if ((lpHostEntry = gethostbyaddr((LPCSTR) &dwIPAddr, 
							AF_INET_LENGTH, AF_INET)) == NULL)
					{
						MessageBeep(0);
						MessageBox(NULL, "Could not get IP address.", szUserEntry,
									MB_OK|MB_ICONSTOP);
					}
			}

		// If the host entry is valid, copy it to the global
		// variable before calling any other Winsock functions
		if (lpHostEntry)
			{
				_fmemcpy(szHostEntryBuffer, lpHostEntry, sizeof(HOSTENT));
				lParam = 0L;	// Set lParam to zero, which indicates no errors
			}
		else
			// Get the error value and store it in the hi-word of lParam
			lParam = MAKELONG(0, WSAGetLastError());

		// Tell Windows to send a message indicating the operation is complete
		SendMessage(hwnd, WM_BLOCK_LOOKUP_DONE, hTask, lParam);

		// If valid, return a pointer to the host entry, otherwise return NULL
		return(lpHostEntry ? (LPHOSTENT)szHostEntryBuffer : (LPHOSTENT)NULL);
	}

VOID	DisplayHostEntry(LONG lParam)
	{
		int nErrCode;												// Error code from the DNS resolver
		
		if (nErrCode = WSAGETASYNCERROR(lParam)) 
			{ 
				wsprintf(szScratchBuffer, "%s LOOKUP caused Winsock ERROR No. %d",
							(LPSTR)szLookupText, nErrCode);
				MessageBeep(0);
				MessageBox(NULL, szScratchBuffer, szLookupText, MB_OK|MB_ICONSTOP);
				//	Set the lookup buffer to NULL when an error occurs.
				szLookupBuffer[0] = '\0';	
			}
		else
			{
				LPHOSTENT lpHostEntry;
				
				lpHostEntry = (LPHOSTENT) szLookupBuffer;
				lstrcpy(szHostName, lpHostEntry->h_name);
				lstrcpy(szIPAddress,
							inet_ntoa(*(LPIN_ADDR)*(lpHostEntry->h_addr_list)));
				wsprintf(szScratchBuffer,
							"%s\tLOOKUP RESULTS\nHost Name:\t%s\nIP Address:\t%s",
							(LPSTR)szLookupText, (LPSTR)szHostName, (LPSTR)szIPAddress);
			}
		PaintWindow(szScratchBuffer);
		MessageBeep(0);
		return;
	}
