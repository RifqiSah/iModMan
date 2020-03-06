Imports System.IO

Module mdlDragonNest
    Dim DNFolder As String = Path.Combine(Application.StartupPath, "XIGNCODE")
    Dim DNExe As String = Path.Combine(Application.StartupPath, "DragonNest.exe")
    Dim DNLauncherExe As String = Path.Combine(Application.StartupPath, "dnlauncher.exe")

    Private Function getResource(sPath As String)
        Dim ret As Boolean = True

        For i As Integer = 0 To 19
            Dim fileName As String = String.Format("Resource{0}.pak", i.ToString("D2"))
            If (Not File.Exists(Path.Combine(sPath, fileName))) Then
                ret = False
            End If
        Next
        Return ret
    End Function

    Public Function isDragonNestExists()
        Return Directory.Exists(DNFolder) And
            File.Exists(DNExe) And
            File.Exists(DNLauncherExe) And
            getResource(Application.StartupPath)
    End Function

    Public Sub runDragonNest()

    End Sub
End Module
