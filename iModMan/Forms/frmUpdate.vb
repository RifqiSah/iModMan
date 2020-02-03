Imports System.ComponentModel
Imports System.IO
Imports System.Net

Public Class frmUpdate
    Private local As String = Application.StartupPath & "\~~update.tmp"

    Private Sub frmUpdate_Activated(sender As Object, e As EventArgs) Handles Me.Activated
        txtChangelog.SelectionLength = 0
    End Sub

    Private Sub frmUpdate_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Icon = My.Resources.Icon
    End Sub

    Private Sub btnNo_Click(sender As Object, e As EventArgs) Handles btnNo.Click
        Visible = False
        frmMain.Show()
        Close()
    End Sub

    Private Sub btnYes_Click(sender As Object, e As EventArgs) Handles btnYes.Click
        Dim client As New WebClient()

        AddHandler client.DownloadProgressChanged, AddressOf ShowDownloadProgress
        AddHandler client.DownloadFileCompleted, AddressOf OnDownloadComplete

        Label3.Visible = False
        prgUpd.Visible = True
        btnYes.Enabled = False
        btnNo.Enabled = False

        ' client.DownloadFileAsync(New Uri(My.Resources.base_mod & "/" & getFilePath()), local)
    End Sub

    Private Sub OnDownloadComplete(ByVal sender As Object, ByVal e As AsyncCompletedEventArgs)
        ' Hidden filenya
        File.SetAttributes(local, FileAttributes.Hidden Or FileAttributes.System)

        Label3.Visible = True
        prgUpd.Visible = False
        btnYes.Enabled = True
        btnNo.Enabled = True

        If Not e.Cancelled AndAlso e.Error Is Nothing Then
            MessageBox.Show("Pengunduhan sukses!" & vbCrLf & "Pemasangan akan dilakukan setelah Anda menekan tombol 'OK'.", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information)

            execFile(local)
            Application.Exit()
        Else
            MessageBox.Show("Pengunduhan gagal!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
        End If
    End Sub

    Private Sub ShowDownloadProgress(ByVal sender As Object, ByVal e As DownloadProgressChangedEventArgs)
        prgUpd.Value = e.ProgressPercentage
    End Sub
End Class