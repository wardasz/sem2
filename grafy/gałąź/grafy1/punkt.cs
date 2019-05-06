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

        //odległość taksówkowa do (0,0)
        public int dystans()
        {
            return x + y;
        }

        //odległość taksówkowa do punktu a (założenie że a jest mniejsze)
        public int dystans(punkt a)
        {
            return (x - a.dajX()) + (y - a.dajY());
        }


        public int porownaj(punkt a)
        {
            if(dystans() != a.dystans())
            {
                if(dystans() > a.dystans())
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
