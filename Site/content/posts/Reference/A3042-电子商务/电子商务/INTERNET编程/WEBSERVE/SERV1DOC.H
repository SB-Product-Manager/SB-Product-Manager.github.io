// servedoc.h : interface of the CServerDoc class
//
/////////////////////////////////////////////////////////////////////////////

// START CUSTOM CODE: Internet Programming
const MAX_LINES = 1000;														// Maximum lines per document
// END MODIFICATIONS: Internet Programming

class CServerDoc : public CDocument
{

protected: // create from serialization only
	CServerDoc();
	DECLARE_DYNCREATE(CServerDoc)
	
// Attributes
public:
	// START CUSTOM CODE: Internet Programming
  CString m_csText[MAX_LINES];										// CString array -- one per line
  LONG m_lLineNumber, m_lColumnNumber;
	UINT m_nServerPort;															// Server socket handle
	SOCKET m_hServerSocket;													// Server port
	SOCKADDR_IN m_sockServerAddr, m_sockClientAddr;	// Socket address structure
	LPHOSTENT m_lpHostEntry;												// Internet host information structure
	LPSERVENT m_lpServEntry;												// Service information structure
	// END MODIFICATIONS: Internet Programming

// Operations
public:

// Implementation
public:
	virtual ~CServerDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CServerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
