Imports Newtonsoft.Json.Linq

Public Class frmChangeLog
    Private Sub frmChangeLog_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Icon = My.Resources.Icon

        WriteLog("iModMan:loadCommit", ErrorType.trace, "Checking commit lists")
        loadCommit()
        WriteLog("iModMan:loadCommit", ErrorType.trace, "OK")
    End Sub

    Private Sub loadCommit()
        Dim sha As String = My.Resources.repo_hash
        Dim json As String = readHttpFile(My.Resources.repo_url)
        Dim commits As JArray = JArray.Parse(json)

        For Each item As JObject In commits
            Dim commit As JObject = item("commit")
            Dim commiter As JObject = commit("committer")
            Dim commit_date As Date = Date.Parse(commiter.SelectToken("date").ToString())

            Dim val As ListViewItem = New ListViewItem(commit_date.ToShortDateString)
            val.SubItems.Add(commiter.SelectToken("name"))
            val.SubItems.Add(commit.SelectToken("message"))
            val.SubItems.Add(item.SelectToken("sha"))

            WriteLog("iModMan:loadCommit", ErrorType.trace, item.SelectToken("sha"))

            If (sha.Equals(item.SelectToken("sha").ToString())) Then
                val.Font = New Font(lstCommit.Font, FontStyle.Bold)
            Else
                val.Font = New Font(lstCommit.Font, FontStyle.Regular)
            End If

            lstCommit.Items.Add(val)
        Next

        lstCommit.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent)
    End Sub
End Class