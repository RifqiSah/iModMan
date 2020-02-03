Imports System.IO

Module mdlAthena

    Dim AthenaFolder As String = Application.StartupPath & "\Athena"
    Dim AthenaExe As String = Application.StartupPath & "\dv-athena-quicklaunch.exe"
    Dim AthenaDll As String = Application.StartupPath & "\dv-athena-launcher.dll"

    Public Function isAthenaExists()
        Return Directory.Exists(AthenaFolder) And File.Exists(AthenaExe) And File.Exists(AthenaDll)
    End Function
End Module
