VERSION 2.00
Begin Form frmSockWeb 
   BackColor       =   &H00C0C0C0&
   Caption         =   "SockWEB File Reader"
   ClientHeight    =   2145
   ClientLeft      =   3930
   ClientTop       =   3315
   ClientWidth     =   7845
   Height          =   2550
   Icon            =   SOCKWEB.FRX:0000
   Left            =   3870
   LinkTopic       =   "Form1"
   ScaleHeight     =   2145
   ScaleWidth      =   7845
   Top             =   2970
   Width           =   7965
   Begin TextBox txtLocalFileName 
      BackColor       =   &H00C0C0C0&
      Enabled         =   0   'False
      Height          =   375
      Left            =   6120
      TabIndex        =   8
      TabStop         =   0   'False
      Text            =   "FILENAME.EXT"
      Top             =   480
      Visible         =   0   'False
      Width           =   1455
   End
   Begin CommandButton cmdCancel 
      Caption         =   "CANCEL"
      Height          =   375
      Left            =   6120
      TabIndex        =   7
      Top             =   1200
      Visible         =   0   'False
      Width           =   1455
   End
   Begin TextBox txtBytesTransferred 
      Alignment       =   1  'Right Justify
      BackColor       =   &H0000FFFF&
      Height          =   375
      Left            =   3840
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   480
      Visible         =   0   'False
      Width           =   2175
   End
   Begin CommandButton cmdRead 
      Caption         =   "READ"
      Default         =   -1  'True
      Height          =   375
      Left            =   3600
      TabIndex        =   4
      Top             =   480
      Width           =   2415
   End
   Begin TextBox txtURL 
      Height          =   375
      Left            =   600
      TabIndex        =   3
      Text            =   "/White_House/images/white_house_home.gif"
      Top             =   1200
      Width           =   5415
   End
   Begin TextBox txtWebServer 
      Height          =   375
      Left            =   600
      TabIndex        =   1
      Text            =   "www.whitehouse.gov"
      Top             =   480
      Width           =   2895
   End
   Begin Label lblLocalFileName 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Local File Name"
      Height          =   195
      Left            =   6120
      TabIndex        =   9
      Top             =   240
      Visible         =   0   'False
      Width           =   1395
   End
   Begin Label lblBytesTransferred 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "BYTES TRANSFERRED"
      Height          =   195
      Left            =   3840
      TabIndex        =   5
      Top             =   240
      Visible         =   0   'False
      Width           =   2085
   End
   Begin Label lblURL 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Universal Resource Locator (URL):"
      Height          =   195
      Left            =   600
      TabIndex        =   2
      Top             =   960
      Width           =   3000
   End
   Begin Label lblWebServer 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Web Server:"
      Height          =   195
      Left            =   600
      TabIndex        =   0
      Top             =   240
      Width           =   1080
   End
End
Declare Function closesocket Lib "WinSock.DLL" (ByVal s As Integer) As Integer
Declare Function WSACleanup Lib "WinSock.DLL" () As Integer
Declare Function WSACancelBlockingCall Lib "WinSock.DLL" () As Integer

Declare Function ConnectWebServerSocket Lib "QWEBLIB.DLL" (ByVal lpszHostName As String) As Integer
Declare Function SendWebQuery Lib "QWEBLIB.DLL" (ByVal nSocket As Integer, ByVal lpszURL As String) As Integer
Declare Function RecvWebFile Lib "QWEBLIB.DLL" (ByVal nSocket As Integer, ByVal hFile As Integer) As Integer
Declare Function ExtractFileName Lib "QWEBLIB.DLL" (ByVal lpszPath As String, ByVal lpszFileName As String) As Long

Const INVALID_SOCKET = -1
Const HFILE_ERROR = -1
Const SOCKET_ERROR = -1

Sub cmdCancel_Click ()
    Dim intStatus As Integer
    intStatus = WSACancelBlockingCall()
End Sub

Sub cmdRead_Click ()
    Dim intStatus As Integer                            ' Status value returned by DLL functions
    Dim nSocket As Integer                                      ' Socket handle for the Web connection
    Dim hFile  As Integer                                               ' File handle for the local data file
    Dim nTotalBytes As Long                                     ' Counter for total bytes transferred
    Dim nBytes As Integer                                               ' Byte-count for each call to recv
    Dim lpszLocalFileName As String     ' Filename for the local data file
    Dim lpszPath As String                                      ' Path string for the URL
    Dim PointerAddress As Long                  ' Stores memory address from DLL functions

    ' Make sure the user entered a URL and server address
    If Len(txtURL.Text) = 0 Or Len(txtWebServer.Text) = 0 Then
			MsgBox "Please enter a server name and a Web URL.", MB_ICONSTOP + MB_OK, "WEB File Reader"
			Exit Sub
    End If

    ' Disable and hide the Read button
    cmdRead.Enabled = 0
    cmdRead.Visible = 0
    
    ' Display the text box that shows the number of bytes transferred
    lblBytesTransferred.Visible = 1
    txtBytesTransferred.Visible = 1
    txtBytesTransferred.Text = "CONNECTING"
    
    ' Display the Cancel button so the user can abort the transfer
    cmdCancel.Visible = 1
    
    ' Display the text box that shows the local file name for the transferred file
    txtLocalFileName.Visible = 1
    txtLocalFileName.Enabled = 1
    lblLocalFileName.Visible = 1
    
    ' Extract from the URL a valid DOS file name
    lpszPath = txtURL.Text
    lpszLocalFileName = String$(13, " ")
    PointerAddress = ExtractFileName(lpszPath, lpszLocalFileName)
    txtLocalFileName.Text = lpszLocalFileName
    
    ' Connect to the Web server
    nSocket = ConnectWebServerSocket(txtWebServer)

    If nSocket <> INVALID_SOCKET Then
	txtBytesTransferred.Text = "SENDING QUERY"
	hFile = SendWebQuery(nSocket, txtURL)
    Else
	' If the connection failed, reset the command buttons and exit
	cmdRead.Enabled = 1
	cmdRead.Visible = 1
	lblBytesTransferred.Visible = 0
	txtBytesTransferred.Visible = 0
	txtBytesTransferred.Text = "0"
	cmdCancel.Visible = 0
	txtLocalFileName.Visible = 0
	lblLocalFileName.Visible = 0
	txtLocalFileName.Text = ""
	Exit Sub
    End If

    ' Read the data for the Web file and write it to the local hard disk
    If hFile <> SOCKET_ERROR And hFile <> HFILE_ERROR Then
	txtBytesTransferred.Text = "READING FILE"
	nTotalBytes = 0
	Do
	    nBytes = RecvWebFile(nSocket, hFile)
	    nTotalBytes = nTotalBytes + nBytes
	    txtBytesTransferred.Text = Str$(nTotalBytes)
	Loop While nBytes > 0
    End If

    ' Reset the command buttons and exit
    txtBytesTransferred.Text = "DONE"
    intStatus = closesocket(nSocket)
    intStatus = WSACleanup()
    lblBytesTransferred.Visible = 0
    txtBytesTransferred.Visible = 0
    cmdCancel.Visible = 0
    txtLocalFileName.Visible = 0
    lblLocalFileName.Visible = 0
    txtLocalFileName.Text = ""
    cmdRead.Enabled = 1
    cmdRead.Visible = 1
End Sub

Sub Form_Load ()
    ' Center the form
    frmSockWeb.Left = (Screen.Width - frmSockWeb.Width) / 2
    frmSockWeb.Top = (Screen.Height - frmSockWeb.Height) / 2
End Sub

