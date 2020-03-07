Imports Newtonsoft.Json.Linq
Imports System.IO

Module mdlModList
    Dim ood As Integer = 0

    Public Sub loadModJson(ByVal cListView As ListView)
        Dim json As String = readHttpFile(My.Resources.mod_url & "/" & My.Resources.mod_patchlist)
        Dim ser As JObject = JObject.Parse(json)
        Dim mod_files As JArray = ser("mod_files")

        frmMain.chkListMod.Checked = False

        WriteLog("iModMan:loadModJson", ErrorType.trace, "Parsing mods data")
        For Each item As JObject In mod_files
            WriteLog("iModMan:loadModJson", ErrorType.trace, item.SelectToken("name").ToString())

            Dim f As clsFFile = New clsFFile(
                item.SelectToken("name").ToString(),
                item.SelectToken("path").ToString(),
                item.SelectToken("version").ToString(),
                item.SelectToken("url").ToString(),
                item.SelectToken("desc").ToString(),
                item.SelectToken("hash").ToString())

            Dim status As Integer = checkModVersion(f.getPath(), f.getVersion())

            Dim val As ListViewItem = New ListViewItem()
            val.SubItems.Add(f.getName())
            val.SubItems.Add(f.getVersion())
            val.SubItems.Add(getModVersionDetails(status))
            val.SubItems.Add(f.getDesc())

            If (status = 1) Then
                val.Checked = True
                val.ForeColor = Color.Red

                ood = ood + 1
            End If

            If (status = 2) Then val.ForeColor = Color.Green
            If (status = 4) Then val.ForeColor = Color.Red

            val.Tag = f
            cListView.Items.Add(val)
        Next

        If (ood > 0) Then
            frmMain.lblNumberUpdates.Text = ood & " buah pembaruan tersedia."
        Else
            frmMain.lblNumberUpdates.Text = "Semua mod telah diperbarui."
        End If

        WriteLog("iModMan:loadModJson", ErrorType.trace, "OK")
        cListView.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent)
    End Sub

    Private Function checkModVersion(ByVal sFileName As String, ByVal version As String)
        Dim filePath As String
        Dim local As String
        Dim server As String = version

        filePath = Path.Combine(Application.StartupPath, sFileName)

        ' Cek filenya apakah ada di local
        If (File.Exists(filePath)) Then
            If (FileLen(filePath) > 0) Then ' pastikan filenya berisi bukan file dummy
                Dim elem As String() = sFileName.Split(New Char() {"_"c}) ' Split nama filenya

                local = elem(elem.Count - 1).Replace(".pak", "").Replace(".", "")
                server = version.Replace(".", "")

                If (server > local) Then
                    Return 1 ' Mod ada update
                Else
                    Return 2 ' ' Mod sudah terbaru
                End If
            Else
                Return 4 ' Ukuran file mod 0KB
            End If
        Else
            Return 3 ' Mod tidak ada/tidak diinstall
        End If

        ' Ada error
        Return -1
    End Function

    Private Function getModVersionDetails(ByVal i As Integer)
        If (i = 1) Then
            Return "Pembaruan tersedia"
        ElseIf (i = 2) Then
            Return "Diperbarui!"
        ElseIf (i = 3) Then
            Return "Tidak dipasang"
        ElseIf (i = 4) Then
            Return "File rusak!"
        Else
            Return "Ada kesalahan!"
        End If
    End Function
End Module
