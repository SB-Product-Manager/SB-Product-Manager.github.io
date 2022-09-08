//	PING.CPP
//	These functions create a raw socket for a Ping program.

#include "..\winsock.h"						// Winsock header file
#include "sockman5.h"							// Prototypes and constants
#include "global5.h"							// Global variables
#include "sockraw5.h"							// IP and ICMP header structures

#define ICMP_ECHO 8								// An ICMP echo message
#define ICMP_ECHOREPLY 0					// An ICMP echo reply message
#define	ICMP_HEADERSIZE 8					// ICMP header size ("echo messages" only)

BOOL PingDialog(VOID)
	{
    DLGPROC lpfnDialogProc;				// Pointer to the dialog procedure
    BOOL bOkay;										// Return value from the dialog

		//	Create a dialog box for the user's entry    
    lpfnDialogProc = MakeProcInstance((DLGPROC)PingDialogProc,
    			hInstanceSockman);
    bOkay = DialogBox(hInstanceSockman, "IDD_PING",  hwndSockman,
    			lpfnDialogProc);
    FreeProcInstance(lpfnDialogProc);
    
    if (bOkay == -1)
    	{
				wsprintf(szScratchBuffer, "Unable to create dialog box!");
				MessageBeep(0);
				MessageBox(hwndSockman, szScratchBuffer,
							"SockMan-PING", MB_OK|MB_ICONINFORMATION);
    		bOkay = FALSE;
    	}
		hPingTask = 0;
		return(bOkay);
	}

BOOL _export CALLBACK PingDialogProc(HWND hwndDlg, UINT iMessage,
			WPARAM wParam, LPARAM	lParam)
	{
		BOOL bPingOkay;		            	// Success flag for Ping operations
		DWORD dwTravelTime;							// Round-trip travel time for ping
		LPSTR lpHost; 									// Most recently used host
								
		switch (iMessage)
			{
				case WM_INITDIALOG:					// Initialize the dialog box
					lpHost = lstrlen(szPingHost) ? szPingHost : szHostName;
					SetDlgItemText(hwndDlg, IDC_PING_HOST, lpHost); 
					SetDlgItemInt(hwndDlg, IDC_PING_TIME, 0, FALSE);
					CenterWindow(hwndDlg);
					return(TRUE);
					
				case WM_CLOSE: 							// Close the dialog box
					PostMessage(hwndDlg, WM_COMMAND, IDEXIT, 0L);
					return(TRUE);
					
				case WM_BLOCK_LOOKUP_DONE:	// IP address was resolved
					wsprintf(szPrintBuffer, "Resolved IP address for %s ping.",
								(LPSTR)szPingHost);
					PaintWindow(szPrintBuffer);
					return(TRUE);
					
				case WM_COMMAND:						// Handle the command buttons
					switch (wParam)
						{ 
							case IDOK:						// The OK button was pushed
								dwTravelTime = 0;
								
								if (hPingTask)
									{
										MessageBeep(0);
										MessageBox(hwndDlg,
													"Ping operation is already in progress use.",
													"SockMan-PING", MB_ICONSTOP | MB_OK);
										return(TRUE);
									}
								hPingTask = TASK_PING;
								
								SetDlgItemInt(hwndDlg, IDC_PING_TIME, (UINT)dwTravelTime,
											TRUE);
								GetDlgItemText(hwndDlg, IDC_PING_HOST, (LPSTR)szPingHost,
											MAX_HOST_NAME);
								if (lstrlen(szPingHost) > 0)
									{
										if (WSAIsBlocking())
											WSACancelBlockingCall();
										bPingOkay = DoPingOperation(hwndDlg, szPingHost, 
													&dwTravelTime);
									}
								else
									{
										wsprintf(szScratchBuffer, "Please enter a host name.");
										MessageBeep(0);
										MessageBox(hwndDlg, szScratchBuffer,
													"SockMan-PING", MB_OK|MB_ICONINFORMATION);
									}
								
								if(!bPingOkay)
									{
										// If Ping failed, the ping buffer contains the error.
										MessageBox(NULL, szPingBuffer, "SockMan-PING",
													MB_OK|MB_ICONSTOP);
										dwTravelTime = 0;
									}
									
								MessageBeep(0);
								SetDlgItemInt(hwndDlg, IDC_PING_TIME, (UINT)dwTravelTime,
											TRUE);
								PaintWindow(szPingBuffer);
								hPingTask = 0;
								return(TRUE);
								
							case IDCANCEL:        // The Cancel button was pushed
								if (WSAIsBlocking())
									WSACancelBlockingCall();
								return(TRUE); 

							case IDEXIT:          // The Exit button was pushed
								if (WSAIsBlocking())
									WSACancelBlockingCall();
								PostMessage(hwndSockman, WM_COMMAND, IDM_FILE_CLEAR, 0L);
								EndDialog(hwndDlg, FALSE);
								return(TRUE); 
						}
					break;
			}
  	return(FALSE);
	}

