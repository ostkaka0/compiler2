using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

using Server;
using System.IO;                                                                                                                

namespace Client
{
    public partial class Form1 : Form
    {
        Socket socket;
        Thread thread;


        public Form1()
        {
            InitializeComponent();
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            Send(MessageType.MESSAGE, tbSendText.Text);
            tbSendText.Text = "";
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            System.Threading.Thread.Sleep(500);

            IPAddress serverIp = new IPAddress(new byte[] { 127, 0, 0, 1 });

            System.Net.IPEndPoint server = new System.Net.IPEndPoint(serverIp, 100);

            socket = new System.Net.Sockets.Socket(System.Net.Sockets.SocketType.Stream, System.Net.Sockets.ProtocolType.Tcp);

            socket.Connect(server);

            Listen();
        }

        private void Listen()
        {
            thread = new Thread(() =>
            {
                string data = "";
                byte[] b = new byte[256];

                while (socket.Connected)
                {
                    int bytesRec;

                    try
                    {
                        bytesRec = socket.Receive(b);
                    }
                    catch (Exception e)
                    {
                        //kill
                        break;
                    }

                    data += Encoding.ASCII.GetString(b, 0, bytesRec);

                    int i = data.IndexOf('\n');
                    while (i > -1)
                    {
                        HandleMessage(data.Substring(0, i).Replace("\r", "").Replace("\b", ""));//publisher.notifyObservers(this, data.Substring(0, i).Replace("\r", "").Replace("\b", ""));
                        if (data.Length > i)
                            data = data.Substring(i + 1);
                        else
                            data = "";
                        i = data.IndexOf((char)(13));
                    }

                    if (data.IndexOf((char)(26)) > -1)
                    {
                        i = data.IndexOf((char)(26));
                        HandleMessage(data.Substring(0, i));//publisher.notifyObservers(this, data.Substring(0, i));
                        //kill();
                        break;
                    }


                }

            });
            thread.Start();
        }

        private void HandleMessage(string data)//(StringReader ostring)
        {
            this.Invoke(new Action(() =>
                {
                    if (data.Length >= 1)//ostring.Length >= 1)
                    {
                        MessageType messageType = MessageType.NULLMESSAGE;
                        messageType = (MessageType)(byte)data.First();//Enum.TryParse<MessageType>(data.First().ToString(), out messageType);

                        switch (messageType)
                        {
                            case MessageType.LOGIN:
                                if (Text.Length >= 2)
                                {
                                    string[] users = data.Substring(1).Split(';');
                                    lvUsers.Items.Clear();
                                    foreach (string user in users)
                                    {
                                        if (user != "")
                                            lvUsers.Items.Add(user);
                                    }
                                }
                                break;
                            case MessageType.JOIN:
                                if (Text.Length >= 2)
                                {
                                    lvUsers.Items.Add(data.Substring(1));
                                }
                                break;
                            case MessageType.LEAVE:
                                break;
                            case MessageType.MESSAGE:
                                if (Text.Length >= 2)
                                    InvokeText(data.Substring(1));
                                break;
                        }
                    }
                }));
        }

        private void InvokeText(string text)
        {
            this.Invoke(new Action(() => this.tbChat.Text += text + Environment.NewLine));
        }

        private void Send(MessageType messageType, String text)
        {
            socket.Send(new byte[]{(byte)messageType});
            socket.Send(Encoding.ASCII.GetBytes(text + "\n\r"));
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            Console.WriteLine(tbLogin.Text.Replace('\n','N').Replace('\r', 'R'));
            Send(MessageType.LOGIN, tbLogin.Text);
        }
    }
}
