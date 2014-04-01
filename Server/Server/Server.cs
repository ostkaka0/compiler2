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
    public class Server : IServer, IObserver
    {
        Publisher publisher = new Publisher();

        ClientListener clientListener = new ClientListener();

        List<Client> connectedClients = new List<Client>();

        CommandFactory commandFactory = new CommandFactory();

        public Server()
        {
            publisher.registerObserver(this);

            commandFactory.registerCommand(new CommandLogin());
            commandFactory.registerCommand(new CommandSpam());

            while (true)
            {
                Client client = clientListener.Listen();

                client.Start(publisher);

                lock (connectedClients)
                    connectedClients.Add(client);

                broadcast(MessageType.MESSAGE, "Server: " + client.Name + " connected!");
            }
        }

        public void notify(object source, string data)
        {
            if (source is Client && data != "")
            {
                Client client = (Client)source;

                MessageType messageType = (MessageType)(byte)data[0];

                Console.WriteLine(source.ToString() + "\t " + data);

                switch (messageType)
                {
                    case MessageType.LOGIN:
                        if (data.Length >= 2)
                        {
                            if (client.Name == "")
                            {
                                string playerList = "";
                                client.Name = data.Substring(1);
                                client.Send(MessageType.MESSAGE, "Yffdlkf");


                                foreach (Client c in connectedClients)
                                {
                                    if (c != client && c.Name != "")
                                    {
                                        playerList += c.Name + ";";
                                        c.Send(MessageType.JOIN, client.Name);
                                    }
                                }

                                client.Send(MessageType.LOGIN, playerList);
                            }
                        }

                        break;

                    case MessageType.JOIN:
                        break;

                    case MessageType.LEAVE:
                        if (connectedClients.Contains(client))
                        {
                            connectedClients.Remove(client);
                            foreach (Client c in connectedClients)
                            {
                                if (c.Name != "")
                                    c.Send(MessageType.LEAVE, client.Name);
                            }
                            client.kill();
                        }
                        break;

                    case MessageType.MESSAGE:
                        if (data.Length >= 2 && client.Name != "")
                        {
                            if (data[1] == '/')
                            {
                                ICommand command = commandFactory.CreateCommand(data.Substring(1));
                                command.Run(this, client);
                            }
                            else
                            {
                                broadcast(MessageType.MESSAGE, client.Name + ": " + data.Substring(1), client);
                                client.Send(MessageType.MESSAGE, "you: " + data.Substring(1));
                            }
                        }
                        break;
                }
                
            }
        }

        public void broadcast(MessageType messageType, string message, params Client[] exceptions)
        {
            lock (connectedClients)
            {
                foreach (Client c in connectedClients)
                {
                    if (!exceptions.Contains(c) && c.Name != "")
                        c.Send(messageType, message);
                }
            }
        }

    }
}