BOOL DoPingOperation(HWND hwnd, LPSTR lpszHostName, PDWORD pdwRoundTrip)
	{
																	// Local variables
		int iPacketSize;							// ICMP packet size 
		int iHostAddrLength;					// Host address length
		int iIPHeadLength;						// IP datagram header length
		int iReceivedBytes;						// Number of bytes received
		int iSentBytes;								// Number of bytes sent
		int nProtocol;								// ICMP protocol number
		int iSocketError;							// Stores any error codes
		PDWORD pdwTimeStamp;					// Tick count at transmission
		DWORD dwReturnTime;						// Tick count upon receipt of echo reply
																	// Structures defined in WINSOCK.H
		SOCKADDR_IN	sockAddrLocal;		// Socket address structures
		SOCKADDR_IN	sockAddrHost;			// 
		SOCKET hSocket;								// Socket handle (or descriptor)
		LPHOSTENT lpHostEntry;				// Internet host data structure
		LPPROTOENT lpProtocolEntry;		// Internet protocol data structure

		BYTE IcmpSendPacket[1024];		// Buffer space for data to send
		BYTE IcmpRecvPacket[4096];		// Buffer space for received data 

		struct icmp *pIcmpHeader;			// A pointer to the ICMP structure
		struct ip *pIpHeader;					// A pointer to the IP header structure

		if ((lpHostEntry = LookupHostBlocking(hwnd, lpszHostName, szPingBuffer, 
					TASK_PING)) == NULL)
			{
				wsprintf(szPingBuffer, "Could not get %s IP address.",
							(LPSTR)lpszHostName);
				return(FALSE);
			}
    
		sockAddrLocal.sin_family = AF_INET;
		sockAddrLocal.sin_addr = *((LPIN_ADDR) *lpHostEntry->h_addr_list);

		// With a raw socket, the program must specify a protocol
		if ((lpProtocolEntry = getprotobyname("icmp")) == NULL)
			nProtocol = htons(IPPROTO_ICMP);
		else
			nProtocol = lpProtocolEntry->p_proto;
		
		// Create a "raw" socket and specify ICMP as the protocol
		if ((hSocket = socket(PF_INET, SOCK_RAW, nProtocol)) == 
					INVALID_SOCKET)
			{
				wsprintf(szPingBuffer, "Could not create a RAW socket.");
				return(FALSE);
			}

		pIcmpHeader = (struct icmp *) IcmpSendPacket;	// Point at the data area
		pIcmpHeader->icmp_type = ICMP_ECHO;						// then fill in the data.
		pIcmpHeader->icmp_code = 0;										// Use Sockman's instance
		pIcmpHeader->icmp_id = hInstanceSockman;			// handle as a unique ID.
		pIcmpHeader->icmp_seq = 0;										// It's important to reset
		pIcmpHeader->icmp_cksum = 0;									// the checksum to zero.
		
		//Put tick count in the optional data area
		pdwTimeStamp = (PDWORD)&IcmpSendPacket[ICMP_HEADERSIZE];
		*pdwTimeStamp = GetTickCount();
		iPacketSize = ICMP_HEADERSIZE + sizeof(DWORD);
		pIcmpHeader->icmp_cksum = InternetChksum((LPWORD)pIcmpHeader, 
					iPacketSize);
    
		if (pIcmpHeader->icmp_cksum !=0 )
			{    
				iSentBytes = sendto(hSocket, (LPSTR) IcmpSendPacket, iPacketSize, 
							NO_FLAGS, (LPSOCKADDR) &sockAddrLocal, sizeof(sockAddrLocal));
				if (iSentBytes == SOCKET_ERROR)
					{
						closesocket(hSocket);
						wsprintf(szPingBuffer,
									"The sendto() function returned a socket error.");
						return(FALSE);
					}
		
				if (iSentBytes != iPacketSize)
					{
						closesocket(hSocket);
						wsprintf(szPingBuffer,
									"Wrong number of bytes sent: %d", iSentBytes);
						return(FALSE);
					}
		
				iHostAddrLength = sizeof(sockAddrHost);
		
				iReceivedBytes = recvfrom(hSocket, (LPSTR) IcmpRecvPacket, 
							sizeof(IcmpRecvPacket), NO_FLAGS, (LPSOCKADDR) &sockAddrHost,
							&iHostAddrLength);
			}
		else
			{
				closesocket(hSocket);
				wsprintf(szPingBuffer,
							"Checksum computation error! Result was zero!");
				return(FALSE);
			}
    
		closesocket(hSocket);
		
		if (iReceivedBytes == SOCKET_ERROR)
			{   
				iSocketError = WSAGetLastError();
				if (iSocketError == 10004)
					{
						wsprintf(szPingBuffer,
									"Ping operation for %s was cancelled.", 
									(LPSTR)lpszHostName);
						*pdwRoundTrip = 0;
						return(TRUE);
					}
				else
					{
						wsprintf(szPingBuffer,
									"Socket Error from recvfrom(): %d", iSocketError);
						return(FALSE);
					}
			}

		dwReturnTime = GetTickCount();
		*pdwRoundTrip = dwReturnTime - *pdwTimeStamp;

		// Point to the IP Header in the received packet
		pIpHeader = (struct ip *)IcmpRecvPacket;

		// Extract bits 4-7 and convert the number of 32-bit words to bytes
		iIPHeadLength = (pIpHeader->ip_verlen >> 4) << 2;

		// Make sure the packet is an ICMP header by testing its side
		if (iReceivedBytes < iIPHeadLength + ICMP_HEADERSIZE)
			{
				wsprintf(szPingBuffer, "Received packet was too short.");
				return(FALSE);
			}

		// Point to the ICMP message which immediately follows the IP header
		pIcmpHeader = (struct icmp *) (IcmpRecvPacket + iIPHeadLength);

		// Make sure this is an ICMP "echo reply"
		if (pIcmpHeader->icmp_type != ICMP_ECHOREPLY)
			{
				wsprintf(szPingBuffer,
							"Received packet was not an echo reply to our ping.");
				return(FALSE);
			}

		// Make sure this process sent the packet
		if (pIcmpHeader->icmp_id != (WORD)hInstanceSockman)
			{
				wsprintf(szPingBuffer,
							"Received packet was not sent by this program.");
				return(FALSE);
			}

		// This appears to be a reply to this process. Note the IP address and 
		// host name that sent the ICMP echo reply message.
		lstrcpy(lpszHostName, (LPSTR)lpHostEntry->h_name);
		wsprintf(szPingBuffer,
					"Round-trip travel time to %s [%s] was %d milliseconds.",
					(LPSTR)lpszHostName, (LPSTR)inet_ntoa(sockAddrHost.sin_addr), 
					*pdwRoundTrip);
		
		return(TRUE); 
	}

WORD InternetChksum(LPWORD lpwIcmpData, WORD wDataLength)
	{
		long	lSum;				// Stores the summation
		WORD	wOddByte;		// Left over byte from the summation
		WORD	wAnswer;		// The 1's complement checksum
		
		lSum = 0L;

		while (wDataLength > 1)
			{
				lSum += *lpwIcmpData++;
				wDataLength -= 2;
			}

		// Handle the odd byte if necessary and make sure the top half is zero
		if (wDataLength == 1)
			{
				wOddByte = 0;
				*((LPBYTE) &wOddByte) = *(LPBYTE)lpwIcmpData;	// One byte only
				lSum += wOddByte;
			}

		// Add back the carry outs from the 16 bits to the low 16 bits
		lSum = (lSum >> 16) + (lSum & 0xffff);	// Add high-16 to low-16
		lSum += (lSum >> 16);										// Add carry
		wAnswer = (WORD)~lSum;										// 1's complement, then truncate 
																						// to 16 bits
		return(wAnswer);
	}

