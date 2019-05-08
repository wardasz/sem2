using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace builder
{
    class Program
    {
        static void Main(string[] args)
        {
            czolg.czolg poj1;
            var fabryka = new fabrykaCzolgow();
            poj1 = fabryka.zbuduj(new builderAbrams());
            poj1.dostan();
            poj1.ostrzelaj();

            licz(10000);
            Console.ReadKey();
        }

        static void licz(int x)
        {
            Console.WriteLine();
            Console.WriteLine();
            DateTime poczatek = DateTime.Now;
            var fabryka = new fabrykaCzolgow();
            for (int y = 0; y < x; y++)
            {
                czolg.czolg poj = fabryka.zbuduj(new builderAbrams());
            }
            DateTime koniec = DateTime.Now;
            Console.WriteLine("Czas trwania dla " + x + " obiektów wyniósł " + (koniec - poczatek));
        }
    }
}
