// servevw.cpp : implementation of the CServerView class
//

#include "stdafx.h"
#include "server1.h"

#include "serv1doc.h"
#include "serv1vw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerView

IMPLEMENT_DYNCREATE(CServerView, CScrollView)

BEGIN_MESSAGE_MAP(CServerView, CScrollView)
	//{{AFX_MSG_MAP(CServerView)
	ON_COMMAND(ID_SERVER_CLOSE, OnServerClose)
	ON_COMMAND(ID_SERVER_OPEN, OnServerOpen)
	ON_UPDATE_COMMAND_UI(ID_SERVER_CLOSE, OnUpdateServerClose)
	ON_UPDATE_COMMAND_UI(ID_SERVER_OPEN, OnUpdateServerOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)

	// START CUSTOM CODE: Internet Programming	
	ON_MESSAGE(WM_SERVER_ACCEPT, OnServerAccept) 
	ON_MESSAGE(WM_CLIENT_CLOSE, OnClientClose) 
	ON_MESSAGE(WM_CLIENT_READ, OnClientRead) 
	// END MODIFICATIONS: Internet Programming

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerView construction/destruction

CServerView::CServerView()
	{
		// START CUSTOM CODE: Internet Programming	
		m_bServerIsOpen = FALSE;
		m_hClientSocket = INVALID_SOCKET;			            
		// END MODIFICATIONS: Internet Programming
	}

CServerView::~CServerView()
	{
		// START CUSTOM CODE: Internet Programming
		
		if (m_bServerIsOpen)
			closesocket(m_pDoc->m_hServerSocket);
			
		if (m_hClientSocket != INVALID_SOCKET)
			closesocket(m_hClientSocket);
		// END MODIFICATIONS: Internet Programming
	}

void CServerView::OnInitialUpdate()
	{
		CScrollView::OnInitialUpdate();

		// START CUSTOM CODE: Internet Programming	
		m_pDoc = GetDocument();
		m_pDoc->SetTitle("CLOSED for BUSINESS");

		m_pParentWnd = GetParent();
		m_pParentMenu = m_pParentWnd->GetMenu();

		// Setup the server window
		TEXTMETRIC tm;
		CRect rectServerSize;
		CClientDC dc(this);
		    
		dc.GetTextMetrics(&tm);
		SetScrollSizes( MM_TEXT, CSize(0,0), CSize(0,(MAX_LINES*tm.tmHeight)), CSize(0, tm.tmHeight));
		GetWindowRect( rectServerSize );
		GetParentFrame()->MoveWindow( rectServerSize.left, rectServerSize.top, (MAX_COLUMNS*tm.tmAveCharWidth), (24*tm.tmHeight), FALSE);
		  
		return;
		// END MODIFICATIONS: Internet Programming
	}

/////////////////////////////////////////////////////////////////////////////
// CServerView drawing

void CServerView::OnDraw(CDC* pDC)
	{
		ASSERT_VALID(m_pDoc);
	
		// TODO: add draw code for native data here
		
		// START CUSTOM CODE: Internet Programming
		TEXTMETRIC tm;
		int iYValue;
	
		pDC->GetTextMetrics(&tm);
		iYValue = 0;
		
		for (int iLine = 0; iLine <= m_pDoc->m_lLineNumber; iLine++)
			{
				pDC->TextOut(0,iYValue, m_pDoc->m_csText[iLine], m_pDoc->m_csText[iLine].GetLength());
				iYValue += tm.tmHeight;
			}
			
		SetScrollSizes(MM_TEXT, CSize(0, ((int) m_pDoc->m_lLineNumber+1) * tm.tmHeight));
		// END MODIFICATIONS: Internet Programming 
		return;		
	}

// START CUSTOM CODE: Internet Programming
void CServerView::PrintString(CString csString)
	{
		if (csString.GetLength() == 0)
			return;
			
		// Print each character in the string except the last one
		for (int iChar = 0; iChar < (csString.GetLength()-1); iChar++)
			PrintChar(csString[iChar], FALSE);	// Don't update scroll bar
			
		// Update the scroll bar when reaching the last character
		PrintChar(csString[iChar], TRUE);
		m_pDoc->UpdateAllViews(NULL, 0L, 0);
		return;
	}
// END MODIFICATIONS: Internet Programming

// START CUSTOM CODE: Internet Programming
void CServerView::PrintString(LPSTR lpszString)
	{
		if (*lpszString == NULL)
			return;
			
		// Print each character in the string except the last one
		for (int iChar = 0; lpszString[iChar+1] != NULL; iChar++)
			PrintChar(lpszString[iChar], FALSE);	// Don't update scroll bar
			
		// Update the scroll bar when reaching the last character
		PrintChar( lpszString[iChar], TRUE);
		m_pDoc->UpdateAllViews(NULL, 0L, 0);
		return;
	}
