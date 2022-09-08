VERSION 2.00
Begin Form frmSockFTP 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "VB Sockman FTP"
   ClientHeight    =   6570
   ClientLeft      =   1680
   ClientTop       =   2625
   ClientWidth     =   8805
   Height          =   6975
   Icon            =   SOCKFTP.FRX:0000
   Left            =   1620
   LinkTopic       =   "Form1"
   ScaleHeight     =   6570
   ScaleWidth      =   8805
   Top             =   2280
   Width           =   8925
   Begin CommandButton cmdNameList 
      Caption         =   "&Name List "
      Height          =   375
      Left            =   3960
      TabIndex        =   7
      Top             =   2040
      Width           =   1215
   End
   Begin CommandButton cmdClear 
      Caption         =   "&Clear"
      Height          =   375
      Left            =   7440
      TabIndex        =   6
      Top             =   1080
      Visible         =   0   'False
      Width           =   1215
   End
   Begin CommandButton cmdListDir 
      Caption         =   "&List "
      Height          =   375
      Left            =   7440
      TabIndex        =   14
      TabStop         =   0   'False
      Top             =   1560
      Width           =   1215
   End
   Begin CommandButton cmdDisconnect 
      Caption         =   "&Disconnect"
      Height          =   375
      Left            =   5280
      TabIndex        =   5
      Top             =   1080
      Visible         =   0   'False
      Width           =   2055
   End
   Begin CommandButton cmdCwdUp 
      Caption         =   "CWD &Up"
      Height          =   375
      Left            =   7440
      TabIndex        =   9
      Top             =   2040
      Width           =   1215
   End
   Begin PictureBox picJPLogo 
      AutoSize        =   -1  'True
      BorderStyle     =   0  'None
      Height          =   480
      Left            =   5280
      Picture         =   SOCKFTP.FRX:0302
      ScaleHeight     =   480
      ScaleWidth      =   480
      TabIndex        =   25
      TabStop         =   0   'False
      Top             =   240
      Width           =   480
   End
   Begin TextBox txtSystemType 
      Height          =   375
      Left            =   1680
      TabIndex        =   17
      TabStop         =   0   'False
      Top             =   1560
      Width           =   2175
   End
   Begin CommandButton cmdChgWorkingDir 
      Caption         =   "Chg &Working Dir"
      Height          =   375
      Left            =   5280
      TabIndex        =   8
      Top             =   2040
      Width           =   2055
   End
   Begin CommandButton cmdRetrieve 
      Caption         =   "&Retrieve"
      Height          =   495
      Left            =   6960
      TabIndex        =   12
      Top             =   5880
      Width           =   1695
   End
   Begin TextBox txtWorkingDir 
      Height          =   375
      Left            =   5280
      TabIndex        =   16
      TabStop         =   0   'False
      Top             =   1560
      Width           =   2055
   End
   Begin ListBox lstServerDialog 
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   9.75
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   4350
      Left            =   120
      TabIndex        =   15
      Top             =   2040
      Width           =   3735
   End
   Begin ListBox lstServerFiles 
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   9.75
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   3150
      Left            =   3960
      TabIndex        =   13
      Top             =   2520
      Width           =   4695
   End
   Begin Frame fraFileType 
      Height          =   615
      Left            =   3960
      TabIndex        =   24
      Top             =   5760
      Width           =   2895
      Begin OptionButton optAsciiFileType 
         Caption         =   "ASCII"
         Height          =   375
         Left            =   1800
         TabIndex        =   11
         Top             =   120
         Width           =   975
      End
      Begin OptionButton optImageFileType 
         Caption         =   "IMAGE (Binary)"
         Height          =   375
         Left            =   120
         TabIndex        =   10
         Top             =   120
         Value           =   -1  'True
         Width           =   1695
      End
   End
   Begin PictureBox picSockman 
      AutoSize        =   -1  'True
      BorderStyle     =   0  'None
      Height          =   480
      Left            =   120
      Picture         =   SOCKFTP.FRX:0604
      ScaleHeight     =   480
      ScaleWidth      =   480
      TabIndex        =   18
      TabStop         =   0   'False
      Top             =   240
      Width           =   480
   End
   Begin CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   7440
      TabIndex        =   4
      Top             =   1080
      Width           =   1215
   End
   Begin CommandButton cmdConnect 
      Caption         =   "&Connect"
      Default         =   -1  'True
      Height          =   375
      Left            =   5280
      TabIndex        =   3
      Top             =   1080
      Width           =   2055
   End
   Begin TextBox txtPassword 
      Height          =   375
      Left            =   1680
      TabIndex        =   2
      Text            =   "guest"
      Top             =   1080
      Width           =   3495
   End
   Begin TextBox txtUserID 
      Height          =   375
      Left            =   1680
      TabIndex        =   1
      Text            =   "anonymous"
      Top             =   600
      Width           =   3495
   End
   Begin TextBox txtHostName 
      Height          =   375
      Left            =   1680
      TabIndex        =   0
      Text            =   "NIC.DDN.MIL"
      Top             =   120
      Width           =   3495
   End
   Begin Label lblFTP 
      AutoSize        =   -1  'True
      Caption         =   "SockMan FTP"
      FontBold        =   -1  'True
      FontItalic      =   -1  'True
      FontName        =   "MS Serif"
      FontSize        =   12
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      ForeColor       =   &H000000FF&
      Height          =   285
      Left            =   6240
      TabIndex        =   27
      Top             =   600
      Width           =   1710
   End
   Begin Label lblInternetProgramming 
      Caption         =   "Internet Programming"
      FontBold        =   -1  'True
      FontItalic      =   -1  'True
      FontName        =   "MS Serif"
      FontSize        =   13.5
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   5880
      TabIndex        =   26
      Top             =   240
      Width           =   3015
      WordWrap        =   -1  'True
   End
   Begin Label lblSystemType 
      Alignment       =   1  'Right Justify
      Caption         =   "System Type: "
      Height          =   255
      Left            =   0
      TabIndex        =   23
      Top             =   1680
      Width           =   1635
   End
   Begin Label lblWorkingDir 
      Alignment       =   1  'Right Justify
      Caption         =   "Working Dir:"
      Height          =   375
      Left            =   3960
      TabIndex        =   22
      Top             =   1560
      Width           =   1215
   End
   Begin Label lblPassword 
      Alignment       =   1  'Right Justify
      Caption         =   "PASSWORD:"
      Height          =   255
      Left            =   0
      TabIndex        =   21
      Top             =   1200
      Width           =   1635
   End
   Begin Label lblUserId 
      Alignment       =   1  'Right Justify
      Caption         =   "USER ID:"
      Height          =   255
      Left            =   60
      TabIndex        =   20
      Top             =   720
      Width           =   1575
   End
   Begin Label lblHostName 
      Alignment       =   1  'Right Justify
      Caption         =   "Host:"
      Height          =   375
      Left            =   240
      TabIndex        =   19
      Top             =   120
      Width           =   1335
   End
