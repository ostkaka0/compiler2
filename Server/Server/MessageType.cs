﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    public enum MessageType : byte
    {
        NULLMESSAGE,
        LOGIN,
        JOIN,
        LEAVE,
        MESSAGE
    }
}
