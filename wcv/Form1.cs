using System;
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
        private CBWrapper testclass;
        public Form1()
        {
            InitializeComponent();
            this.testclass = new CBWrapper();
        }

        
        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            testclass.Create();
            //libwcv.ClipboardViewer cv = new ClipboardViewer();
            ////cv.ShowViewer();
            //button1.Text = cv.ToString();
            //this.Text = cv.ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            testclass.Destroy();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            testclass.GetData();
        }
    }
}
