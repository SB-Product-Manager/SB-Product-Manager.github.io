// QSMTP
//
// Customize the following variables and constants for your use:
//		HOST_NAME
//		The HELO parameter in MailMessage[]
//		The MAIL parameter in MailMessage[]
//		The RCPT parameter in MailMessage[]

#include	<string.h>
#include "..\winsock.h"

#define PROG_NAME "Quick SMTP Demo"

#define HOST_NAME "your.host"			// Define the mail server for your account
#define WINSOCK_VERSION 0x0101		// Program requires Winsock version 1.1
#define DEFAULT_PROTOCOL 0				// No protocol specified, use default
#define NO_FLAGS 0								// No special flags specified

char sScratchBuffer[100];					// General purpose buffer for messages

VOID SendMail(SOCKET hSocket)
{
    BYTE	sReceiveBuffer[4096];		// Buffer for mail server replies
    int		iLength;  							// Length of mail server reply
    int		iMsg = 0;								// Index into SMTP command array
    int		iEnd;										// Pointer to the end of the reply buffer
    
		// Define SMTP command strings as an array. 
		// Make sure last element remains NULL.
    // Command strings are sent in sequence. 
    char	*MailMessage[]	=	
    		{
    			"HELO HOST.COM\r\n",
    			"MAIL FROM:<your_mailbox@your.host>\r\n",
			    "RCPT TO:<your_mailbox@your.host>\r\n",
			    "DATA\r\n",
			    "This is my message to myself.\r\n\r\n.\r\n",
			    "QUIT\r\n",
			    0
			  };
			  
    iEnd = 0;
    do
    	{
    		if (send(hSocket, (LPSTR)MailMessage[iMsg], 
    					strlen(MailMessage[iMsg]), NO_FLAGS) == SOCKET_ERROR)
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
				
	      MessageBox(NULL, (LPSTR)sReceiveBuffer, (LPSTR)MailMessage[iMsg],
	            MB_OK|MB_ICONSTOP);
	            
				iMsg++;
			} 
		while (MailMessage[iMsg]);
		
		return;
	}

SOCKET ConnectMailServerSocket(VOID)
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
								lpServEnt = getservbyname("mail", DEFAULT_PROTOCOL);
						
								if (lpServEnt == NULL)
									nProtocolPort = htons(IPPORT_SMTP);	
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
		SOCKET hSocket;		// Socket handle for the SMTP connection

		hSocket = ConnectMailServerSocket();

		if (hSocket != INVALID_SOCKET)
			{
				SendMail(hSocket);
				closesocket(hSocket);
			}
			
		WSACleanup();
		return(NULL); 
	}
