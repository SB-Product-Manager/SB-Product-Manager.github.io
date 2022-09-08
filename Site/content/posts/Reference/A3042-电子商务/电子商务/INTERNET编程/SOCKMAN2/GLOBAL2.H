// GLOBAL.H
// Global Variables

#include "..\winsock.h"													// Winsock header file
#include "sockman2.h"														// Prototypes and constants

//	Global Sockman variables
extern HWND hwndSockman;												// Sockman window handle
extern HANDLE hInstanceSockman;									// Sockman instance handle
extern char szAppName[9];												// Application name
extern char szPrintBuffer[MAX_PRINT_BUFFER+1];	// Buffer for text to paint
extern char szScratchBuffer[MAX_PRINT_BUFFER+1];// General purpose buffer

// Global variables for DNS lookup operations
extern char szHostName[MAX_HOST_NAME+1];				// Host name
extern char szIPAddress[MAX_IP_ADDRESS+1];			// Dotted-decimal address
extern char szLookupText[MAX_HOST_NAME+1];			// Buffer for lookup text
extern char szLookupBuffer[MAXGETHOSTSTRUCT];		// Buffer for host data
extern HTASK hAsyncLookupTask;									// Asynchronous task handle
extern DWORD dwLookupAddr;											// 32-bit binary IP address
