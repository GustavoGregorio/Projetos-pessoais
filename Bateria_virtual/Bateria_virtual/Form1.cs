using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Media;
using IrrKlang;
using System.IO.Ports;



namespace Bateria_virtual
{
    public partial class Form1 : Form
    {
        public string linha;
        public Form1()
        {
            InitializeComponent();
            serialPort1.DataReceived += serialPort1_DataReceived;
            FormClosing += new FormClosingEventHandler(Form_Fechar);
        }

        private delegate void LineReceivedEvent(string line);
        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            linha = serialPort1.ReadLine();
            this.BeginInvoke(new LineReceivedEvent(LineReceived), linha);
        }
        private void LineReceived(string line)
        {
            // richTextBox1.Text = line;
            switch (line)
            {
                case "1":
                    ISoundEngine engine1 = new ISoundEngine();
                    engine1.Play2D(@"C:\Users\Gregster\Documents\Visual Studio 2012\Projects\Bateria_virtual\Bateria_virtual\HiHat.wav");
                    break;
                case "2":
                    ISoundEngine engine2 = new ISoundEngine();
                    engine2.Play2D(@"C:\Users\Gregster\Documents\Visual Studio 2012\Projects\Bateria_virtual\Bateria_virtual\Snare.wav");
                    break;
                case "3":
                    ISoundEngine engine3 = new ISoundEngine();
                    engine3.Play2D(@"C:\Users\Gregster\Documents\Visual Studio 2012\Projects\Bateria_virtual\Bateria_virtual\Tom.wav");
                    break;

                case "4":
                    ISoundEngine engine4 = new ISoundEngine();
                    engine4.Play2D(@"C:\Users\Gregster\Documents\Visual Studio 2012\Projects\Bateria_virtual\Bateria_virtual\Crash.wav");
                    break;
            }

        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Open();
                    serialPort1.Write("a");
                }
                catch
                {
                    MessageBox.Show("Ocorreu um erro. Por favor, certifique-se de que a porta correta foi selecionada, e se o dispositivo foi plugado.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }
        private void button2_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Write("b");
                    serialPort1.Close();
                    
                }
                catch
                {
                    MessageBox.Show("Ocorreu um erro. Por favor, certifique-se de que a porta correta foi selecionada, e se o dispositivo foi plugado.", "Erro", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }
        private void Form_Fechar(object sender, FormClosingEventArgs e)
        {
            DialogResult resposta = MessageBox.Show("Deseja mesmo encerrar este aplicativo?",
                                            "Sair", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

            if (resposta == DialogResult.Yes)
            {
                if (serialPort1.IsOpen)
                {
                    serialPort1.Write("b");
                    serialPort1.Close();
                }
                else
                {
                    serialPort1.Close();
                }
            }
            if (resposta == DialogResult.No)
            {
                e.Cancel = true;
            }

        }

    }
}

