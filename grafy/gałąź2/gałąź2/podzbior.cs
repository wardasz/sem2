using System;
using System.Collections.Generic;
using System.Text;

namespace gałąź2
{
    class podzbior
    {
        private List<punkt> punkty;
        private List<linia> galaz;
        private punkt kozen;
        private int koszt;

        public podzbior(List<punkt> lista)
        {
            punkty = new List<punkt>(lista);
            policzKozen();            
            koszt = 0;
            galaz = new List<linia>();
            if (punkty.Count == 2)
            {
                
                dodajLinie(punkty[0], kozen);
                dodajLinie(punkty[1], kozen);
                foreach (linia l in galaz)
                {
                    koszt = koszt + l.dlugosc();
                }
            }
            if(punkty.Count > 2)
            {
                foreach(punkt p in punkty)
                {
                    List<punkt> tmp = new List<punkt>(punkty);
                    tmp.Remove(p);
                    podzbior mniejszy = Program.szukaj(tmp);
                    if (koszt == 0)
                    {
                        galaz = new List<linia>(mniejszy.dajGalaz());
                        punkt malyKozen = mniejszy.dajKozen();
                        dodajLinie(malyKozen, kozen);
                        dodajLinie(p, kozen);
                        foreach (linia l in galaz)
                        {
                            koszt = koszt + l.dlugosc();
                        }
                    }
                    else
                    {
                        List<linia> staraGalonz = new List<linia>(galaz);
                        galaz = new List<linia>(mniejszy.dajGalaz());
                        punkt malyKozen = mniejszy.dajKozen();
                        dodajLinie(malyKozen, kozen);
                        dodajLinie(p, kozen);
                        int nowyKoszt = 0;
                        foreach (linia l in galaz)
                        {
                            nowyKoszt = nowyKoszt + l.dlugosc();
                        }
                        if (nowyKoszt < koszt)
                        {
                            koszt = nowyKoszt;
                        }
                        else
                        {
                            galaz = new List<linia>(staraGalonz);
                        }
                    }
                    
                }
            }
        }

        public List<linia> dajGalaz()
        {
            return galaz;
        }

        public punkt dajKozen()
        {
            return kozen;
        }

        public void ukozen()
        {
            punkt zero = new punkt(0, 0);
            dodajLinie(zero, kozen);
        }

        public bool czyTo(List<punkt> lista)
        {
            if (lista.Count == punkty.Count)
            {
                foreach(punkt p in lista)
                {
                    if (punkty.Contains(p) == false) return false;
                }
            }
            else
            {
                return false;
            }
            return true;
        }

        private void policzKozen()
        {
            int x = punkty[0].dajX();
            int y = punkty[0].dajY();
            foreach(punkt p in punkty)
            {
                if (p.dajX() < x) x = p.dajX();
                if (p.dajY() < y) y = p.dajY();
            }
            kozen = new punkt(x, y);
        }

        public void dodajLinie(punkt p1, punkt p2)
        {
            if (p1.dajX() == p2.dajX() && p1.dajY() == p2.dajY())
            {
                return;
            }

            if (p1.dajX() == p2.dajX() || p1.dajY() == p2.dajY())
            {
                galaz.Add(new linia(p1, p2));
                return;
            }

            punkt tmp = new punkt(Math.Max(p1.dajX(), p2.dajX()), Math.Min(p1.dajY(), p2.dajY()));
            dodajLinie(p1, tmp);
            dodajLinie(p2, tmp);
        }
    }
}
