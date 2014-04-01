using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    public class CommandHelp : ICommand
    {
        Client source = null;
        Dictionary<string, ICommand> commands = null;

        public CommandHelp()
        {
        }

        public CommandHelp(Dictionary<string, ICommand> commands)
        {
            this.commands = commands;
        }

        public void Run(IServer server, Client source)
        {
            if (commands != null)
            {
                string text = "Commands:";

                foreach(var pair in commands)
                {
                    text += "\n\r" + pair.Key + "\t-\t" + "A simple command.";
                }

                source.Send(MessageType.MESSAGE, text);
            }
        }

        public ICommand Create(ICommandFactory commandFactory, string[] args)
        {
            return new CommandHelp(commandFactory.getCommands());
        }


        public string getName()
        {
            return "help";
        }
    }
}
