using System.Windows;
using wcvlib;

namespace wpfwcv
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public wcvlib.ClipboardViewerForm f;
        //public wcvlib.ClipboardViewerForm f1;
        //public wcvlib.ClipboardViewerForm f2;
        //public wcvlib.ClipboardViewerForm f3;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            f = new ClipboardViewerForm();
            f.Show();
            //f1 = new ClipboardViewerForm();f1.Show();

            //f2 = new ClipboardViewerForm(); f2.Show();

            //f3 = new ClipboardViewerForm(); f3.Show();

        }
    }
}
