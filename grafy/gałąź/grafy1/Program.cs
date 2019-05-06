using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace gałąź
{
    class Program
    {
        public static List<linia> galaz;
        static void Main(string[] args)
        {
          
            var s = new FileInfo(Directory.GetCurrentDirectory());
            var s2 = s.Directory.Parent.Parent;
            String sciezka = s2.ToString() + "\\dane.csv";
            List<punkt> punkty = new List<punkt>();
            List<punkt> skrajne = new List<punkt>();
            List<kandydat> kandydaci = new List<kandydat>();
            galaz = new List<linia>();
            punkt tmp;
            
            using (var reader = new StreamReader(sciezka))
            {            
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var values = line.Split(',');

                    tmp = new punkt(Convert.ToInt32(values[0]), Convert.ToInt32(values[1]));
                    punkty.Add(tmp);
                }
            }

            punkty.Sort((a, b) => (a.porownaj(b)));

            while (punkty.Count > 1)
            {
                int miotla = 0;
                skrajne.Clear();
                kandydaci.Clear();

                foreach (punkt pu in punkty)
                {
                    if (pu.dajY() >= miotla)
                    {
                        skrajne.Add(pu);
                        miotla = pu.dajY();
                    }
                }

                skrajne.Sort((a, b) => (a.porownaj(b)));

                for (int i = 1; i < skrajne.Count(); i++)
                {
                    kandydaci.Add(new kandydat(skrajne.ElementAt(i - 1), skrajne.ElementAt(i)));
                }

                kandydaci.Sort((a, b) => (a.porownaj(b)));
                kandydat wybrany = kandydaci.ElementAt(0);
                punkt p = wybrany.dajP();
                punkt q = wybrany.dajQ();
                punkty.Remove(p);
                punkty.Remove(q);
                punkt pq = new punkt(wybrany.dajX(), wybrany.dajY());

                bool dodano = false;
                for (int i = 0; i < punkty.Count(); i++)
                {
                    if (pq.porownaj(punkty.ElementAt(i)) == -1)
                    {
                        punkty.Insert(i, pq);
                        dodano = true;
                        break;
                    }
                }
                if (dodano == false)
                {
                    punkty.Add(pq);
                }
                dodajLinie(p, pq);
                dodajLinie(q, pq);
            }

            punkt r = new punkt(0, 0);
            dodajLinie(punkty.ElementAt(0), r);

            foreach(linia l in galaz)
            {
                l.napisz();
            }

            Console.ReadKey();
        }

        public static void dodajLinie(punkt p1, punkt p2)
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
