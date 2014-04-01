using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    class CommandLogin : ICommand
    {
        string[] args;

        public CommandLogin()
        {
            args = new string[0];
        }

        private CommandLogin(string[] args)
        {
            this.args = args;
        }

        public ICommand Create(ICommandFactory commandFactory, string[] args)
        {
            return new CommandLogin(args);
        }

        public void Run(IServer server, Client source)
        {
            if (args.Length >= 2)
            {
                source.Name = args[1];
            }
        }

        public string getName()
        {
            return "login";
        }
    }
}
