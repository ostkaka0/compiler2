using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    public class CommandSpam : ICommand
    {
        private string spamText;

        public CommandSpam()
        {
            this.spamText = "";
        }

        private CommandSpam( string spamText)
        {
            this.spamText = spamText;
        }

        public void Run(IServer server, Client source)
        {
            for (int i = 0; i < 100; i++)
            {
                server.broadcast(MessageType.MESSAGE, source.ToString() + ": " + spamText);
            }
        }

        public ICommand Create(ICommandFactory commandFactory, string[] args)
        {
            if (args.Length > 1)
                return new CommandSpam(string.Join(" ", args).Substring(args[0].Length + 1));
            else
                return new CommandSpam();
        }

        public string getName()
        {
            return "spam";
        }
    }
}
