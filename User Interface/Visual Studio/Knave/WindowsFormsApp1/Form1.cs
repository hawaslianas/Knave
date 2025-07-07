using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;



namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        //int PanelWidth = 720;
        //int PanelHight = 960;
        int PX, PY;
        bool A = true;
        //int[] TargetX = newint[]{ 1,  2 ,  3 ,  4 ,  5 , 6 , 7 , 8 };
        //int[] TargetX = new int[] { 3,128 , 417, 722, 832,723,418,127};
        //int[] TargetY = new int[] { 307, 85, 0, 85, 307, 529,614, 530};
        // 5 4 3 5 3
        int[] TargetX = new int[] { 832, 721, 417, 832, 417 };
        int[] TargetY = new int[] { 307, 534,   0, 307,   0 };
        double a=0;
        int i = 0, j = 0;
        int type = 0;

        string SerialData;
        SByte indexOfA, indexOfB, indexOfC;
        string NX, NY, NM;
        


        public object SerialPort1 { get; private set; }

        public Form1()
        {
            InitializeComponent();
        }



        private void Form1_Load(object sender, EventArgs e)
        {
            CheckForIllegalCrossThreadCalls = false;
            Bt_Start.Enabled = true;
            Bt_Stop.Enabled = false;
            BuadRate.Text = "115200";
            MainPanel.Visible = false;
            Robot_EF.Visible = false;
            Serial_COM.Text = "COM13";
        }

        private void Serial_COM_DropDown(object sender, EventArgs e)
        {
            string[] portLists = SerialPort.GetPortNames();
            Serial_COM.Items.Clear();
            Serial_COM.Items.AddRange(portLists);

        }

        private void Bt_Start_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = Serial_COM.Text;
                serialPort1.BaudRate = Convert.ToInt32(BuadRate.Text);
                serialPort1.Open();
                if (serialPort1.IsOpen)
                    serialPort1.Write("ST8" + "G");
                
                Bt_Start.Enabled = false;
                Bt_Stop.Enabled = true;
                progressBar1.Value = 100;
             

                    Robot_EF.Location = new Point(100, 150);
            }

            catch(Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }

        private void BT_RST_Click(object sender, EventArgs e)
        {
            if(serialPort1.IsOpen)
            {
                serialPort1.Write("ST" + 0 + "G");
            }
            
        }

        private void Bt_Stop_Click(object sender, EventArgs e)
        {
            try
            {
                if (serialPort1.IsOpen)
                { serialPort1.Write("ST9" + "G"); }
                serialPort1.Close();

                Bt_Stop.Enabled = false;
                Bt_Start.Enabled = true;
                progressBar1.Value = 0;
            }
            catch(Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }

    

        private void Bt_Generate_Click(object sender, EventArgs e)
        {
            if (combo_Project.Text == "Spring and Damper")
            {
                MainPanel.Visible = true;
                //Rehab_Panel.Visible = false;
                type = 1;
                Positive_Side.Visible = true;
                Negative_Side.Visible = false;
                Positive_Side.Location = new Point(445, 305);
                Circular_Background.Visible = false;
                grayball.Visible = true;
                grayball.BringToFront();
                Target.Visible = false;
                Moon.Visible = false;
                if (serialPort1.IsOpen)
                    serialPort1.Write("ST1" + "G");
                else MessageBox.Show("Please Connect to Port First");
            }
            else if (combo_Project.Text == "Collision")
            {
                MainPanel.Visible = true;
                type = 2;
                Moon.Visible = true;
                Negative_Side.Visible = false;
                Positive_Side.Visible = false;
                Circular_Background.Visible = false;
                grayball.Visible = true;
                grayball.BringToFront();
                Target.Visible   = false;
                if(serialPort1.IsOpen)
                serialPort1.Write("ST2" + "G");
                else MessageBox.Show("Please Connect to Port First");
            }
            else if (combo_Project.Text == "Rehabitation")
            {
                MainPanel.Visible = true;
                //Rehab_Panel.Visible = true;
                type = 3;
                Moon.Visible = false;
                Negative_Side.Visible = false;
                Circular_Background.Visible = true;
                grayball.Visible = true;
                grayball.BringToFront();
                Target.Visible = true;
                Target.BringToFront();
                if (serialPort1.IsOpen)
                    serialPort1.Write("ST3" + "G");
                else MessageBox.Show("Please Connect to Port First");
            }
            else { MessageBox.Show("Please choose a Project"); }
        }

        private void Form1_FormClosing(object sender,FormClosingEventArgs e)
        {
            try
            {
                serialPort1.Close();
            }
            catch(Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialData = serialPort1.ReadLine();
            this.BeginInvoke(new EventHandler(ProcessData));
        }

        private void ProcessData(object sender, EventArgs e)
        {
           
            {
                try
                {
                    indexOfA = Convert.ToSByte(SerialData.IndexOf("A"));
                    indexOfB = Convert.ToSByte(SerialData.IndexOf("B"));
                    indexOfC = Convert.ToSByte(SerialData.IndexOf("C"));

                    NX = SerialData.Substring(0, indexOfA);
                    NY = SerialData.Substring(indexOfA + 1, (indexOfB - indexOfA) - 1);
                    NM = SerialData.Substring(indexOfB + 1, (indexOfC - indexOfB) - 1);

                    PX = Convert.ToInt32(NX);
                    PY = Convert.ToInt32(NY);


                    if (type == 1)
                    {
                        grayball.Location = new Point(PX + 472, PY + 331);
                        TB_EF_X.Text = Convert.ToString(PX);
                        TB_EF_Y.Text = Convert.ToString(PY);
                        TBP_EF_X.Text = Convert.ToString(PX + 472);
                        TBP_EF_Y.Text = Convert.ToString(PY + 331);

                    }
                    else if (type == 2)
                    {
                        grayball.Location = new Point(PX + 472, PY + 331);
                        TB_EF_X.Text = Convert.ToString(PX);
                        TB_EF_Y.Text = Convert.ToString(PY);
                        TBP_EF_X.Text = Convert.ToString(PX + 472);
                        TBP_EF_Y.Text = Convert.ToString(PY + 331);
                    }
                    else if (type == 3)
                    {
                        grayball.Location = new Point(PX + 472, PY + 331);

                        a = Math.Sqrt((grayball.Location.X - Target.Location.X) ^ 2 +
                            (grayball.Location.Y - Target.Location.Y) ^ 2);
                        if (a < 6)
                        {
                            i++;
                            j++;
                            Target.Location = new Point(TargetX[i], TargetY[j]);
                            if (i == 5) i = -1;
                            if (j == 5) j = -1;
                            if (serialPort1.IsOpen)
                            {
                                serialPort1.Write("STXG");
                                
                                //serialPort1.WriteLine("STXG");
                            }
                        }
                        TB_EF_X.Text = Convert.ToString(PX);
                        TB_EF_Y.Text = Convert.ToString(PY);
                        TBP_EF_X.Text = Convert.ToString(PX + 472);
                        TBP_EF_Y.Text = Convert.ToString(PY + 331);
                    }
                }


                catch (Exception error)
                {
                    //MessageBox.Show(error.Message);
                }
            }
        }
        private void keyup(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Enter)
            Robot_EF.Top += 1;
        }
    }
}
