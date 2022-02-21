using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;


namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        Mutex mutex = new Mutex(false, "TEG");
        public Form1()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
            
        }

        private void PrintText(object writer)
        {
            try
            {
                if(mutex.WaitOne())
                {
                    if (Convert.ToInt32(writer) == 1)
                    {
                        richTextBox4.Text = richTextBox1.Text;
                        richTextBox7.Text += richTextBox1.Text;
                    }
                    else if (Convert.ToInt32(writer) == 2)
                    {
                        richTextBox5.Text = richTextBox2.Text;
                        richTextBox7.Text += richTextBox2.Text;
                    }
                    else if (Convert.ToInt32(writer) == 3)
                    {
                        richTextBox6.Text = richTextBox3.Text;
                        richTextBox7.Text += richTextBox3.Text;
                    }
                }
            } catch(Exception e)
            {
                MessageBox.Show(e.ToString());
            }
            finally
            {
                mutex.ReleaseMutex();
            }
            
        }

        private void PrintTextAsync(object writer)
        {
            if (Convert.ToInt32(writer) == 1)
            {
                richTextBox4.Text = richTextBox1.Text;
                richTextBox7.Text += richTextBox1.Text;
            }
            else if (Convert.ToInt32(writer) == 2)
            {
                richTextBox5.Text = richTextBox2.Text;
                richTextBox7.Text += richTextBox2.Text;
            }
            else if (Convert.ToInt32(writer) == 3)
            {
                richTextBox6.Text = richTextBox3.Text;
                richTextBox7.Text += richTextBox3.Text;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Thread thread_1 = new Thread(PrintText);
            Thread thread_2 = new Thread(PrintText);
            Thread thread_3 = new Thread(PrintText);
            thread_1.Start(1);
            thread_2.Start(2);
            thread_3.Start(3);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Thread thread_1 = new Thread(PrintTextAsync);
            Thread thread_2 = new Thread(PrintTextAsync);
            Thread thread_3 = new Thread(PrintTextAsync);
            thread_1.Start(1);
            thread_2.Start(2);
            thread_3.Start(3);
        }

    }
}
