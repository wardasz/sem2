using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace wyznaczaniePrzeciec
{
    class zdarzenie
    {
        private int typ; //1-początek odcinka, 2-pionowy, 3-koniec odcinka
        private int kiedy;
        private int wysokosc;
        private int dol;

        public zdarzenie(int t, int x, int y)
        {
            typ = t;
            kiedy = x;
            wysokosc = y;
            dol = y;
        }

        public zdarzenie(int t, int x, int y1, int y2)
        {
            typ = t;
            kiedy = x;
            wysokosc = y1;
            dol = y2;
        }

        public int dajTyp()
        {
            return typ;
        }

        public int dajX()
        {
            return kiedy;
        }

        public int dajY()
        {
            return wysokosc;
        }

        public int dajY2()
        {
            return dol;
        }

        public int porownaj(zdarzenie a)
        {
            if (kiedy < a.dajX()) return -1;
            if (kiedy > a.dajX()) return 1;
            if (typ < a.dajTyp()) return -1;
            else return 1;
        }        
    }
}
