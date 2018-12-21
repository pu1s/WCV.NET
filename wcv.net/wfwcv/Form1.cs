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
            this.Shown += Form1_Shown;
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            this.Text = button1.Handle.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //wcvlib.UniHandle uh;
            f = new ClipboardViewerForm();
            this.Text = f.Handle.ToString();
            IntPtr h = IntPtr.Zero;
            wcvlib.UniHandle uniHandle = new UniHandle(ref h);
            f.Show();
            var hh = Handle;
            //uniHandle = uniHandle.Create(ref hh);
           
            button1.Text = uniHandle.ToString();
        }

        private void F_Shown(object sender, EventArgs e)
        {
            
        }
    }
}