// END MODIFICATIONS: Internet Programming

// START CUSTOM CODE: Internet Programming
void CServerView::PrintChar(char chChar, BOOL bLastChar)
	{
		// Ignore carriage-returns, the following statements detect new-lines.
		if (chChar =='\r')
			return;
			
	  CClientDC dc(this);
	  TEXTMETRIC tm;
	  CPoint pt, ptOrigin;
	  CRect rectServerSize;
	
		OnPrepareDC(&dc);       
	  dc.GetTextMetrics(&tm);                        
	
	  if (chChar =='\n')
	    {  
	    	// Move to column zero for a new line.
	      m_pDoc->m_lColumnNumber = 0;
	      if (m_pDoc->m_lLineNumber == (MAX_LINES-1))
	        {
	          for (int iLine = 0; iLine < MAX_LINES; iLine++)
	          	m_pDoc->m_csText[iLine] = m_pDoc->m_csText[iLine+1];
	          	
	          m_pDoc->m_csText[iLine].Empty;
	          m_pDoc->UpdateAllViews(this, 0L, 0);
	        }
	      else
	        m_pDoc->m_lLineNumber++;
	
	      SetScrollSizes( MM_TEXT, CSize(0, ((int) m_pDoc->m_lLineNumber+1) * tm.tmHeight));
	    }
	  else
	  	{
	  		if (m_pDoc->m_lColumnNumber++ >= MAX_COLUMNS)
	  			{
	  				m_pDoc->m_lColumnNumber = 1;
	  				if (m_pDoc->m_lLineNumber == (MAX_LINES-1))
	  					{
	  						for (int iLine = 0; iLine < MAX_LINES; iLine ++)
	  							m_pDoc->m_csText[iLine] = m_pDoc->m_csText[iLine+1];
	  						
	  						m_pDoc->m_csText[iLine].Empty;
	  						m_pDoc->UpdateAllViews(this, 0L, 0);
	  					}
	  				else
	  					m_pDoc->m_lLineNumber++;
	  			}   
	  			
	  		m_pDoc->m_csText[m_pDoc->m_lLineNumber] += chChar;
	  		
	      if (bLastChar)
	      	dc.TextOut(0, (int) m_pDoc->m_lLineNumber * tm.tmHeight,
	      				m_pDoc->m_csText[m_pDoc->m_lLineNumber],
	      				m_pDoc->m_csText[m_pDoc->m_lLineNumber].GetLength());
	                   
	    }                             
	    
	  // If last character then update the position on the scroll bar
		if (bLastChar)
			{
				pt = GetScrollPosition();             
				if ((int) m_pDoc->m_lLineNumber * tm.tmHeight < pt.y)
					{
						pt.y = (int) m_pDoc->m_lLineNumber * tm.tmHeight;
						ScrollToPosition(pt);
					}
				else
					{
						CScrollView::GetClientRect( rectServerSize);                            
						if ((((int)m_pDoc->m_lLineNumber * tm.tmHeight) + tm.tmHeight) > rectServerSize.bottom)
							{
								ptOrigin = dc.GetViewportOrg();  
		            pt.x = ptOrigin.x;
		            pt.y = ((int) m_pDoc->m_lLineNumber * tm.tmHeight) + tm.tmHeight - rectServerSize.bottom;
		            ScrollToPosition(pt );
							}
					}
	    }
		return;
	}
// END MODIFICATIONS: Internet Programming

/////////////////////////////////////////////////////////////////////////////
// CServerView printing

BOOL CServerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CServerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CServerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CServerView diagnostics

#ifdef _DEBUG
void CServerView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CServerView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CServerDoc* CServerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CServerDoc)));
	return (CServerDoc*)m_pDocument;
}
#endif //_DEBUG

