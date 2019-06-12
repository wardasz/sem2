using System;
using System.Collections.Generic;
using System.Text;

namespace projekt
{
    public class liniaMontazowa
    {
        public liniaMontazowa()
        {

        }

        public void montuj(zamowienie z, int ile)
        {
            Iodwiedzajacy kontroler = new odwiedzajacyWykonawca(ile);
            z.akceptuj(kontroler);
        }
    }
}