End

Sub cmdChgWorkingDir_Click ()
    Dim intServerReplyCode As Integer
    Dim intListIndex As Integer
    Dim strDir As String
    
    intListIndex = frmSockFTP.lstServerFiles.ListIndex
    strDir = frmSockFTP.lstServerFiles.List(intListIndex)
    
    txtWorkingDir.Text = strDoCWDCommand(strDir)
End Sub

Sub cmdClear_Click ()
    frmSockFTP.lstServerDialog.Clear
End Sub

Sub cmdConnect_Click ()
    Dim intServerReplyCode As Integer
    Dim strCommand As String
    
    frmSockFTP.cmdConnect.Visible = False
    frmSockFTP.cmdExit.Visible = False
    frmSockFTP.lstServerFiles.Clear

    glbintControlSocket = ConnectFTPControlSocket(frmSockFTP.txtHostName)
    
    If glbintControlSocket <> INVALID_SOCKET Then
        Beep
        MsgBox strGetServerReply(), MB_OK Or MB_ICONINFORMATION, "SockFTP"
        subShowServerCommand ("CONNECTED to: " & frmSockFTP.txtHostName)
        intServerReplyCode = intDoUSERCommand()

        If intServerReplyCode = 331 Then
            Beep
            MsgBox strGetServerReply(), MB_OK Or MB_ICONINFORMATION, "SockFTP"
            intServerReplyCode = intDoPASSCommand()

            If intServerReplyCode = 230 Then
                Beep
                MsgBox strGetServerReply(), MB_OK Or MB_ICONINFORMATION, "SockFTP"
                frmSockFTP.txtWorkingDir = strDoPWDCommand()
                frmSockFTP.txtSystemType = strDoSYSTCommand()
                frmSockFTP.cmdDisconnect.Visible = True
                frmSockFTP.cmdClear.Visible = True
                subShowServerCommand ("Logged into " & frmSockFTP.txtHostName)
                intServerReplyCode = intDoListCommand("NLST")
                subShowButtons (True)
            Else
                subCloseIncompleteConnection
            End If
        Else
            subCloseIncompleteConnection
        End If
        
    Else
        ' Make buttons visible if the connection failed. Otherwise, let
        ' cmdDisconnect_Click make them visible when disconnecting.
        frmSockFTP.cmdConnect.Visible = True
        frmSockFTP.cmdExit.Visible = True
    End If
