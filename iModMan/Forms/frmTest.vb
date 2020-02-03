Imports System.Reflection

Public Class frmTest
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim hash As String = Space(256)
        Dim ret As Integer

        ret = GetMD5FileHash("G:\iModMan\bin\Newtonsoft.Json.dlls", hash)
        WriteLog("iModMan", 1, "Coba ngetes aja ada isinya ga")

        TextBox1.Text = hash
    End Sub

    Private Sub frmTest_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        LoadWin32Library(Application.StartupPath & "\iModMan\iNative.dll")
        LoadWin32Library(Application.StartupPath & "\iModMan\iCrypto.dll")
    End Sub
End Class