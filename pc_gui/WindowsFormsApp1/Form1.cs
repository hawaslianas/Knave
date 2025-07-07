// -----------------------------------------------------------------------------
// Form1.cs
// -----------------------------------------------------------------------------
// PC GUI for KNAVE 2-DOF Five Bar Haptic Device
//
// Responsibilities:
//   - Provide a graphical interface for device control and monitoring
//   - Communicate with the embedded firmware via serial
//   - Send commands, receive data, and visualize device state
//
// Author: [Your Name]
// Last Cleaned: July 2025
// -----------------------------------------------------------------------------

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
        // -------------------- Target Points for Demo/Control --------------------
        private readonly int[] targetX = new int[] { 832, 721, 417, 832, 417 };
        private readonly int[] targetY = new int[] { 307, 534, 0, 307, 0 };

        // -------------------- State Variables --------------------
        private int currentTargetIndex = 0;
        private int posX, posY;
        private bool isActive = true;
        private int projectType = 0;
        private string serialData;
        private sbyte indexOfA, indexOfB, indexOfC;
        private string parsedX, parsedY, parsedM;

        public Form1()
        {
            InitializeComponent();
        }

        // -------------------------------------------------------------------------
        // Form Load and UI Setup
        // -------------------------------------------------------------------------
        /// <summary>
        /// Initializes UI elements and default values on form load.
        /// </summary>
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

        /// <summary>
        /// Refreshes the list of available serial ports in the dropdown.
        /// </summary>
        private void Serial_COM_DropDown(object sender, EventArgs e)
        {
            string[] portLists = SerialPort.GetPortNames();
            Serial_COM.Items.Clear();
            Serial_COM.Items.AddRange(portLists);
        }

        // -------------------------------------------------------------------------
        // Serial Communication and Control
        // -------------------------------------------------------------------------
        /// <summary>
        /// Handles the Start button click: opens serial port and sends start command.
        /// </summary>
        private void Bt_Start_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = Serial_COM.Text;
                serialPort1.BaudRate = Convert.ToInt32(BuadRate.Text);
                serialPort1.Open();
                if (serialPort1.IsOpen)
                    serialPort1.Write("ST8G");

                Bt_Start.Enabled = false;
                Bt_Stop.Enabled = true;
                progressBar1.Value = 100;
                Robot_EF.Location = new Point(100, 150);
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }

        /// <summary>
        /// Handles the Reset button click: sends reset command to device.
        /// </summary>
        private void BT_RST_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write("ST0G");
            }
        }

        /// <summary>
        /// Handles the Stop button click: sends stop command and closes serial port.
        /// </summary>
        private void Bt_Stop_Click(object sender, EventArgs e)
        {
            try
            {
                if (serialPort1.IsOpen)
                {
                    serialPort1.Write("ST9G");
                    serialPort1.Close();
                }
                Bt_Stop.Enabled = false;
                Bt_Start.Enabled = true;
                progressBar1.Value = 0;
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }

        // -------------------------------------------------------------------------
        // Project Selection and UI Logic
        // -------------------------------------------------------------------------
        /// <summary>
        /// Handles the Generate button click: sets up the UI and sends project command.
        /// </summary>
        private void Bt_Generate_Click(object sender, EventArgs e)
        {
            if (combo_Project.Text == "Spring and Damper")
            {
                MainPanel.Visible = true;
                projectType = 1;
                Positive_Side.Visible = true;
                Negative_Side.Visible = false;
                Positive_Side.Location = new Point(445, 305);
                Circular_Background.Visible = false;
                grayball.Visible = true;
                grayball.BringToFront();
                Target.Visible = false;
                Moon.Visible = false;
                if (serialPort1.IsOpen)
                    serialPort1.Write("ST1G");
                else MessageBox.Show("Please Connect to Port First");
            }
            else if (combo_Project.Text == "Collision")
            {
                MainPanel.Visible = true;
                projectType = 2;
                Moon.Visible = true;
                Negative_Side.Visible = false;
                Positive_Side.Visible = false;
                Circular_Background.Visible = false;
                grayball.Visible = true;
                grayball.BringToFront();
                Target.Visible = false;
                if (serialPort1.IsOpen)
                    serialPort1.Write("ST2G");
                else MessageBox.Show("Please Connect to Port First");
            }
            else if (combo_Project.Text == "Rehabitation")
            {
                MainPanel.Visible = true;
                projectType = 3;
                Moon.Visible = false;
                Negative_Side.Visible = false;
                Circular_Background.Visible = true;
                grayball.Visible = true;
                grayball.BringToFront();
                Target.Visible = true;
                Target.BringToFront();
                if (serialPort1.IsOpen)
                    serialPort1.Write("ST3G");
                else MessageBox.Show("Please Connect to Port First");
            }
            else { MessageBox.Show("Please choose a Project"); }
        }

        // -------------------------------------------------------------------------
        // Form Closing and Serial Data Handling
        // -------------------------------------------------------------------------
        /// <summary>
        /// Ensures serial port is closed on form close.
        /// </summary>
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                serialPort1.Close();
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }

        /// <summary>
        /// Handles incoming serial data and invokes processing.
        /// </summary>
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            serialData = serialPort1.ReadLine();
            this.BeginInvoke(new EventHandler(ProcessData));
        }

        /// <summary>
        /// Processes received serial data and updates UI/state.
        /// </summary>
        private void ProcessData(object sender, EventArgs e)
        {
            try
            {
                indexOfA = Convert.ToSByte(serialData.IndexOf("A"));
                indexOfB = Convert.ToSByte(serialData.IndexOf("B"));
                indexOfC = Convert.ToSByte(serialData.IndexOf("C"));

                parsedX = serialData.Substring(0, indexOfA);
                parsedY = serialData.Substring(indexOfA + 1, (indexOfB - indexOfA) - 1);
                parsedM = serialData.Substring(indexOfB + 1, (indexOfC - indexOfB) - 1);
                // TODO: Update UI or state with parsed values
            }
            catch (Exception error)
            {
                MessageBox.Show("Data Parse Error: " + error.Message);
            }
        }

        // -------------------------------------------------------------------------
        // (Other event handlers and logic can be similarly documented and cleaned)
        // -------------------------------------------------------------------------
    }
}
