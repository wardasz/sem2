﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace builder
{
    class builderAbrams : builderCzolgow
    {
        public builderAbrams()
        {
            produkt = nowy();
        }

        public czolg.czolg dajCzolg()
        {
            return produkt;
        }

        public override czolg.czolg nowy()
        {
            return new czolg.czolg();
        }

        public override builderCzolgow ustawNazwe()
        {
            produkt.nazwa = "Abrams";
            return this;
        }

        public override builderCzolgow ustawKaliber()
        {
            produkt.kaliber = 120;
            return this;
        }

        public override builderCzolgow ustawPancerz()
        {
            produkt.pancerz = 100;
            return this;
        }

    }
}
