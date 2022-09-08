// servevw.h : interface of the CServerView class
//
/////////////////////////////////////////////////////////////////////////////

class CServerView : public CScrollView
{
private:
	// START CUSTOM CODE: Internet Programming
 	char m_chMsgBuffer[100];
	SOCKET m_hClientSocket;
	SOCKADDR_IN m_sockClientAddr;									// Socket address structure

	BOOL m_bServerIsOpen;
		
	CServerDoc *m_pDoc;
	CWnd *m_pParentWnd;
	CMenu *m_pParentMenu;
	// END MODIFICATIONS: Internet Programming

protected: // create from serialization only
	CServerView();
	DECLARE_DYNCREATE(CServerView)

// Attributes
public:
	CServerDoc* GetDocument();

// Operations
public:
// START CUSTOM CODE: Internet Programming
	virtual void ReportWinsockErr(LPSTR lpszErrorMsg);
	virtual void PrintChar(char chChar, BOOL bLastChar);
	virtual void PrintString(LPSTR lpszString);
	virtual void PrintString(CString csString);
// END MODIFICATIONS: Internet Programming

// Implementation
public:
	virtual ~CServerView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnInitialUpdate(); // called first time after construct

	// Printing support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
	//{{AFX_MSG(CServerView)
	afx_msg void OnServerClose();
	afx_msg void OnServerOpen();
	afx_msg void OnUpdateServerClose(CCmdUI* pCmdUI);
	afx_msg void OnUpdateServerOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	//}}AFX_MSG

	// START CUSTOM CODE: Internet Programming
	afx_msg LRESULT OnServerAccept(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientClose(void);
	afx_msg LRESULT OnClientRead(WPARAM wParam, LPARAM lParam);
	// END MODIFICATIONS: Internet Programming

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in servevw.cpp
inline CServerDoc* CServerView::GetDocument()
   { return (CServerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
