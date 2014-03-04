using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    public interface Observable
    {
        void notifyObservers(object source, string data);
        void registerObserver(Observer observer);
        void unregisterObserver(Observer observer);
    }
}
