#include <stdlib.h>								// Required for ltoa() and ultoa()
#include <time.h>									// Required for ctime()
#include "..\winsock.h"						// Winsock header file

#define PROG_NAME "Simple Timeserver Query"

#define HOST_NAME "cerfnet.com"		// This can be any valid host name
#define WINSOCK_VERSION 0x0101		// Program requires Winsock version 1.1
#define DEFAULT_PROTOCOL 0				// No protocol specified, use default
#define NO_FLAGS 0								// No special flags specified
#define PC_REF_TIME	2208988800L		// Reference point for PC date and time

SOCKET ConnectTimeServerSocket(VOID)
	{
		WSADATA wsaData;							// Winsock implementation details
		LPHOSTENT lpHostEnt;					// Internet host information structure
		SOCKADDR_IN sockAddr;					// Socket address structure
		LPSERVENT lpServEnt;					// Service information structure
		short iTimePort;							// Well-known port assignment is 37
		int nConnect;									// Socket connection results

		SOCKET nTimeserverSocket = INVALID_SOCKET;	// Default socket number

		if (WSAStartup(WINSOCK_VERSION, &wsaData))
			MessageBox(NULL, "Could not load Windows Sockets DLL.", 
						PROG_NAME, MB_OK|MB_ICONSTOP);
						
		else 	// Resolve the host name
			{
				lpHostEnt = gethostbyname(HOST_NAME);
				
				if (!lpHostEnt)
					MessageBox(NULL, "Could not get IP address!", HOST_NAME, 
								MB_OK|MB_ICONSTOP);
			
				else	// Create the socket	
					{
						nTimeserverSocket = socket(PF_INET, SOCK_STREAM, 
									DEFAULT_PROTOCOL);
						
						if (nTimeserverSocket == INVALID_SOCKET)
							MessageBox(NULL, "Invalid socket!!", PROG_NAME, 
										MB_OK|MB_ICONSTOP);
										
						else	// Configure the socket
							{ 
								// Get the time service information
								lpServEnt = getservbyname("time", "tcp");
						
								// If getservbyname() failes, use the well-known port
								if (lpServEnt == NULL)
									iTimePort = htons(IPPORT_TIMESERVER);
								else
									iTimePort = lpServEnt->s_port;

								// Define the socket address	
								sockAddr.sin_family = AF_INET;		// Internet address family
								sockAddr.sin_port = iTimePort;
								sockAddr.sin_addr = *((LPIN_ADDR)*lpHostEnt->h_addr_list);
						
								// Connect the socket
								nConnect = connect(nTimeserverSocket, (LPSOCKADDR)&sockAddr, 
											sizeof(sockAddr));
								
								if( nConnect)
									{
										MessageBox(NULL, "Error connecting socket!!", 
													PROG_NAME, MB_OK|MB_ICONSTOP);
										nTimeserverSocket = INVALID_SOCKET;
									}
							}
					}
			}
		return(nTimeserverSocket);
	}

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, 
			LPSTR lpszCmdParam, int nCmdShow)
	{
		SOCKET nSocket;								// Socket number for the timeserver
		int nCharSent;								// Number of characters transmitted
		int nCharRecv;								// Number of characters received
		DWORD dwNetTime;							// Internet time value as an unsigned long
		LONG lNetTime;								// Internet time value as a signed long
		LONG lPCTime;									// PC time value as a signed long
		char szHostOrder[33];					// Hex time value in host byte order
		char szNetOrder[33];					// Hex time value in network byte order
		char szUnsignedValue[33];			// Internet time value as an unsigned long
		char szSignedValue[33];				// Internet time value as a signed long
		char szMsg[100];							// General purpose buffer for messages

		nSocket = ConnectTimeServerSocket();

		if (nSocket != INVALID_SOCKET)
			{	
				// Ask the server for the current time by sending a CR/LF
				nCharSent = send(nSocket, "\n", lstrlen("\n"), NO_FLAGS);
							
				if (nCharSent == SOCKET_ERROR)
					MessageBox(NULL, "Error occurred during send()!", PROG_NAME,
								MB_OK|MB_ICONSTOP);
								
				else	// Get the current time from the timeserver
					{
						nCharRecv = recv(nSocket, (LPSTR)&lNetTime, sizeof(lNetTime),
									NO_FLAGS);
									
						if (nCharRecv == SOCKET_ERROR)
							MessageBox(NULL, "Error occurred during recv()!", PROG_NAME,
										MB_OK|MB_ICONSTOP);
										
						else // Convert the results from network to host byte-order
							{
								lPCTime = ntohl(lNetTime);
																					
								// Convert numbers to ASCII values for message box use
								ltoa(lPCTime, szHostOrder, 16);		// Use hexadecimal (16)
								ltoa(lNetTime, szNetOrder, 16);		// Use hexadecimal (16)
									
								lPCTime = lPCTime - PC_REF_TIME;	// Subtract PC reference
								
								wsprintf(szMsg, 
											"%s\n\nBYTE-ORDER\n\nNetwork:\t%s\nHost PC:\t%s",
											(LPSTR)ctime(&lPCTime), (LPSTR)szNetOrder, (LPSTR)szHostOrder);
								MessageBox(NULL, szMsg, PROG_NAME,
											MB_OK|MB_ICONINFORMATION);

								// Assign the network time value to an unsigned variable
								dwNetTime = lNetTime;

								// Format the 32-bit network time value as an unsigned long
								ultoa(dwNetTime, szUnsignedValue, 10);

								// Format the 32-bit network time value as a signed long
								ltoa(lNetTime, szSignedValue, 10);

								// Display the 32-bit number from the network.
								wsprintf(szMsg, "Unsigned:\t%s\nSigned:\t\t%s", 
											(LPSTR)szUnsignedValue, (LPSTR)szSignedValue);
								MessageBox(NULL, szMsg, PROG_NAME,
											MB_OK|MB_ICONINFORMATION);
							}
					}
			}
			
		WSACleanup();	// Free all allocated program resources and exit
		return(NULL); 
	}
