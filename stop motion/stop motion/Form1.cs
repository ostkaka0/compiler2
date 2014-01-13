using AviFile;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace stop_motion
{
    public partial class Form1 : Form
    {
        string sourcePath = "bored";
        bool running = false;
        int readFiles = 0;
        int totalFiles = 0;

        Random random = new Random();

        delegate void d_();

        public Form1()
        {
            InitializeComponent();
        }

        private string openFile()
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            // Set filter options and filter index.
            openFileDialog1.Filter = "Png Files (.jpg)|*.jpg";
            openFileDialog1.FilterIndex = 1;

            openFileDialog1.Multiselect = false;

            // Call the ShowDialog method to show the dialog box.
            /*bool? userClickedOK*/
            DialogResult result = openFileDialog1.ShowDialog();

            // Process input if the user clicked OK.
            if (result == DialogResult.OK)
            {
                // Open the selected file to read.
                return Path.GetDirectoryName(openFileDialog1.FileName);
            }

            return "";
        }

        private void UpdateProgressBar()
        {
            progressBar1.Maximum = totalFiles;
            progressBar1.Value = readFiles;
        }

        private void btnGenerate_Click(object sender, EventArgs e)
        {
            if (sourcePath == "")
                return;

            string[] paths = Directory.GetDirectories(Directory.GetParent(sourcePath).FullName);

            totalFiles = paths.Length;
            readFiles = 0;

            foreach (string path in paths)
            {
                if (path.Split('\\').Last().StartsWith("scene"))
                {
                    running = true;
                    //new System.Threading.Tasks.Task(()=>//System.Threading.Tasks.Task(() =>
                    //{
                    generateVideo(path);
                    //}).Start();
                    readFiles++;
                    UpdateProgressBar();
                }
                else
                {
                    totalFiles--;
                }
            }
        }

        private void generateVideo(string path)
        {
            //try
            {
                Console.WriteLine(path);
                //sourcePath = openFile();
                //http://www.codeproject.com/Articles/7388/A-Simple-C-Wrapper-for-the-AviFile-Library

                //myReadyNAS device, got files via FTP from my webcam
                var jpgFileList = Directory.EnumerateFiles(path, "*.jpg");

                //load the first image
                Bitmap bitmap = (Bitmap)Image.FromFile(jpgFileList.First());

                Size size = new Size(1280, 720);

                if (cbFlipX.Checked && cbFlipY.Checked)
                    bitmap.RotateFlip(RotateFlipType.Rotate180FlipXY);
                else if (cbFlipX.Checked)
                    bitmap.RotateFlip(RotateFlipType.Rotate180FlipX);
                else if (cbFlipY.Checked)
                    bitmap.RotateFlip(RotateFlipType.Rotate180FlipY);

                //create a new AVI file
                AviManager aviManager = new AviManager(Environment.CurrentDirectory + "\\scenes\\" + path.Split('\\').Last().Replace(",", "").Replace(".","") + ".avi", false);

                //add a new video stream and one frame to the new file
                //set IsCompressed = false

                VideoStream aviStream = aviManager.AddVideoStream(true, 12, new Bitmap(bitmap, size));

                

                /*this.Invoke(new d_(()=>
                {
                    this.totalFiles += jpgFileList.Count();
                    this.readFiles++;
                    this.UpdateProgressBar();
                }));*/

                jpgFileList.Skip(1).ToList().ForEach(file =>
                {
                    Console.WriteLine(file);
                    bitmap = new Bitmap(Bitmap.FromFile(file), size);

                    if (cbFlipX.Checked && cbFlipY.Checked)
                        bitmap.RotateFlip(RotateFlipType.Rotate180FlipXY);
                    else if (cbFlipX.Checked)
                        bitmap.RotateFlip(RotateFlipType.Rotate180FlipX);
                    else if (cbFlipY.Checked)
                        bitmap.RotateFlip(RotateFlipType.Rotate180FlipY);

                    aviStream.AddFrame(bitmap);
                    bitmap.Dispose();

                });

                aviManager.Close();
            }
            //catch (System.Exception exception)
            {
              //  MessageBox.Show(exception.Message);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            sourcePath = openFile();
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            generateVideo(sourcePath);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string[] paths = Directory.GetDirectories(Directory.GetParent(sourcePath).FullName);

            Size size = new Size(1280, 720);

            foreach (string path in paths)
            {
                if (path.Split('\\').Last().StartsWith("scene"))
                {
                    string[] files = Directory.GetFiles(path);

                    Directory.CreateDirectory(Directory.GetParent(path).FullName + "\\720p format\\" + path.Split('\\').Last());

                    Console.WriteLine(path);

                    foreach (string file in files)
                    {
                        Console.Write(".");

                        if (file.EndsWith(".jpg"))
                        {
                            Image image = Image.FromFile(file);
                            image.RotateFlip(RotateFlipType.Rotate180FlipXY);
                            Bitmap bitmap = new Bitmap(image, size);

                            //bitmap.RotateFlip(RotateFlipType.Rotate180FlipXY);

                            bitmap.Save(Directory.GetParent(path).FullName + "\\720p format\\" + path.Split('\\').Last() + "\\" + file.Split('\\').Last());

                            image.Dispose();
                            bitmap.Dispose();
                        }
                    }
                    Console.WriteLine();
                }
            }
        }
    }
}