End Sub

Sub cmdCwdUp_Click ()
    Dim intServerReplyCode As Integer

    txtWorkingDir.Text = strDoCDUPCommand()
End Sub

Sub cmdDisconnect_Click ()
    Dim intServerReplyCode As Integer
    Dim intWinsockReplyCode As Integer
    Dim strCommand As String
    
    frmSockFTP.cmdDisconnect.Visible = False
    frmSockFTP.cmdClear.Visible = False
    subShowButtons (False)

    strCommand = "QUIT" & Chr(13) & Chr(10) ' Add the CRLF
    subShowServerCommand (strCommand)
    intServerReplyCode = SendFTPCommand(glbintControlSocket, strCommand)
    subShowServerReplyCode (intServerReplyCode)

    intWinsockReplyCode = closesocket(glbintControlSocket)

    frmSockFTP.txtWorkingDir = ""
    frmSockFTP.txtSystemType = ""
    frmSockFTP.cmdConnect.Visible = True
    frmSockFTP.cmdExit.Visible = True
    frmSockFTP.lstServerFiles.Clear

End Sub

Sub cmdExit_Click ()
    Dim intSuccess As Integer
    
    intSuccess = CloseWinsock()
    End
End Sub

Sub cmdListDir_Click ()
    Dim intServerReplyCode As Integer

    intServerReplyCode = intDoListCommand("LIST")
End Sub

Sub cmdNameList_Click ()
    Dim intServerReplyCode As Integer

    intServerReplyCode = intDoListCommand("NLST")
End Sub

Sub cmdRetrieve_Click ()
    Dim intServerReplyCode As Integer
    Dim intListIndex, optImage As Integer
    Dim strFile As String
    
    intListIndex = frmSockFTP.lstServerFiles.ListIndex
    strFile = frmSockFTP.lstServerFiles.List(intListIndex)
    optImage = optImageFileType.Value

    intServerReplyCode = intDoRETRCommand(strFile, optImage)
End Sub

Sub Form_Load ()
    Dim intSuccess As Integer
    
    subCenterForm frmSockFTP
    subShowButtons (False)
    intSuccess = LoadWinsock()
End Sub

Sub Form_Unload (Cancel As Integer)
    cmdExit_Click
End Sub

