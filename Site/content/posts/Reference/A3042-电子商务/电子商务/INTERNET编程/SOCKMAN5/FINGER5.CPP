// FINGER.CPP
// Functions used for Finger user information protocol queries.

#include "..\winsock.h"				// Winsock header file
#include "sockman5.h"					// Prototypes and constants
#include "global5.h"					// Global variables

BOOL FingerDialog(VOID)
	{
		DLGPROC lpfnDialogProc;
		BOOL bOkay;

		//	Create a dialog box for the user's entry		
		lpfnDialogProc = MakeProcInstance((DLGPROC)FingerDialogProc,
					hInstanceSockman);
		bOkay = DialogBox(hInstanceSockman,"IDD_FINGER",	hwndSockman,
					lpfnDialogProc);
		FreeProcInstance(lpfnDialogProc);

    if (bOkay == -1)
    	{
				wsprintf(szScratchBuffer, "Unable to create dialog box!");
				MessageBeep(0);
				MessageBox(hwndSockman, szScratchBuffer,
							"SockMan-FINGER QUERY", MB_OK|MB_ICONINFORMATION);
    		bOkay = FALSE;
    	}
			
		return(bOkay);
	}

BOOL _export CALLBACK FingerDialogProc(HWND hwndDlg, UINT iMessage,
			WPARAM wParam, LPARAM	lParam)
	{
		LPSTR lpHost;							// The most recently used host name or address
		
		switch(iMessage)
			{
				case WM_INITDIALOG:		// Initialize the dialog box
					lpHost = lstrlen(szFingerHost) ? szFingerHost : szHostName;
					SetDlgItemText(hwndDlg, IDC_FINGER_HOST, lpHost); 
					SetDlgItemText(hwndDlg, IDC_FINGER_USER, szFingerUser); 
					CenterWindow(hwndDlg);
					return(TRUE);
					
				case WM_CLOSE:				// Close the dialog box
					PostMessage(hwndDlg, WM_COMMAND, IDCANCEL, 0L);
					return(TRUE);
					
				case WM_COMMAND:			// Handle the command buttons 
					switch(wParam)
						{ 
							case IDOK:			// The OK button was clicked
								GetDlgItemText(hwndDlg, IDC_FINGER_HOST,
											(LPSTR)szFingerHost, MAX_HOST_NAME);
								GetDlgItemText(hwndDlg, IDC_FINGER_USER,
											(LPSTR)szFingerUser, MAX_USER_NAME);
								lstrcpy(szLookupText, szFingerHost);
								EndDialog(hwndDlg, TRUE);
								return(TRUE);
								
							case IDCANCEL:	// The Cancel button was clicked
								EndDialog(hwndDlg, FALSE);
								return(TRUE);
						}
					break;
			}
		return(FALSE);
	}

VOID LookupFingerHost(LPARAM lError)
	{
		// Sockman uses WSAAsyncGetServByName to fill szFingerBuffer with 
		// the service entry information. The function extracts the finger 
		// service port from szFingerBuffer before reusing the buffer to 
		// store the host entry information.

		if (WSAGETASYNCERROR(lError)) 
			nFingerPort = htons(IPPORT_FINGER);
		else
			nFingerPort = ((LPSERVENT)szFingerBuffer)->s_port;

		hFingerTask = LookupHostAsync(hwndSockman, szFingerHost, 
					szFingerBuffer, (LPDWORD)&dwFingerAddr);
				
		if (!hFingerTask)
			{
				wsprintf(szFingerBuffer, "Unable to lookup: %s", 
							(LPSTR)szFingerHost);
				MessageBeep(0);
				MessageBox(hwndSockman, szFingerBuffer, "SockMan - FINGER",
							MB_OK|MB_ICONSTOP);
			}
		return;
	}
		
