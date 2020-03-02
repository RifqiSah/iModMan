Module mdlMain
    Public Sub Main()
        Application.EnableVisualStyles()

        Dim Cmd() As String = Environment.GetCommandLineArgs
        If UBound(Cmd) > 0 Then ' Ada ?
            Select Case Cmd(1).ToUpper
                Case "/CHECK"
                    doUpdateProg()
                    Application.Run()

                    Exit Sub
            End Select
        End If

        MsgBox("Terjadi kesalahan saat menjalankan program!", MsgBoxStyle.Critical)
        Application.Exit()
    End Sub
End Module
