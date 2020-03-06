Imports System.IO
Imports System.Xml

Module mdlDragonNest
    Dim DNPatchConfig As String = "http://patchsea.dragonnest.com/Game/DragonNest/Patch/PatchConfigList.xml"
    Dim DNFolder As String = Path.Combine(Application.StartupPath, "XIGNCODE")
    Dim DNExe As String = Path.Combine(Application.StartupPath, "DragonNest.exe")
    Dim DNLauncherExe As String = Path.Combine(Application.StartupPath, "dnlauncher.exe")

    Private Function getResource(sPath As String)
        Dim ret As Boolean = True

        For i As Integer = 0 To 19
            Dim fileName As String = String.Format("Resource{0}.pak", i.ToString("D2"))
            If (Not File.Exists(Path.Combine(sPath, fileName))) Then
                ret = False
            End If
        Next
        Return ret
    End Function

    Public Function isDragonNestExists()
        Return Directory.Exists(DNFolder) And
            File.Exists(DNExe) And
            File.Exists(DNLauncherExe) And
            getResource(Application.StartupPath)
    End Function

    Public Sub runDragonNest()
        Dim ip As String = Nothing
        Dim port As String = Nothing

        Dim xml As XmlTextReader = New XmlTextReader(DNPatchConfig) With {
            .WhitespaceHandling = WhitespaceHandling.None
        }

        xml.Read() ' XML declaration
        xml.Read() ' Document
        xml.Read() ' ChannelList 
        xml.Read() ' Local

        ' Skip-skip
        xml.Read() ' Version
        xml.Read() ' Update
        xml.Read() ' Guidepage
        xml.Read() ' Homepage

        While Not xml.EOF
            If Not xml.IsStartElement() Then Exit While ' Kalau tidak element pertama exit aja

            xml.Read() ' Login tag

            If (xml.HasAttributes) Then
                ip &= xml.GetAttribute("addr") & ";"
                port &= xml.GetAttribute("port") & ";"
            End If
        End While

        Dim param As String = String.Format("/ip:{0} /port:{1} /language:{2}", ip.TrimEnd(";"), port.TrimEnd(";"), "ENG")
        execFile(DNExe, param)
        Threading.Thread.Sleep(2000)
        Application.Exit()
    End Sub
End Module
