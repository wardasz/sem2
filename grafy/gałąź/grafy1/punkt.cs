using System;
using System.Collections.Generic;
using System.Text;

namespace gałąź
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

        public void napisz()
        {
            Console.WriteLine(x + "," + y);
        }

        public int porownaj1(punkt a)
        {
            if (x != a.dajX())
            {
                if (x > a.dajX())
                {
                    return -1;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                if (x > a.dajY())
                {
                    return 1;
                }
                else
                {
                    return -1;
                }
            }
        }

        public int dystans()
        {
            return x + y;
        }

        public int porownaj2(punkt a)
        {
            if (dystans() != a.dystans())
            {
                if (dystans() > a.dystans())
                {
                    return -1;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                if (x > a.dajX())
                {
                    return 1;
                }
                else
                {
                    return -1;
                }
            }
        }

        public bool tenSam(punkt a)
        {
            bool wynik = false;
            if (x == a.dajX() && y == a.dajY()) wynik = true;
            return wynik;
        }
    }
}
