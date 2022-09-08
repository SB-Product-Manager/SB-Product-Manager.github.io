Option Explicit

Declare Function closesocket Lib "WINSOCK.DLL" (ByVal hSocket As Integer) As Integer
Declare Function lstrcpy Lib "KERNEL" (ByVal lpToString As Any, ByVal lpFromString As Any) As Long

Declare Function LoadWinsock Lib "QFTPLIB.DLL" () As Integer
Declare Function CloseWinsock Lib "QFTPLIB.DLL" () As Integer
Declare Function CreateListenSocket Lib "QFTPLIB.DLL" (ByVal hControlSocket As Integer) As Integer
Declare Function ConnectFTPControlSocket Lib "QFTPLIB.DLL" (ByVal lpszHostName As String) As Integer
Declare Function ReadDataChannel Lib "QFTPLIB.DLL" (ByVal hCtrlSocket As Integer, ByVal hDataSocket As Integer, ByVal lpszFileName As String) As Integer
Declare Function SendFTPCommand Lib "QFTPLIB.DLL" (ByVal hControlSocket As Integer, ByVal lpszCommandBuffer As String) As Integer
Declare Function GetFTPServerReplyText Lib "QFTPLIB.DLL" () As Long
Declare Function AcceptDataConnection Lib "QFTPLIB.DLL" (ByVal hListenSocket As Integer) As Integer
Declare Function TransferFile Lib "QFTPLIB.DLL" (ByVal hCtrlSocket As Integer, ByVal hDataSocket As Integer, ByVal hFile As Integer) As Integer
Declare Function CreateTransferFile Lib "QFTPLIB.DLL" (ByVal lpszFileName As String) As Integer
Declare Function ExtractFileName Lib "QFTPLIB.DLL" (ByVal lpszPath As String, ByVal lpszFileName As String) As Long

Global Const HFILE_ERROR = -1
Global Const INVALID_SOCKET = -1
Global glbintControlSocket As Integer

Global Const YELLOW = &HFFFF&
Global Const WHITE = &HFFFFFF

Function intDoListCommand (strListCommand As String) As Integer
    Dim intListenSocket As Integer
    Dim intDataSocket As Integer
    Dim strCommand As String
    Dim intServerReplyCode, intWinsockReply  As Integer
    
    subShowButtons (False)
    
    intListenSocket = CreateListenSocket(glbintControlSocket)

    If intListenSocket <> INVALID_SOCKET Then
	strCommand = strListCommand & Chr(13) & Chr(10) ' Add the CRLF
	subShowServerCommand (strCommand)
	intServerReplyCode = SendFTPCommand(glbintControlSocket, strCommand)
	subShowServerReplyCode (intServerReplyCode)
	
	If intServerReplyCode < 400 Then
	    intDataSocket = AcceptDataConnection(intListenSocket)

	    If intDataSocket <> INVALID_SOCKET Then
		intServerReplyCode = ReadDataChannel(glbintControlSocket, intDataSocket, strListCommand & ".CMD")
		subShowServerReplyCode (intServerReplyCode)
		intServerReplyCode = closesocket(intDataSocket)

		' This subroutine reads command results and adds the files to the list box.
		subReadListFile (strListCommand & ".CMD")
		
	    Else
		intWinsockReply = closesocket(intListenSocket)
		intServerReplyCode = 999
		subShowServerReplyCode (intServerReplyCode)
		subShowServerCommand ("INVALID DATA SOCKET!")
	    End If
	    
	Else
	    subShowServerCommand ("UNEXPECTED Reply Code " & intServerReplyCode)
	End If

	
    Else
	intServerReplyCode = 999
	subShowServerReplyCode (intServerReplyCode)
	subShowServerCommand ("INVALID LISTEN SOCKET!")
    End If

    intDoListCommand = intServerReplyCode
    subShowButtons (True)
End Function

Function intDoPASSCommand () As Integer
    Dim strCommand As String
    Dim intServerReplyCode As Integer

    strCommand = "PASS " & frmSockFTP.txtPassword & Chr(13) & Chr(10) ' Add the CRLF
    subShowServerCommand (strCommand)
    intServerReplyCode = SendFTPCommand(glbintControlSocket, strCommand)
    subShowServerReplyCode (intServerReplyCode)
    
    If intServerReplyCode <> 230 Then
	subShowServerCommand ("EXPECTED Reply Code 230")
    End If
    
    intDoPASSCommand = intServerReplyCode
