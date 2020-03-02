Imports System.IO

Module mdlExec
    Public Sub execFile(sPath As String, sParam As String)
        Dim psi As New ProcessStartInfo

        psi.FileName = sPath
        psi.Arguments = sParam
        psi.Verb = "runas"
        psi.WorkingDirectory = Path.GetDirectoryName(sPath)
        psi.UseShellExecute = False

        Process.Start(psi)
    End Sub
End Module
