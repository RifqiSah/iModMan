Imports System.IO

Module mdlAthena

    Dim AthenaFolder As String = Path.Combine(Application.StartupPath, "Athena")
    Dim AthenaExe As String = Path.Combine(Application.StartupPath, "dv-athena-quicklaunch.exe")
    Dim AthenaDll As String = Path.Combine(Application.StartupPath, "dv-athena-launcher.dll")

    Public Function isAthenaExists()
        Return Directory.Exists(AthenaFolder) And File.Exists(AthenaExe) And File.Exists(AthenaDll)
    End Function
End Module
