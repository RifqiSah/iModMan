Imports Newtonsoft.Json.Linq

Public Class frmChangeLog
    Private Sub frmChangeLog_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Icon = My.Resources.Icon
        loadCommit()
    End Sub

    Private Sub loadCommit()
        Dim sha As String = "74611b0c6a71cdfaa235989119cfd39acb8fa9aa"
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