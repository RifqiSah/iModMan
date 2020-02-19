<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class frmMain
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
        Me.lstMod = New System.Windows.Forms.ListView()
        Me.lstModC1 = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.lstModC2 = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.lstModC3 = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.lstModC4 = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.lstModC5 = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.chkListMod = New System.Windows.Forms.CheckBox()
        Me.btnProcess = New System.Windows.Forms.Button()
        Me.lblNumberUpdates = New System.Windows.Forms.Label()
        Me.chkEnlarge = New System.Windows.Forms.CheckBox()
        Me.linkLblUpd = New System.Windows.Forms.LinkLabel()
        Me.SuspendLayout()
        '
        'lstMod
        '
        Me.lstMod.Activation = System.Windows.Forms.ItemActivation.OneClick
        Me.lstMod.CheckBoxes = True
        Me.lstMod.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.lstModC1, Me.lstModC2, Me.lstModC3, Me.lstModC4, Me.lstModC5})
        Me.lstMod.FullRowSelect = True
        Me.lstMod.GridLines = True
        Me.lstMod.HideSelection = False
        Me.lstMod.Location = New System.Drawing.Point(13, 12)
        Me.lstMod.Name = "lstMod"
        Me.lstMod.Size = New System.Drawing.Size(646, 218)
        Me.lstMod.TabIndex = 0
        Me.lstMod.UseCompatibleStateImageBehavior = False
        Me.lstMod.View = System.Windows.Forms.View.Details
        '
        'lstModC1
        '
        Me.lstModC1.Text = "-"
        Me.lstModC1.Width = 26
        '
        'lstModC2
        '
        Me.lstModC2.Text = "Nama Mod"
        Me.lstModC2.Width = 81
        '
        'lstModC3
        '
        Me.lstModC3.Text = "Ver"
        Me.lstModC3.Width = 36
        '
        'lstModC4
        '
        Me.lstModC4.Text = "Status"
        Me.lstModC4.Width = 61
        '
        'lstModC5
        '
        Me.lstModC5.Text = "Tentang Mod"
        Me.lstModC5.Width = 235
        '
        'chkListMod
        '
        Me.chkListMod.AutoSize = True
        Me.chkListMod.Location = New System.Drawing.Point(13, 243)
        Me.chkListMod.Name = "chkListMod"
        Me.chkListMod.Size = New System.Drawing.Size(105, 17)
        Me.chkListMod.TabIndex = 1
        Me.chkListMod.Text = "Pilih semua mod."
        Me.chkListMod.UseVisualStyleBackColor = True
        '
        'btnProcess
        '
        Me.btnProcess.Location = New System.Drawing.Point(543, 265)
        Me.btnProcess.Name = "btnProcess"
        Me.btnProcess.Size = New System.Drawing.Size(116, 37)
        Me.btnProcess.TabIndex = 2
        Me.btnProcess.Text = "Pasang!"
        Me.btnProcess.UseVisualStyleBackColor = True
        '
        'lblNumberUpdates
        '
        Me.lblNumberUpdates.Location = New System.Drawing.Point(413, 243)
        Me.lblNumberUpdates.Name = "lblNumberUpdates"
        Me.lblNumberUpdates.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblNumberUpdates.Size = New System.Drawing.Size(246, 13)
        Me.lblNumberUpdates.TabIndex = 3
        Me.lblNumberUpdates.Text = "{0} buah pembaruan tersedia."
        Me.lblNumberUpdates.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'chkEnlarge
        '
        Me.chkEnlarge.AutoSize = True
        Me.chkEnlarge.Location = New System.Drawing.Point(13, 265)
        Me.chkEnlarge.Name = "chkEnlarge"
        Me.chkEnlarge.Size = New System.Drawing.Size(175, 17)
        Me.chkEnlarge.TabIndex = 4
        Me.chkEnlarge.Text = "Perbesar mod secara otomatis."
        Me.chkEnlarge.UseVisualStyleBackColor = True
        '
        'linkLblUpd
        '
        Me.linkLblUpd.AutoSize = True
        Me.linkLblUpd.Location = New System.Drawing.Point(526, 9)
        Me.linkLblUpd.Name = "linkLblUpd"
        Me.linkLblUpd.Size = New System.Drawing.Size(0, 13)
        Me.linkLblUpd.TabIndex = 6
        '
        'frmMain
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(671, 314)
        Me.Controls.Add(Me.linkLblUpd)
        Me.Controls.Add(Me.chkEnlarge)
        Me.Controls.Add(Me.lblNumberUpdates)
        Me.Controls.Add(Me.btnProcess)
        Me.Controls.Add(Me.chkListMod)
        Me.Controls.Add(Me.lstMod)
        Me.Font = New System.Drawing.Font("Tahoma", 8.25!)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.KeyPreview = True
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "frmMain"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Informate Mod Manager"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents lstMod As ListView
    Friend WithEvents lstModC1 As ColumnHeader
    Friend WithEvents lstModC2 As ColumnHeader
    Friend WithEvents lstModC3 As ColumnHeader
    Friend WithEvents chkListMod As CheckBox
    Friend WithEvents lstModC4 As ColumnHeader
    Friend WithEvents lstModC5 As ColumnHeader
    Friend WithEvents btnProcess As Button
    Friend WithEvents lblNumberUpdates As Label
    Friend WithEvents chkEnlarge As CheckBox
    Friend WithEvents linkLblUpd As LinkLabel
End Class