End Function

Function intDoRETRCommand (strFileName As String, optImage As Integer) As Integer
    Dim intListenSocket As Integer
    Dim intDataSocket As Integer
    Dim strCommand As String
    Dim strType As String
    Dim strServerReply As String
    Dim intServerReplyCode, intWinsockReply  As Integer
    
    subShowButtons (False)
    
    intListenSocket = CreateListenSocket(glbintControlSocket)

    If intListenSocket <> INVALID_SOCKET Then
	If optImage = True Then
	    strType = "I"
	Else
	    strType = "A N"
	End If

	strCommand = "TYPE " & strType & Chr(13) & Chr(10) ' Add the CRLF
	subShowServerCommand (strCommand)
	intServerReplyCode = SendFTPCommand(glbintControlSocket, strCommand)
	subShowServerReplyCode (intServerReplyCode)
	
	strCommand = "RETR " & strFileName & Chr(13) & Chr(10) ' Add the CRLF
	subShowServerCommand (strCommand)
	intServerReplyCode = SendFTPCommand(glbintControlSocket, strCommand)
	subShowServerReplyCode (intServerReplyCode)
	
	If intServerReplyCode < 400 Then
	    intDataSocket = AcceptDataConnection(intListenSocket)

	    If intDataSocket <> INVALID_SOCKET Then
		strServerReply = strTransferFile(intDataSocket, strFileName)
		subShowServerCommand (strServerReply)
		intServerReplyCode = CInt(Left$(strServerReply, 3))
		Beep
		intWinsockReply = closesocket(intDataSocket)
	    Else
		intWinsockReply = closesocket(intListenSocket)
		intServerReplyCode = 999
		subShowServerReplyCode (intServerReplyCode)
		subShowServerCommand ("INVALID DATA SOCKET!")
	    End If
	    
	Else
	    subShowServerCommand ("UNEXPECTED Reply Code " & intServerReplyCode)
	End If
    Else
	intServerReplyCode = 999
	subShowServerReplyCode (intServerReplyCode)
	subShowServerCommand ("INVALID LISTEN SOCKET!")
    End If

    intDoRETRCommand = intServerReplyCode
    subShowButtons (True)
End Function

Function intDoUSERCommand () As Integer
    Dim strCommand As String
    Dim intServerReplyCode As Integer

    strCommand = "USER " & frmSockFTP.txtUserID & Chr(13) & Chr(10) ' Add the CRLF
    subShowServerCommand (strCommand)
    intServerReplyCode = SendFTPCommand(glbintControlSocket, strCommand)
    subShowServerReplyCode (intServerReplyCode)

    If intServerReplyCode <> 331 Then
	subShowServerCommand ("EXPECTED Reply Code 331")
    End If
    
    intDoUSERCommand = intServerReplyCode
End Function

Function strCutCrLf (strText As String) As String
    Dim intCrLfLocation As Integer

    intCrLfLocation = InStr(1, strText, Chr(13) & Chr(10))  ' Add the CRLF

    If intCrLfLocation > 0 Then
	intCrLfLocation = intCrLfLocation - 1
    Else
	intCrLfLocation = Len(strText)
    End If
    
    strCutCrLf = Left(strText, intCrLfLocation)
End Function

Function strDoCDUPCommand () As String
    Dim strCommand As String                ' The command string to transmit
    Dim intServerReplyCode As Integer       ' The server's reply

    subShowButtons (False)                ' Turn the buttons off

    strCommand = "CDUP" & Chr(13) & Chr(10) ' Add the CRLF
    subShowServerCommand (strCommand)       ' Display the command for the user
    intServerReplyCode = SendFTPCommand(glbintControlSocket, strCommand)
    subShowServerReplyCode (intServerReplyCode)
    
    If intServerReplyCode = 250 Then        ' If command was successful display the new file list
	intServerReplyCode = intDoListCommand("NLST")
    End If
    
    strDoCDUPCommand = strDoPWDCommand()
    subShowButtons (True)
End Function

Function strDoCWDCommand (strDirectory As String) As String
    Dim strCommand As String
    Dim intServerReplyCode As Integer

    subShowButtons (False)
    strCommand = "CWD " & strDirectory & Chr(13) & Chr(10) ' Add the CRLF
    subShowServerCommand (strCommand)
    intServerReplyCode = SendFTPCommand(glbintControlSocket, strCommand)
    subShowServerReplyCode (intServerReplyCode)
    
    If intServerReplyCode = 250 Then
	intServerReplyCode = intDoListCommand("NLST")
    End If
    
    strDoCWDCommand = strDoPWDCommand()
    subShowButtons (True)
