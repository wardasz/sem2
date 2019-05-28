using System;
using System.Collections.Generic;
using System.IO;

namespace gałąź2
{
    class Program
    {
        public static List<podzbior> policzone;
        static void Main(string[] args)
        {
            policzone = new List<podzbior>();
            var s = new FileInfo(Directory.GetCurrentDirectory());
            var s2 = s.Directory.Parent.Parent;
            String sciezka = s2.ToString() + "\\dane.csv";
            List<punkt> punkty = new List<punkt>();           
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

            List<string> maski = new List<string>();
            for (int x = 1; x <= (Math.Pow(2, punkty.Count) - 1); x++)
            {
                string maska = Convert.ToString(x, 2);
                while (maska.Length < punkty.Count)
                {
                    maska = "0" + maska;
                }
                maski.Add(maska);
            }

            for(int x = 1; x < punkty.Count; x++)
            {
                foreach (string maska in maski)
                {
                    int suma = 0;
                    foreach(char c in maska)
                    {
                        if (c == '1')
                        {
                            suma++;
                        }
                    }
                    if (suma == x)
                    {
                        List<punkt> nowa = new List<punkt>();
                        for (int i = 0; i < punkty.Count; i++)
                        {
                            if (maska[i] == '1')
                            {
                                nowa.Add(punkty[i]);
                            }
                        }
                        podzbior nowy = new podzbior(nowa);
                        policzone.Add(nowy);
                    }
                }
            }
            podzbior wynik = new podzbior(punkty);
            wynik.ukozen();
            List<linia> rozwiazanie = wynik.dajGalaz();

            foreach(linia l in rozwiazanie)
            {
                l.napisz();
            }



            Console.ReadKey();
        }     

        public static podzbior szukaj(List<punkt> punkty)
        {
            foreach(podzbior p in policzone)
            {
                if (p.czyTo(punkty)) return p;
            }
            return null;
        }
    }
}
