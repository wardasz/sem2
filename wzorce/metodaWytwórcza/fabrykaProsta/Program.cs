using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using metodaWytworcza;


namespace metodaWytworcza
{
    class Program
    {
        static void Main(string[] args)
        {
            Ipojazd poj1 = fabrykaCzolgow.dajFabryke().stwoz("Abrams");
            poj1.ostrzelaj();
            czolg.czolg poj2 = (czolg.czolg)fabrykaCzolgow.dajFabryke().stwoz("Abrams");
            poj2.ostrzelaj();
            poj2.dostan();
            Ipojazd poj3 = fabrykaBwp.dajFabryke().stwoz("Darlo");
            poj3.ostrzelaj();
            Console.ReadKey();
        }
    }
}
