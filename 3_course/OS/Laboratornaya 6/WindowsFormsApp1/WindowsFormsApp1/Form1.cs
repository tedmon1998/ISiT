using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        int result;
        public Form1()
        {
            InitializeComponent();
        }

        private void Generate()
        {
            Random random = new Random();
            result = random.Next(0, 9);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Thread thread1 = new Thread(Generate);
            thread1.Start();
            textBox5.Text = result.ToString();
            Thread thread2 = new Thread(Generate);
            thread2.Start();
            textBox7.Text = result.ToString();
            Thread thread3 = new Thread(Generate);
            thread3.Start();
            textBox8.Text = result.ToString();

            if (textBox5.Text == textBox7.Text && textBox5.Text == textBox8.Text)
                textBox1.Text = "Все три числа равны";
            else if (textBox5.Text == textBox7.Text || textBox5.Text == textBox8.Text || textBox7.Text == textBox8.Text)
                textBox1.Text = "Два числа одинаковых";
            else if (Convert.ToInt32(textBox5.Text) == 1 && Convert.ToInt32(textBox7.Text) == 1 && Convert.ToInt32(textBox8.Text) == 1)
                textBox1.Text = "Три единицы";
            else if (Convert.ToInt32(textBox5.Text) == 7 && Convert.ToInt32(textBox7.Text) == 7 && Convert.ToInt32(textBox8.Text) == 7)
                textBox1.Text = "Три семерки";
            else if ((Convert.ToInt32(textBox5.Text) == 1 && Convert.ToInt32(textBox7.Text) == 1) ||
                (Convert.ToInt32(textBox5.Text) == 1 && Convert.ToInt32(textBox8.Text) == 1) ||
                (Convert.ToInt32(textBox7.Text) == 1 && Convert.ToInt32(textBox8.Text) == 1))
                textBox1.Text = "Две единицы";
            else if (Convert.ToInt32(textBox5.Text) == 4 || Convert.ToInt32(textBox7.Text) == 4 || Convert.ToInt32(textBox8.Text) == 4)
                textBox1.Text = "Имеется четверка";
            else
                textBox1.Text = "";
        }
    }
}
