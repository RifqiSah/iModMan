Imports System.Reflection

Public Class frmTest
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        TextBox1.Text = resolveModule("iCore.dll", "clsCrypto").SHA256CheckSum("G:\iModMan\bin\iModMan.exe")
        'TextBox2.Text = resolveModule("iCore.dll", "clsCrypto").SHA256Checksum("H:\Tools\DN Tools\DN PAK Hasil\00Resource_rifqisah_testing_besar_1.0.0.pak")
    End Sub

    Private Sub loadDll()

    End Sub
End Class