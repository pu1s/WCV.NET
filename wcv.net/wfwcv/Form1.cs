using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using wcvlib;

namespace wfwcv
{
    public partial class Form1 : Form
    {
        public wcvlib.ClipboardViewerForm f;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            f = new ClipboardViewerForm();
            f.Show();
        }
    }
}
