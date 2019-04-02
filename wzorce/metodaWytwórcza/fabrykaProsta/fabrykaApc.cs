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
    class fabrykaApc
    {
        private static fabrykaApc instancja;
        protected fabrykaApc() { }

        public static fabrykaApc dajFabryke()
        {
            if (instancja == null)
            {
                instancja = new fabrykaApc();
            }
            return instancja;
        }

        public apc.apc dajTransporter(string nazwa)
        {
            switch (nazwa)
            {
                case "BRT60":
                    return new BRT60();
                case "LAV":
                    return new LAV();
                case "M60":
                    return new M60();
                case "Rosomak":
                    return new Rosomak();
                case "Streaker":
                    return new Streaker();
                default:
                    return null;
            }
        }
    }
}
