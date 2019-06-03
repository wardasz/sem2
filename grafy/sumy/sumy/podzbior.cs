using System;
using System.Collections.Generic;
using System.Text;

namespace sumy
{
    class podzbior
    {
        private List<skladnik> skladniki;

        public podzbior(List<skladnik> a)
        {
            skladniki = new List<skladnik>(a);
        }

        public podzbior(int a)
        {
            skladnik nowy = new skladnik(a);
            skladniki = new List<skladnik>();
            skladniki.Add(nowy);
        }

        public List<skladnik> dajListe()
        {
            return skladniki;
        }

        public int dajSume()
        {
            int suma = 0;
            foreach(skladnik i in skladniki)
            {
                suma = suma + i.dajWartosc();
            }
            return suma;
        }

        public void plusik(int a)
        {
            foreach(skladnik i in skladniki)
            {
                i.zwieksz(a);
            }
        }
    }
}
