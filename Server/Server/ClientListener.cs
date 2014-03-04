using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Server
{
    public class ClientListener
    {
        Socket listener;

        public ClientListener()
        {
            IPAddress ip = System.Net.IPAddress.Any;
            System.Net.IPEndPoint me = new System.Net.IPEndPoint(ip, 100);

            listener = new System.Net.Sockets.Socket(System.Net.Sockets.SocketType.Stream, System.Net.Sockets.ProtocolType.Tcp);
            listener.Bind(me);
        }

        ~ClientListener()
        {

        }

        public Client Listen()
        {
            listener.Listen(50);

            return new Client(listener.Accept());
        }
    }
}
