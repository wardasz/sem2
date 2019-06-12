using System;
using System.Collections.Generic;
using System.Text;

namespace projekt
{
    public class posrednik
    {
        private bioroZamowien bioro;
        private liniaMontazowa linia;
        private magazyn mag;

        public posrednik()
        {
            bioro = new bioroZamowien();
            linia = new liniaMontazowa();
            mag = new magazyn();
        }

        public void dostawa(int i){
            mag.dostawa(i);
        }

        public void zamowienie(string s, int i)
        {
            bioro.zamow(s, i);
        }

        public void praca(string s, int i)
        {
            if (mag.czyStarczy(i)==false)
            {
                loger log = loger.dajInstancje();
                log.loguj("Za mało cześci w magazynie by wykonać żądaną pracę");
                Console.WriteLine("Brakuje części");
                return;
            }
            zamowienie z = bioro.znajdzZmowienie(s);
            if (z != null)
            {
                mag.zapotrzebowanie(i);
                Iodwiedzajacy wykonawca = new odwiedzajacyWykonawca(i);
                z.akceptuj(wykonawca);
                mag.dostawa(wykonawca.dajWynik());
            }
        }

        public void kontrola()
        {
            int zapotrzebowanie = bioro.kontrola();
            if (mag.czyStarczy(zapotrzebowanie) == false)
            {
                loger log = loger.dajInstancje();
                log.loguj("W magazynie jest za mało części by wykonać wszystkie zamówienia");
                Console.WriteLine("W magazynie jest za mało części by wykonać wszystkie zamówienia");
            }
            else
            {
                Console.WriteLine("W magazynie jest dość części by wykonać wszystkie zamówienia");
            }
        }
    }
}
