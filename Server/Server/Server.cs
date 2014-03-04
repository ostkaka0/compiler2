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
    public class Server : Observer
    {
        Publisher publisher = new Publisher();
        ClientListener clientListener = new ClientListener();

        List<Client> connectedClients = new List<Client>();
        /*Socket listener;
        IPAddress ip;

        Socket remoteClient;*/

        public Server()
        {
            publisher.registerObserver(this);

            while (true)
            {
                Client client = clientListener.Listen();

                client.Start(publisher);

                lock (connectedClients)
                    connectedClients.Add(client);

                broadcast("Server: " + client.ToString() + " connected!");
            }
        }

        public void notify(object source, string data)
        {
            if (source is Client)
            {
                Client client = (Client)source;

                Console.WriteLine(source.ToString() + "\t " + data);
                if (data.StartsWith("/"))
                {
                    string[] args = data.Split(' ');
                    switch (args.First().ToLower())
                    {
                        case "/disconnect":
                            Console.WriteLine(source.ToString() + " disconnected!");
                            broadcast(client.ToString() + " disconnected!", client);
                            client.kill();
                            lock (connectedClients)
                                connectedClients.Remove(client);
                            break;

                        case "/spam":
                            if (args.Length > 1)
                            {
                                int i = 100;

                                string spamText = data.Substring(args[0].Length + 1);

                                if (args.Length > 2 && args[1].StartsWith("#") && args[1].Length > 1)
                                {
                                    int.TryParse(args[1].Substring(1), out i);

                                    if (i == 0)
                                    {
                                        client.Send("Invalid amount of spam!");
                                        break;
                                    }
                                    else
                                    {
                                        spamText = spamText.Substring(args[1].Length + 1);
                                    }

                                }
                                else
                                {
                                    i = 100;
                                }

                                broadcast(client.ToString() + " is now spamming...");

                                for (; i > 0; i--)
                                {
                                    broadcast(spamText);
                                }

                                broadcast(client.ToString() + " just spammed.");

                            }
                            else
                            {
                                client.Send("/spam [#amount] <spam text>");
                            }
                            break;
                            
                    }
                }
                else
                {
                    broadcast("Server: " + source.ToString() + ": " + data, client);
                }
            }
        }

        public void broadcast(string message, params Client[] exceptions)
        {
            lock (connectedClients)
            {
                foreach (Client c in connectedClients)
                {
                    if (!exceptions.Contains(c))
                        c.Send(message);
                }
            }
        }

    }
}
