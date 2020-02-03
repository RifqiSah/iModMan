Module mdlMain
    Public Sub main()
        ' Init style
        Application.EnableVisualStyles()

        ' Cek apakah aplikasi sudah berjalan sebelumnya
        If (resolveModule("iCore.dll", "clsMutext").IsAppAplreadyRunning()) Then
            MessageBox.Show(Form.ActiveForm, Application.ProductName & " sedang berjalan!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Application.Exit()

            Exit Sub
        End If

        ' Cek koneksi internetnya
        If (resolveModule("iCore.dll", "clsInternet").CheckConnection() = False) Then
            MessageBox.Show(Form.ActiveForm, "Pastikan koneksi internet Anda tersedia sebelum menjalankan " & Application.ProductName & "!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Application.Exit()

            Exit Sub
        End If

        ' Cek update programnya
        doUpdateProg(frmMain)

        ' Run program
        Application.Run()
    End Sub
End Module
