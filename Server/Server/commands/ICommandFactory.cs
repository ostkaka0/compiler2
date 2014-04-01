using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    public interface ICommandFactory
    {
        ICommand CreateCommand(string message);

        void registerCommand(string name, ICommand command);

        Dictionary<string, ICommand> getCommands();
    }
}
