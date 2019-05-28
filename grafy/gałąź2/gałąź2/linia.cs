using System;
using System.Collections.Generic;
using System.Text;

namespace gałąź2
{
    class linia
    {
        private punkt p1;
        private punkt p2;

        public linia(punkt P1, punkt P2)
        {
            p1 = P1;
            p2 = P2;
        }

        public int dlugosc()
        {
            int dysX = p1.dajX() - p2.dajX();
            if (dysX < 0) dysX = dysX * -1;
            int dysY = p1.dajY() - p2.dajY();
            if (dysY < 0) dysY = dysY * -1;
            return dysX + dysY;
        }

        public void napisz()
        {
            Console.WriteLine("Linia łącząca punkty (" + p1.dajX() + "," + p1.dajY() + ") oraz (" + p2.dajX() + "," + p2.dajY() + ")");
        }
    }
}
