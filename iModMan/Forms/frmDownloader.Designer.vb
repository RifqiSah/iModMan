<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class frmDownloader
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.lblFileInfo = New System.Windows.Forms.Label()
        Me.progFile = New System.Windows.Forms.ProgressBar()
        Me.SuspendLayout()
        '
        'lblFileInfo
        '
        Me.lblFileInfo.Location = New System.Drawing.Point(9, 33)
        Me.lblFileInfo.Name = "lblFileInfo"
        Me.lblFileInfo.Size = New System.Drawing.Size(323, 13)
        Me.lblFileInfo.TabIndex = 0
        Me.lblFileInfo.Text = "{0}"
        Me.lblFileInfo.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'progFile
        '
        Me.progFile.Location = New System.Drawing.Point(12, 12)
        Me.progFile.Name = "progFile"
        Me.progFile.Size = New System.Drawing.Size(320, 13)
        Me.progFile.TabIndex = 4
        '
        'frmDownloader
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(344, 57)
        Me.ControlBox = False
        Me.Controls.Add(Me.progFile)
        Me.Controls.Add(Me.lblFileInfo)
        Me.Font = New System.Drawing.Font("Tahoma", 8.25!)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "frmDownloader"
        Me.ShowInTaskbar = False
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.TopMost = True
        Me.ResumeLayout(False)

    End Sub

    Friend WithEvents lblFileInfo As Label
    Friend WithEvents progFile As ProgressBar
End Class
