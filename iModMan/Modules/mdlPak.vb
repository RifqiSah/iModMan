Imports System.IO

Module mdlPak

    Public Function pakExpand(ByVal sModFile As String) As Boolean
        Debug.WriteLine("Memproses berkas {0}", sModFile)

        Using fileStream As New FileStream(sModFile, FileMode.Open)
            If (fileStream.Length >= 536870912L) Then
                MessageBox.Show(Form.ActiveForm, String.Format("Berkas {0} sudah diperbesar sebelumnya!", sModFile), "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning)
                Return False
            End If

            fileStream.SetLength(536870912L)

            Debug.WriteLine("Berkas berhasil diperbesar!")
            Return True
        End Using

        Return False
    End Function

    Public Function pakShrink(ByVal sModFile As String) As Boolean
        Debug.WriteLine("memproses berkas {0}", sModFile)

        Try
            Using fileStream As New FileStream(sModFile, FileMode.Open)
                Dim buffer() As Byte = New Byte((fileStream.Length) - 1) {}

                fileStream.Seek(0L, SeekOrigin.Begin)
                fileStream.Read(buffer, 0, 4)

                If (1397314117 = BitConverter.ToInt32(buffer, 0)) Then
                    Debug.WriteLine("Berkas yang diberikan adalah 'Eris Mod' dan tidak dapat diperkecil!")
                    Return False
                End If

                fileStream.Seek(260L, SeekOrigin.Begin)
                fileStream.Read(buffer, 0, 8)

                Dim int32_1 As Integer = BitConverter.ToInt32(buffer, 0)
                Dim int32_2 As Integer = BitConverter.ToInt32(buffer, 4)

                Debug.WriteLine("{0:D} entries @ 0x{1:X}", int32_1, int32_2)

                Dim num1 As Integer = int32_2 + int32_1 * 316 + 1

                fileStream.Seek(Convert.ToInt64(int32_2), SeekOrigin.Begin)
                For index As Integer = 0 To index < int32_1
                    fileStream.Read(buffer, 0, 316)

                    Dim num2 As Integer = BitConverter.ToInt32(buffer, 268) + BitConverter.ToInt32(buffer, 256) + 1
                    If (num2 > num1) Then num1 = num2
                Next

                Debug.WriteLine("Byte terakhir berlokasi pada 0x{0:X}. Potong disitu ...", num1)
                fileStream.SetLength(Convert.ToInt64(num1))
                Debug.WriteLine("Berkas berhasil diperkecil!")

                Return True
            End Using
        Catch ex As Exception
            MessageBox.Show(Form.ActiveForm, "Kesalahan terjadi!" & vbCrLf & vbCrLf & "Error:" & vbCrLf & ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Return False
        End Try

        Return False
    End Function
End Module
