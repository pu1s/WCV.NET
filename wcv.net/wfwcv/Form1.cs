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
using stdcli;

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
            //wcvlib.UniHandle uh;
            f = new ClipboardViewerForm();
            IntPtr h = IntPtr.Zero;
            stdcli.UniHandle uniHandle = new stdcli.UniHandle(ref h);
            f.Show();
            var hh = Handle;
            //uniHandle = uniHandle.Create(ref hh);
           
            button1.Text = uniHandle.ToString();
        }
    }
}
