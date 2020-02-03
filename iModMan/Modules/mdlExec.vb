Imports System.Runtime.InteropServices

Module mdlExec
    Public Sub execFile(sPath As String)
        Dim psi As New ProcessStartInfo

        psi.FileName = sPath
        psi.Verb = "runas"
        psi.UseShellExecute = False

        Process.Start(psi)
    End Sub
End Module
