using System;
using System.Collections.Generic;
using System.Text;

namespace gałąź2
{
    class punkt
    {
        private int x;
        private int y;

        public punkt(int a, int b)
        {
            x = a;
            y = b;
        }

        public int dajX()
        {
            return x;
        }

        public int dajY()
        {
            return y;
        }

        public int dystans()
        {
            return x + y;
        }

        public void napisz()
        {
            Console.WriteLine(x + "," + y);
        }
    }
}
