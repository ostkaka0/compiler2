using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    public class CommandNotFound : ICommand
    {
        string command = null;
        public CommandNotFound()
        {
        }

        private CommandNotFound(string command)
        {
            this.command = command;
        }

        public void Run(IServer server, Client source)
        {
            source.Send(MessageType.MESSAGE, "Command '/" + command + "' is undefined!");
        }

        public ICommand Create(ICommandFactory commandFactory, string[] args)
        {
            CommandNotFound command = new CommandNotFound();

            command.command = args[0];
            return command;
        }

        public string getName()
        {
            return "";
        }
    }
}
