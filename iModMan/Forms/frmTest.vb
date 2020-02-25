Imports System.IO
Imports System.Reflection
Imports Newtonsoft.Json.Linq

Public Class frmTest
    Dim str As String = Space(1024 * 1000)
    Dim ret As Boolean = False

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        ret = DnPakRead(TextBox1.Text, str)
        If (ret = False) Then
            MsgBox("Ada Error!")
            Exit Sub
        End If

        TextBox2.Text = str
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click

    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        ret = DnPakUnpack(TextBox1.Text, Path.GetDirectoryName(TextBox1.Text))
        If (ret = False) Then
            MsgBox("Ada Error!")
            Exit Sub
        End If

        TextBox2.Text = "Sukses unpack!"
    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        ret = ReadEris(TextBox1.Text, str)
        If (ret = False) Then
            MsgBox("Ada Error!")
            Exit Sub
        End If

        TextBox2.Text = str
    End Sub

    Private Sub frmTest_Closed(sender As Object, e As EventArgs) Handles Me.Closed
        Application.Exit()
    End Sub

    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        Dim sFile As String = "G:\\iModMan\\bin\\test.dias"
        DiasPakPack(sFile, "")
    End Sub

    Private Sub partialPaks()
        Dim afrom As Integer = Integer.Parse(txtPartialFrom.Text)
        Dim ato As Integer = Integer.Parse(txtPartialTo.Text)

        For i As Integer = afrom To ato
            Dim url As String = String.Format("http://patchsea.dragonnest.com/Game/DragonNest/Patch/{0}/Patch{0}.pak", i.ToString("D8"))
            Dim fName As String = String.Format("Patch{0}.pak", i.ToString("D8"))
            Dim f As clsFFile = New clsFFile(
                fName,
                "H:\Dragon Nest\DN Partial Paks\" & fName,
                "0.0.0.0",
                url,
                "DN Partial PAK",
                "NO HASH")
            frmDownloader.fileDownloadList.Add(f)
        Next

        frmDownloader.setForm(Me)
        frmDownloader.setOther(True)
        frmDownloader.Show()
    End Sub

    Private Sub loadPartialPaks()
        Dim dir As DirectoryInfo = New DirectoryInfo("H:\Dragon Nest\DN Partial Paks")
        Dim files As FileInfo() = dir.GetFiles().OrderBy(Function(p) p.Name).ToArray()

        For Each file As FileInfo In files
            cmbPartialPak.Items.Add(file.Name)
        Next

        cmbPartialPak.SelectedIndex = 0
    End Sub

    Private Sub btnPartialDownload_Click(sender As Object, e As EventArgs) Handles btnPartialDownload.Click
        partialPaks()
    End Sub

    Private Sub txtPartialFrom_KeyPress(sender As Object, e As KeyPressEventArgs) Handles txtPartialFrom.KeyPress
        If Not Char.IsNumber(e.KeyChar) AndAlso Not Char.IsControl(e.KeyChar) Then e.KeyChar = ""
    End Sub

    Private Sub txtPartialTo_KeyPress(sender As Object, e As KeyPressEventArgs) Handles txtPartialTo.KeyPress
        If Not Char.IsNumber(e.KeyChar) AndAlso Not Char.IsControl(e.KeyChar) Then e.KeyChar = ""
    End Sub

    Private Sub frmTest_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        loadPartialPaks()
    End Sub

    Private Sub cmbPartialPak_SelectedIndexChanged(sender As Object, e As EventArgs) Handles cmbPartialPak.SelectedIndexChanged
        TextBox1.Text = "H:\Dragon Nest\DN Partial Paks\" & cmbPartialPak.SelectedItem.ToString()
    End Sub
End Class