using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        string path = "C:";
        public Form1()
        {
            InitializeComponent();
            DirectoryInfo dir = new DirectoryInfo(path+@"\");
            /*listBox1.Items.Add("***Info catalog***");
            label1.Text = "Структура диска " + dir.Root.ToString().Split(':')[0];
            listBox1.Items.Add("Полное имя: " + dir.FullName);
            listBox1.Items.Add("Имя каталога: " + dir.Name);
            listBox1.Items.Add("Родительский каталога: " + dir.Parent);
            listBox1.Items.Add("Время создания: " + dir.CreationTime);
            listBox1.Items.Add("Атрибуты: " + dir.Attributes);
            listBox1.Items.Add("Корневой каталог: " + dir.Root);
            listBox1.Items.Add("------------------");*/
            addListBox(dir);
        }

        private void addListBox(DirectoryInfo dir)
        {
            listBox1.Items.Clear();
            listBox1.Items.Add("------------------------");
            listBox1.Items.Add("---КАТАЛОГ---");

            foreach (DirectoryInfo i in dir.GetDirectories())
            {
                listBox1.Items.Add(i);
            }

            listBox1.Items.Add("------------------------");
            listBox1.Items.Add("---ФАЙЛЫ---");
            foreach (FileInfo i in dir.GetFiles())
            {
                listBox1.Items.Add(i);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                string catalogName = listBox1.SelectedItem?.ToString();
                path += @"\"+catalogName;
                if (Path.GetExtension(path).Length > 0)
                {
                    MessageBox.Show(path);
                    listBox2.Items.Clear();
                    listBox2.Items.Add(File.ReadAllText(path, Encoding.Default));
                }
                else
                {
                    DirectoryInfo dir = new DirectoryInfo(path);
                    addListBox(dir);
                    label2.Text = "Структура каталога " + dir.Name;
                }    
                
            } catch (Exception er)
            {
                MessageBox.Show(er.ToString());
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            path = Path.GetDirectoryName(path);
            DirectoryInfo dir = new DirectoryInfo(path);
            addListBox(dir);
            label2.Text = "Структура каталога " + dir.Name;
        }
    }
}
