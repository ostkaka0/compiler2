using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace stopmotionEditor
{
    public class PictureItem
    {
        public string path;
        public string name;
        public int pictureId;

        public PictureItem(string path, int pictureId)
        {
            this.path = path;
            this.name = path.Split('\\').Last().Replace(".png", "");
            this.pictureId = pictureId;
        }

        public override string ToString()
        {
            return "[" + pictureId.ToString() + "]\t" + name;
        }
    }
}
