﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace part2
{
    class Program
    {
        //public static String adresTekst = "D:\\studia\\magisterka\\sem2\\seminarium\\oczyszczony.txt";
        //public static String adresDane = "D:\\studia\\magisterka\\sem2\\seminarium\\rejestr.txt";

        public static String adresTekst = "D:\\studia\\sem2\\seminarium\\oczyszczony.txt";
        public static String adresDane = "D:\\studia\\sem2\\seminarium\\rejestr.txt";

        public static String tekst = "";
        public static List<litera> litery = new List<litera>();

        static void Main(string[] args)
        {
            
            litery.Add(new litera('a'));
            litery.Add(new litera('ą'));
            litery.Add(new litera('b'));
            litery.Add(new litera('c'));
            litery.Add(new litera('ć'));
            litery.Add(new litera('d'));
            litery.Add(new litera('e'));
            litery.Add(new litera('ę'));
            litery.Add(new litera('f'));
            litery.Add(new litera('g'));
            litery.Add(new litera('h'));
            litery.Add(new litera('i'));
            litery.Add(new litera('j'));
            litery.Add(new litera('k'));
            litery.Add(new litera('l'));
            litery.Add(new litera('ł'));
            litery.Add(new litera('m'));
            litery.Add(new litera('n'));
            litery.Add(new litera('ń'));
            litery.Add(new litera('o'));
            litery.Add(new litera('ó'));
            litery.Add(new litera('p'));
            litery.Add(new litera('r'));
            litery.Add(new litera('s'));
            litery.Add(new litera('ś'));
            litery.Add(new litera('t'));
            litery.Add(new litera('u'));
            litery.Add(new litera('w'));
            litery.Add(new litera('y'));
            litery.Add(new litera('z'));
            litery.Add(new litera('ż'));
            litery.Add(new litera('ź'));

            Console.WriteLine("Witaj w dziwnym huffmanowskim programiku made by wardasz");
            while (true)
            {
                menu();
                int wybor = Convert.ToInt32(Console.ReadLine());
                Console.Clear();
                switch (wybor)
                {
                    case 1:
                        wypiszTekst();
                        break;
                    case 2:
                        wypiszLitery();
                        break;
                    case 3:
                        wczytajTekst();
                        break;
                    case 4:
                        policz();
                        break;
                    case 5:
                        zapisz();
                        break;
                    case 6:
                        wczytajTekst();
                        policz();
                        zapisz();
                        break;
                    case 0:
                        return;                     
                    default:
                        Console.WriteLine("Niezrozumiano polecenia");
                        break;
                }
                Console.WriteLine();
                Console.WriteLine();
            }
        }

        static void menu()
        {
            Console.WriteLine("Co chcesz zrobić? (wpisz cyfrę)");
            Console.WriteLine("1-Wypisz wczytany tekst");
            Console.WriteLine("2-Wypisz listę liter");
            Console.WriteLine("3-Wczytaj tekst");
            Console.WriteLine("4-Policz znaki w tekście");
            Console.WriteLine("5-Zapisz znaki do pliku");
            Console.WriteLine("6-Wombo combo");
            Console.WriteLine("0-zamknij program");
        }

        public static void wypiszTekst()
        {
            Console.WriteLine(tekst);
        }

        public static void wypiszLitery()
        {
            foreach (litera l in litery)
            {
                l.napisz();
            }
        }

        public static void wczytajTekst()
        {
            tekst = System.IO.File.ReadAllText(adresTekst);
        }

        public static void policz()
        {
            foreach (char znak in tekst)
            {
                litera l = litery.Select(n => n).Where(x => x.dajLitere() == znak).FirstOrDefault();
                if (l != null)
                {
                    l.podbij();
                }
            }
            litery.Sort((b, a) => (a.ileRazy().CompareTo(b.ileRazy())));
            int suma = 0;
            foreach (litera l in litery)
            {
                suma = suma + l.ileRazy();
            }
            foreach (litera l in litery)
            {
                l.policzProcent(suma);
            }
        }

        public static void zapisz()
        {
            Console.WriteLine("Podaj opis:");
            string opis = Console.ReadLine();
            foreach (litera l in litery)
            {
                opis = opis + " " + l.dajLitere() + "-" + l.jakiProcent();
            }
            using (StreamWriter writer = new StreamWriter(adresDane, true))
            {
                writer.WriteLine(opis);

            }
        }
    }
}
