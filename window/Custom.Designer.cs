namespace APKStudio.Window
{
    partial class Custom
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            this.WindowButtons = new System.Windows.Forms.PictureBox();
            this.WindowBorder = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.WindowButtons)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.WindowBorder)).BeginInit();
            this.SuspendLayout();
            // 
            // WindowButtons
            // 
            this.WindowButtons.Image = Resource.sprite_main_window_button;
            this.WindowButtons.Location = new System.Drawing.Point(82, 0);
            this.WindowButtons.Name = "WindowButtons";
            this.WindowButtons.Size = new System.Drawing.Size(105, 105);
            this.WindowButtons.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.WindowButtons.TabIndex = 1;
            this.WindowButtons.TabStop = false;
            this.WindowButtons.Visible = false;
            // 
            // WindowBorder
            // 
            this.WindowBorder.Image = Resource.sprite_main_window_border;
            this.WindowBorder.Location = new System.Drawing.Point(0, 0);
            this.WindowBorder.Name = "WindowBorder";
            this.WindowBorder.Size = new System.Drawing.Size(64, 64);
            this.WindowBorder.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.WindowBorder.TabIndex = 0;
            this.WindowBorder.TabStop = false;
            this.WindowBorder.Visible = false;
            // 
            // CustomWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.WindowButtons);
            this.Controls.Add(this.WindowBorder);
            this.DoubleBuffered = true;
            this.Name = "CustomWindow";
            this.Size = new System.Drawing.Size(220, 151);
            this.Load += new System.EventHandler(this.ctlModernBlack_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.ctlSkin_Paint);
            this.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.ctlSkin_MouseDoubleClick);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ctlSkin_MouseDown);
            this.MouseLeave += new System.EventHandler(this.ctlSkin_MouseLeave);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.ctlSkin_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ctlSkin_MouseUp);
            this.Resize += new System.EventHandler(this.ctlSkin_Resize);
            ((System.ComponentModel.ISupportInitialize)(this.WindowButtons)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.WindowBorder)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        private System.Windows.Forms.PictureBox WindowBorder;
        private System.Windows.Forms.PictureBox WindowButtons;
    }
}
