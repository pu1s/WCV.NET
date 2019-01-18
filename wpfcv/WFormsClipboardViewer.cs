using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace wpfcv
{
    

    public class WFormsClipboardViewer : System.Windows.Forms.Form
    {
        [DllImport("user32.dll")]
        public static extern IntPtr SetClipboardViewer(IntPtr _nextClipboardViewerHandle);

        [DllImport("user32.dll")]
        public static extern IntPtr GetClipboardViewer();

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool ChangeClipboardChain(IntPtr hWndRemove, IntPtr _nextClipboardViewerHandle);

        [DllImport("user32.dll", SetLastError = true)]
        public static extern int SendMessage(IntPtr hWnd, int Msg, IntPtr wParam, IntPtr lParam);

        private const int wm_create = 0x0001;
        private const int wm_destroy = 0x0002;
        private const int wm_changechain = 0x030D;

        public WFormsClipboardViewer()
        {

        }
        private IntPtr _clipboardViewerHandle;
        private IntPtr _nextClipboardViewerHandle;

        public IntPtr ClipboardViewerHandle { get => _clipboardViewerHandle; private set => _clipboardViewerHandle = value; }
        public IntPtr NextClipboardViewerHandle { get => _nextClipboardViewerHandle; private set => _nextClipboardViewerHandle = value; }

        public override string ToString()
        {
            return IntPtr.Zero == _clipboardViewerHandle ? "ClipboardViewerObject: " + _clipboardViewerHandle.ToString() : "ClipboardViewerObject: NULL";
        }
        protected override void DefWndProc(ref Message m)
        {
            base.DefWndProc(ref m);
        }
    }
}
