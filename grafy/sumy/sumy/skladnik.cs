using System;
using System.Collections.Generic;
using System.Text;

namespace sumy
{
    class skladnik
    {
        private int wartosc;

        public skladnik(int a)
        {
            wartosc = a;
        }

        public int dajWartosc()
        {
            return wartosc;
        }

        public int porownaj(skladnik p)
        {
            if (wartosc > p.dajWartosc())
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
