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
        int[] TargetX = new int[] { 3,128 , 417, 722, 832,723,418,127};
        int[] TargetY = new int[] { 307, 85, 0, 85, 307, 529,614, 530};
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
            Bt_Start.Enabled = true;
            Bt_Stop.Enabled = false;
            BuadRate.Text = "115200";
            MainPanel.Visible = false;
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

        private void Bt_Stop_Click(object sender, EventArgs e)
        {
            try
            {
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
            if (combo_Project.Text == "Charges")
            {
                MainPanel.Visible = true;
                //Rehab_Panel.Visible = false;
                type = 1;
                Circular_Background.Visible = false;
                grayball.Visible = false;
                Target.Visible = false;
                if (serialPort1.IsOpen)
                    serialPort1.Write("ST1" + "G");
                else MessageBox.Show("Please Connect to Port First");

            }
            else if (combo_Project.Text == "Rehabitation")
            {
                MainPanel.Visible = true;
                //Rehab_Panel.Visible = true;
                type = 2;
                Circular_Background.Visible = true;
                grayball.Visible = true;
                Target.Visible = true;
                if(serialPort1.IsOpen)
                serialPort1.Write("ST0" + "G");
                else MessageBox.Show("Please Connect to Port First");
            }
            else { MessageBox.Show("Please choose a Project"); }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
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
                    Robot_EF.Location = new Point(PX/10, PY/10);
                    //MessageBox.Show("Bye Recieved");
                }
                else if(type == 2)
                {
                    grayball.Location = new Point(PX+ 472, PY+ 331);
                    
                    a = Math.Abs(Math.Sqrt(grayball.Location.X ^ 2 + grayball.Location.Y ^ 2)
                        - Math.Sqrt(Target.Location.X ^ 2 + Target.Location.Y ^ 2));
                    if (a < 1)
                    {
                        i++;
                        j++;
                        Target.Location = new Point(TargetX[i],TargetY[j]);
                        if (i == 7) i = -1;
                        if (j == 7) j = -1;
                        //MessageBox.Show(Convert.ToString(TargetX[i]) +" "+ Convert.ToString(TargetY[j]));
                    }
                }
                
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }

        private void keyup(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Enter)
            Robot_EF.Top += 1;
        }
    }
}
