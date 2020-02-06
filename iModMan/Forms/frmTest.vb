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
End Class