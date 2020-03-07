Imports System.IO

Module mdlMain

    Public Sub Main()
        ' Initialisi pertama
        LoadNativeDlls()
        WriteLog("iModMan:Main", ErrorType.info, "==== Program Start ====")
        LoadManagedDlls()

        ' Init style
        Application.EnableVisualStyles()

        ' Cek apakah aplikasi sudah berjalan sebelumnya
        If (IsAppAplreadyRunning()) Then
            MessageBox.Show(Form.ActiveForm, Application.ProductName & " sedang berjalan!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            ProgramEnd()

            Exit Sub
        End If

        ' Cek koneksi internetnya
        If (IsInternetAvailable() = False) Then
            MessageBox.Show(Form.ActiveForm, "Pastikan koneksi internet Anda tersedia sebelum menjalankan " & Application.ProductName & "!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            ProgramEnd()

            Exit Sub
        End If

        ' Untuk commandline
        Dim Cmd() As String = Environment.GetCommandLineArgs

        If UBound(Cmd) > 0 Then ' Ada ?
            WriteLog("iModMan:Main", ErrorType.debug, String.Format("Command line: {0}", Cmd(1)))

            Select Case Cmd(1).ToUpper
                Case "/TOOLS"
                    frmTest.Show()
                    Application.Run()

                Case "/UPDATED"
                    frmMain.Show()
                    Application.Run()

                Case Else
                    MsgBox("Command line '" & Cmd(1) & "' tidak ditemukan!", MsgBoxStyle.Critical, "Error")

            End Select
        Else ' Kosong ?
            WriteLog("iModMan:Main", ErrorType.debug, "Attempting to check for updates")

            execFile(Path.Combine(Application.StartupPath, "iModMan\Updater.exe"), "/CHECK")
            ProgramEnd()
        End If
    End Sub

    Public Sub ProgramEnd(Optional ByVal code As Integer = 0)
        ' WriteLog("iModMan:Main", ErrorType.debug, String.Format("Program will terminated with error code {0}.", code))
        WriteLog("iModMan:Main", ErrorType.info, "==== Program Terminated ====" & vbCrLf)

        Application.Exit()
    End Sub

    Private Sub LoadNativeDlls()
        ' Extrnal DLL
        LoadWin32Library(Path.Combine(Application.StartupPath, "iModMan\zlibwapi.dll"))

        ' Internal DLL
        LoadWin32Library(Path.Combine(Application.StartupPath, "iModMan\iNative.dll"))
        LoadWin32Library(Path.Combine(Application.StartupPath, "iModMan\iCrypto.dll"))
        LoadWin32Library(Path.Combine(Application.StartupPath, "iModMan\iDias.dll"))
    End Sub

    Private Sub LoadManagedDlls()
        Try
            AddHandler AppDomain.CurrentDomain.AssemblyResolve, AddressOf DoResolve
        Catch ex As Exception
            WriteLog("iModMan:Main", ErrorType.errors, ex.Message)
            MessageBox.Show(Form.ActiveForm, ex.Message, "Error", MessageBoxIcon.Error)
        End Try
    End Sub

    Private Function DoResolve(ByVal sender As Object, ByVal e As ResolveEventArgs) As Reflection.Assembly
        Dim handle As Reflection.Assembly = Nothing
        Dim file As String = e.Name.Substring(0, InStr(e.Name, ",") - 1) & ".dll"

        WriteLog("iModMan:LoadManagedDlls", 5, String.Format("- Resolving {0}", file))
        Try
            handle = Reflection.Assembly.LoadFrom(Path.Combine(Application.StartupPath, "iModMan", file))
        Catch ex As Exception
            WriteLog("iModMan:LoadManagedDlls", ErrorType.errors, ex.Message)
            MessageBox.Show(Form.ActiveForm, ex.Message, "Error", MessageBoxIcon.Error)
        End Try

        Return handle
    End Function
End Module
