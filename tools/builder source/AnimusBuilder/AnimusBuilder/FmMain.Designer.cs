namespace AnimusBuilder
{
    partial class FmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FmMain));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.BtnOutputPath = new System.Windows.Forms.Button();
            this.TbOutputPath = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.BtnModPath = new System.Windows.Forms.Button();
            this.TbModPath = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.BtnAnimusPath = new System.Windows.Forms.Button();
            this.TbAnimusPath = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.BtnSave = new System.Windows.Forms.Button();
            this.BtnLoad = new System.Windows.Forms.Button();
            this.BtnBuild = new System.Windows.Forms.Button();
            this.BtnSelectControl = new System.Windows.Forms.Button();
            this.FlpHPins = new System.Windows.Forms.FlowLayoutPanel();
            this.FlpPool = new System.Windows.Forms.FlowLayoutPanel();
            this.LController = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.TbName = new System.Windows.Forms.TextBox();
            this.TbVariant = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.TbBuild = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.NudRefresh = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.FlpVPins = new System.Windows.Forms.FlowLayoutPanel();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.LbMods = new System.Windows.Forms.ListBox();
            this.LbModPool = new System.Windows.Forms.ListBox();
            this.label12 = new System.Windows.Forms.Label();
            this.BtAddMod = new System.Windows.Forms.Button();
            this.BtnBuildAll = new System.Windows.Forms.Button();
            this.BtnResetPins = new System.Windows.Forms.Button();
            this.BtnResetMod = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NudRefresh)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.BtnOutputPath);
            this.groupBox1.Controls.Add(this.TbOutputPath);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.BtnModPath);
            this.groupBox1.Controls.Add(this.TbModPath);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.BtnAnimusPath);
            this.groupBox1.Controls.Add(this.TbAnimusPath);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 485);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(540, 113);
            this.groupBox1.TabIndex = 26;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Paths";
            // 
            // BtnOutputPath
            // 
            this.BtnOutputPath.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BtnOutputPath.Location = new System.Drawing.Point(459, 77);
            this.BtnOutputPath.Name = "BtnOutputPath";
            this.BtnOutputPath.Size = new System.Drawing.Size(75, 23);
            this.BtnOutputPath.TabIndex = 8;
            this.BtnOutputPath.Text = "Browse";
            this.BtnOutputPath.UseVisualStyleBackColor = true;
            this.BtnOutputPath.Click += new System.EventHandler(this.BtnOutputPath_Click);
            // 
            // TbOutputPath
            // 
            this.TbOutputPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TbOutputPath.Location = new System.Drawing.Point(116, 79);
            this.TbOutputPath.Name = "TbOutputPath";
            this.TbOutputPath.Size = new System.Drawing.Size(337, 20);
            this.TbOutputPath.TabIndex = 7;
            this.TbOutputPath.TextChanged += new System.EventHandler(this.TbOutputPath_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 82);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(67, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Output Path:";
            // 
            // BtnModPath
            // 
            this.BtnModPath.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BtnModPath.Location = new System.Drawing.Point(459, 48);
            this.BtnModPath.Name = "BtnModPath";
            this.BtnModPath.Size = new System.Drawing.Size(75, 23);
            this.BtnModPath.TabIndex = 5;
            this.BtnModPath.Text = "Browse";
            this.BtnModPath.UseVisualStyleBackColor = true;
            this.BtnModPath.Click += new System.EventHandler(this.BtnModPath_Click);
            // 
            // TbModPath
            // 
            this.TbModPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TbModPath.Location = new System.Drawing.Point(116, 50);
            this.TbModPath.Name = "TbModPath";
            this.TbModPath.Size = new System.Drawing.Size(337, 20);
            this.TbModPath.TabIndex = 4;
            this.TbModPath.TextChanged += new System.EventHandler(this.TbModPath_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 53);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(93, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Mod Source Path:";
            // 
            // BtnAnimusPath
            // 
            this.BtnAnimusPath.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BtnAnimusPath.Location = new System.Drawing.Point(459, 19);
            this.BtnAnimusPath.Name = "BtnAnimusPath";
            this.BtnAnimusPath.Size = new System.Drawing.Size(75, 23);
            this.BtnAnimusPath.TabIndex = 2;
            this.BtnAnimusPath.Text = "Browse";
            this.BtnAnimusPath.UseVisualStyleBackColor = true;
            this.BtnAnimusPath.Click += new System.EventHandler(this.BtnAnimusPath_Click);
            // 
            // TbAnimusPath
            // 
            this.TbAnimusPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TbAnimusPath.Location = new System.Drawing.Point(116, 21);
            this.TbAnimusPath.Name = "TbAnimusPath";
            this.TbAnimusPath.Size = new System.Drawing.Size(337, 20);
            this.TbAnimusPath.TabIndex = 1;
            this.TbAnimusPath.TextChanged += new System.EventHandler(this.TbAnimusPath_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(106, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Animus Source Path:";
            // 
            // BtnSave
            // 
            this.BtnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BtnSave.Location = new System.Drawing.Point(234, 12);
            this.BtnSave.Name = "BtnSave";
            this.BtnSave.Size = new System.Drawing.Size(75, 23);
            this.BtnSave.TabIndex = 2;
            this.BtnSave.Text = "Save";
            this.BtnSave.UseVisualStyleBackColor = true;
            this.BtnSave.Click += new System.EventHandler(this.BtnSave_Click);
            // 
            // BtnLoad
            // 
            this.BtnLoad.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BtnLoad.Location = new System.Drawing.Point(315, 12);
            this.BtnLoad.Name = "BtnLoad";
            this.BtnLoad.Size = new System.Drawing.Size(75, 23);
            this.BtnLoad.TabIndex = 3;
            this.BtnLoad.Text = "Load";
            this.BtnLoad.UseVisualStyleBackColor = true;
            this.BtnLoad.Click += new System.EventHandler(this.BtnLoad_Click);
            // 
            // BtnBuild
            // 
            this.BtnBuild.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BtnBuild.Location = new System.Drawing.Point(396, 12);
            this.BtnBuild.Name = "BtnBuild";
            this.BtnBuild.Size = new System.Drawing.Size(75, 23);
            this.BtnBuild.TabIndex = 4;
            this.BtnBuild.Text = "Build";
            this.BtnBuild.UseVisualStyleBackColor = true;
            this.BtnBuild.Click += new System.EventHandler(this.BtnBuild_Click);
            // 
            // BtnSelectControl
            // 
            this.BtnSelectControl.Location = new System.Drawing.Point(12, 12);
            this.BtnSelectControl.Name = "BtnSelectControl";
            this.BtnSelectControl.Size = new System.Drawing.Size(99, 23);
            this.BtnSelectControl.TabIndex = 0;
            this.BtnSelectControl.Text = "Select Controller";
            this.BtnSelectControl.UseVisualStyleBackColor = true;
            this.BtnSelectControl.Click += new System.EventHandler(this.BtnSelectControl_Click);
            // 
            // FlpHPins
            // 
            this.FlpHPins.AllowDrop = true;
            this.FlpHPins.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.FlpHPins.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.FlpHPins.Location = new System.Drawing.Point(21, 170);
            this.FlpHPins.Name = "FlpHPins";
            this.FlpHPins.Size = new System.Drawing.Size(325, 84);
            this.FlpHPins.TabIndex = 18;
            // 
            // FlpPool
            // 
            this.FlpPool.AllowDrop = true;
            this.FlpPool.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.FlpPool.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.FlpPool.Location = new System.Drawing.Point(352, 170);
            this.FlpPool.Name = "FlpPool";
            this.FlpPool.Size = new System.Drawing.Size(200, 187);
            this.FlpPool.TabIndex = 17;
            // 
            // LController
            // 
            this.LController.AutoSize = true;
            this.LController.Location = new System.Drawing.Point(117, 17);
            this.LController.Name = "LController";
            this.LController.Size = new System.Drawing.Size(113, 13);
            this.LController.TabIndex = 1;
            this.LController.Text = "No Controller Selected";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(18, 50);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(38, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Name:";
            // 
            // TbName
            // 
            this.TbName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TbName.Location = new System.Drawing.Point(128, 47);
            this.TbName.Name = "TbName";
            this.TbName.Size = new System.Drawing.Size(424, 20);
            this.TbName.TabIndex = 7;
            // 
            // TbVariant
            // 
            this.TbVariant.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TbVariant.Location = new System.Drawing.Point(128, 73);
            this.TbVariant.Name = "TbVariant";
            this.TbVariant.Size = new System.Drawing.Size(424, 20);
            this.TbVariant.TabIndex = 9;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(18, 76);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(43, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Variant:";
            // 
            // TbBuild
            // 
            this.TbBuild.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TbBuild.Location = new System.Drawing.Point(128, 99);
            this.TbBuild.Name = "TbBuild";
            this.TbBuild.Size = new System.Drawing.Size(424, 20);
            this.TbBuild.TabIndex = 11;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(18, 102);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(33, 13);
            this.label6.TabIndex = 10;
            this.label6.Text = "Build:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(18, 128);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(77, 13);
            this.label7.TabIndex = 12;
            this.label7.Text = "Refresh Delay:";
            // 
            // NudRefresh
            // 
            this.NudRefresh.Location = new System.Drawing.Point(128, 126);
            this.NudRefresh.Name = "NudRefresh";
            this.NudRefresh.Size = new System.Drawing.Size(120, 20);
            this.NudRefresh.TabIndex = 13;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(18, 154);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(77, 13);
            this.label8.TabIndex = 14;
            this.label8.Text = "Horizontal Pins";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(18, 257);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(65, 13);
            this.label9.TabIndex = 19;
            this.label9.Text = "Vertical Pins";
            // 
            // FlpVPins
            // 
            this.FlpVPins.AllowDrop = true;
            this.FlpVPins.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.FlpVPins.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.FlpVPins.Location = new System.Drawing.Point(21, 273);
            this.FlpVPins.Name = "FlpVPins";
            this.FlpVPins.Size = new System.Drawing.Size(325, 84);
            this.FlpVPins.TabIndex = 20;
            // 
            // label10
            // 
            this.label10.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(349, 154);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(73, 13);
            this.label10.TabIndex = 15;
            this.label10.Text = "Available Pins";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(18, 371);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(36, 13);
            this.label11.TabIndex = 21;
            this.label11.Text = "Mods:";
            // 
            // LbMods
            // 
            this.LbMods.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.LbMods.FormattingEnabled = true;
            this.LbMods.Location = new System.Drawing.Point(21, 387);
            this.LbMods.Name = "LbMods";
            this.LbMods.Size = new System.Drawing.Size(245, 95);
            this.LbMods.TabIndex = 22;
            // 
            // LbModPool
            // 
            this.LbModPool.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.LbModPool.FormattingEnabled = true;
            this.LbModPool.Location = new System.Drawing.Point(315, 387);
            this.LbModPool.Name = "LbModPool";
            this.LbModPool.Size = new System.Drawing.Size(237, 95);
            this.LbModPool.TabIndex = 25;
            // 
            // label12
            // 
            this.label12.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(312, 371);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(82, 13);
            this.label12.TabIndex = 24;
            this.label12.Text = "Available Mods:";
            // 
            // BtAddMod
            // 
            this.BtAddMod.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BtAddMod.Location = new System.Drawing.Point(272, 387);
            this.BtAddMod.Name = "BtAddMod";
            this.BtAddMod.Size = new System.Drawing.Size(37, 95);
            this.BtAddMod.TabIndex = 23;
            this.BtAddMod.Text = "<<";
            this.BtAddMod.UseVisualStyleBackColor = true;
            this.BtAddMod.Click += new System.EventHandler(this.BtAddMod_Click);
            // 
            // BtnBuildAll
            // 
            this.BtnBuildAll.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BtnBuildAll.Location = new System.Drawing.Point(477, 12);
            this.BtnBuildAll.Name = "BtnBuildAll";
            this.BtnBuildAll.Size = new System.Drawing.Size(75, 23);
            this.BtnBuildAll.TabIndex = 5;
            this.BtnBuildAll.Text = "Build All";
            this.BtnBuildAll.UseVisualStyleBackColor = true;
            // 
            // BtnResetPins
            // 
            this.BtnResetPins.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BtnResetPins.Location = new System.Drawing.Point(477, 144);
            this.BtnResetPins.Name = "BtnResetPins";
            this.BtnResetPins.Size = new System.Drawing.Size(75, 23);
            this.BtnResetPins.TabIndex = 16;
            this.BtnResetPins.Text = "Reset";
            this.BtnResetPins.UseVisualStyleBackColor = true;
            this.BtnResetPins.Click += new System.EventHandler(this.BtnResetPins_Click);
            // 
            // BtnResetMod
            // 
            this.BtnResetMod.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BtnResetMod.Location = new System.Drawing.Point(477, 362);
            this.BtnResetMod.Name = "BtnResetMod";
            this.BtnResetMod.Size = new System.Drawing.Size(75, 23);
            this.BtnResetMod.TabIndex = 28;
            this.BtnResetMod.Text = "Reset";
            this.BtnResetMod.UseVisualStyleBackColor = true;
            this.BtnResetMod.Click += new System.EventHandler(this.BtnResetMod_Click);
            // 
            // FmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(564, 610);
            this.Controls.Add(this.BtnResetMod);
            this.Controls.Add(this.BtnResetPins);
            this.Controls.Add(this.BtnBuildAll);
            this.Controls.Add(this.BtAddMod);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.LbModPool);
            this.Controls.Add(this.LbMods);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.FlpVPins);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.NudRefresh);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.TbBuild);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.TbVariant);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.TbName);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.LController);
            this.Controls.Add(this.FlpPool);
            this.Controls.Add(this.FlpHPins);
            this.Controls.Add(this.BtnSelectControl);
            this.Controls.Add(this.BtnBuild);
            this.Controls.Add(this.BtnLoad);
            this.Controls.Add(this.BtnSave);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FmMain";
            this.Text = "Animus Builder Innova - 1.0 0004";
            this.Load += new System.EventHandler(this.FmMain_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NudRefresh)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button BtnOutputPath;
        private System.Windows.Forms.TextBox TbOutputPath;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button BtnModPath;
        private System.Windows.Forms.TextBox TbModPath;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button BtnAnimusPath;
        private System.Windows.Forms.TextBox TbAnimusPath;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button BtnSave;
        private System.Windows.Forms.Button BtnLoad;
        private System.Windows.Forms.Button BtnBuild;
        private System.Windows.Forms.Button BtnSelectControl;
        private System.Windows.Forms.FlowLayoutPanel FlpHPins;
        private System.Windows.Forms.FlowLayoutPanel FlpPool;
        private System.Windows.Forms.Label LController;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox TbName;
        private System.Windows.Forms.TextBox TbVariant;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox TbBuild;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown NudRefresh;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.FlowLayoutPanel FlpVPins;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.ListBox LbMods;
        private System.Windows.Forms.ListBox LbModPool;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button BtAddMod;
        private System.Windows.Forms.Button BtnBuildAll;
        private System.Windows.Forms.Button BtnResetPins;
        private System.Windows.Forms.Button BtnResetMod;

    }
}

