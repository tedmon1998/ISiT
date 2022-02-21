using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Collections;

namespace WindowsFormsApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void GetTxt()
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.InitialDirectory = "c:\\";
                openFileDialog.Filter = "Text files (*.txt; *.json; *.xml;)|*.txt; *.json; *.xml|All files (*.*)|*.*";
                openFileDialog.FilterIndex = 1;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        var fileOpenStream = openFileDialog.OpenFile();

                        using (StreamReader fileText = new StreamReader(fileOpenStream))
                        {
                            richTextBox1.Text = fileText.ReadToEnd();
                        }
                        listBox1.Items.Clear();
                        FileInfo fileinfo = new FileInfo(openFileDialog.FileName);
                        DirectoryInfo parent = new DirectoryInfo(fileinfo.DirectoryName);
                        foreach(FileInfo file in parent.GetFiles("*.txt"))
                        {
                            listBox1.Items.Add(file);
                        }
                    }
                    catch (Exception)
                    {
                        MessageBox.Show("Файл имеет не правильное расширение, допускается : .txt|.json|.xml", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            GetTxt();
            listBox2.Font = new Font("Times New Roman", 14);
            listBox2.Items.Add("Студент: " + "Тунян Эдмон");
            listBox2.Items.Add("Группа: " + "607-91");
            listBox2.Items.Add("Курс: " + "3");
            listBox2.Items.Add("Предмет: " + "ОС");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            GetTxt();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            SortedList Sizes = new SortedList();
            foreach (FileInfo file in listBox1.Items)
            {
                Sizes.Add(file.Length, file);
            }
            listBox1.Items.Clear();
            for (int i=0; i<Sizes.Count; i++)
            {
                listBox1.Items.Add(Sizes.GetByIndex(i));
            }
        }

    }
}
