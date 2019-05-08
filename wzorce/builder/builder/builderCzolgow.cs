using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace builder
{
    public abstract class builderCzolgow
    {
        protected czolg.czolg produkt;
        public czolg.czolg Czolg { get => produkt; }
        public abstract czolg.czolg nowy();

        public abstract builderCzolgow ustawNazwe();
        public abstract builderCzolgow ustawKaliber();
        public abstract builderCzolgow ustawPancerz();

        public static implicit operator czolg.czolg(builderCzolgow builder)
        {
            return builder.ustawNazwe().ustawKaliber().ustawPancerz().Czolg;
        }
    }
}
