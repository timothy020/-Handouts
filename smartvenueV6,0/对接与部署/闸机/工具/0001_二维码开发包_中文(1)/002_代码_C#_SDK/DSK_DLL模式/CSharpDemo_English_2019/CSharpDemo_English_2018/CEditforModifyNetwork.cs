using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CSharpDemo
{
    public partial class CEditforModifyNetwork : Form
    {
        public bool blnOKEnter = false;

        public string   editPortstr;
        public string   editMACstr;
        public string OldeditMACstr;
        public string[] arrayIP   = new string[4];
        public string[] arrayMask = new string[4];
        public string[] arrayGate = new string[4];
        public string[] arrayMAC  = new string[6];
        public string[] arrayOldMAC = new string[6];

        public CEditforModifyNetwork(string DeviceIP, string DevicePort, string DeviceMask, string DeviceGate, string DeviceMAC)
        {
            InitializeComponent();
            //textBox1.Text = "255.255.255.255";
            // textBox2.Text = "9998";
            txtOldIP.Text = DeviceIP;
            txtOldPort.Text = DevicePort;
            txtOldMask.Text = DeviceMask;
            txtOldGate.Text = DeviceGate;
            txtOldMAC.Text = DeviceMAC;

            txtNewIP.Text = DeviceIP;
            txtNewPort.Text = DevicePort;
            txtNewMask.Text = DeviceMask;
            txtNewGate.Text = DeviceGate;
            txtNewMAC.Text = DeviceMAC;

        }

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            blnOKEnter = true;
            arrayIP   = this.txtNewIP.Text.Trim().Split('.');
            arrayMask = this.txtNewMask.Text.Trim().Split('.');
            arrayGate = this.txtNewGate.Text.Trim().Split('.');
            if (arrayIP.Length != 4)
            {
                MessageBox.Show("IP is error");
                return;
            }
            if (arrayMask.Length != 4)
            {
                MessageBox.Show("Mask is error");
                return;
            }
            if (arrayGate.Length != 4)
            {
                MessageBox.Show("Gate is error");
                return;
            }
            editPortstr = this.txtNewPort.Text.Trim();
            editMACstr  = this.txtNewMAC.Text.Trim();
            if (editMACstr.Length != 12)
            {
                MessageBox.Show("MAC is error");
                return;
            }
            for (int kk = 0; kk < 6; kk++)
            {
                arrayMAC[kk] = editMACstr.Substring(kk * 2, 2);
             }

            OldeditMACstr = this.txtOldMAC.Text.Trim();
            if (OldeditMACstr.Length != 12)
            {
                MessageBox.Show("Old MAC is error");
                return;
            }
            for (int kk = 0; kk < 6; kk++)
            {
                arrayOldMAC[kk] = OldeditMACstr.Substring(kk * 2, 2);
            }
            this.Close();

        }
    }
}
