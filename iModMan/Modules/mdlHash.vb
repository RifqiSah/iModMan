﻿Module mdlHash

    Public Function MD5CheckSum(ByVal sFile As String) As String
        Dim hash As String = Space(32)
        GetMD5FileHash(sFile, hash)

        Return hash
    End Function


    Public Function SHA256CheckSum(ByVal sFile As String) As String
        Dim hash As String = Space(64)
        GetSHA256FileHash(sFile, hash)

        Return hash
    End Function
End Module
