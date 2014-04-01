using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    public class Publisher : IObservable
    {
        List<IObserver> observers = new List<IObserver>();

        public void notifyObservers(object source, string data)
        {
            foreach (IObserver o in observers)
                o.notify(source, data);
        }

        public void registerObserver(IObserver observer)
        {
            observers.Add(observer);
        }

        public void unregisterObserver(IObserver observer)
        {
            observers.Remove(observer);
        }

    }
}
