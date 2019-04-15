using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace fabrykaAbstrakcyjna
{
    class Program
    {
        static void Main(string[] args)
        {
            czolg.czolg poj1 = fabrykaEU.dajFabryke().zrobCzolg();
            poj1.ostrzelaj();
            poj1.dostan();

            bwp.bwp poj2 = fabrykaUS.dajFabryke().zrobBwp();
            poj2.ostrzelaj();
            poj2.przełam();            

            Console.ReadKey();


        }
    }
}
