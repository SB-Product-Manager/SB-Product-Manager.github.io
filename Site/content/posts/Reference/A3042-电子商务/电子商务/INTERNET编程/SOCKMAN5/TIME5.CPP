//	TIME.CPP
//	Functions used for timer server queries

#include <time.h>											// Includes PC time structures
#include <dos.h>											// Required by time structures
#include	"..\winsock.h"							// Winsock header file
#include	"sockman5.h"								// Prototypes and constants
#include	"global5.h"									// Global variables

#define PC_REF_TIME 2208988800L				// 1 January 1970

BOOL TimeServerDialog(VOID)
	{
    DLGPROC lpfnDialogProc;						// Pointer to the dialog procedure
    BOOL bOkay;												// Return value from the dialog

		//	Create a dialog box for the user's entry    
    lpfnDialogProc = MakeProcInstance((DLGPROC)TimeServerDialogProc,
    			hInstanceSockman);
    bOkay = DialogBox(hInstanceSockman, "IDD_TIMESERVER",  hwndSockman,
    			lpfnDialogProc);
    FreeProcInstance(lpfnDialogProc);
    
    if (bOkay == -1)
    	{
				wsprintf(szScratchBuffer, "Unable to create dialog box!");
				MessageBeep(0);
				MessageBox(hwndSockman, szScratchBuffer,
							"SockMan-TIME SERVER QUERY", MB_OK|MB_ICONINFORMATION);
    		bOkay = FALSE;
    	}
			
		return(bOkay);
	}

BOOL _export CALLBACK TimeServerDialogProc(HWND hwndDlg, UINT iMessage,
			WPARAM wParam, LPARAM	lParam)
	{
		static BOOL bSetTime;             // Flag to set the clock after query
		time_t lPCTime;										// PC time value
		time_t lNetTime;									// Network time value
		NPSTR npTime;											// Pointer to an ASCII time string
		LPSTR lpHost; 										// Most recently used host
					
		switch (iMessage)
			{
				case WM_INITDIALOG:						// Initialize the dialog box
					bSetTime = FALSE;						// Default to time server query only
					time(&lPCTime);							// Get the local PC time
					npTime = ctime(&lPCTime);		// Convert time value to ASCII string
					*(npTime+24) = '\0';				// Truncate the newline character

					lpHost = lstrlen(szTimeServer) ? szTimeServer : szHostName;
					SetDlgItemText(hwndDlg, IDC_TIMESERVER, lpHost); 
					SetDlgItemText(hwndDlg, IDC_LOCAL_TIME, npTime); 
					CenterWindow(hwndDlg);
					return(TRUE);
					
				case WM_CLOSE:								// Close the dialog box
					PostMessage(hwndDlg, WM_COMMAND, IDCANCEL, 0L);
					return(TRUE);
					
				case WM_GOT_SERVICE:					// Time service data retrieved okay
					LookupTimeServer(hwndDlg, lParam);
					return(TRUE);
					
				case WM_COMMAND:							// Handle the command buttons
					switch (wParam)
						{ 
							case IDSETTIME:					// The Set Time button was pushed
								bSetTime = TRUE;			// Fall through and perform the query
							case IDOK:              // The OK button was pushed
								GetDlgItemText(hwndDlg, IDC_TIMESERVER, (LPSTR)szTimeServer, MAX_HOST_NAME);
								if (lstrlen(szTimeServer) > 0)
									hTimeServerTask = AsyncGetServiceInfo(hwndDlg, TASK_TIMESERVER);
								else
									{
										bSetTime = FALSE;
										wsprintf(szScratchBuffer, "Please enter a host name.");
										MessageBeep(0);
										MessageBox(hwndSockman, szScratchBuffer,
													"SockMan-TIME SERVER QUERY", MB_OK|MB_ICONINFORMATION);
									}
								return(TRUE);
								
							case IDCANCEL:					// The Cancel button was pushed
								PostMessage(hwndSockman, WM_COMMAND, IDM_FILE_CLEAR, 0L);
								EndDialog(hwndDlg, FALSE);
								return(TRUE); 
						}
					break;
				
				case WM_ASYNC_LOOKUP_DONE:		// Time server host name was resolved
					PaintWindow("Asynchronous lookup for Time Server completed.");
					lNetTime = TimeServerQuery(hwndDlg, lParam);
					hTimeServerTask = 0;
					
					if (lNetTime != SOCKET_ERROR)
						{
							if (bSetTime)						
								{											
									// Set the PC clock using the standard run-time functions
									// with DOS date and time structures.
									struct tm *npTMStruct;
									struct dostime_t dosTimeStruct;
									struct dosdate_t dosDateStruct;
									
									npTMStruct = localtime(&lNetTime);
									
									dosTimeStruct.hour = (BYTE)(npTMStruct->tm_hour);
									dosTimeStruct.minute = (BYTE)(npTMStruct->tm_min);
									dosTimeStruct.second = (BYTE)(npTMStruct->tm_sec);
									dosTimeStruct.hsecond = (BYTE)0;
									_dos_settime(&dosTimeStruct);

									dosDateStruct.year = npTMStruct->tm_year + 1900;
									dosDateStruct.month = (BYTE)(npTMStruct->tm_mon +1);
									dosDateStruct.day = (BYTE)(npTMStruct->tm_mday);
									_dos_setdate(&dosDateStruct);
									
									bSetTime = FALSE;
								}
							npTime = ctime(&lNetTime);
							*(npTime+24) = '\0';		// Truncate the newline character
							SetDlgItemText(hwndDlg, IDC_SERVER_TIME, npTime); 
							
							if (bSetTime)
								SetDlgItemText(hwndDlg, IDC_LOCAL_TIME, npTime); 
							else
								{
									time(&lPCTime);
									npTime = ctime(&lPCTime);
									*(npTime+24) = '\0';// Truncate the newline character
									SetDlgItemText(hwndDlg, IDC_LOCAL_TIME, npTime); 
								}
							PaintWindow((LPSTR)npTime);
						}
					else
							SetDlgItemText(hwndDlg, IDC_SERVER_TIME, ""); 
							
					MessageBeep(0);
					return(TRUE);
			}
  	return(FALSE);
	}

