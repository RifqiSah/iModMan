Imports Newtonsoft.Json.Linq
Imports System.IO

Module mdlUpdater
    Dim frm As Form

    Public Sub doUpdateProg(sFrm As Form)
        frm = sFrm

        ' Delete file yang lama
        If (File.Exists(Application.StartupPath & "\iModMan\~~update.tmp")) Then File.Delete(Application.StartupPath & "\iModMan\~~update.tmp")

        ' Ambil file JSON nya untuk informasi
        Dim json As String = readHttpFile(My.Resources.base_mod & "/" & My.Resources.patchlist)
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

        frmDownloader.setForm(frm)
        frmDownloader.Show()
    End Sub
End Module
