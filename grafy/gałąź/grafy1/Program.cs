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

            foreach(punkt pu in punkty)
            {
                pu.napisz();
            }

            while (punkty.Count > 1)
            {
                punkt p = punkty.ElementAt(0);
                punkt q = punkty.ElementAt(1);
                punkty.RemoveAt(1);
                punkty.RemoveAt(0);
                punkt pq = new punkt(Math.Min(p.dajX(), q.dajX()), Math.Min(p.dajY(), q.dajY()));

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
            dodajLinie(r, punkty.ElementAt(0));

            foreach (linia l in galaz)
            {
                l.napisz();
            }


            //Console.WriteLine("p i q");
              //  p.napisz();
                //q.napisz();
             //   Console.WriteLine();
              //  foreach (punkt pu in punkty)
               // {
               //     pu.napisz();
              //  }

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
