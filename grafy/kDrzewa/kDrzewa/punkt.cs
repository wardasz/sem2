using System;
using System.Collections.Generic;
using System.Text;

namespace kDrzewa
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

        public int porownajX(punkt a)
        {
            if (x < a.dajX()) return -1;
            else if (x > a.dajX()) return 1;
            else if (y > a.dajY()) return 1;
            else return -1;

        }

        public int porownajY(punkt a)
        {
            if (y < a.dajY()) return -1;
            else if (y > a.dajY()) return 1;
            else if (x > a.dajX()) return 1;
            else return -1;
        }

        public void napisz()
        {
            Console.WriteLine(x + "," + y);
        }       
    }
}
