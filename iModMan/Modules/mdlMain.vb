Module mdlMain
    Public Sub mainadadad()
        ' Load dulu DLL nya
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

        ' Cek update programnya
        doUpdateProg(frmMain)

        ' Run program
        Application.Run()
    End Sub

    Public Sub main()
        LoadNativeDlls()

        Dim ret As Boolean = DiasPackFile("G:\PakSource2\Source\CompileMe", "G:\PakSource2\Source\00Resource_rifqisah_gatauapa_1.0.0.dias.pak")
        MsgBox(ret)

        ret = DiasUnpackFile("G:\PakSource2\Source\00Resource_rifqisah_gatauapa_1.0.0.dias.pak", "G:\PakSource2\Source\testaja")
        MsgBox(ret)
    End Sub

    Private Sub LoadNativeDlls()
        LoadWin32Library(Application.StartupPath & "\iModMan\iNative.dll")
        LoadWin32Library(Application.StartupPath & "\iModMan\iCrypto.dll")
        LoadWin32Library(Application.StartupPath & "\iModMan\iDias.dll")
    End Sub
End Module