End Function

Function strDoPWDCommand () As String
    Dim strCommand As String
    Dim strDirectory As String
    Dim intServerReplyCode As Integer

    subShowButtons (False)
    strCommand = "PWD" & Chr(13) & Chr(10) ' Add the CRLF
    subShowServerCommand (strCommand)
    intServerReplyCode = SendFTPCommand(glbintControlSocket, strCommand)
    subShowServerReplyCode (intServerReplyCode)

    If intServerReplyCode = 257 Then
	strDirectory = strGetServerReplyText()
	strDirectory = strCutCrLf(strDirectory)
	strDirectory = strExtractQuotedExpression(strDirectory)
    Else
	strDirectory = ""
    End If

    strDoPWDCommand = strDirectory
    subShowButtons (True)
End Function

Function strDoSYSTCommand () As String
    Dim strCommand As String
    Dim strSystemType As String
    Dim intServerReplyCode As Integer

    subShowButtons (False)

    strCommand = "SYST" & Chr(13) & Chr(10) ' Add the CRLF
    subShowServerCommand (strCommand)
    intServerReplyCode = SendFTPCommand(glbintControlSocket, strCommand)
    subShowServerReplyCode (intServerReplyCode)
    
    If intServerReplyCode = 215 Then
	strSystemType = strGetServerReplyText()
	strSystemType = strCutCrLf(strSystemType)
    Else
	strSystemType = ""
    End If
    strDoSYSTCommand = strSystemType

    subShowButtons (True)
End Function

Function strExtractQuotedExpression (strValue As String) As String
    Dim int1stQuoteLocation As Integer
    Dim int2ndQuoteLocation As Integer
    Dim strQuotedValue As String

    ' Use the caller's value if two quotes are not found
    strQuotedValue = strValue
    
    int1stQuoteLocation = InStr(1, strValue, Chr(34)) ' Double quote
    
    If int1stQuoteLocation > 0 Then
	int2ndQuoteLocation = InStr(int1stQuoteLocation + 1, strValue, Chr(34))
	If int2ndQuoteLocation > 0 Then
	    strQuotedValue = Mid$(strValue, int1stQuoteLocation + 1, int2ndQuoteLocation - int1stQuoteLocation - 1)
	End If
    End If

    strExtractQuotedExpression = strQuotedValue
End Function

Function strGetServerReply () As String
    Dim lpReplyTextAddress As Long
    Dim strReply As String

    lpReplyTextAddress = GetFTPServerReplyText()
    strReply = Space$(2048)

    lpReplyTextAddress = lstrcpy(strReply, lpReplyTextAddress)

    strGetServerReply = strReply
End Function

Function strGetServerReplyText () As String
    Dim strReplyText As String
    
    strReplyText = strGetServerReply()
    strGetServerReplyText = Right(strReplyText, Len(strReplyText) - 4)

End Function

