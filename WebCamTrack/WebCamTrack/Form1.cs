using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

// BLIBLIOTECAS DO PROJETO
using AForge;
using AForge.Video.DirectShow;
using AForge.Video;
using AForge.Imaging.Filters;
using AForge.Imaging;
using System.Threading;



namespace WebCamTrack
{
    public partial class Form1 : Form
    {
        private FilterInfoCollection VideoCaptureDevices;
        private VideoCaptureDevice FinalVideo;
        private VideoCaptureDevice FinalVideo2;
        int count = 0;
        public Form1()
        {
            InitializeComponent();
            VideoCaptureDevices = new FilterInfoCollection(FilterCategory.VideoInputDevice);
            foreach (FilterInfo VideoCaptureDevice in VideoCaptureDevices)
            {
                comboBox1.Items.Add(VideoCaptureDevice.Name);
            }
            comboBox1.SelectedIndex = 0;

        }

        private void button1_Click(object sender, EventArgs e)
        {
            FinalVideo = new VideoCaptureDevice(VideoCaptureDevices[comboBox1.SelectedIndex].MonikerString);
            FinalVideo.NewFrame += new NewFrameEventHandler(FinalVideo_NewFrame);
            FinalVideo.Start();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            FinalVideo2 = new VideoCaptureDevice(VideoCaptureDevices[comboBox1.SelectedIndex].MonikerString);
            FinalVideo2.NewFrame += new NewFrameEventHandler(FinalVideo_NewFrame2);
            FinalVideo2.Start();
            //   FinalVideo.Stop();
        }

        void FinalVideo_NewFrame(object sender, NewFrameEventArgs eventArgs)
        {
            Icon newIcon = new Icon(@"c:\users\gregster\documents\visual studio 2012\Projects\WebCamTrack\WebCamTrack\bin\Debug\favicon.ico");
            BlobCounter bc = new BlobCounter();
            EuclideanColorFiltering filter = new EuclideanColorFiltering();
            Bitmap video = (Bitmap)eventArgs.Frame.Clone();//sem filtro
            Bitmap video1 = (Bitmap)eventArgs.Frame.Clone();// imagem com filtro
            //
            filter.CenterColor = new RGB(0, 0, 0);
            filter.Radius = 100;
            filter.ApplyInPlace(video1);//aplicando o filtro
            bc.MinWidth = 5;
            bc.MinHeight = 5;
            bc.FilterBlobs = true;
            //  bc.ObjectsOrder = ObjectsOrder.Size;
            bc.ProcessImage(video1);// processando a imagem que ja foi filtrada para identificar objetos
            Rectangle[] rects = bc.GetObjectsRectangles();
            foreach (Rectangle recs in rects)
                if (rects.Length > 0)
                {
                    Rectangle objectRect = rects[0];
                    Graphics g = Graphics.FromImage(video);//identificar objetos a partir da imagem com filtro
                    Graphics h = Graphics.FromImage(video1);
                    using (Pen pen = new Pen(Color.FromArgb(160, 255, 160), 5))
                    {
                        g.DrawIcon(newIcon, objectRect);
                       // g.DrawRectangle(pen, objectRect);
                        h.DrawRectangle(pen, objectRect);
                    }
                    g.Dispose();
                    h.Dispose();
                }
            pictureBox1.Image = video;
            pictureBox2.Image = video1;
        }


        void FinalVideo_NewFrame2(object sender, NewFrameEventArgs eventArgs)
        {

            Icon newIcon = new Icon(@"c:\users\gregster\documents\visual studio 2012\Projects\WebCamTrack\WebCamTrack\bin\Debug\Aqua-Ball-Red-icon.ico");
            BlobCounter bc = new BlobCounter();
            EuclideanColorFiltering filter = new EuclideanColorFiltering();
            Bitmap video = (Bitmap)eventArgs.Frame.Clone();//sem filtro
            Bitmap video1 = (Bitmap)eventArgs.Frame.Clone();// imagem com filtro
            //
            filter.CenterColor = new RGB(10, 10, 10);
            filter.Radius = 20;
            filter.ApplyInPlace(video1);//aplicando o filtro
            bc.MinWidth = 12;
            bc.MinHeight = 12;
            bc.FilterBlobs = true;
            //  bc.ObjectsOrder = ObjectsOrder.Size;
            bc.ProcessImage(video1);// processando a imagem que ja foi filtrada para identificar objetos
            Rectangle[] rects = bc.GetObjectsRectangles();
            foreach (Rectangle recs in rects)
                if (rects.Length > 0)
                {

                    foreach (Rectangle objectRect in rects)
                    {

                        Graphics g = Graphics.FromImage(video);//Desenhar quadrado em frente da imagem
                        Graphics i = Graphics.FromImage(video);
                        Graphics h = Graphics.FromImage(video1);
                        if (objectRect.Width < 50 && objectRect.Height < 50)
                        {
                            count = count + 1;
                        }
                    
                        using (Pen pen = new Pen(Color.FromArgb(160, 255, 160), 5))
                        {
                            g.DrawIcon(newIcon, objectRect); 
                            h.DrawRectangle(pen, objectRect);
                            
                        }
                        string strNumber = Convert.ToString(count);
                        // Create font and brush.
                        Font drawFont = new Font("Arial", 16);
                        SolidBrush drawBrush = new SolidBrush(Color.Black);
                        // Create point for upper-left corner of drawing.
                        PointF drawPoint = new PointF(150.0F, 150.0F);
                        // Draw string to screen.
                        i.DrawString(strNumber, drawFont, drawBrush, drawPoint);

                        i.Dispose();
                        g.Dispose();
                        h.Dispose();
                    }  
                }      
            pictureBox1.Image = video;
            pictureBox2.Image = video1;
        }


    }
}
