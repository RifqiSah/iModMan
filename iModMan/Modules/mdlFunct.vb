Imports System.Text.RegularExpressions
Imports System.IO
Imports System.Net

Module mdlFunct

    Public Function GetFileNameFromURL(ByVal URL As String) As String
        Try
            Return URL.Substring(URL.LastIndexOf("/") + 1)
        Catch ex As Exception
            Return URL
        End Try
    End Function

    Public Sub keepLatestFile(ByVal sModFileName As String)
        Dim lst As List(Of String) = New List(Of String)

        Dim reg As Regex = New Regex("_[0-9]+\.[0-9]+\.[0-9]+")
        Dim reg2 As Regex = New Regex("[0-9]+\.[0-9]+\.[0-9]+")
        Dim modpath As String = Application.StartupPath

        Dim m As Match = reg.Match(sModFileName)
        Dim key As String = m.ToString()
        Dim filePatern As String = sModFileName.Replace(".pak", "").Replace(key, "")

        ' Search file yg sama dalam 1 directory
        Dim fileCount As String = My.Computer.FileSystem.GetFiles(modpath, FileIO.SearchOption.SearchTopLevelOnly, filePatern & "*").Count
        For Each file As String In My.Computer.FileSystem.GetFiles(modpath, FileIO.SearchOption.SearchTopLevelOnly, filePatern & "*")
            Dim fileInfo = My.Computer.FileSystem.GetFileInfo(file)

            ' Hanya ketika filenya lebih dari 1 artinya user sudah mengupdate file modnya
            If (fileCount > 1) Then
                fileInfo.Delete() ' Delete filenya
                fileCount = fileCount - 1 ' Kurangi terus hingga 1
            End If
        Next
    End Sub

    Public Function keepLatestFilePE(ByVal cFile As clsFFile) As Integer
        Dim AppPath As String = Application.StartupPath

        If (File.Exists(AppPath & "\" & cFile.getPath())) Then
            If (cFile.getVersion.Replace(".", "") > FileVersionInfo.GetVersionInfo(AppPath & "\" & cFile.getPath()).FileVersion.Replace(".", "")) Then
                Return 1
            End If
        Else
            Return 2
        End If

        Return 0
    End Function

    Public Function readHttpFile(ByVal sURL As String) As String
        Dim request As HttpWebRequest = Nothing
        Dim response As HttpWebResponse = Nothing
        Dim reader As StreamReader = Nothing

        frmMain.lstMod.Items.Clear()
        frmMain.chkEnlarge.CheckState = CheckState.Unchecked

        Try
            ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12

            request = DirectCast(WebRequest.Create(sURL), HttpWebRequest)
            request.UserAgent = "request"

            response = DirectCast(request.GetResponse(), HttpWebResponse)
            reader = New StreamReader(response.GetResponseStream())
        Catch ex As Exception
            MessageBox.Show("Kesalahan terjadi!" & vbCrLf & vbCrLf & "Error:" & vbCrLf & ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Application.Exit()
        End Try

        Dim ret As String = reader.ReadToEnd()

        reader.Close()
        response.Close()

        Return ret
    End Function
End Module
