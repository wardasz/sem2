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
    class fabrykaCzolgow
    {
        private static fabrykaCzolgow instancja;
        protected fabrykaCzolgow() { }

        public static fabrykaCzolgow dajFabryke()
        {
            if (instancja == null)
            {
                instancja = new fabrykaCzolgow();
            }
            return instancja;
        }

        public czolg.czolg dajCzolg(string nazwa)
        {
            switch (nazwa)
            {
                case "Abrams":
                    return new Abrams();
                case "T95":
                    return new T95();
                case "Leclerc":
                    return new Leclerc();
                case "Leopard":
                    return new Leopard();
                case "Merkava":
                    return new Merkava();
                default:
                    return null;
            }
        }
    }
}
