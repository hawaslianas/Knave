namespace WindowsFormsApp1
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.Robot_EF = new System.Windows.Forms.PictureBox();
            this.Negative_Side = new System.Windows.Forms.PictureBox();
            this.Positive_Side = new System.Windows.Forms.PictureBox();
            this.HIAST_logo = new System.Windows.Forms.PictureBox();
            this.Knave_logo = new System.Windows.Forms.PictureBox();
            this.MainPanel = new System.Windows.Forms.Panel();
            this.Target = new System.Windows.Forms.PictureBox();
            this.grayball = new System.Windows.Forms.PictureBox();
            this.Circular_Background = new System.Windows.Forms.PictureBox();
            this.Settings_Box = new System.Windows.Forms.GroupBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.Bt_Start = new System.Windows.Forms.Button();
            this.Bt_Stop = new System.Windows.Forms.Button();
            this.BuadRate = new System.Windows.Forms.ComboBox();
            this.BuadRate_label = new System.Windows.Forms.Label();
            this.Serial_COM = new System.Windows.Forms.ComboBox();
            this.Serial_Label = new System.Windows.Forms.Label();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.Bt_Generate = new System.Windows.Forms.Button();
            this.combo_Project = new System.Windows.Forms.ComboBox();
            this.Project = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.Robot_EF)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Negative_Side)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Positive_Side)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.HIAST_logo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Knave_logo)).BeginInit();
            this.MainPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Target)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.grayball)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Circular_Background)).BeginInit();
            this.Settings_Box.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // Robot_EF
            // 
            this.Robot_EF.BackColor = System.Drawing.Color.Transparent;
            this.Robot_EF.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("Robot_EF.BackgroundImage")));
            this.Robot_EF.Image = ((System.Drawing.Image)(resources.GetObject("Robot_EF.Image")));
            this.Robot_EF.Location = new System.Drawing.Point(455, 335);
            this.Robot_EF.Name = "Robot_EF";
            this.Robot_EF.Size = new System.Drawing.Size(48, 47);
            this.Robot_EF.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.Robot_EF.TabIndex = 0;
            this.Robot_EF.TabStop = false;
            // 
            // Negative_Side
            // 
            this.Negative_Side.BackColor = System.Drawing.Color.Transparent;
            this.Negative_Side.Image = ((System.Drawing.Image)(resources.GetObject("Negative_Side.Image")));
            this.Negative_Side.Location = new System.Drawing.Point(653, 310);
            this.Negative_Side.Name = "Negative_Side";
            this.Negative_Side.Size = new System.Drawing.Size(104, 97);
            this.Negative_Side.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Negative_Side.TabIndex = 1;
            this.Negative_Side.TabStop = false;
            // 
            // Positive_Side
            // 
            this.Positive_Side.BackColor = System.Drawing.Color.Transparent;
            this.Positive_Side.Image = ((System.Drawing.Image)(resources.GetObject("Positive_Side.Image")));
            this.Positive_Side.Location = new System.Drawing.Point(200, 310);
            this.Positive_Side.Name = "Positive_Side";
            this.Positive_Side.Size = new System.Drawing.Size(104, 97);
            this.Positive_Side.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Positive_Side.TabIndex = 2;
            this.Positive_Side.TabStop = false;
            // 
            // HIAST_logo
            // 
            this.HIAST_logo.Image = ((System.Drawing.Image)(resources.GetObject("HIAST_logo.Image")));
            this.HIAST_logo.Location = new System.Drawing.Point(12, 23);
            this.HIAST_logo.Name = "HIAST_logo";
            this.HIAST_logo.Size = new System.Drawing.Size(151, 145);
            this.HIAST_logo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.HIAST_logo.TabIndex = 3;
            this.HIAST_logo.TabStop = false;
            // 
            // Knave_logo
            // 
            this.Knave_logo.BackColor = System.Drawing.Color.Transparent;
            this.Knave_logo.Image = ((System.Drawing.Image)(resources.GetObject("Knave_logo.Image")));
            this.Knave_logo.Location = new System.Drawing.Point(167, 51);
            this.Knave_logo.Name = "Knave_logo";
            this.Knave_logo.Size = new System.Drawing.Size(349, 88);
            this.Knave_logo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Knave_logo.TabIndex = 4;
            this.Knave_logo.TabStop = false;
            // 
            // MainPanel
            // 
            this.MainPanel.Controls.Add(this.Target);
            this.MainPanel.Controls.Add(this.grayball);
            this.MainPanel.Controls.Add(this.Circular_Background);
            this.MainPanel.Controls.Add(this.Robot_EF);
            this.MainPanel.Controls.Add(this.Negative_Side);
            this.MainPanel.Controls.Add(this.Positive_Side);
            this.MainPanel.Location = new System.Drawing.Point(167, 185);
            this.MainPanel.Name = "MainPanel";
            this.MainPanel.Size = new System.Drawing.Size(960, 720);
            this.MainPanel.TabIndex = 5;
            // 
            // Target
            // 
            this.Target.Image = ((System.Drawing.Image)(resources.GetObject("Target.Image")));
            this.Target.Location = new System.Drawing.Point(3, 307);
            this.Target.Name = "Target";
            this.Target.Size = new System.Drawing.Size(128, 100);
            this.Target.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Target.TabIndex = 1;
            this.Target.TabStop = false;
            // 
            // grayball
            // 
            this.grayball.Image = ((System.Drawing.Image)(resources.GetObject("grayball.Image")));
            this.grayball.Location = new System.Drawing.Point(472, 331);
            this.grayball.Name = "grayball";
            this.grayball.Size = new System.Drawing.Size(51, 51);
            this.grayball.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.grayball.TabIndex = 2;
            this.grayball.TabStop = false;
            // 
            // Circular_Background
            // 
            this.Circular_Background.BackColor = System.Drawing.Color.Transparent;
            this.Circular_Background.Image = ((System.Drawing.Image)(resources.GetObject("Circular_Background.Image")));
            this.Circular_Background.Location = new System.Drawing.Point(3, 0);
            this.Circular_Background.Name = "Circular_Background";
            this.Circular_Background.Size = new System.Drawing.Size(957, 714);
            this.Circular_Background.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Circular_Background.TabIndex = 0;
            this.Circular_Background.TabStop = false;
            // 
            // Settings_Box
            // 
            this.Settings_Box.Controls.Add(this.progressBar1);
            this.Settings_Box.Controls.Add(this.Bt_Start);
            this.Settings_Box.Controls.Add(this.Bt_Stop);
            this.Settings_Box.Controls.Add(this.BuadRate);
            this.Settings_Box.Controls.Add(this.BuadRate_label);
            this.Settings_Box.Controls.Add(this.Serial_COM);
            this.Settings_Box.Controls.Add(this.Serial_Label);
            this.Settings_Box.Location = new System.Drawing.Point(1133, 626);
            this.Settings_Box.Name = "Settings_Box";
            this.Settings_Box.Size = new System.Drawing.Size(212, 244);
            this.Settings_Box.TabIndex = 6;
            this.Settings_Box.TabStop = false;
            this.Settings_Box.Text = "Communication Settings";
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(47, 215);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(143, 23);
            this.progressBar1.TabIndex = 6;
            // 
            // Bt_Start
            // 
            this.Bt_Start.Location = new System.Drawing.Point(47, 131);
            this.Bt_Start.Name = "Bt_Start";
            this.Bt_Start.Size = new System.Drawing.Size(143, 23);
            this.Bt_Start.TabIndex = 4;
            this.Bt_Start.Text = "Start Communication";
            this.Bt_Start.UseVisualStyleBackColor = true;
            this.Bt_Start.Click += new System.EventHandler(this.Bt_Start_Click);
            // 
            // Bt_Stop
            // 
            this.Bt_Stop.Location = new System.Drawing.Point(47, 170);
            this.Bt_Stop.Name = "Bt_Stop";
            this.Bt_Stop.Size = new System.Drawing.Size(143, 23);
            this.Bt_Stop.TabIndex = 5;
            this.Bt_Stop.Text = "Terminate Communication";
            this.Bt_Stop.UseVisualStyleBackColor = true;
            this.Bt_Stop.Click += new System.EventHandler(this.Bt_Stop_Click);
            // 
            // BuadRate
            // 
            this.BuadRate.FormattingEnabled = true;
            this.BuadRate.Items.AddRange(new object[] {
            "1200",
            "2400",
            "4800",
            "9600",
            "19200",
            "38400",
            "57600",
            "115200"});
            this.BuadRate.Location = new System.Drawing.Point(84, 79);
            this.BuadRate.Name = "BuadRate";
            this.BuadRate.Size = new System.Drawing.Size(121, 21);
            this.BuadRate.TabIndex = 3;
            // 
            // BuadRate_label
            // 
            this.BuadRate_label.AutoSize = true;
            this.BuadRate_label.Location = new System.Drawing.Point(19, 82);
            this.BuadRate_label.Name = "BuadRate_label";
            this.BuadRate_label.Size = new System.Drawing.Size(57, 13);
            this.BuadRate_label.TabIndex = 2;
            this.BuadRate_label.Text = "Buad Rate";
            // 
            // Serial_COM
            // 
            this.Serial_COM.FormattingEnabled = true;
            this.Serial_COM.Items.AddRange(new object[] {
            "COM 1",
            "COM 2",
            "COM 3",
            "COM 4",
            "COM 5",
            "COM 6",
            "COM 7",
            "COM 8",
            "COM 9",
            "COM 10",
            "COM 11",
            "COM 12",
            "COM 13"});
            this.Serial_COM.Location = new System.Drawing.Point(84, 36);
            this.Serial_COM.Name = "Serial_COM";
            this.Serial_COM.Size = new System.Drawing.Size(121, 21);
            this.Serial_COM.TabIndex = 1;
            this.Serial_COM.DropDown += new System.EventHandler(this.Serial_COM_DropDown);
            // 
            // Serial_Label
            // 
            this.Serial_Label.AutoSize = true;
            this.Serial_Label.Location = new System.Drawing.Point(19, 39);
            this.Serial_Label.Name = "Serial_Label";
            this.Serial_Label.Size = new System.Drawing.Size(59, 13);
            this.Serial_Label.TabIndex = 0;
            this.Serial_Label.Text = "Serial COM";
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.Bt_Generate);
            this.groupBox1.Controls.Add(this.combo_Project);
            this.groupBox1.Controls.Add(this.Project);
            this.groupBox1.Location = new System.Drawing.Point(1133, 316);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(205, 179);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Projec Type Settings";
            // 
            // Bt_Generate
            // 
            this.Bt_Generate.Location = new System.Drawing.Point(31, 83);
            this.Bt_Generate.Name = "Bt_Generate";
            this.Bt_Generate.Size = new System.Drawing.Size(143, 23);
            this.Bt_Generate.TabIndex = 5;
            this.Bt_Generate.Text = "Generate";
            this.Bt_Generate.UseVisualStyleBackColor = true;
            this.Bt_Generate.Click += new System.EventHandler(this.Bt_Generate_Click);
            // 
            // combo_Project
            // 
            this.combo_Project.FormattingEnabled = true;
            this.combo_Project.Items.AddRange(new object[] {
            "Charges",
            "Rehabitation"});
            this.combo_Project.Location = new System.Drawing.Point(84, 38);
            this.combo_Project.Name = "combo_Project";
            this.combo_Project.Size = new System.Drawing.Size(121, 21);
            this.combo_Project.TabIndex = 3;
            // 
            // Project
            // 
            this.Project.AutoSize = true;
            this.Project.Location = new System.Drawing.Point(19, 41);
            this.Project.Name = "Project";
            this.Project.Size = new System.Drawing.Size(41, 13);
            this.Project.TabIndex = 2;
            this.Project.Text = "Project";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1350, 911);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.Settings_Box);
            this.Controls.Add(this.MainPanel);
            this.Controls.Add(this.Knave_logo);
            this.Controls.Add(this.HIAST_logo);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.keyup);
            ((System.ComponentModel.ISupportInitialize)(this.Robot_EF)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Negative_Side)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Positive_Side)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.HIAST_logo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Knave_logo)).EndInit();
            this.MainPanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.Target)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.grayball)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Circular_Background)).EndInit();
            this.Settings_Box.ResumeLayout(false);
            this.Settings_Box.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox Robot_EF;
        private System.Windows.Forms.PictureBox Negative_Side;
        private System.Windows.Forms.PictureBox Positive_Side;
        private System.Windows.Forms.PictureBox HIAST_logo;
        private System.Windows.Forms.PictureBox Knave_logo;
        private System.Windows.Forms.Panel MainPanel;
        private System.Windows.Forms.GroupBox Settings_Box;
        private System.Windows.Forms.Button Bt_Stop;
        private System.Windows.Forms.Button Bt_Start;
        private System.Windows.Forms.ComboBox BuadRate;
        private System.Windows.Forms.Label BuadRate_label;
        private System.Windows.Forms.ComboBox Serial_COM;
        private System.Windows.Forms.Label Serial_Label;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button Bt_Generate;
        private System.Windows.Forms.ComboBox combo_Project;
        private System.Windows.Forms.Label Project;
        private System.Windows.Forms.PictureBox Target;
        private System.Windows.Forms.PictureBox grayball;
        private System.Windows.Forms.PictureBox Circular_Background;
    }
}

