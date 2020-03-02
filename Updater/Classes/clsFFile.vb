Public Class clsFFile
    Private name As String
    Private path As String
    Private version As String
    Private url As String
    Private desc As String
    Private hash As String

    Public Sub New(sName As String, sPath As String, sVersion As String, sUrl As String, sDesc As String, sHash As String)
        name = sName
        path = sPath
        version = sVersion
        url = sUrl
        desc = sDesc
        hash = sHash
    End Sub

    Public Function getName() As String
        Return name
    End Function

    Public Sub setName(sName As String)
        name = sName
    End Sub

    Public Function getPath() As String
        Return path
    End Function

    Public Sub setPath(sPath As String)
        path = sPath
    End Sub

    Public Function getVersion() As String
        Return version
    End Function

    Public Sub setVersion(sVersion As String)
        version = sVersion
    End Sub

    Public Function getUrl() As String
        Return url
    End Function

    Public Sub setUrl(sUrl As String)
        url = sUrl
    End Sub

    Public Function getDesc() As String
        Return desc
    End Function

    Public Sub setDesc(sDesc As String)
        desc = sDesc
    End Sub

    Public Function getHash() As String
        Return hash
    End Function

    Public Sub setHash(shash As String)
        hash = shash
    End Sub

    ' ============ CUSTOM FUNCTION ============
    Public Function getFileName() As String
        Return path.Split("/").Last.ToString()
    End Function
End Class
