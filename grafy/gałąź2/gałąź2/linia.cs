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

        public void napisz()
        {
            Console.WriteLine("Linia łącząca punkty (" + p1.dajX() + "," + p1.dajY() + ") oraz (" + p2.dajX() + "," + p2.dajY() + ")");
        }
    }
}
