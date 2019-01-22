using System;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace wcvlib
{

    /// <summary>
    /// Объект просмоторщика буфера обмена Windows
    /// </summary>
    public class ClipboardViewer
    {
        public delegate ClipboardViewer ini();
        public delegate void ClipboardViewerEnabled();

        public ClipboardViewer()
        {
            _clipboardViewerForm = null;
        }

       

        private class ClipboardViewerForm : System.Windows.Forms.Form
        {
            //
            // Основные объявления pinvoke
            //
            [DllImport("user32.dll")]
            public static extern IntPtr SetClipboardViewer(IntPtr _nextClipboardViewerHandle);

            [DllImport("user32.dll")]
            public static extern IntPtr GetClipboardViewer();

            [DllImport("user32.dll")]
            [return: MarshalAs(UnmanagedType.Bool)]
            public static extern bool ChangeClipboardChain(IntPtr hWndRemove, IntPtr _nextClipboardViewerHandle);

            [DllImport("user32.dll", SetLastError = true)]
            public static extern int SendMessage(IntPtr hWnd, int Msg, IntPtr wParam, IntPtr lParam);
            //
            // Константы
            //
            private const int wm_create = 0x0001;
            private const int wm_destroy = 0x0002;
            private const int wm_changeclipboardchain = 0x030D;
            private const int wm_drawclipboard = 0x0308;

            public ClipboardViewerForm()
            {
            }

            //
            // Overrides
            //
            protected override void WndProc(ref Message m)
            {
                base.WndProc(ref m);
            }
        }
        private static bool _isEnabled;
        private ClipboardViewerForm _clipboardViewerForm;
        public static event ClipboardViewerEnabled ClipboardViewerEnable;
        public static event ClipboardViewerEnabled ClipboardViewerDisable;
        protected static void OnClipboardViewerEnabled()
        {
            _isEnabled = true;
        }
        protected static void OnClipboardViewerDisabled()
        {
            _isEnabled = false;
        }
        //
        // Инициализация
        //
        public ClipboardViewer Init()
        {
            _clipboardViewerForm = new ClipboardViewerForm
            {
                Visible = true
            };
            _clipboardViewerForm.CreateControl();
            Debug.Assert(_clipboardViewerForm.Handle != IntPtr.Zero);
            if (_clipboardViewerForm.Handle != IntPtr.Zero)
            {
                OnClipboardViewerEnabled();
                return this;
            }
            else
            {
                return null;
            }
        }
        // TODO: переобдумать
        public Task<bool> InitAsync()
        {
            _clipboardViewerForm = new ClipboardViewerForm
            {
                Visible = true
            };
            _clipboardViewerForm.CreateControl();
            if (_clipboardViewerForm.Handle != IntPtr.Zero)
            {
                OnClipboardViewerEnabled();
                return Task.FromResult<bool>(true);
            }
            else
            {
                return null;
            }
        }
        public static bool IsEnabled { get => _isEnabled; private set => _isEnabled = value; }
    }
    public interface IClipboardDataObject<T>
    {

    }


}


