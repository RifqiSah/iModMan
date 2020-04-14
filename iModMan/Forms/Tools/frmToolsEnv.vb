Imports System.IO

Public Class frmToolsEnv
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        prosesEnv(TextBox1.Text)
    End Sub

    Private Sub prosesEnv(ByVal sFile As String)
        If Not (File.Exists(sFile)) Then
            MsgBox("Invalid file!", MsgBoxStyle.Critical)
            Exit Sub
        End If

        Dim dPath = Path.GetDirectoryName(sFile) & "\"
        Dim dFiles As String() = TextBox2.Text.Split(vbCrLf)

        For Each dFile As String In dFiles
            Dim sDesc As String = Path.Combine(dPath, dFile.Trim())
            File.Copy(sFile, sDesc, True)
        Next

        MsgBox("Selesai!", MsgBoxStyle.Information)
    End Sub

    Private Sub TextBox1_DragDrop(sender As Object, e As DragEventArgs) Handles TextBox1.DragDrop
        If e.Data.GetDataPresent(DataFormats.FileDrop) Then
            Dim MyFiles() As String = e.Data.GetData(DataFormats.FileDrop)
            TextBox1.Text = MyFiles(0)
        End If
    End Sub
End Class