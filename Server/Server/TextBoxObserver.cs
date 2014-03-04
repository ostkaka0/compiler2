using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Server
{
    public class TextBoxObserver : TextBox, Observer
    {
        public void notify(object source, string data)
        {
            this.Text = data;
        }

    }
}
