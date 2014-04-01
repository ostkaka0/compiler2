using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    public class CommandFactory : ICommandFactory
    {
        Dictionary<string, ICommand> commands = new Dictionary<string, ICommand>();

        public CommandFactory()
        {
           registerCommand(new CommandHelp());
        }

        public ICommand CreateCommand(string message)
        {
            string[] args = message.Substring(1).Split(' ');


            if (commands.ContainsKey(args[0]))
            {
                return commands[args[0]].Create(this, args);
            }
            else
            {
                return new CommandNotFound();
            }
        }

        public void registerCommand(ICommand command)
        {
            commands.Add(command.getName(), command);
        }


        public void registerCommand(string name, ICommand command)
        {
            throw new NotImplementedException();
        }

        public Dictionary<string, ICommand> getCommands()
        {
            return commands;
        }
    }
}
