using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PlayerIOClient;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            PlayerIO.QuickConnect.SimpleRegister("eeo-ruiegvlaw0sdzzak1msc3a", "guest", "guest", "", "", "", new Dictionary<string,string>(), "");
            //PlayerIO.QuickConnect.SimpleRegister(
        }
    }
}
