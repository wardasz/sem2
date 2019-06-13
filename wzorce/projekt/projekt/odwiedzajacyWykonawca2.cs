﻿using System;
using System.Collections.Generic;
using System.Text;

namespace projekt
{
    class odwiedzajacyWykonawca2 : Iodwiedzajacy
    {
        private int materialy;
        private int materialyStart;

        public odwiedzajacyWykonawca2(int a)
        {
            materialy = a;
            materialyStart = a;
        }

        public void odwiedz(pojazd poj)
        {
            czolg cz = poj as czolg;
            while(cz.czyGotowe() == false && materialy > 0)
            {
                materialy--;
                cz.montuj();
            }

        }
        public int dajWynik()
        {
            Console.WriteLine("Wykonano " + (materialyStart - materialy) + " operacji montażowych, " + materialy + " zestawów części zwrócono do magazynu");
            return materialy;
        }
    }
}