BOOL FingerHostAsync(LPARAM lError)
	{
		int nErr;											// Error code from asynchronous lookup

    if (nErr = WSAGETASYNCERROR(lError)) 
			{
				MessageBeep(0);
				PaintWindow("Async lookup failed! Trying a blocking finger.");
				hFingerTask = TASK_BLOCK_FINGER;
				FingerHostBlocking();
				hFingerTask = 0;
				return(FALSE);
			}
			
		// All data required to perform the Finger query is available so do it.
		return(DoFingerOperation());	
	}
			
BOOL FingerHostBlocking(VOID)
	{
		LPSERVENT lpServiceEntry;				// Service information structure

		if (!LookupHostBlocking(hwndSockman, szFingerHost,
					(LPSTR)&szFingerBuffer, TASK_BLOCK_FINGER))
			return(FALSE);								// Failed to resolve the host address
		                                      
		// If getservbyname() fails, use the well-known port.
		if ((lpServiceEntry = getservbyname("finger", NULL)) == NULL)
			nFingerPort = htons(IPPORT_FINGER);	
		else
			nFingerPort = lpServiceEntry->s_port;
		
		// All data required to perform the Finger query is available so do it.	
		return(DoFingerOperation());
	}

BOOL DoFingerOperation(VOID)
	{
		PHOSTENT pHostEntry;					// Internet host information structure
		SOCKET nSocket;								// Socket number used by this program
		SOCKADDR_IN sockAddr;					// Socket address structure
		int nErr;											// Error code
		int nCharSent;								// Number of characters received
		int nCharRecv;								// Number of characters transmitted
		BOOL bOkay = FALSE;						// Status code for the Finger operation
		int nLength = 0;							// Length of returned Finger information
		
		// Data buffers 
		char szUser[MAX_HOST_NAME+MAX_USER_NAME+3];	// Finger query buffer
		char szFingerInfo[MAX_PRINT_BUFFER+1];			// Finger results buffer

		if ((nSocket = socket(PF_INET, SOCK_STREAM, DEFAULT_PROTOCOL)) !=
					INVALID_SOCKET)
			{
				pHostEntry = (PHOSTENT)szFingerBuffer;
				
				sockAddr.sin_family = AF_INET;					// Internet Address family
				sockAddr.sin_port = nFingerPort;
				sockAddr.sin_addr = *((LPIN_ADDR)*pHostEntry->h_addr_list);
				
				if (!connect(nSocket, (SOCKADDR *)&sockAddr, sizeof(sockAddr)))
					{
						wsprintf(szUser, "%s\r\n", (LPSTR)szFingerUser);
						
						if ((nCharSent = send(nSocket, szUser, lstrlen(szUser), 
									NO_FLAGS)) != SOCKET_ERROR)
							{
								do
									{
										nCharRecv = recv(nSocket,(LPSTR)&szFingerInfo[nLength],
													sizeof(szFingerInfo) - nLength, NO_FLAGS);
										nLength+=nCharRecv;
									}
								while (nCharRecv > 0);
										
								closesocket(nSocket);
						
								if (nCharRecv != SOCKET_ERROR)
									{
										// Null terminate the Finger buffer
										szFingerInfo[nLength] = '\0';	
										// Set the Scratch buffer to zero length
										szScratchBuffer[0] = '\0';		
											
										wsprintf(szScratchBuffer, "FINGER:\t%s@%s\n\n", 
													(LPSTR)szFingerUser, (LPSTR)szFingerHost);
										lstrcat(szScratchBuffer, szFingerInfo);
										PaintWindow(szScratchBuffer);
										MessageBeep(0);
										bOkay = TRUE;
									}
							}
					}
			}
		
		if (!bOkay)	
			{
				nErr = WSAGetLastError();
				closesocket(nSocket);
				wsprintf(szFingerInfo, "Error number %d", nErr);
				MessageBeep(MB_ICONSTOP);
				MessageBox(hwndSockman, szFingerInfo, "Finger Operation",
							MB_OK|MB_ICONSTOP);
			}
		return(bOkay);
	}
