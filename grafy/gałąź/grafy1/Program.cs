using System;
using System.Collections.Generic;
using System.IO;

namespace grafy1
{
    class Program
    {

        static void Main(string[] args)
        {
          
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

            punkty.Sort((a, b) => (a.porownaj(b)));

            foreach(punkt p in punkty)
            {
                p.napisz();
            }
            

            Console.ReadKey();
        }

    }
}
