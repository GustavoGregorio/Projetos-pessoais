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
using System.IO.Ports;



namespace LuvaEletronica
{
    public partial class Form1 : Form
    {
        [System.Runtime.InteropServices.DllImport("user32.dll")]
        public static extern void mouse_event(int dwFlags, int dx, int dy, int cButtons, int dwExtraInfo);
        [System.Runtime.InteropServices.DllImport("user32.dll")]
        public static extern void keybd_event(int bVk, byte bScan, uint dwFlags, uint dwExtraInfo);
        public const int CLICK_MOUSEESQUERDO = 0x02;
        public const int SOLTAR_MOUSEESQUERDO = 0x04;
        public const int CLICK_MOUSEDIREITO = 0x08;
        public const int SOLTAR_MOUSEDIREITO = 0x10;
        public const uint SOLTAR_TECLADO = 0x0002;
        public const uint PRESSIONAR_TECLADO = 0x0001;
        public string linha;
        public int[] flag = { 0, 0, 0, 0, 0, 0, 0, 0 };
        public int verificador = 0;
        public string resol;
        public string resol2;
        public int posX;
        public int posY;


        public Form1()
        {
            InitializeComponent();
            serialPort1.DataReceived += serialPort1_DataReceived;
            FormClosing += new FormClosingEventHandler(Form_Fechar);
            int w = Screen.PrimaryScreen.Bounds.Width;
            int h = Screen.PrimaryScreen.Bounds.Height;
            resol = Convert.ToString(w);
            resol2 = Convert.ToString(h);
            textBox1.Text = resol + 'x' + resol2;
            posX = w / 2;
            posY = h / 2;
        }

        private delegate void LineReceivedEvent(string line);
        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                linha = serialPort1.ReadLine();
                this.BeginInvoke(new LineReceivedEvent(LineReceived), linha);
            }
        }

        private void LineReceived(string line)
        {
            for (int verif = 0; verif < 10; verif++)
            {
                if (line[verif] == '-')
                {
                    //System.Threading.Thread.Sleep(100);
                    verificador = 1;
                }
            }

            if (serialPort1.IsOpen && verificador == 0)
            {
                int o = 100;
                int m = 100;

                //Mouse
                #region
                if (checkBox2.Checked)
                {
                    Cursor.Position = new Point(posX, posY);   
                    string posicaoX = String.Concat(line[0], line[1], line[2], line[3]);
                    string posicaoY = String.Concat(line[4], line[5], line[6]);
                    posX = Math.Abs(int.Parse(posicaoX));
                    posY = Math.Abs(int.Parse(posicaoY));
                     
                }
                #endregion

                //Teclado
                #region
                if (checkBox1.Checked)
                {
                    //Botao 1
                    #region
                    if (line[7] == '1' && flag[0] == 0)
                    {
                        mouse_event(CLICK_MOUSEESQUERDO, o, m, 0, 0);
                        flag[0] = 1;
                    }

                    if (line[7] == '0' && flag[0] == 1)
                    {
                        mouse_event(SOLTAR_MOUSEESQUERDO, o, m, 0, 0);
                        flag[0] = 0;
                    }
                    #endregion

                    //Botao 2
                    #region
                    if (line[8] == '1' && flag[1] == 0)
                    {
                        mouse_event(CLICK_MOUSEDIREITO, o, m, 0, 0);
                        flag[1] = 1;
                    }

                    if (line[8] == '0' && flag[1] == 1)
                    {
                        mouse_event(SOLTAR_MOUSEDIREITO, o, m, 0, 0);
                        flag[1] = 0;
                    }
                    #endregion

                    //Botao 3
                    #region
                    if (line[9] == '1' && flag[2] == 0)
                    {
                        int ascii = verif_botao(maskedTextBox1.Text);
                        keybd_event((int)ascii, 0, PRESSIONAR_TECLADO | 0, 0);
                        flag[2] = 1;
                    }

                    if (line[9] == '0' && flag[2] == 1)
                    {
                        int ascii = verif_botao(maskedTextBox1.Text);
                        keybd_event((int)ascii, 0, PRESSIONAR_TECLADO | SOLTAR_TECLADO, 0);
                        flag[2] = 0;
                    }
                    #endregion
                    /*
                //Botao 4
                #region
                if (line[10] == '1' && flag[3] == 0)
                {
                    int ascii = verif_botao(maskedTextBox2.Text);
                    keybd_event((int)ascii, 0, PRESSIONAR_TECLADO | 0, 0);
                    flag[3] = 1;
                }

                if (line[10] == '0' && flag[3] == 1)
                {
                    int ascii = verif_botao(maskedTextBox2.Text);
                    keybd_event((int)ascii, 0, PRESSIONAR_TECLADO | SOLTAR_TECLADO, 0);
                    flag[3] = 0;
                }
                #endregion

                //Botao 5
                #region
                if (line[11] == '1' && flag[4] == 0)
                {
                    int ascii = verif_botao(maskedTextBox3.Text);
                    keybd_event((int)ascii, 0, PRESSIONAR_TECLADO | 0, 0);
                    flag[4] = 1;
                }

                if (line[11] == '0' && flag[4] == 1)
                {
                    int ascii = verif_botao(maskedTextBox3.Text);
                    keybd_event((int)ascii, 0, PRESSIONAR_TECLADO | SOLTAR_TECLADO, 0);
                    flag[4] = 0;
                }
                #endregion

                //Botao 6
                #region
                if (line[12] == '1' && flag[5] == 0)
                {
                    int ascii = verif_botao(maskedTextBox4.Text);
                    keybd_event((int)ascii, 0, PRESSIONAR_TECLADO | 0, 0);
                    flag[5] = 1;
                }

                if (line[12] == '0' && flag[5] == 1)
                {
                    int ascii = verif_botao(maskedTextBox4.Text);
                    keybd_event((int)ascii, 0, PRESSIONAR_TECLADO | SOLTAR_TECLADO, 0);
                    flag[5] = 0;
                }
                #endregion

                //Botao 7
                #region
                if (line[13] == '1' && flag[6] == 0)
                {
                    int ascii = verif_botao(maskedTextBox5.Text);
                    keybd_event((int)ascii, 0, PRESSIONAR_TECLADO | 0, 0);
                    flag[6] = 1;
                }

                if (line[13] == '0' && flag[6] == 1)
                {
                    int ascii = verif_botao(maskedTextBox5.Text);
                    keybd_event((int)ascii, 0, PRESSIONAR_TECLADO | SOLTAR_TECLADO, 0);
                    flag[6] = 0;
                }
                #endregion

                //Botao 8
                #region
                if (line[14] == '1' && flag[7] == 0)
                {
                    int ascii = verif_botao(maskedTextBox6.Text);
                    keybd_event((int)ascii, 0, PRESSIONAR_TECLADO | 0, 0);
                    flag[7] = 1;
                }

                if (line[14] == '0' && flag[7] == 1)
                {
                    int ascii = verif_botao(maskedTextBox6.Text);
                    keybd_event((int)ascii, 0, PRESSIONAR_TECLADO | SOLTAR_TECLADO, 0);
                    flag[7] = 0;
                }
                #endregion
                 */
                }
                #endregion              
            }
            verificador = 0;
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
        private void button1_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Open();
                    //serialPort1.Write("x" + resol);
                    //serialPort1.Write("y" + resol2);
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
        private int verif_botao(string text)
        {
            byte[] caracteres = new byte[System.Text.Encoding.ASCII.GetByteCount(text)];
            caracteres = System.Text.Encoding.ASCII.GetBytes(text);
            int ascii = caracteres[0];
            return ascii;
        }

    }
}
