using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace СontourSelection
{
    public partial class Form1 : Form
    {
        Pen pen;
        Point p1;
        bool mode;

        public Form1()
        {
            InitializeComponent();
            mode = true;
            Image image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            Graphics g = Graphics.FromImage(image);
            g.Clear(Color.AntiqueWhite);
            g.Dispose();
            pictureBox1.Image = image;
            pen = new Pen(Color.Black, 4);
            pen.StartCap = LineCap.Round;
            pen.EndCap = LineCap.Round;
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            p1 = e.Location;
            if(!mode)
            {
                button2.Enabled = true;
            }
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (mode)
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

        private void button1_Click(object sender, EventArgs e)
        {
            if (mode)
                button1.Text = "Draw";
            else
            {
                button1.Text = "Select";
                button2.Enabled = false;
            }

            mode = !mode;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            mode = true;
            button1.Text = "Select";
            button2.Enabled = false;
            Image image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            Graphics g = Graphics.FromImage(image);
            g.Clear(Color.AntiqueWhite);
            g.Dispose();
            pictureBox1.Image = image;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Bitmap img = new Bitmap(pictureBox1.Image);
            var countur = Contour(p1.X, p1.Y, img.GetPixel(p1.X, p1.Y));

            Graphics g = Graphics.FromImage(pictureBox1.Image);
            SolidBrush s = new SolidBrush(Color.Red);

            for (int i = 0; i < countur.Count; ++i)
                g.FillRectangle(s, countur[i].X, countur[i].Y, 1, 1);

            s.Dispose();
            pictureBox1.Invalidate();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();

            sfd.Filter = "Пикчи (*.jpg, *.png) | *.jpg, *.png |Все (*.*) | *.*";
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                string s = sfd.FileName;
                pictureBox1.Image.Save(s);
            }
        }


        private List<int> Direction(int x, int y, int dir)
        {
            int x1 = x;
            int y1 = y;
            List<int> res = new List<int> { 0, 0 };
            switch (dir)
            {
                case 0:
                    x1--;
                    break;
                case 1:
                    x1--;
                    y1++;
                    break;
                case 2:
                    y1++;
                    break;
                case 3:
                    x1++;
                    y1++;
                    break;
                case 4:
                    x1++;
                    break;
                case 5:
                    x1++;
                    y1--;
                    break;
                case 6:
                    y1--;
                    break;
                case 7:
                    x1--;
                    y1--;
                    break;
            }
            res[0] = x1;
            res[1] = y1;
            return res;
        }

        private int text_dir(int dir)
        {
            return (dir + 1) % 8;
        }

        private List<Point> Contour(int x, int y, Color color)
        {
            Bitmap img = pictureBox1.Image as Bitmap;
            while (color == img.GetPixel(x, y))
                x+= 1;
            List<Point> countour = new List<Point>();
            Point p = new Point(x, y);
            countour.Add(p);

            int dir1 = 2;
            Point pp;
            while(true)
            {
                int dir2 = Math.Abs((dir1 + 6) % 8);
                while (color == img.GetPixel(Direction(x, y, dir2)[0], Direction(x, y, dir2)[1]))
                    dir2 = text_dir(dir2);

                x = Direction(x, y, dir2)[0];
                y = Direction(x, y, dir2)[1];

                pp = new Point(x, y);
                countour.Add(pp);

                dir1 = dir2;
                if (pp == p)
                    break;
            }
            return countour;
        }


    }
}
