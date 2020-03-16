Imports Newtonsoft.Json.Linq
Imports System.IO
Imports System.Net

Module mdlUpdater
    Public Sub execFile(sPath As String)
        Dim psi As New ProcessStartInfo

        psi.FileName = sPath
        psi.Arguments = "/UPDATED"
        psi.Verb = "runas"
        psi.WorkingDirectory = Path.GetDirectoryName(sPath)
        psi.UseShellExecute = False

        Process.Start(psi)
    End Sub

    Private Function readHttpFile(ByVal sURL As String) As String
        Dim request As HttpWebRequest = Nothing
        Dim response As HttpWebResponse = Nothing
        Dim reader As StreamReader = Nothing

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

        Return reader.ReadToEnd()
    End Function

    Private Function keepLatestFilePE(ByVal cFile As clsFFile) As Integer
        Dim AppPath As String = Path.Combine(Application.StartupPath, "..")

        If (File.Exists(AppPath & "\" & cFile.getPath())) Then
            If (cFile.getVersion.Replace(".", "") > FileVersionInfo.GetVersionInfo(AppPath & "\" & cFile.getPath()).FileVersion.Replace(".", "")) Then
                Return 1
            End If
        Else
            Return 2
        End If

        Return 0
    End Function

    Public Sub doUpdateProg()
        ' Ambil file JSON nya untuk informasi
        Dim json As String = readHttpFile("https://dn.alriftech.com/mods/patchlist.json")
        Dim ser As JObject = JObject.Parse(json)
        Dim main_files As JArray = ser("main_files")

        ' Lihat perubahan apa yang terjadi
        ' changeLog = String.Format(ser.Item("main").ToString())

        For Each item As JObject In main_files
            Dim f As clsFFile = New clsFFile(
                item.SelectToken("name").ToString(),
                item.SelectToken("path").ToString(),
                item.SelectToken("version").ToString(),
                item.SelectToken("url").ToString(),
                item.SelectToken("desc").ToString(),
                item.SelectToken("hash").ToString())

            ' Mulai pengecekan file
            Dim ret As Integer = keepLatestFilePE(f)
            If (ret <> 0) Then
                frmDownloader.fileDownloadList.Add(f)
            End If
        Next

        frmDownloader.Show()
    End Sub
End Module
