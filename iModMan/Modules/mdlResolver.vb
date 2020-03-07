Imports System.ComponentModel
Imports System.IO
Imports System.Reflection
Imports System.Runtime.InteropServices

Module mdlResolver
    <DllImport("kernel32.dll", SetLastError:=True, CharSet:=CharSet.Ansi)>
    Public Function LoadLibrary(ByVal lpFileName As String) As IntPtr
    End Function

    Public Function resolveModule(sModule As String, sClassName As String) As Object
        Dim ass As Assembly = Assembly.LoadFrom(Path.Combine(Application.StartupPath, "iModMan", sModule))
        Dim str As String = String.Format("{0}.{1}", Path.GetFileNameWithoutExtension(sModule), sClassName)
        Dim funcs As Object = ass.CreateInstance(str)

        Return funcs
    End Function

    Public Function LoadWin32Library(ByVal libPath As String) As IntPtr
        If String.IsNullOrEmpty(libPath) Then Throw New ArgumentNullException("libPath")
        If Environment.Is64BitProcess Then Throw New Exception(String.Format("Can't load {0} because this is a 64-bit proccess", libPath))

        Dim moduleHandle As IntPtr = LoadLibrary(libPath)

        If moduleHandle = IntPtr.Zero Then
            Dim lasterror = Marshal.GetLastWin32Error()
            Dim innerEx = New Win32Exception(lasterror)
            innerEx.Data.Add("LastWin32Error", lasterror)
            Throw New Exception("Can't load DLL " & libPath, innerEx)
        End If

        Return moduleHandle
    End Function
End Module
