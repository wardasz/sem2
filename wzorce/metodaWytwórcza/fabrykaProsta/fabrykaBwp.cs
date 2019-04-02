using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using metodaWytworcza.czolg;
using metodaWytworcza.dziala;
using metodaWytworcza.bwp;
using metodaWytworcza.apc;

namespace metodaWytworcza
{
    class fabrykaBwp
    {
        private static fabrykaBwp instancja;
        protected fabrykaBwp() { }

        public static fabrykaBwp dajFabryke()
        {
            if (instancja == null)
            {
                instancja = new fabrykaBwp();
            }
            return instancja;

        }
        public bwp.bwp dajBewupa(string nazwa)
        {
            switch (nazwa)
            {
                case "AMTRC":
                    return new AMTRC();
                case "BMP1":
                    return new BMP1();
                case "Bradley":
                    return new Bradley();
                case "Darlo":
                    return new Darlo();
                case "Warior":
                    return new Warior();
                default:
                    return null;
            }
        }
    }
}
