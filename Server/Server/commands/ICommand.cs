using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Server
{
    public interface ICommand
    {
        ICommand Create(ICommandFactory commandFactory, string[] args);
        void Run(IServer server, Client source);

        string getName();
    }
}
