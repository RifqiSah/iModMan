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
        Me.mnuMain = New System.Windows.Forms.MenuStrip()
        Me.FileToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.PerbaruiDaftarMODToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem2 = New System.Windows.Forms.ToolStripSeparator()
        Me.ExitToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AksiToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AthenaToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.NormalToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.LogPerubahanToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.TentangToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuMain.SuspendLayout()
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
        Me.lstMod.Location = New System.Drawing.Point(13, 34)
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
        Me.chkListMod.Location = New System.Drawing.Point(13, 265)
        Me.chkListMod.Name = "chkListMod"
        Me.chkListMod.Size = New System.Drawing.Size(105, 17)
        Me.chkListMod.TabIndex = 1
        Me.chkListMod.Text = "Pilih semua mod."
        Me.chkListMod.UseVisualStyleBackColor = True
        '
        'btnProcess
        '
        Me.btnProcess.Location = New System.Drawing.Point(543, 287)
        Me.btnProcess.Name = "btnProcess"
        Me.btnProcess.Size = New System.Drawing.Size(116, 37)
        Me.btnProcess.TabIndex = 2
        Me.btnProcess.Text = "Pasang!"
        Me.btnProcess.UseVisualStyleBackColor = True
        '
        'lblNumberUpdates
        '
        Me.lblNumberUpdates.Location = New System.Drawing.Point(413, 265)
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
        Me.chkEnlarge.Location = New System.Drawing.Point(13, 287)
        Me.chkEnlarge.Name = "chkEnlarge"
        Me.chkEnlarge.Size = New System.Drawing.Size(175, 17)
        Me.chkEnlarge.TabIndex = 4
        Me.chkEnlarge.Text = "Perbesar mod secara otomatis."
        Me.chkEnlarge.UseVisualStyleBackColor = True
        '
        'linkLblUpd
        '
        Me.linkLblUpd.AutoSize = True
        Me.linkLblUpd.Location = New System.Drawing.Point(526, 31)
        Me.linkLblUpd.Name = "linkLblUpd"
        Me.linkLblUpd.Size = New System.Drawing.Size(0, 13)
        Me.linkLblUpd.TabIndex = 6
        '
        'mnuMain
        '
        Me.mnuMain.BackColor = System.Drawing.SystemColors.Menu
        Me.mnuMain.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FileToolStripMenuItem, Me.AksiToolStripMenuItem, Me.TentangToolStripMenuItem})
        Me.mnuMain.Location = New System.Drawing.Point(0, 0)
        Me.mnuMain.Name = "mnuMain"
        Me.mnuMain.Size = New System.Drawing.Size(671, 24)
        Me.mnuMain.TabIndex = 8
        Me.mnuMain.Text = "&File"
        '
        'FileToolStripMenuItem
        '
        Me.FileToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.PerbaruiDaftarMODToolStripMenuItem, Me.LogPerubahanToolStripMenuItem, Me.ToolStripMenuItem2, Me.ExitToolStripMenuItem})
        Me.FileToolStripMenuItem.Name = "FileToolStripMenuItem"
        Me.FileToolStripMenuItem.Size = New System.Drawing.Size(37, 20)
        Me.FileToolStripMenuItem.Text = "&File"
        '
        'PerbaruiDaftarMODToolStripMenuItem
        '
        Me.PerbaruiDaftarMODToolStripMenuItem.Name = "PerbaruiDaftarMODToolStripMenuItem"
        Me.PerbaruiDaftarMODToolStripMenuItem.Size = New System.Drawing.Size(184, 22)
        Me.PerbaruiDaftarMODToolStripMenuItem.Text = "Perbarui Daftar &MOD"
        '
        'ToolStripMenuItem2
        '
        Me.ToolStripMenuItem2.Name = "ToolStripMenuItem2"
        Me.ToolStripMenuItem2.Size = New System.Drawing.Size(180, 6)
        '
        'ExitToolStripMenuItem
        '
        Me.ExitToolStripMenuItem.Name = "ExitToolStripMenuItem"
        Me.ExitToolStripMenuItem.Size = New System.Drawing.Size(184, 22)
        Me.ExitToolStripMenuItem.Text = "&Keluar"
        '
        'AksiToolStripMenuItem
        '
        Me.AksiToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.AthenaToolStripMenuItem, Me.NormalToolStripMenuItem})
        Me.AksiToolStripMenuItem.Name = "AksiToolStripMenuItem"
        Me.AksiToolStripMenuItem.Size = New System.Drawing.Size(85, 20)
        Me.AksiToolStripMenuItem.Text = "&Dragon Nest"
        '
        'AthenaToolStripMenuItem
        '
        Me.AthenaToolStripMenuItem.Name = "AthenaToolStripMenuItem"
        Me.AthenaToolStripMenuItem.Size = New System.Drawing.Size(180, 22)
        Me.AthenaToolStripMenuItem.Text = "&Athena"
        '
        'NormalToolStripMenuItem
        '
        Me.NormalToolStripMenuItem.Name = "NormalToolStripMenuItem"
        Me.NormalToolStripMenuItem.Size = New System.Drawing.Size(180, 22)
        Me.NormalToolStripMenuItem.Text = "&Normal"
        '
        'LogPerubahanToolStripMenuItem
        '
        Me.LogPerubahanToolStripMenuItem.Name = "LogPerubahanToolStripMenuItem"
        Me.LogPerubahanToolStripMenuItem.Size = New System.Drawing.Size(184, 22)
        Me.LogPerubahanToolStripMenuItem.Text = "&Log Perubahan"
        '
        'TentangToolStripMenuItem
        '
        Me.TentangToolStripMenuItem.Name = "TentangToolStripMenuItem"
        Me.TentangToolStripMenuItem.Size = New System.Drawing.Size(61, 20)
        Me.TentangToolStripMenuItem.Text = "&Tentang"
        '
        'frmMain
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(671, 336)
        Me.Controls.Add(Me.linkLblUpd)
        Me.Controls.Add(Me.chkEnlarge)
        Me.Controls.Add(Me.lblNumberUpdates)
        Me.Controls.Add(Me.btnProcess)
        Me.Controls.Add(Me.chkListMod)
        Me.Controls.Add(Me.lstMod)
        Me.Controls.Add(Me.mnuMain)
        Me.Font = New System.Drawing.Font("Tahoma", 8.25!)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.KeyPreview = True
        Me.MainMenuStrip = Me.mnuMain
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "frmMain"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Informate Mod Manager"
        Me.mnuMain.ResumeLayout(False)
        Me.mnuMain.PerformLayout()
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
    Friend WithEvents mnuMain As MenuStrip
    Friend WithEvents FileToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ExitToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents PerbaruiDaftarMODToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem2 As ToolStripSeparator
    Friend WithEvents AksiToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents AthenaToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents NormalToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents LogPerubahanToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents TentangToolStripMenuItem As ToolStripMenuItem
End Class
