using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace СontourSelection
{
    public partial class Form1 : Form
    {

        List<Point> contour;
        Pen pen;
        Point p1;

        public Form1()
        {
            InitializeComponent();
            Image image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            Graphics g = Graphics.FromImage(image);
            g.Clear(Color.AntiqueWhite);
            g.Dispose();
            pictureBox1.Image = image;
            pen = new Pen(Color.Black, 3);
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            p1 = e.Location;
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {

            if (e.Button == MouseButtons.Left)
            {
                Graphics g = Graphics.FromImage(pictureBox1.Image);
                g.DrawLine(pen, p1, e.Location);
                g.Dispose();
                p1 = e.Location;
                pictureBox1.Invalidate();

            }
        }
    }
}
