using System;
using System.Collections.Generic;
using System.Text;

namespace kDrzewa
{
    class lisc
    {
        private int d;
        private int typ; //1-punkt, 2-pion, 3-poziom
        private int wspolzendna;
        private punkt punkcik;

        private lisc lewy;
        private lisc prawy;

        public lisc(int D, int T, int wspol)
        {
            d = D;
            typ = T;
            wspolzendna = wspol;
            lewy = null;
            prawy = null;
        }

        public lisc(int D, int T, punkt p)
        {
            d = D;
            typ = T;
            punkcik = p;
            lewy = null;
            prawy = null;
        }

        public int dajD()
        {
            return d;
        }

        public int dajTyp()
        {
            return typ;
        }

        public int dajPoziom()
        {
            return wspolzendna;
        }

        public punkt dajPunkt()
        {
            return punkcik;
        }

        public lisc dajLewego()
        {
            return lewy;
        }

        public lisc dajPrawego()
        {
            return prawy;
        }

        public void podepnijNaLewo(lisc a)
        {
            lewy = a;
        }

        public void podepnijNaPrawo(lisc a)
        {
            prawy = a;
        }

        public void napisz()
        {
            if (lewy != null) lewy.napisz();
            Console.Write("Liść na głębokości " + d);
            switch (typ)
            {
                case 1:
                    Console.WriteLine("; punkt o współżędnych (" + punkcik.dajX() + "," + punkcik.dajY() + ")");
                    break;
                case 2:
                    Console.WriteLine("; linia pionowa o współżędnej " + wspolzendna);
                    break;
                case 3:
                    Console.WriteLine("; linia pozioma o współżędnej " + wspolzendna);
                    break;
            }
            if (prawy != null) prawy.napisz();
        }
    }
}
