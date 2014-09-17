namespace APKStudio.Window
{
    partial class Rename
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
            this.DesignLabelFind = new System.Windows.Forms.Label();
            this.DesignTextboxNewname = new System.Windows.Forms.TextBox();
            this.DesignButtonCommit = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // DesignLabelFind
            // 
            this.DesignLabelFind.Dock = System.Windows.Forms.DockStyle.Top;
            this.DesignLabelFind.Location = new System.Drawing.Point(5, 5);
            this.DesignLabelFind.Name = "DesignLabelFind";
            this.DesignLabelFind.Size = new System.Drawing.Size(294, 16);
            this.DesignLabelFind.TabIndex = 0;
            this.DesignLabelFind.Text = "Rename to";
            // 
            // DesignTextboxNewname
            // 
            this.DesignTextboxNewname.Dock = System.Windows.Forms.DockStyle.Top;
            this.DesignTextboxNewname.Location = new System.Drawing.Point(5, 21);
            this.DesignTextboxNewname.Name = "DesignTextboxNewname";
            this.DesignTextboxNewname.Size = new System.Drawing.Size(294, 20);
            this.DesignTextboxNewname.TabIndex = 1;
            // 
            // DesignButtonCommit
            // 
            this.DesignButtonCommit.Location = new System.Drawing.Point(224, 52);
            this.DesignButtonCommit.Name = "DesignButtonCommit";
            this.DesignButtonCommit.Size = new System.Drawing.Size(75, 23);
            this.DesignButtonCommit.TabIndex = 2;
            this.DesignButtonCommit.Text = "Commit";
            this.DesignButtonCommit.UseVisualStyleBackColor = true;
            this.DesignButtonCommit.Click += new System.EventHandler(this.OnFindButtonClick);
            // 
            // Rename
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(304, 81);
            this.Controls.Add(this.DesignButtonCommit);
            this.Controls.Add(this.DesignTextboxNewname);
            this.Controls.Add(this.DesignLabelFind);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximumSize = new System.Drawing.Size(320, 120);
            this.MinimumSize = new System.Drawing.Size(320, 120);
            this.Name = "Rename";
            this.Padding = new System.Windows.Forms.Padding(5);
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "Rename";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label DesignLabelFind;
        private System.Windows.Forms.TextBox DesignTextboxNewname;
        private System.Windows.Forms.Button DesignButtonCommit;
    }
}