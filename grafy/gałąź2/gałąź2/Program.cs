using System;
using System.Collections.Generic;
using System.IO;

namespace gałąź2
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

            while (punkty.Count > 1)
            {
                punkt p = punkty[0];
                punkt q = punkty[1];
                punkt min = new punkt(Math.Min(p.dajX(), q.dajX()), Math.Min(p.dajY(), q.dajY()));

                for (int i = 0; i < punkty.Count; i++)
                {
                    for (int j = 0; j < punkty.Count; j++)
                    {
                        if (i != j)
                        {
                            punkt nowy = new punkt(Math.Min(punkty[i].dajX(), punkty[j].dajX()), Math.Min(punkty[i].dajY(), punkty[j].dajY()));
                            if (nowy.lepszy(min))
                            {
                                min = nowy;
                                p = punkty[i];
                                q = punkty[j];
                            }
                        }
                    }
                }
            
                punkty.Remove(p);
                punkty.Remove(q);
                punkty.Add(min);
                dodajLinie(p, min);
                dodajLinie(q, min);
            }

            punkt r = new punkt(0, 0);
            dodajLinie(punkty[0], r);

            foreach (linia l in galaz)
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