Function strTransferFile (hDataSocket As Integer, strFileName As String) As String
    Dim hFile As Integer            ' File handle for the local file
    Dim intBytes As Integer         ' Bytes received for each data channel read
    Dim lngTotalBytes As Long       ' Total bytes received from the data channel
    Dim strServerReply              ' Reply from server after the transfer
    Dim lngPointerAddress           ' LPSTR Pointer value
    Dim strLocalFile As String      ' Local filename
    Dim strHostName As String       ' Remote host name
    Dim strUserID As String         ' User ID used to log in
    Dim strPassword As String       ' Password used to login
    Dim strSystemType As String     ' Remote host system type

    ' Create a valid DOS filename from the user's selection
    strLocalFile = Space$(13)
    lngPointerAddress = ExtractFileName(strFileName, strLocalFile)
    hFile = CreateTransferFile(strLocalFile)

    If hFile <> HFILE_ERROR Then

	' Save text-box values
	strHostName = frmSockFTP.txtHostName.Text
	strUserID = frmSockFTP.txtUserID.Text
	strPassword = frmSockFTP.txtPassword.Text
	strSystemType = frmSockFTP.txtSystemType.Text
	
	' Change the background to yellow to highlight the transfer action
	frmSockFTP.txtHostName.BackColor = YELLOW
	frmSockFTP.txtUserID.BackColor = YELLOW
	frmSockFTP.txtPassword.BackColor = YELLOW
	frmSockFTP.txtSystemType.BackColor = YELLOW

	' Fill the text-boxes with the file transfer information
	frmSockFTP.txtHostName.Text = "TRANSFERING FILE"
	frmSockFTP.txtUserID.Text = strFileName
	frmSockFTP.txtPassword.Text = strLocalFile

	' Change the text-box labels for the file transfer
	frmSockFTP.lblUserId.Caption = "Remote File:"
	frmSockFTP.lblPassword.Caption = "Local File:"
	frmSockFTP.lblSystemType.Caption = "Bytes:"
	
	' Initialize the total byte counter and enter the read loop
	lngTotalBytes = 0
	Do
	    ' Read data from the data channel and update the byte count
	    intBytes = TransferFile(glbintControlSocket, hDataSocket, hFile)
	    lngTotalBytes = lngTotalBytes + intBytes
	    frmSockFTP.txtSystemType.Text = Str$(lngTotalBytes)
	Loop While intBytes > 0

	' Read the server's reply
	strServerReply = strGetServerReply()
	MsgBox strServerReply, , "SockFTP"
	
	' Restore the background colors
	frmSockFTP.txtHostName.BackColor = WHITE
	frmSockFTP.txtUserID.BackColor = WHITE
	frmSockFTP.txtPassword.BackColor = WHITE
	frmSockFTP.txtSystemType.BackColor = WHITE
	
	' Restore the text-box values
	frmSockFTP.txtHostName.Text = strHostName
	frmSockFTP.txtUserID.Text = strUserID
	frmSockFTP.txtPassword.Text = strPassword
	frmSockFTP.txtSystemType.Text = strSystemType

	' Restore the text-box labels
	frmSockFTP.lblUserId.Caption = "USER ID:"
	frmSockFTP.lblPassword.Caption = "PASSWORD:"
	frmSockFTP.lblSystemType.Caption = "System Type:"

	strTransferFile = strServerReply
    Else
	MsgBox "Unable to create " & strLocalFile, , "SockFTP"
	strTransferFile = "File creation error."
    End If
    
End Function

Sub subCenterForm (frm As Form)
    ' Center form horizontally
    frm.Left = (Screen.Width - frm.Width) / 2
    ' Center form vertically
    frm.Top = (Screen.Height - frm.Height) / 2
End Sub

Sub subCloseIncompleteConnection ()
    Dim intWinsockReplyCode As Integer

    intWinsockReplyCode = closesocket(glbintControlSocket)
    
    frmSockFTP.cmdDisconnect.Visible = False
    frmSockFTP.cmdClear.Visible = False
    
    frmSockFTP.cmdConnect.Visible = True
    frmSockFTP.cmdExit.Visible = True

    subShowServerCommand ("Socket closed--incomplete connection!")
End Sub

Sub subReadListFile (strFileName As String)
    Dim intFileHandle As Integer
    
    intFileHandle = FreeFile
    
    frmSockFTP.lstServerFiles.Clear

    On Error GoTo ErrorHandler

    Open strFileName For Input Access Read Lock Write As intFileHandle
    
    Do While Not EOF(intFileHandle)

	Line Input #intFileHandle, strFileName
	frmSockFTP.lstServerFiles.AddItem strFileName
    Loop

Closefile:
    Close #intFileHandle
    Exit Sub

ErrorHandler:
    Resume Closefile
End Sub

Sub subShowButtons (intButtonToggle As Integer)
    frmSockFTP.cmdListDir.Enabled = intButtonToggle
    frmSockFTP.cmdRetrieve.Enabled = intButtonToggle
    frmSockFTP.cmdChgWorkingDir.Enabled = intButtonToggle
    frmSockFTP.cmdCwdUp.Enabled = intButtonToggle
    frmSockFTP.cmdNameList.Enabled = intButtonToggle
End Sub

Sub subShowServerCommand (ByVal strCommand As String)
    Dim strListBox As String
    
    strListBox = strCutCrLf(strCommand)

    frmSockFTP.lstServerDialog.AddItem strListBox, 0
End Sub

Sub subShowServerReplyCode (intReplyCode As Integer)
    Dim strListBox As String
    
    strListBox = Str$(intReplyCode)
    frmSockFTP.lstServerDialog.AddItem strListBox, 0
End Sub

