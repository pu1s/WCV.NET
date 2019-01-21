using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using wcvlib;

namespace wpfcv
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();
            ClipboardViewerForm.ClipboardViewerCreated += ClipboardViewer_ClipboardViewerCreated;
            clipboardViewer = new ClipboardViewerForm();
           
        }

        private void ClipboardViewer_ClipboardViewerCreated(object sender, EventArgs e)
        {
            btn1.Content = "CV Created";
        }

        private ClipboardViewerForm clipboardViewer;
        private void Button_Click(object sender, RoutedEventArgs e)
        {

            btn1.Content = clipboardViewer.Handle.ToString();
            btn1.Content += ":";
            btn1.Content += clipboardViewer.NextClipboardViewerHandle.ToString();
        }
    }
}
