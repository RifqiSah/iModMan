Imports System.ComponentModel
Imports System.IO
Imports System.Net

Public Class frmDownloader
    Public fileDownloadList As New List(Of clsFFile)()

    Dim frm As Form
    Dim other As Boolean = False

    Public Sub setForm(sFrm As Form)
        frm = sFrm
    End Sub

    Public Sub setOther(sO As Boolean)
        other = sO
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
            Dim fPath As String = ""

            lblFileInfo.Text = f.getFileName()
            client.QueryString.Add("file_name", f.getFileName())

            If (other) Then
                fPath = f.getPath()
            Else
                fPath = Path.Combine(Application.StartupPath, f.getPath())

                client.QueryString.Add("file_path", fPath)
                client.QueryString.Add("file_hash", f.getHash())
            End If

            client.DownloadFileAsync(New Uri(f.getUrl()), fPath)

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
            If (Not other) Then
                Dim sHash As String = SHA256CheckSum(filePath).Trim(Chr(0))

                If (Not sHash.Equals(fileHash)) Then
                    MessageBox.Show("Pengunduhan gagal!" & vbCrLf & "File '" & fileName & "' rusak! Silahkan lakukan pengunduhan ulang.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
                    File.Delete(filePath)

                    GoTo Lewat
                End If

                If (Path.GetExtension(filePath) = ".pak") Then ' Filter file *.PAK saja
                    If (Integer.Parse(ReadIniValue("Application", "PakEnlarge")) And Not isAthenaExists()) Then
                        pakExpand(filePath)
                    End If

                    ' Ambil file yang terbaru saja
                    keepLatestFile(fileName)
                End If

                ' MessageBox.Show("Pengunduhan sukses!", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information)
            End If
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