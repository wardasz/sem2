using System;
using System.Collections.Generic;
using System.Text;

namespace paraPunktow2
{
    class listy
    {
        private List<punkt> Sx = new List<punkt>();
        private List<punkt> Sy = new List<punkt>();

        public listy()
        {

        }

        public List<punkt> dajSx()
        {
            return Sx;
        }

        public List<punkt> dajSy()
        {
            return Sy;
        }

        public void dodaj(punkt p)
        {
            Sx.Add(p);
            Sy.Add(p);
        }

        public void dodajX(punkt p)
        {
            Sx.Add(p);
        }

        public void dodajY(punkt p)
        {
            Sy.Add(p);
        }

        public void wypisz()
        {
            Console.WriteLine("Sx:");
            foreach (punkt p in Sx)
            {
                p.napisz();
            }
            Console.WriteLine("Sy:");
            foreach (punkt p in Sy)
            {
                p.napisz();
            }
            Console.WriteLine();
        }

        public void sortuj()
        {
            Sx.Sort((a, b) => (a.porownajX(b)));
            Sy.Sort((a, b) => (a.porownajY(b)));
        }
    }
}
