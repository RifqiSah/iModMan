Imports System.IO
Imports System.Security.Cryptography

Module mdlHash

    Public Function SHA256CheckSum(ByVal sFile As String) As String
        Using stream As FileStream = File.OpenRead(sFile)
            Dim sha As SHA256Managed = New SHA256Managed()
            Dim checksum As Byte() = sha.ComputeHash(stream)

            Return BitConverter.ToString(checksum).Replace("-", String.Empty)
        End Using
    End Function
End Module
