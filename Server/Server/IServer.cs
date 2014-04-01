using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Server
{
    public interface IServer
    {
        void broadcast(MessageType messageType, string message, params Client[] exceptions);
    }
}
