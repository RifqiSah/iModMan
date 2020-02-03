Imports System.ComponentModel
Imports System.IO
Imports System.Net

Public Class frmDownloader
    Public fileDownloadList As New List(Of clsFFile)()
    Dim i As Integer = -1
    Dim frm As Form

    Public Sub setForm(sFrm As Form)
        frm = sFrm
    End Sub

    Private Sub frmDownloader_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        ' MsgBox(fileDownloadList.Count)
    End Sub

    Private Sub frmDownloader_Shown(sender As Object, e As EventArgs) Handles Me.Shown
        doUpdate()
    End Sub

    Private Sub doUpdate()
        If (fileDownloadList.Count > 0) Then
            Dim client As WebClient = New WebClient()

            AddHandler client.DownloadProgressChanged, AddressOf ShowDownloadProgress
            AddHandler client.DownloadFileCompleted, AddressOf OnDownloadComplete

            Dim f As clsFFile = fileDownloadList.Item(0)

            lblFileInfo.Text = f.getFileName()
            client.QueryString.Add("file_name", f.getFileName())
            client.QueryString.Add("file_path", Application.StartupPath & "/" & f.getPath())
            client.QueryString.Add("file_hash", f.getHash())
            client.DownloadFileAsync(New Uri(f.getUrl()), Application.StartupPath & "/" & f.getPath())

            fileDownloadList.RemoveAt(0)
        Else
            If (Not IsNothing(frm)) Then frm.Show()
            Close()
        End If
    End Sub

    Private Sub OnDownloadComplete(ByVal sender As Object, ByVal e As AsyncCompletedEventArgs)
        Dim fileName As String = (CType((sender), WebClient)).QueryString("file_name")
        Dim filePath As String = (CType((sender), WebClient)).QueryString("file_path")
        Dim fileHash As String = (CType((sender), WebClient)).QueryString("file_hash")

        If Not e.Cancelled AndAlso e.Error Is Nothing Then
            Dim sHash As String = resolveModule("iCore.dll", "clsCrypto").SHA256CheckSum(filePath)
            If (String.Compare(sHash, fileHash) <> 0) Then
                MessageBox.Show("Pengunduhan gagal!" & vbCrLf & "File '" & fileName & "' rusak! Silahkan buka ulang aplikasi untuk mengunduh ulang.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
                File.Delete(filePath)

                GoTo Lewat
            End If

            If (Path.GetExtension(filePath) = ".pak") Then ' Hanya .pak saja yang diperbesar
                If (Integer.Parse(ReadIniValue("Application", "PakEnlarge")) And Not isAthenaExists()) Then pakExpand(filePath)

                ' Ambil file yang terbaru saja
                keepLatestFile(fileName)
            End If

            ' MessageBox.Show("Pengunduhan sukses!", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information)
        Else
            MessageBox.Show("Pengunduhan gagal!" & vbCrLf & e.Error.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            File.Delete(filePath)
            Application.Exit()
        End If

Lewat:
        doUpdate()
    End Sub

    Private Sub ShowDownloadProgress(ByVal sender As Object, ByVal e As DownloadProgressChangedEventArgs)
        progFile.Value = e.ProgressPercentage
    End Sub
End Class