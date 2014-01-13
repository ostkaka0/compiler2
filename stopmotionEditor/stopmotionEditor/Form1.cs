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
using System.Threading;

namespace stopmotionEditor
{
    public partial class Form1 : Form
    {
        private int id = 1;

        public Form1()
        {
            InitializeComponent();
        }

        private string SaveDialog(string filter)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();

            // Set filter options and filter index.
            saveFileDialog1.Filter = filter;
            saveFileDialog1.FilterIndex = 1;

            // Call the ShowDialog method to show the dialog box.
            /*bool? userClickedOK*/
            DialogResult result = saveFileDialog1.ShowDialog();

            // Process input if the user clicked OK.
            if (result == DialogResult.OK)
            {
                return saveFileDialog1.FileName;
            }
            else return "";
        }

        private string LoadDialog(string filter)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            openFileDialog1.Filter = filter;
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;
            openFileDialog1.Multiselect = true;

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                return openFileDialog1.FileName;
            }
            else return "";
        }

        //btnLoad
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                OpenFileDialog openFileDialog1 = new OpenFileDialog();

                openFileDialog1.Filter = "jpg files (*.jpg)|*.jpg|All files (*.*)|*.*";
                openFileDialog1.FilterIndex = 2;
                openFileDialog1.RestoreDirectory = true;
                openFileDialog1.Multiselect = true;

                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    List<string> files = new List<string>(openFileDialog1.FileNames);

                    files.Sort();

                    foreach (String file in files)
                    {
                        listBox.Items.Add(new PictureItem(file, id++));
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            tsslbFrames.Text = "Frames: " + listBox.Items.Count.ToString();
            tsslbSeconds.Text = "Seconds: " + ((Decimal)listBox.Items.Count / (Decimal)12.0).ToString();

        }

        private void listBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox.SelectedItem != null)
            {
                try
                {
                    Bitmap bitmap = new Bitmap((listBox.SelectedItem as PictureItem).path);
                    bitmap.RotateFlip(RotateFlipType.RotateNoneFlipXY);
                    //bitmap.RotateFlip(RotateFlipType.Rotate180FlipNone);
                    pictureBox.Image = bitmap;
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex);
                }
            }
        }

        private void btnMoveUp_Click(object sender, EventArgs e)
        {
            if (listBox.SelectedItem != null && listBox.SelectedIndex > 0)
            {
                var temp = listBox.Items[listBox.SelectedIndex - 1];
                listBox.Items[listBox.SelectedIndex - 1] = listBox.Items[listBox.SelectedIndex];
                listBox.Items[listBox.SelectedIndex] = temp;
                listBox.SelectedIndex--;
            }
        }

        private void btnMoveDown_Click(object sender, EventArgs e)
        {
            if (listBox.SelectedItem != null && listBox.SelectedIndex < listBox.Items.Count - 1)
            {
                var temp = listBox.Items[listBox.SelectedIndex + 1];
                listBox.Items[listBox.SelectedIndex + 1] = listBox.Items[listBox.SelectedIndex];
                listBox.Items[listBox.SelectedIndex] = temp;
                listBox.SelectedIndex++;
            }
        }

        private void btnDuplicate_Click(object sender, EventArgs e)
        {
            if (listBox.SelectedItem != null)
            {
                listBox.Items.Insert(listBox.SelectedIndex + 1, listBox.SelectedItem);
                listBox.SelectedIndex++;

                tsslbFrames.Text = "Frames: " + listBox.Items.Count.ToString();
                tsslbSeconds.Text = "Seconds: " + ((Decimal)listBox.Items.Count / (Decimal)12.0).ToString();
            }
        }

        private void btnRemove_Click(object sender, EventArgs e)
        {
            if (listBox.SelectedItem != null)
            {
                int selectedIndex = listBox.SelectedIndex;

                listBox.Items.RemoveAt(listBox.SelectedIndex);

                if (listBox.Items.Count > selectedIndex)
                    listBox.SelectedIndex = selectedIndex;
                else if (listBox.Items.Count > 0)
                    listBox.SelectedIndex = selectedIndex - 1;

                tsslbFrames.Text = "Frames: " + listBox.Items.Count.ToString();
                tsslbSeconds.Text = "Seconds: " + ((Decimal)listBox.Items.Count / (Decimal)12.0).ToString();
            }
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            listBox.Items.Clear();
            id = 1;

            tsslbFrames.Text = "Frames: " + listBox.Items.Count.ToString();
            tsslbSeconds.Text = "Seconds: " + ((Decimal)listBox.Items.Count / (Decimal)12.0).ToString();
        }

        private void btnExport_Click(object sender, EventArgs e)
        {
            string path = SaveDialog("Avi Files (.avi)|*.avi");

            if (path != "")
            {                     
                new Thread(() =>
                {
                    AviManager aviManager = null;

                    try
                    {
                        Console.WriteLine(path);

                        //sourcePath = openFile();
                        //http://www.codeproject.com/Articles/7388/A-Simple-C-Wrapper-for-the-AviFile-Library

                        //myReadyNAS device, got files via FTP from my webcam
                        List<PictureItem> jpgFileList = new List<PictureItem>();
                        PictureItem[] tempArray = new PictureItem[listBox.Items.Count];
                        listBox.Items.CopyTo(tempArray, 0);
                        jpgFileList.AddRange(tempArray);

                        this.Invoke(new Action(() =>
                        {
                            this.toolStripProgressBar1.Maximum = jpgFileList.Count;
                            this.tableLayoutPanel1.Enabled = false;
                        }));

                        //load the first image
                        Bitmap bitmap = (Bitmap)Image.FromFile(jpgFileList.First().path);

                        bitmap.RotateFlip(RotateFlipType.RotateNoneFlipXY);

                        //create a new AVI file
                        aviManager = new AviManager(path, false);

                        //add a new video stream and one frame to the new file
                        //set IsCompressed = false

                        VideoStream aviStream = aviManager.AddVideoStream(true, 12, bitmap);

                        jpgFileList.Skip(1).ToList().ForEach(file =>
                        {
                            Console.WriteLine(file);
                            bitmap = new Bitmap(Bitmap.FromFile(file.path));
                            bitmap.RotateFlip(RotateFlipType.RotateNoneFlipXY);

                            aviStream.AddFrame(bitmap);
                            bitmap.Dispose();

                            this.Invoke(new Action(() =>
                            {
                                this.toolStripProgressBar1.Value++;
                            }));
                        });

                        aviManager.Close();

                        this.Invoke(new Action(() =>
                        {
                            this.toolStripProgressBar1.Value = 0;
                            this.tableLayoutPanel1.Enabled = true;
                        }));
                    }
                    catch (Exception ex)
                    {
                        if (aviManager != null)
                            aviManager.Close();

                        this.Invoke(new Action(() =>
                        {
                            this.toolStripProgressBar1.Value = 0;
                            this.tableLayoutPanel1.Enabled = true;
                            MessageBox.Show(ex.Message);
                        }));
                    }
                }).Start();
            }


        }

        private void btnLoadScene_Click(object sender, EventArgs e)
        {
            string path = LoadDialog("Stop Motion Scene files (*.sms)|*.sms|All files (*.*)|*.*");

            if (path != "")
            {
                try
                {
                    StreamReader reader = new StreamReader(path);

                    listBox.Items.Clear();
                    id = 1;

                    while (!reader.EndOfStream)
                    {
                        string data = reader.ReadLine();

                        if (data.First() == '%')
                            listBox.Items.Add(listBox.Items[int.Parse(data.Substring(1))]);
                        else
                            listBox.Items.Add(new PictureItem(data, id++));
                    }

                    reader.Close();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }

                tsslbFrames.Text = "Frames: " + listBox.Items.Count.ToString();
                tsslbSeconds.Text = "Seconds: " + ((Decimal)listBox.Items.Count / (Decimal)12.0).ToString();
            }
        }

        private void btnSaveScene_Click(object sender, EventArgs e)
        {
            string path = SaveDialog("Stop Motion Scene files (*.sms)|*.sms|All files (*.*)|*.*");

            if (path != "")
            {
                try
                {
                    StreamWriter writer = new StreamWriter(path);
                    Dictionary<int, int> items = new Dictionary<int, int>();

                    foreach (var item in listBox.Items)
                    {
                        if (items.ContainsKey((item as PictureItem).pictureId))
                        {
                            writer.WriteLine("%" + items[(item as PictureItem).pictureId].ToString());
                        }
                        else
                        {
                            writer.WriteLine((item as PictureItem).path);
                        }
                    }

                    writer.Close();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }
    }
}
