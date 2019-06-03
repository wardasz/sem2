using System;
using System.Collections.Generic;
using System.IO;

namespace sumy
{
    class Program
    {
        static void Main(string[] args)
        {
            List<podzbior> podzbiory = new List<podzbior>();
            List<skladnik> skladniki = new List<skladnik>();
            int limit;
            
            var s = new FileInfo(Directory.GetCurrentDirectory());
            var s2 = s.Directory.Parent.Parent;
            String sciezka = s2.ToString() + "\\dane.csv";
           
            bool pierwsza = true;
            skladnik tmp;

            using (var reader = new StreamReader(sciezka))
            {
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    if (pierwsza == true)
                    {
                        limit = Convert.ToInt32(line);
                        pierwsza = false;
                    }
                    else
                    {
                        tmp = new skladnik(Convert.ToInt32(line));
                        skladniki.Add(tmp);
                    }
                }
            }

            int n = skladniki.Count;
            skladniki.Sort((a, b) => (a.porownaj(b)));
            foreach(skladnik i in skladniki)
            {
                Console.WriteLine(i.dajWartosc() + "  " + i.GetHashCode());
            }

            podzbior start = new podzbior(0);
            for(int i=0; i<n; i++)
            {
                podzbior a = new podzbior(podzbiory[i].dajListe());
                podzbior b = new podzbior(podzbiory[i].dajListe());
                b.plusik(skladniki[i + 1].dajWartosc());
                //podzbior kolejny = 
            }



            Console.ReadKey();
        }
    }
}
