﻿Imports System.Runtime.InteropServices
Imports System.Text

Module mdlAPI
    Public Enum ErrorType
        info = 1
        warning = 2
        errors = 3
        trace = 4
        debug = 5
    End Enum

    <DllImport("kernel32.dll", SetLastError:=True)>
    Public Function GetPrivateProfileString(ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As StringBuilder, ByVal nSize As Integer, ByVal lpFileName As String) As Integer
    End Function

    <DllImport("kernel32.dll", SetLastError:=True)>
    Public Function WritePrivateProfileString(ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpString As String, ByVal lpFileName As String) As Boolean
    End Function

    Public Declare Function GetMD5FileHash Lib "iCrypto.dll" (ByVal sFilePath As String, ByVal Hash As String) As Boolean
    Public Declare Function GetSHA256FileHash Lib "iCrypto.dll" (ByVal sFilePath As String, ByVal Hash As String) As Boolean

    Public Declare Function ReadEris Lib "iDias.dll" (ByVal sSource As String, ByVal sMessage As String) As Boolean

    Public Declare Function DnPakRead Lib "iDias.dll" (ByVal sSource As String, ByVal sMessage As String) As Boolean
    Public Declare Function DnPakPack Lib "iDias.dll" (ByVal sSource As String, ByVal sDestination As String) As Boolean
    Public Declare Function DnPakUnpack Lib "iDias.dll" (ByVal sSource As String, ByVal sDestination As String) As Boolean

    Public Declare Function DiasPakRead Lib "iDias.dll" (ByVal sSource As String, ByVal sMessage As String) As Boolean
    Public Declare Function DiasPakPack Lib "iDias.dll" (ByVal sSource As String, ByVal sDestination As String) As Boolean
    Public Declare Function DiasPakUnpack Lib "iDias.dll" (ByVal sSource As String, ByVal sDestination As String) As Boolean

    Public Declare Sub DisplayError Lib "iNative.dll" (ByVal sFunc As String)
    Public Declare Sub DisplayErrorEx Lib "iNative.dll" (ByVal sModule As String, ByVal sFunct As String)
    Public Declare Function IsInternetAvailable Lib "iNative.dll" () As Boolean
    Public Declare Function IsAppAplreadyRunning Lib "iNative.dll" () As Boolean
    Public Declare Sub WriteLog Lib "iNative.dll" (ByVal sModule As String, ByVal iType As Integer, ByVal sMessage As String)
End Module
