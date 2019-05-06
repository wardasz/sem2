using System;
using System.Collections.Generic;
using System.Text;

namespace gałąź
{
    class kandydat
    {
        punkt p1;
        punkt p2;
        int x;
        int y;

        public kandydat(punkt a, punkt b)
        {
            p1 = a;
            p2 = b;
            x = Math.Min(a.dajX(), b.dajX());
            y = Math.Min(a.dajY(), b.dajY());
        }

        public int dajX()
        {
            return x;
        }

        public int dajY()
        {
            return y;
        }

        public punkt dajP()
        {
            return p1;
        }

        public punkt dajQ()
        {
            return p2;
        }

        public void napisz()
        {
            Console.WriteLine("Kandydat o <p,q> = " + x + "," + y);
            p1.napisz();
            p2.napisz();
            Console.WriteLine();
        }

        public int dystans()
        {
            return x + y;
        }

        public int porownaj(kandydat a)
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
    }
}
