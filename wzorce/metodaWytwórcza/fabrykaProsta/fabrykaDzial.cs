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
    class fabrykaDzial
    {
        private static fabrykaDzial instancja;
        protected fabrykaDzial() { }

        public static fabrykaDzial dajFabryke()
        {
            if (instancja == null)
            {
                instancja = new fabrykaDzial();
            }
            return instancja;
        }

        public dziala.dziala dajArtylerie(string nazwa)
        {
            switch (nazwa)
            {
                case "Dana":
                    return new Dana();
                case "Grille":
                    return new Grille();
                case "Hummel":
                    return new Hummel();
                case "Krab":
                    return new Krab();
                case "Panzerhaubica":
                    return new Panzerhaubica();
                default:
                    return null;
            }
        }
    }
}
