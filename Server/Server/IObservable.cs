﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    public interface IObservable
    {
        void notifyObservers(object source, string data);
        void registerObserver(IObserver observer);
        void unregisterObserver(IObserver observer);
    }
}
