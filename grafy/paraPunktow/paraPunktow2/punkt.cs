using System;
using System.Collections.Generic;
using System.Text;

namespace paraPunktow2
{
    class punkt
    {
        private int x;
        private int y;
        bool przed;

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

        public bool czyPrzed()
        {
            return przed;
        }

        public void ustawPrzed(bool a)
        {
            przed = a;
        }

        public void napisz()
        {
            Console.WriteLine(x + "," + y);
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

        public double dystans(punkt a)
        {
            int X = x - a.dajX();
            if (X < 0) X = X * -1;
            int Y = y - a.dajY();
            if (Y < 0) Y = Y * -1;
            double dys = X * X + Y * Y;
            return dys;
        }
    }
}
