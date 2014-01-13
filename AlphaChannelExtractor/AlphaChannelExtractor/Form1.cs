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

namespace AlphaChannelExtractor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private Bitmap Generate(string background, string foreground, string mixed)
        {
            Bitmap bg = new Bitmap(background);
            Bitmap fg = new Bitmap(foreground);
            Bitmap m = new Bitmap(mixed);

            Bitmap result = new Bitmap(m.Width, m.Height);

            for (int x = 0; x < m.Width; x++)
            {
                for (int y = 0; y < m.Height; y++)
                {
                    Color bgPixel = bg.GetPixel(x, y);
                    Color fgPixel = fg.GetPixel(x, y);
                    Color mPixel = m.GetPixel(x, y);

                    result.SetPixel(x, y, SolveColor(bgPixel, fgPixel, mPixel));
                }
            }

            return result;
        }

        private Color SolveColor(Color bgPixel, Color fgPixel, Color mPixel)
        {
            
                double dColor =
                    Math.Max(Math.Max(
                    Math.Abs(mPixel.R * mPixel.A - bgPixel.R * bgPixel.A),
                    Math.Abs(mPixel.G * mPixel.A - bgPixel.G * bgPixel.A)),
                    Math.Abs(mPixel.B * mPixel.A - bgPixel.B * bgPixel.A));

                double dMax =
                    Math.Max(Math.Max(
                    Math.Abs(fgPixel.R * fgPixel.A - bgPixel.R * bgPixel.A),
                    Math.Abs(fgPixel.G * fgPixel.A - bgPixel.G * bgPixel.A)),
                    Math.Abs(fgPixel.B * fgPixel.A - bgPixel.B * bgPixel.A));


                if (dMax == 0)
                    return Color.FromArgb(0, bgPixel);

                double opacity = dColor / dMax;

                if (opacity*255 < 256)
                    return Color.FromArgb((int)(opacity * 255), fgPixel);
                else
                    return Color.FromArgb(255, fgPixel);
        }

        private string openFile()
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            // Set filter options and filter index.
            openFileDialog1.Filter = "Png Files (.png)|*.png";
            openFileDialog1.FilterIndex = 1;

            openFileDialog1.Multiselect = false;

            // Call the ShowDialog method to show the dialog box.
            /*bool? userClickedOK*/
            DialogResult result = openFileDialog1.ShowDialog();

            // Process input if the user clicked OK.
            if (result == DialogResult.OK)
            {
                // Open the selected file to read.
                return openFileDialog1.FileName;
            }

            return "";
        }

        private void btnForeground_Click(object sender, EventArgs e)
        {
            string path = openFile();
            if (path != "")
                tbForeground.Text = path;
        }

        private void btnBackground_Click(object sender, EventArgs e)
        {
            string path = openFile();
            if (path != "")
                tbBackground.Text = path;
        }

        private void btnMixed_Click(object sender, EventArgs e)
        {
            string path = openFile();
            if (path != "")
                tbMixed.Text = path;
        }


        private void btnResult_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();

            // Set filter options and filter index.
            saveFileDialog1.Filter = "Png Files (.png)|*.png";
            saveFileDialog1.FilterIndex = 1;

            // Call the ShowDialog method to show the dialog box.
            /*bool? userClickedOK*/
            DialogResult result = saveFileDialog1.ShowDialog();

            // Process input if the user clicked OK.
            if (result == DialogResult.OK)
            {
                // Open the selected file to read.
                Bitmap bitmap = Generate(tbBackground.Text, tbForeground.Text, tbMixed.Text);

                //System.IO.Stream stream = saveFileDialog1.OpenFile();

                bitmap.Save(saveFileDialog1.FileName);
            }
        }

    }
}
