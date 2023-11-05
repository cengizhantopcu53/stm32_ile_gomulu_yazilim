using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace ArayuzileTestEtme
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private string data;
        private void Form1_Load(object sender, EventArgs e)
        {
            textBox1.ReadOnly = true;                    //textBox1'i yalnızca okunabilir şekilde ayarla
            string[] ports = SerialPort.GetPortNames();  //Seri portları diziye ekleme
            foreach (string port in ports)
                comboBox1.Items.Add(port); //Seri portları comBox1' ekleme
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.Write("1");    //Seri porta "1" gönder    
            button2.Enabled = true;    //Button2'yi tıklanabilir hale getir
            button1.Enabled = false;   //Button1'i tıklanamaz hale getir
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Write("0");    //Seri porta "0" gönder
            button1.Enabled = true;    //Button1'i tıklanabilir hale getir
            button2.Enabled = false;   //Button2'yi tıklanamaz hale getir
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort1.PortName = comboBox1.SelectedItem.ToString(); //comboBox1'de seçili olan portu port ismine ata
            serialPort1.Open(); //Seri portu aç
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (serialPort1.IsOpen) serialPort1.Close();  //Eğer port açıksa kapat
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            data = serialPort1.ReadLine(); //Veriyi al
            this.Invoke(new EventHandler(displayData_event));
        }

        private void displayData_event(object sender, EventArgs e)
        {
            textBox1.Text += data + "\n"; //Gelen veriyi textBox içine ekle
        }
    }
}
