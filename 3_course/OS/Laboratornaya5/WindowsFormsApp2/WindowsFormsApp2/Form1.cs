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

namespace WindowsFormsApp2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private bool Test()
        {
            if (textBox1.Text == "")
            {
                MessageBox.Show("Введите имя каталога или файла");
                return false;
            }
            else if (textBox2.Text == "")
            {
                MessageBox.Show("Введите место расположения");
                return false;
            }
            else return true;
        }


        private void Search()
        {
            try
            {
                if (!Directory.Exists(Path.GetDirectoryName(textBox2.Text)))
                {
                    MessageBox.Show("Такого пути не существует");
                }
                else
                {
                    // конкретный поиск Directory.GetFileSystemEntries(textBox2.Text, textBox1.Text, SearchOption.AllDirectories);
                    string[] dirArr = Directory.GetFileSystemEntries(textBox2.Text);
                    foreach (string item in dirArr)
                    {
                        listBox1.Items.Add(Path.GetFileName(item));
                    }
                }
            }
            catch(AccessViolationException)
            {
                MessageBox.Show("Попытка получить доступ к системным папкам или файлам");
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (Test())
            {
                Search();
            }    
        }
    }
}
