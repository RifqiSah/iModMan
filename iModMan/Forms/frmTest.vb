Imports System.Reflection

Public Class frmTest
    Private Sub frmTest_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Application.EnableVisualStyles()

        LoadWin32Library(Application.StartupPath & "\iModMan\zlibwapi.dll")
        LoadWin32Library(Application.StartupPath & "\iModMan\iNative.dll")
        LoadWin32Library(Application.StartupPath & "\iModMan\iCrypto.dll")
        LoadWin32Library(Application.StartupPath & "\iModMan\iDias.dll")
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim str As String = Space(1024 * 1000)
        Dim ret As Boolean = ReadPak(TextBox1.Text, str)

        If (ret = False) Then
            MsgBox("Ada Error!")
            Exit Sub
        End If

        TextBox2.Text = str
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click

    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click

    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        Dim str As String = Space(1024 * 1000)
        Dim ret As Boolean = ReadPak("H:\\Tools\\DN Tools\\DN PAK Mentah\\00Resource_dvmk_dv-battle-training-ground-ex-1.1.0.eris.pak", str)

        If (ret = False) Then
            MsgBox("Ada Error!")
            Exit Sub
        End If

        TextBox2.Text = str
    End Sub
End Class