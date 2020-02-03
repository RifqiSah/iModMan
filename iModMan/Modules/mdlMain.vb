Module mdlMain
    Public Sub main()
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

    Private Sub LoadNativeDlls()
        LoadWin32Library(Application.StartupPath & "\iModMan\iNative.dll")
        LoadWin32Library(Application.StartupPath & "\iModMan\iCrypto.dll")
    End Sub
End Module
