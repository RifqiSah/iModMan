Imports System.ComponentModel

Public Class frmMain

    Private Sub frmLists_Load(sender As Object, e As EventArgs) Handles Me.Load
        loadModJson(lstMod)
        Icon = My.Resources.Icon
    End Sub

    Private Sub frmLists_Shown(sender As Object, e As EventArgs) Handles Me.Shown
        ' Enlarge pak
        If (isAthenaExists()) Then
            chkEnlarge.Checked = False
            chkEnlarge.Enabled = False
            chkEnlarge.Text = chkEnlarge.Text + " (Athena Terpasang)"
        Else
            chkEnlarge.Checked = Integer.Parse(ReadIniValue("Application", "PakEnlarge"))
        End If
    End Sub

    Private Sub frmLists_KeyDown(sender As Object, e As KeyEventArgs) Handles Me.KeyDown
        If (e.KeyData = Keys.F5) Then
            loadModJson(lstMod)
        End If
    End Sub

    Private Sub lstMod_MouseDown(sender As Object, e As MouseEventArgs) Handles lstMod.MouseDown
        Dim lvi = lstMod.GetItemAt(e.X, e.Y)
        If lvi IsNot Nothing Then
            lvi.Checked = Not lvi.Checked
        End If

        If (lstMod.CheckedItems.Count = lstMod.Items.Count) Then
            chkListMod.CheckState = CheckState.Checked
        ElseIf (lstMod.CheckedItems.Count > 0) Then
            chkListMod.CheckState = CheckState.Indeterminate
        Else
            chkListMod.CheckState = CheckState.Unchecked
        End If
    End Sub

    Private Sub chkListMod_Click(sender As Object, e As EventArgs) Handles chkListMod.Click
        For Each item As ListViewItem In lstMod.Items
            item.Checked = chkListMod.Checked
        Next
    End Sub

    Private Sub btnProcess_Click(sender As Object, e As EventArgs) Handles btnProcess.Click
        Dim checkedList As ListView.CheckedListViewItemCollection = lstMod.CheckedItems

        If (checkedList.Count = 0) Then
            MessageBox.Show("Tidak ada mod yang dipilih, mohon pilih setidaknya 1 buah mod untuk melanjutkan pemasangan!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Exit Sub
        End If

        For Each list As ListViewItem In checkedList
            If (list.SubItems(3).Text.Equals("Diperbarui!")) Then
                MessageBox.Show("Anda tidak dapat mengunduh ulang mod yang ter-update!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
                Exit Sub
            End If

            Dim f As clsFFile = list.Tag
            frmDownloader.fileDownloadList.Add(f)
        Next

        frmDownloader.setForm(Nothing)
        frmDownloader.Show()
    End Sub

    Private Sub chkEnlarge_CheckedChanged(sender As Object, e As EventArgs) Handles chkEnlarge.CheckedChanged
        WriteIniValue("Application", "PakEnlarge", chkEnlarge.CheckState)
    End Sub

    Private Sub frmMain_Closed(sender As Object, e As EventArgs) Handles Me.Closed
        Application.Exit()
    End Sub

    Private Sub showChangeLogFrm()
        frmChangeLog.ShowDialog(Me)
    End Sub

    Private Sub lblCommit_LinkClicked(sender As Object, e As LinkLabelLinkClickedEventArgs) Handles lblCommit.LinkClicked
        Dim th As Threading.Thread = New Threading.Thread(AddressOf showChangeLogFrm)
        th.Start()
    End Sub
End Class