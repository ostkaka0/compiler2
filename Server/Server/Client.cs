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

        public Client(Socket socket)
        {
            this.socket = socket;
        }

        ~Client()
        {
            thread.Abort();
        }

        public void Start(Publisher publisher)
        {
            this.publisher = publisher;
            this.Send("Welcome!");
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
                            publisher.notifyObservers(this, "/disconnect");
                            break;
                        }

                        data += Encoding.ASCII.GetString(b, 0, bytesRec);

                        int i = data.IndexOf('\n');
                        while (i > -1)
                        {
                            publisher.notifyObservers(this, data.Substring(0, i).Replace("\r", "").Replace("\b",""));
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
                            publisher.notifyObservers(this, "/disconnect");
                            break;
                        }


                    }

                });
            thread.Start();
        }

        public void Send(String text)
        {
            try
            {
                byte[] bs = Encoding.ASCII.GetBytes(text + "\n\r");
                socket.Send(bs);
            }
            catch (Exception e)
            {
                kill();
                publisher.notifyObservers(this, "/disconnect");
            }
        }

        public void kill()
        {
            if (socket.Connected)
            {
                socket.Disconnect(false);
                socket.Close();
            }
        }

        public override string ToString()
        {
            return socket.RemoteEndPoint.ToString();
        }

    }
}
