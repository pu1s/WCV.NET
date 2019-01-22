﻿using System;
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
        private ClipboardViewer clipboardViewer = null;
        public  MainWindow()
        {
            InitializeComponent();
            //ClipboardViewerForm.ClipboardViewerCreated += ClipboardViewer_ClipboardViewerCreated;
            clipboardViewer = new ClipboardViewer();
           
           
        }

        //private void ClipboardViewer_ClipboardViewerCreated(object sender, EventArgs e)
        //{
        //    btn1.Content = "CV Created";
        //}

        //private ClipboardViewerForm clipboardViewer;
        private async void Button_Click(object sender, RoutedEventArgs e)
        {
            if (await clipboardViewer.InitAsync()) ;
            //btn1.Content = clipboardViewer.Handle.ToString();
            //btn1.Content += ":";
            //btn1.Content += clipboardViewer.NextClipboardViewerHandle.ToString();
        }
    }
}