VOID LookupTimeServer(HWND hwnd, LPARAM lError)
	{
		// Function is called after accessing the network services database.
		// Use the default protocol port if errors occurred.
		if (WSAGETASYNCERROR(lError)) 
			nTimeServerPort = htons(IPPORT_TIMESERVER);
		else
			nTimeServerPort = ((LPSERVENT)szTimeServerBuffer)->s_port;

		// Resolve the host address
		hTimeServerTask = LookupHostAsync(hwnd, szTimeServer, szTimeServerBuffer,
					(LPDWORD)&dwTimeServerAddr);
					
		// Paint any error messages in Sockman's main window.
		if (!hTimeServerTask)
			{
				wsprintf(szTimeServerBuffer, "Unable to lookup: %s", (LPSTR)szTimeServer);
				MessageBeep(0);
				MessageBox(hwnd, szTimeServerBuffer,
							"SockMan-TIME SERVER QUERY", MB_OK|MB_ICONINFORMATION);
				PaintWindow(szTimeServerBuffer);
			}
		return;
	}

LONG TimeServerQuery(HWND hwnd, LPARAM lError)
	{
		SOCKET hSocket;									// Socket handle
		SOCKADDR_IN socketAddr;					// Socket address structure
		LPHOSTENT lpHostEntry;					// Host entry structure
		LONG lNetTime;									// Network time value
		LONG lPCTime = SOCKET_ERROR;		// PC time value
		int nLength;										// Length of reply from the server
		int nErr;												// Stores Winsock error codes 

		if (!WSAGETASYNCERROR(lError)) 
			{
				lpHostEntry = (LPHOSTENT)szTimeServerBuffer;
				
		    socketAddr.sin_family = AF_INET;
		    socketAddr.sin_port = nTimeServerPort;
		    socketAddr.sin_addr = *((LPIN_ADDR) *lpHostEntry->h_addr_list);
		    
		    if ((hSocket = socket(PF_INET, SOCK_STREAM, DEFAULT_PROTOCOL)) 
		    			!= INVALID_SOCKET)
					{
				    if (!connect(hSocket, (PSOCKADDR)&socketAddr, 
				    			sizeof(socketAddr)))
				    	{
						    send(hSocket, "\n", sizeof("\n"), NO_FLAGS);
						    nLength = recv(hSocket, (LPSTR)&lNetTime, sizeof(lNetTime),
						    			NO_FLAGS);
								closesocket(hSocket);
								
						    if(nLength != SOCKET_ERROR) 
						    	{
								    lPCTime = ntohl(lNetTime);
								    lPCTime -= PC_REF_TIME;
								  }
				    	}
					}
			}
		if (lPCTime == SOCKET_ERROR)
			{
    		nErr = WSAGetLastError();
    		wsprintf( szTimeServerBuffer, "%d", nErr );
    		MessageBeep(0);
				MessageBox(hwnd, szTimeServerBuffer,
							"recv() returned error number:",
							MB_OK|MB_ICONINFORMATION);
			}

    return(lPCTime);
	}
