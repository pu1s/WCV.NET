﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using libwcv;


namespace wcv
{
    public partial class Form1 : Form
    {
        private libwcv.ClipboardViewer cv;
        public Form1()
        {
            InitializeComponent();
            cv = new ClipboardViewer();
            cv.ClipboardViewerCreated += Cv_ClipboardViewerCreated;
        }

        private void Cv_ClipboardViewerCreated(object sender, EventArgs e)
        {
           
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void button1_Click(object sender, EventArgs e)
        {

            cv.ShowViewer();
            richTextBox1.Text = cv.ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            button2.Text = "Hide";
            cv.HideViewer();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            
        }
    }
}
