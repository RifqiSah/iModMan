Imports System.IO

Module mdlMain
    <Obsolete>
    Public Sub Main()
        ' Load dulu DLL nya
        AppDomain.CurrentDomain.AppendPrivatePath("iModMan")
        LoadNativeDlls()

        ' Init style
        Application.EnableVisualStyles()

        ' Cek apakah aplikasi sudah berjalan sebelumnya
        If (IsAppAplreadyRunning()) Then
            MessageBox.Show(Form.ActiveForm, Application.ProductName & " sedang berjalan!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Application.Exit()

            Exit Sub
        End If

        ' Cek koneksi internetnya
        If (IsInternetAvailable() = False) Then
            MessageBox.Show(Form.ActiveForm, "Pastikan koneksi internet Anda tersedia sebelum menjalankan " & Application.ProductName & "!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Application.Exit()

            Exit Sub
        End If

        ' Untuk commandline
        Dim Cmd() As String = Environment.GetCommandLineArgs
        If UBound(Cmd) > 0 Then ' Ada ?
            Select Case Cmd(1).ToUpper
                Case "/TOOLS"
                    frmTest.Show()
                    Application.Run()

                Case "/UPDATED"
                    frmMain.Show()
                    ' doUpdateProg(frmMain)
                    Application.Run()

                Case Else
                    MsgBox("Command line '" & Cmd(1) & "' tidak ditemukan!", MsgBoxStyle.Critical, "Error")

            End Select
        Else ' Kosong ?
            execFile(Path.Combine(Application.StartupPath, "iModMan\Updater.exe"), "/CHECK")
            Application.Exit()
        End If
    End Sub

    Private Sub LoadNativeDlls()
        ' Extrnal DLL
        LoadWin32Library(Path.Combine(Application.StartupPath, "iModMan\zlibwapi.dll"))

        ' Internal DLL
        LoadWin32Library(Path.Combine(Application.StartupPath, "iModMan\iNative.dll"))
        LoadWin32Library(Path.Combine(Application.StartupPath, "iModMan\iCrypto.dll"))
        LoadWin32Library(Path.Combine(Application.StartupPath, "iModMan\iDias.dll"))
    End Sub
End Module
