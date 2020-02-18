Imports System.IO
Imports System.Reflection

Public Class frmTest
    Dim str As String = Space(1024 * 1000)
    Dim ret As Boolean = False

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        ret = ReadPak(TextBox1.Text, str)
        If (ret = False) Then
            MsgBox("Ada Error!")
            Exit Sub
        End If

        TextBox2.Text = str
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click

    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        ret = DiasUnpackFile(TextBox1.Text, Path.GetDirectoryName(TextBox1.Text))
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
End Class