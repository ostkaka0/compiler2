namespace AlphaChannelExtractor
{
    partial class Form1
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
            this.tbBackground = new System.Windows.Forms.TextBox();
            this.tbResult = new System.Windows.Forms.TextBox();
            this.tbForeground = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.btnForeground = new System.Windows.Forms.Button();
            this.btnBackground = new System.Windows.Forms.Button();
            this.btnResult = new System.Windows.Forms.Button();
            this.btnMixed = new System.Windows.Forms.Button();
            this.tbMixed = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // tbBackground
            // 
            this.tbBackground.Location = new System.Drawing.Point(91, 14);
            this.tbBackground.Name = "tbBackground";
            this.tbBackground.Size = new System.Drawing.Size(100, 20);
            this.tbBackground.TabIndex = 0;
            // 
            // tbResult
            // 
            this.tbResult.Location = new System.Drawing.Point(91, 113);
            this.tbResult.Name = "tbResult";
            this.tbResult.Size = new System.Drawing.Size(100, 20);
            this.tbResult.TabIndex = 1;
            // 
            // tbForeground
            // 
            this.tbForeground.Location = new System.Drawing.Point(91, 43);
            this.tbForeground.Name = "tbForeground";
            this.tbForeground.Size = new System.Drawing.Size(100, 20);
            this.tbForeground.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Background";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(8, 46);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(61, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Foreground";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 116);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(32, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Save";
            // 
            // btnForeground
            // 
            this.btnForeground.Location = new System.Drawing.Point(197, 41);
            this.btnForeground.Name = "btnForeground";
            this.btnForeground.Size = new System.Drawing.Size(75, 23);
            this.btnForeground.TabIndex = 6;
            this.btnForeground.Text = "Load";
            this.btnForeground.UseVisualStyleBackColor = true;
            this.btnForeground.Click += new System.EventHandler(this.btnForeground_Click);
            // 
            // btnBackground
            // 
            this.btnBackground.Location = new System.Drawing.Point(197, 12);
            this.btnBackground.Name = "btnBackground";
            this.btnBackground.Size = new System.Drawing.Size(75, 23);
            this.btnBackground.TabIndex = 7;
            this.btnBackground.Text = "Load";
            this.btnBackground.UseVisualStyleBackColor = true;
            this.btnBackground.Click += new System.EventHandler(this.btnBackground_Click);
            // 
            // btnResult
            // 
            this.btnResult.Location = new System.Drawing.Point(197, 113);
            this.btnResult.Name = "btnResult";
            this.btnResult.Size = new System.Drawing.Size(75, 23);
            this.btnResult.TabIndex = 8;
            this.btnResult.Text = "Save";
            this.btnResult.UseVisualStyleBackColor = true;
            this.btnResult.Click += new System.EventHandler(this.btnResult_Click);
            // 
            // btnMixed
            // 
            this.btnMixed.Location = new System.Drawing.Point(197, 70);
            this.btnMixed.Name = "btnMixed";
            this.btnMixed.Size = new System.Drawing.Size(75, 23);
            this.btnMixed.TabIndex = 9;
            this.btnMixed.Text = "Load";
            this.btnMixed.UseVisualStyleBackColor = true;
            this.btnMixed.Click += new System.EventHandler(this.btnMixed_Click);
            // 
            // tbMixed
            // 
            this.tbMixed.Location = new System.Drawing.Point(91, 72);
            this.tbMixed.Name = "tbMixed";
            this.tbMixed.Size = new System.Drawing.Size(100, 20);
            this.tbMixed.TabIndex = 10;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 75);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Mixed";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.tbMixed);
            this.Controls.Add(this.btnMixed);
            this.Controls.Add(this.btnResult);
            this.Controls.Add(this.btnBackground);
            this.Controls.Add(this.btnForeground);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tbForeground);
            this.Controls.Add(this.tbResult);
            this.Controls.Add(this.tbBackground);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbBackground;
        private System.Windows.Forms.TextBox tbResult;
        private System.Windows.Forms.TextBox tbForeground;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnForeground;
        private System.Windows.Forms.Button btnBackground;
        private System.Windows.Forms.Button btnResult;
        private System.Windows.Forms.Button btnMixed;
        private System.Windows.Forms.TextBox tbMixed;
        private System.Windows.Forms.Label label4;
    }
}

