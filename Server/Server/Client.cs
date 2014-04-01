using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace Server
{
    public class Client
    {
        Publisher publisher;
        Socket socket;
        Thread thread;
        string name;

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public Client(Socket socket)
        {
            this.socket = socket;
            name = "";
        }

        ~Client()
        {
            thread.Abort();
        }

        public void Start(Publisher publisher)
        {
            this.publisher = publisher;
            this.Send(MessageType.MESSAGE, "Welcome!");  
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
                            kill();
                            break;
                        }

                        data += Encoding.ASCII.GetString(b, 0, bytesRec);

                        int i = data.IndexOf(Constants.messageBreakChar);
                        while (i > -1)
                        {
                            publisher.notifyObservers(this, data.Substring(0, i));//.Replace("\r", "").Replace("\b",""));
                            if (data.Length > i)
                                data = data.Substring(i + 1);
                            else
                                data = "";
                            i = data.IndexOf((char)(13));
                        }

                        if (data.IndexOf((char)(26)) > -1)
                        {
                            i = data.IndexOf((char)(26));
                            publisher.notifyObservers(this, data.Substring(0, i));
                            kill();
                            break;
                        }


                    }

                });
            thread.Start();
        }

        public void Send(MessageType messageType, String text)
        {
            try
            {
                List<byte> bs = new List<byte>();
                bs.Add((byte)messageType);
                bs.AddRange(Encoding.ASCII.GetBytes(text + Constants.messageBreakChar));
                //byte[] bs = 
                socket.Send(bs.ToArray());
            }
            catch (Exception e)
            {
                kill();
            }
        }

        public void kill()
        {
            if (socket.Connected)
            {
                socket.Disconnect(false);
                socket.Close();
                publisher.notifyObservers(this, ((char)(byte)MessageType.LEAVE).ToString());
            }
        }

        public override string ToString()
        {
            return this.name;
        }

    }
}
