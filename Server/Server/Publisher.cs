using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    public class Publisher : Observable
    {
        List<Observer> observers = new List<Observer>();

        public void notifyObservers(object source, string data)
        {
            foreach (Observer o in observers)
                o.notify(source, data);
        }

        public void registerObserver(Observer observer)
        {
            observers.Add(observer);
        }

        public void unregisterObserver(Observer observer)
        {
            observers.Remove(observer);
        }

    }
}
