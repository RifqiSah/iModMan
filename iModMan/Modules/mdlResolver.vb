Imports System.IO
Imports System.Reflection

Module mdlResolver

    Public Function resolveModule(sModule As String, sClassName As String) As Object
        Dim ass As Assembly = Assembly.LoadFrom(Application.StartupPath & "\iModMan\" & sModule)
        Dim str As String = String.Format("{0}.{1}", Path.GetFileNameWithoutExtension(sModule), sClassName)
        Dim funcs As Object = ass.CreateInstance(str)

        Return funcs
    End Function
End Module
