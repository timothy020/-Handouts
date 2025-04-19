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
    public partial class CSharpEditforIP : Form
    {
        public bool blnOKEnter = false;
        public string editIPstr ;
        public string editPortstr;

        public CSharpEditforIP()
        {
            InitializeComponent();
            textBox1.Text = "255.255.255.255";
            textBox2.Text = "9998";

        }

        private void button1_Click(object sender, EventArgs e)
        {
            blnOKEnter = true;
            editIPstr = textBox1.Text.ToString();
            editPortstr = textBox2.Text.ToString();

            this.Close();
        }
    }
}
