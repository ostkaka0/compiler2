namespace stop_motion
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
            this.btnGenerate = new System.Windows.Forms.Button();
            this.btnPathilator = new System.Windows.Forms.Button();
            this.cbFlipX = new System.Windows.Forms.CheckBox();
            this.cbFlipY = new System.Windows.Forms.CheckBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnGenerate
            // 
            this.btnGenerate.Location = new System.Drawing.Point(158, 134);
            this.btnGenerate.Name = "btnGenerate";
            this.btnGenerate.Size = new System.Drawing.Size(75, 23);
            this.btnGenerate.TabIndex = 0;
            this.btnGenerate.Text = "make all .avi";
            this.btnGenerate.UseVisualStyleBackColor = true;
            this.btnGenerate.Click += new System.EventHandler(this.btnGenerate_Click);
            // 
            // btnPathilator
            // 
            this.btnPathilator.Location = new System.Drawing.Point(26, 56);
            this.btnPathilator.Name = "btnPathilator";
            this.btnPathilator.Size = new System.Drawing.Size(75, 23);
            this.btnPathilator.TabIndex = 1;
            this.btnPathilator.Text = "pathilator";
            this.btnPathilator.UseVisualStyleBackColor = true;
            this.btnPathilator.Click += new System.EventHandler(this.button1_Click);
            // 
            // cbFlipX
            // 
            this.cbFlipX.AutoSize = true;
            this.cbFlipX.Location = new System.Drawing.Point(181, 56);
            this.cbFlipX.Name = "cbFlipX";
            this.cbFlipX.Size = new System.Drawing.Size(52, 17);
            this.cbFlipX.TabIndex = 2;
            this.cbFlipX.Text = "Flip X";
            this.cbFlipX.UseVisualStyleBackColor = true;
            // 
            // cbFlipY
            // 
            this.cbFlipY.AutoSize = true;
            this.cbFlipY.Location = new System.Drawing.Point(181, 79);
            this.cbFlipY.Name = "cbFlipY";
            this.cbFlipY.Size = new System.Drawing.Size(52, 17);
            this.cbFlipY.TabIndex = 3;
            this.cbFlipY.Text = "Flip Y";
            this.cbFlipY.UseVisualStyleBackColor = true;
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(12, 227);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(260, 23);
            this.progressBar1.TabIndex = 4;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 134);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 5;
            this.button1.Text = "make .avi";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(79, 183);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(138, 23);
            this.button2.TabIndex = 6;
            this.button2.Text = "make smaller";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(872, 528);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.cbFlipY);
            this.Controls.Add(this.cbFlipX);
            this.Controls.Add(this.btnPathilator);
            this.Controls.Add(this.btnGenerate);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnGenerate;
        private System.Windows.Forms.Button btnPathilator;
        private System.Windows.Forms.CheckBox cbFlipX;
        private System.Windows.Forms.CheckBox cbFlipY;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}

