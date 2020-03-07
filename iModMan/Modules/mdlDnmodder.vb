Imports System.IO

Module mdlDnmodder
    Dim DNModderFolder As String = Path.Combine(Application.StartupPath, "DNModder")
    Dim DNModderDll1 As String = Path.Combine(Application.StartupPath, "ddraw.dll")
    Dim DNModderDll2 As String = Path.Combine(Application.StartupPath, "bdvid32_2.dll")

    Public Function isDNModderExists()
        WriteLog("iModMan:isDNModderExists", ErrorType.debug, "Checking DNModder installation")
        Return Directory.Exists(DNModderFolder) And File.Exists(DNModderDll1) And File.Exists(DNModderDll2)
    End Function
End Module
