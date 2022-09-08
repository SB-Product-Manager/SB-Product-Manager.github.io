// servedoc.cpp : implementation of the CServerDoc class
//

#include "stdafx.h"
#include "server1.h"

#include "serv1doc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerDoc

IMPLEMENT_DYNCREATE(CServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CServerDoc, CDocument)
	//{{AFX_MSG_MAP(CServerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDoc construction/destruction

CServerDoc::CServerDoc()
{
	// TODO: add one-time construction code here
	
	// START CUSTOM CODE: Internet Programming
	m_lLineNumber = 0;
	m_lColumnNumber = 0;
	// END MODIFICATIONS: Internet Programming
}

CServerDoc::~CServerDoc()
{
}

BOOL CServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return(FALSE);
	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	// START CUSTOM CODE: Internet Programming
  // Get the port to demonstrate from the SERVER.INI file
	m_nServerPort = GetPrivateProfileInt("ProtocolPort", "Port", 5000, ".\\server.ini");
	// END MODIFICATIONS: Internet Programming

	return(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CServerDoc serialization

void CServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CServerDoc diagnostics

#ifdef _DEBUG
void CServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CServerDoc commands

