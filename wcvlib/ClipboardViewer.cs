using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace wcvlib
{
    public class ClipboardViewerForm : System.Windows.Forms.Form
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

		private const int wm_create                 = 0x0001;
		private const int wm_destroy                = 0x0002;
		private const int wm_changeclipboardchain   = 0x030D;
		private const int wm_drawclipboard          = 0x0308;

        public ClipboardViewerForm()
        {
            this.Visible = true;
        }
        private IntPtr _clipboardViewerHandle;
        private IntPtr _nextClipboardViewerHandle;

        public IntPtr ClipboardViewerHandle { get => _clipboardViewerHandle; private set => _clipboardViewerHandle = value; }
        public IntPtr NextClipboardViewerHandle { get => _nextClipboardViewerHandle; private set => _nextClipboardViewerHandle = value; }

        public override string ToString()
        {
            return IntPtr.Zero != _clipboardViewerHandle ? "ClipboardViewerObject: " + _clipboardViewerHandle.ToString() : "ClipboardViewerObject: NULL";
        }
        protected override void WndProc(ref Message m)
        {
            switch (m.Msg)
            {
                case wm_create:
                    _nextClipboardViewerHandle = SetClipboardViewer(this.Handle);
                    OnClipboardViewerCreated();
                    break;
                case wm_changeclipboardchain:
                    if(m.WParam == _nextClipboardViewerHandle)
                    {
                        _nextClipboardViewerHandle = m.LParam;
                    }
                    else if(_nextClipboardViewerHandle != IntPtr.Zero)
                    {
                        SendMessage(_nextClipboardViewerHandle, m.Msg, m.WParam, m.LParam);
                    }
                    break;
                case wm_drawclipboard:
                    //TODO -> entry point
                    if(_nextClipboardViewerHandle != IntPtr.Zero)
                    SendMessage(_nextClipboardViewerHandle, m.Msg, m.WParam, m.LParam);
                    break;
                case wm_destroy:
                    break;
            }
            base.WndProc(ref m);
        }

        static public event EventHandler ClipboardViewerCreated;
        protected void OnClipboardViewerCreated()
        {
            ClipboardViewerCreated?.Invoke(this, new EventArgs());
        }
    }

    
    public class ClipboardViewer
    {
        private ClipboardViewerForm viewerForm;

        public ClipboardViewerForm ViewerForm { get => viewerForm; private set => viewerForm = value; }
        public string ViewerFormCaption { get; }

        public ClipboardViewer(string viewerFormCaption_)
        {
            ViewerFormCaption = viewerFormCaption_;
        }
    }
}