// START CUSTOM CODE: Internet Programming
VOID CServerView::ReportWinsockErr(LPSTR lpszErrorMsg)
	{
		wsprintf(m_chMsgBuffer, "\nWinsock error %d: %s\n\n", WSAGetLastError(), lpszErrorMsg);
		PrintString((LPSTR)lpszErrorMsg);
		MessageBeep(MB_ICONSTOP);
		MessageBox(m_chMsgBuffer,  AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;   
	}
// END MODIFICATIONS: Internet Programming

/////////////////////////////////////////////////////////////////////////////
// CServerView message handlers

// START CUSTOM CODE: Internet Programming
LRESULT CServerView::OnServerAccept(WPARAM wParam, LPARAM lParam)
	{ 
		int iErrorCode;
		int nLength = sizeof(SOCKADDR);
		
		if (WSAGETSELECTERROR(lParam))
			{
				ReportWinsockErr("Error detected on entry into OnServerAccept.");
				return 0L;
			}
			
		if (WSAGETSELECTEVENT(lParam) == FD_ACCEPT)
			{
				PrintString("Connection has arrived!\n");
						
				m_hClientSocket = accept(m_pDoc->m_hServerSocket, (LPSOCKADDR)&m_sockClientAddr, (LPINT)&nLength);
						
				if (m_hClientSocket == INVALID_SOCKET)
					{
						ReportWinsockErr("Server socket failed to accept connection.");
						return 0L;
					}
				
				CString csDottedDecimal = "CONNECTED to ";
				csDottedDecimal += inet_ntoa(m_sockClientAddr.sin_addr);
				m_pDoc->SetTitle(csDottedDecimal);
				csDottedDecimal += "\n";
				
				PrintString(csDottedDecimal);
        CString csText = "<Title>Internet Programming</Title>";
        csText += "<h1>Internet Programming</H1><p><hr>";
        csText += "<H3>Kris Jamsa, Ph.D., and Ken Cope</H3><p>";
				csText += "<H5>Published by Jamsa Press, 1995</H5><p><hr>";
				LPSTR lpszResponse = csText.GetBuffer(1000);
						
				iErrorCode = send( m_hClientSocket, lpszResponse, lstrlen(lpszResponse), NO_FLAGS);    
				if (iErrorCode == SOCKET_ERROR)
					ReportWinsockErr("Error sending response to client.");
				else
					PrintString("Response sent!\n");
        OnClientClose();
			}
		return 0L;
	}
// END MODIFICATIONS: Internet Programming

void CServerView::OnServerClose() 
	{
		if (m_hClientSocket != INVALID_SOCKET)	
			{
				if (WSAAsyncSelect(m_hClientSocket, m_hWnd, NO_FLAGS, NO_FLAGS))
					ReportWinsockErr("WSAAsyncSelect error in OnServerClose.");
					
				closesocket(m_hClientSocket);
				m_hClientSocket = INVALID_SOCKET;
			}
		
		closesocket(m_pDoc->m_hServerSocket);
		
		m_bServerIsOpen = FALSE;
		
		m_pDoc->SetTitle("CLOSED for BUSINESS");
		
		PrintString("\nServer CLOSED for BUSINESS.\n");
		return;
	}

LRESULT CServerView::OnClientClose(void)
	{
		int iErrorCode = closesocket(m_hClientSocket);
		
		m_hClientSocket = INVALID_SOCKET;
						
		if (iErrorCode == SOCKET_ERROR)
			ReportWinsockErr("Error closing client socket!");
		else
			PrintString("Client socket closed successfully, ready for next client!\n\n");
			
		m_pDoc->SetTitle("WAITING for CONNECTION");
		return 0L;
	}

LRESULT CServerView::OnClientClose(WPARAM wParam, LPARAM lParam)
	{
    if (WSAGETASYNCERROR(lParam)) 
			ReportWinsockErr("Error detected on entry into OnClientClose");

		int iErrorCode = closesocket(m_hClientSocket);
		
		m_hClientSocket = INVALID_SOCKET;
						
		if (iErrorCode == SOCKET_ERROR)
			ReportWinsockErr("Error closing client socket!");
		else
			PrintString("Client socket closed successfully, ready for next client!\n\n");
			
		m_pDoc->SetTitle("WAITING for CONNECTION");
		return 0L;
	}

void CServerView::OnServerOpen() 
	{ 
		WSADATA wsaData;
		int iErrorCode;
		char chLocalInfo[64];
		
	 	if (WSAStartup(WINSOCK_VERSION, &wsaData))
			{
				MessageBeep(MB_ICONSTOP);
				MessageBox("Winsock could not be initialized!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		    WSACleanup();
		    return;
		  }
		else
			WSACleanup();
			
		if (gethostname(chLocalInfo, sizeof(chLocalInfo)))
			{
				ReportWinsockErr("\nCould not resolve local host!\nAre you on-line?\n");
				return;
			}
			
		CString csWinsockID = "\nSERVER READY on ";
		csWinsockID += chLocalInfo;
		csWinsockID += " at PORT No. ";
		csWinsockID += itoa(m_pDoc->m_nServerPort, chLocalInfo, 10);
		csWinsockID += "\n";
		csWinsockID += wsaData.szDescription;
		csWinsockID += "\n";
		PrintString(csWinsockID);
			
	  // Setup the Winsock server using the same procedures found in the quick programs.
	 	m_pDoc->m_hServerSocket = socket(PF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
	 	
	 	if (m_pDoc->m_hServerSocket == INVALID_SOCKET)
	 		{
	 			ReportWinsockErr("Could not create server socket.");
	 			return;
	 		}
	 	
	 	m_pDoc->m_sockServerAddr.sin_family = AF_INET;
	 	m_pDoc->m_sockServerAddr.sin_addr.s_addr = INADDR_ANY;   
	 	m_pDoc->m_sockServerAddr.sin_port = htons(m_pDoc->m_nServerPort);
	 	
	 	// Bind the server socket like the data socket in the QFTP programs.
	 	if (bind(m_pDoc->m_hServerSocket, (LPSOCKADDR)&m_pDoc->m_sockServerAddr, sizeof(m_pDoc->m_sockServerAddr)) == SOCKET_ERROR)
	 		{
	 			ReportWinsockErr("Could not bind server socket.");
	 			return;
	 		}
	 		
	 	// Since the application framework handles all the Windows 
	 	// dirty work, use the asynchronous Winsock functions and design
	 	// the server for optimal Windows performance.
		iErrorCode = WSAAsyncSelect(m_pDoc->m_hServerSocket, m_hWnd, WM_SERVER_ACCEPT, FD_ACCEPT);
		
		if (iErrorCode == SOCKET_ERROR) 
			{
				ReportWinsockErr("WSAAsyncSelect failed on server socket.");
				return;
			}
	 		
	 	if (listen(m_pDoc->m_hServerSocket, QUEUE_SIZE) == SOCKET_ERROR)
	 		{
	 			ReportWinsockErr("Server socket failed to listen.");
				m_pParentMenu->EnableMenuItem(ID_SERVER_OPEN, MF_ENABLED);
	 			return;
	 		}
	
		PrintString("Server socket initialized -- waiting for connections.\n\n");
		
		m_bServerIsOpen = TRUE;
		m_pDoc->SetTitle("WAITING for CONNECTION");
		// END MODIFICATIONS: Internet Programming
		return;	
	}

LRESULT CServerView::OnClientRead(WPARAM wParam, LPARAM lParam)
	{
		// Rather than perform recv's in a loop, let Windows 
		// and Winsock continue to notify the program as data 
		// arrives in the buffer. If the program performed recvs 
		// in a loop, the possibility exists that the program might
		// receive FD_READ notifications for data that already retrieved.
		if (WSAGETASYNCERROR(lParam))
			ReportWinsockErr("Error detected on entry into OnClientRead.");

		int iBytesRead;
		int iBufferLength;
		int iEnd;
		int iSpaceRemaining;
		char chIncomingDataBuffer[1024];
		
		iBufferLength = iSpaceRemaining = sizeof(chIncomingDataBuffer);
		
		iEnd = 0;
		
		iSpaceRemaining -= iEnd;
		iBytesRead = recv(m_hClientSocket, (LPSTR)(chIncomingDataBuffer+iEnd), iSpaceRemaining, NO_FLAGS);
    			
		iEnd+=iBytesRead;
    		
		
    if (iBytesRead == SOCKET_ERROR)
			ReportWinsockErr("OnClientRead recv reported a socket error.");
					
		chIncomingDataBuffer[iEnd] = '\0';
		
		if (lstrlen(chIncomingDataBuffer) != 0)
			PrintString(chIncomingDataBuffer);
		else
			// Since Windows send notification of FD_READ and FD_CLOSE,
			// assume the client has closed the connection if zero bytes
			// are received. The program uses a blocking socket, which means if the
			// connection were still open, recv() would wait for data.
			OnClientClose();

		return(0L); 
	}

void CServerView::OnUpdateServerClose(CCmdUI* pCmdUI) 
	{
		// If the server is open then let the user close it.
		pCmdUI->Enable(m_bServerIsOpen ? TRUE : FALSE);
	}

void CServerView::OnUpdateServerOpen(CCmdUI* pCmdUI) 
	{
		// If the server is open don't let the user try to open it again.
		pCmdUI->Enable(m_bServerIsOpen ? FALSE : TRUE);
	}

void CServerView::OnUpdateFileNew(CCmdUI* pCmdUI) 
	{
		// Always disable the file new option for this class.
		pCmdUI->Enable(FALSE);
	}

void CServerView::OnUpdateFileOpen(CCmdUI* pCmdUI) 
	{
		// Always disable the file open option for this class.
		pCmdUI->Enable(FALSE);
	}

void CServerView::OnUpdateFileSave(CCmdUI* pCmdUI) 
	{
		// Always disable the file save option for this class.
		pCmdUI->Enable(FALSE);
	}

void CServerView::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
	{
		// Always disable the file save as option for this class.
		pCmdUI->Enable(FALSE);
	}
// END MODIFICATIONS: Internet Programming
