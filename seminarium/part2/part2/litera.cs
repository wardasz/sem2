using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace part2
{
    public class litera
    {
        private char znak;
        private int wystopienia;
        private double procent;

        public litera(char a)
        {
            znak = a;
            wystopienia = 0;
            procent = 0;
        }

        public char dajLitere()
        {
            return znak;
        }

        public int ileRazy()
        {
            return wystopienia;
        }

        public double jakiProcent()
        {
            return procent;
        }

        public void podbij()
        {
            wystopienia++;
        }

        public void zeruj()
        {
            wystopienia = 0;
        }

        public void policzProcent(int suma)
        {
            procent = (double)wystopienia / (double)suma;
        }

        public void napisz()
        {
            if(wystopienia>0) Console.WriteLine(znak + ": " + wystopienia + " - " + (procent*100) + "%");
        }
    }
}
