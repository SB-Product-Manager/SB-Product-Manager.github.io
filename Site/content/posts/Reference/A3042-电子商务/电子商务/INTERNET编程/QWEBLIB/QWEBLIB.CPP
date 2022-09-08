#include <string.h>								// Required for _fstrrchr()
#include "..\winsock.h"						// Winsock header file

#define PROG_NAME "QWEBLIB.DLL"

#define WINSOCK_VERSION 0x0101		// Program requires Winsock version 1.1
#define NO_FLAGS 0								// No special flags specified
#define WEB_PORT 80								// Well-known port for Web's HTTP protocol

extern "C" SOCKET _export FAR PASCAL ConnectWebServerSocket(LPSTR lpszHostName)
	{
		WSADATA wsaData;							// Winsock implementation details
		LPHOSTENT pHostEnt;						// Internet host information structure
		SOCKADDR_IN sockAddr;					// Socket address structure
		int nConnect;									// Socket connection results
		char szMsg[100];							// Message buffer
    
		SOCKET nServerSocket = INVALID_SOCKET;

		if (WSAStartup(WINSOCK_VERSION, &wsaData))
			MessageBox(NULL, "Could not load Windows Sockets DLL.", 
						PROG_NAME, MB_OK|MB_ICONSTOP);
		else if (!(pHostEnt = gethostbyname(lpszHostName)))
			{
				MessageBox(NULL, "Could not get IP address!", lpszHostName, 
						MB_OK|MB_ICONSTOP);
			}
		else
			{
				nServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
										
				if (nServerSocket == INVALID_SOCKET)
					MessageBox(NULL, "Invalid socket!!", PROG_NAME, 
								MB_OK|MB_ICONSTOP);
														
				else	// Configure the socket
					{ 
						// Define the socket address	
						sockAddr.sin_family = AF_INET;
						sockAddr.sin_port = htons(WEB_PORT);	// WEB_PORT = 80
						sockAddr.sin_addr = *((LPIN_ADDR)*pHostEnt->h_addr_list);
										
						// Connect the socket
						nConnect = connect(nServerSocket, (LPSOCKADDR)&sockAddr, 
									sizeof(sockAddr));
												
						if (nConnect)
							{
								nConnect = WSAGetLastError();
								wsprintf(szMsg,"%d Error connecting socket!!", nConnect);
								MessageBox(NULL, szMsg, PROG_NAME, MB_OK|MB_ICONSTOP);
								nServerSocket = INVALID_SOCKET;
							}
					}
			}
		return(nServerSocket);
	}

extern "C" LPSTR _export FAR PASCAL ExtractFileName(LPSTR lpPathString, 
			LPSTR lpszFileName)
	{
		LPSTR lp;									// General purpose pointer
		UINT i;										// General purpose index
		UINT iExtLength = 0;			// Length of file extension (following the dash)

		// Find the last forward slash (assume UNIX/NT directory conventions)		
		if (lp = _fstrrchr(lpPathString, '/'))
			lp++;
		else
			lp = lpPathString;
			
		// Loop while the length of the name is less than 8 characters 
		// (a valid DOS length), the character is not a dot and the 
		// pointer is valid
		for (i = 0; i < 8 && *lp != '.' && lp; i++)
			*(lpszFileName+i) = *(lp++);
				    
		// Add a dot to mark the start of the file extension
		*(lpszFileName+i) = '.';
		i++;
				
		// Find the last dot and use up to the next three characters for
		// the new file name.
		if (lp = _fstrrchr(lpPathString, '.'))
				for (iExtLength = 0; iExtLength < 3 && (*(lp)); iExtLength++)
						*(lpszFileName+(i++)) = *(++lp);
						
		// Null-terminate the new file name
		*(lpszFileName+i) = '\0';

		return(lpszFileName);
	}

extern "C" HFILE _export FAR PASCAL SendWebQuery(SOCKET nSocket, LPSTR lpszQuery)
	{
		HFILE hFile;									// File handle for data-stroage file
		OFSTRUCT openFileBuff;				// Windows open file structure
		char szFileName[13];					// Storage buffer for the new file name
		char szWebQuery[100];					// Buffer to hold the Web query
		int nCharSent;								// Number of characters transmitted
		char szMsg[100];							// General purpose buffer for messages

		wsprintf(szWebQuery,"GET %s\n", (LPSTR)lpszQuery);
		nCharSent = send(nSocket, szWebQuery, lstrlen(szWebQuery), NO_FLAGS);
							
		if (nCharSent == SOCKET_ERROR)
			{
				nCharSent = WSAGetLastError();
				wsprintf(szMsg,"%d Error occurred during send()!", nCharSent);
				MessageBox(NULL, szMsg, PROG_NAME, MB_OK|MB_ICONSTOP);
				hFile = SOCKET_ERROR;
			}
					
		else
			{
        ExtractFileName(lpszQuery, szFileName);

				hFile = OpenFile(szFileName, (OFSTRUCT far *)&openFileBuff, OF_CREATE);
				if (hFile == HFILE_ERROR)
					{
						wsprintf(szMsg,"Error occurred opening file: %s", (LPSTR)szFileName);
						MessageBox(NULL, szMsg, PROG_NAME, MB_OK|MB_ICONSTOP);
					}
			}
		return(hFile);
	}
										
extern "C" UINT _export FAR PASCAL RecvWebFile(SOCKET nSocket, HFILE hFile)
	{
		char szWebInfo[5000];	 				// Buffer to hold Web information
		int nCharRecv;								// Number of characters received
		char szMsg[1000];							// General purpose buffer for messages
		static LONG lTotalData;				// Tracks the total bytes transferred

		
		nCharRecv = recv(nSocket, (LPSTR)&szWebInfo, sizeof(szWebInfo), NO_FLAGS);
		lTotalData += nCharRecv;
		if (nCharRecv > 0 )
			{
				if (HFILE_ERROR == _lwrite (hFile, szWebInfo, nCharRecv))
					{
						lTotalData = 0;
						_lclose(hFile);
						wsprintf(szMsg,"%d Error occurred during recv()!", nCharRecv);
						MessageBox(NULL, szMsg, PROG_NAME, MB_OK|MB_ICONSTOP);
						return(HFILE_ERROR);
					}
					
				if (nCharRecv == lTotalData)
					{ 
						if (*(szWebInfo+0) == '<')
							{
								*(szWebInfo+nCharRecv) = '\0';
								wsprintf(szMsg,"%s", (LPSTR)szWebInfo);
								MessageBox(NULL, szMsg, PROG_NAME, MB_OK|MB_ICONSTOP);
							}
					}
    	}
    else if (nCharRecv == SOCKET_ERROR)
			{
				lTotalData = 0;
				_lclose(hFile);
				nCharRecv = WSAGetLastError();
				wsprintf(szMsg,"%d Error occurred during recv()!", nCharRecv);
				MessageBox(NULL, szMsg, PROG_NAME, MB_OK|MB_ICONSTOP);
				return(SOCKET_ERROR);
			}

    if (nCharRecv == 0)
    	{
    		lTotalData = 0;
    		_lclose(hFile);
    	}
		
		return(nCharRecv);
	}

int _export FAR PASCAL LibMain(HANDLE hInstance, WORD wDataSeg, WORD wHeapSize, LPSTR lpszCmdParam)
	{
		if (wHeapSize > 0)
			UnlockData (0);
			
		return(1);
	}
	
int _export FAR PASCAL WEP (int nParam)
	{
		return(1);
	}
