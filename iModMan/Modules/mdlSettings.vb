Imports System.Text

Module mdlSettings

    Private IniFile As String = Application.StartupPath & "\iModMan\settings.ini"

    Public Function ReadIniValue(lpBlock As String, lpKey As String) As String
        Dim Ret As Integer
        Dim Tmp As New StringBuilder(500)

        Ret = GetPrivateProfileString(lpBlock, lpKey, "", Tmp, Tmp.Capacity, IniFile)
        If (Ret) Then
            Return Tmp.ToString()
            Exit Function
        End If

        Return ""
    End Function

    Public Sub WriteIniValue(lpBlock As String, lpKey As String, lpValue As String)
        Dim Ret As Integer
        Ret = WritePrivateProfileString(lpBlock, lpKey, lpValue, IniFile)
    End Sub
End Module
