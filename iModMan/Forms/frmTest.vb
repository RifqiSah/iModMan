Imports System.Reflection

Public Class frmTest
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim str As String = Space(1024 * 1024)
        Dim ret As Boolean = ReadPak(TextBox1.Text, str)

        If (ret = False) Then
            MsgBox("Ada Error!")
            Exit Sub
        End If

        TextBox2.Text = str
    End Sub

    Private Sub frmTest_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        LoadWin32Library(Application.StartupPath & "\iModMan\zlibwapi.dll")
        LoadWin32Library(Application.StartupPath & "\iModMan\iNative.dll")
        LoadWin32Library(Application.StartupPath & "\iModMan\iCrypto.dll")
        LoadWin32Library(Application.StartupPath & "\iModMan\iDias.dll")
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Dim str As String = Space(1024 * 1024)
        Dim ret As Boolean = DiasUnpackFile("G:\\iModMan\\bin\\iModMan\\00Resource_dv_lk_cyclones.pak\\test.pak", str)

        If (ret = False) Then
            MsgBox("Ada Error!")
            Exit Sub
        End If

        TextBox2.Text = str
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        DiasUnpackFile("G:\\iModMan\\bin\\iModMan\\00Resource_dv_lk_cyclones.pak\\test.pak", "G:\\iModMan\\bin\\iModMan\\00Resource_dv_lk_cyclones.pak\\")
    End Sub
End Class