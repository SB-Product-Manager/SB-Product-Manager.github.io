// QPOP3
//
//	Customize the following variables and constants for your use:
//		HOST_NAME
//		The USER parameter in POPMessage[]
//		The PASS parameter in POPMessage[]

#include	<string.h>							// Required for strlen()
#include "..\winsock.h"						// Winsock header file

#define PROG_NAME "Quick POP3 Demo"

#define HOST_NAME "your.host"			// Define the POP server for your account
#define WINSOCK_VERSION 0x0101		// Program requires Winsock version 1.1
#define DEFAULT_PROTOCOL 0				// No protocol specified, use default
#define DEFAULT_POP3_PORT 110			// Well-know port assignment
#define NO_FLAGS 0								// No special flags specified

char sScratchBuffer[100];					// General purpose buffer for messages

VOID GetMail(SOCKET hSocket)
{
		BYTE	sReceiveBuffer[4096];		// Buffer for incoming mail messages
    int		iLength;  							// Length of data received
    int		iMsg = 0;								// Index into the POP command array
    int		iEnd;										// Pointer to the end of the mail buffer
    
		// Define POP3 command strings as an array. 
		// Make sure last element remains NULL.
    // Command strings are sent in sequence. 
    char	*POPMessage[]	=	
    		{
    			"USER your_mailbox_id\r\n",
			    "PASS your_password\r\n",
			    "STAT\r\n",
			    "LIST\r\n",
			    "RETR 1\r\n",
			    "DELE 1\r\n",
			    "QUIT\r\n",
			    0
			  };
			  
    iEnd = 0;
    do
    	{
    		if (send(hSocket, (LPSTR)POPMessage[iMsg], 
    					strlen(POPMessage[iMsg]), NO_FLAGS) == SOCKET_ERROR)
    			{
			      MessageBox(NULL, 
			      			"The send() function returned a socket error.",
			            PROG_NAME, MB_OK|MB_ICONSTOP);
						break;	      
					}    		
		    iLength = recv(hSocket, (LPSTR)sReceiveBuffer+iEnd, 
		    			sizeof(sReceiveBuffer)-iEnd, NO_FLAGS);
		    			
		  	if (iLength == 0 || iLength == SOCKET_ERROR)
					{
			      MessageBox(NULL, 
			      			"The recv() function returned a socket error.",
			            PROG_NAME, MB_OK|MB_ICONSTOP);
						break;	      
					}
					
				iEnd += iLength;
				sReceiveBuffer[iEnd] = '\0';
				
	      MessageBox(NULL, (LPSTR)sReceiveBuffer, (LPSTR)POPMessage[iMsg],
	            MB_OK|MB_ICONSTOP);
	            
				iMsg++;
			} 
		while (POPMessage[iMsg]);
		
		return;
	}

SOCKET ConnectPOPServerSocket(VOID)
	{
		WSADATA wsaData;							// Winsock implementation details
		LPHOSTENT lpHostEnt;					// Internet host information structure
		SOCKADDR_IN sockAddr;					// Socket address structure
		LPSERVENT lpServEnt;					// Service information structure
		short nProtocolPort;					// Protocol port
		int nConnect;									// Socket connection results

		SOCKET hServerSocket = INVALID_SOCKET;	// Default socket number

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
						hServerSocket = socket(PF_INET, SOCK_STREAM, 
									DEFAULT_PROTOCOL);
						
						if (hServerSocket == INVALID_SOCKET)
							MessageBox(NULL, "Invalid socket!!", PROG_NAME, 
										MB_OK|MB_ICONSTOP);
										
						else	// Configure the socket
							{ 
								// Get the time service information
								lpServEnt = getservbyname("postoffice", DEFAULT_PROTOCOL);
						
								if (lpServEnt == NULL)
									nProtocolPort = htons(DEFAULT_POP3_PORT);	
								else
									nProtocolPort = lpServEnt->s_port;

								// Define the socket address	
								sockAddr.sin_family = AF_INET;		
								sockAddr.sin_port = nProtocolPort;
								sockAddr.sin_addr = *((LPIN_ADDR)*lpHostEnt->h_addr_list);
						
								// Connect the socket
								nConnect = connect(hServerSocket, (PSOCKADDR)&sockAddr, 
											sizeof(sockAddr));
								
								if( nConnect)
									{
										MessageBox(NULL, "Error connecting socket!!", 
													PROG_NAME, MB_OK|MB_ICONSTOP);
										hServerSocket = INVALID_SOCKET;
									}
							}
					}
			}
		return(hServerSocket);
	}

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, 
			LPSTR lpszCmdParam, int nCmdShow)
	{
		SOCKET hSocket;		// Socket handle for POP server connection

		hSocket = ConnectPOPServerSocket();

		if (hSocket != INVALID_SOCKET)
			{
				GetMail(hSocket);
				closesocket(hSocket);
			}
			
		WSACleanup();
		return(NULL); 
	}
