using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace kDrzewa
{
    class Program
    {
        static void Main(string[] args)
        {
            var s = new FileInfo(Directory.GetCurrentDirectory());
            var s2 = s.Directory.Parent.Parent;
            String s3 = s2.ToString() + "\\dane.csv";

            List<punkt> punkty = new List<punkt>();
            punkt dodawany;

            using (var reader = new StreamReader(s3))
            {
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var values = line.Split(',');

                    dodawany = new punkt(Convert.ToInt32(values[0]), Convert.ToInt32(values[1]));
                    punkty.Add(dodawany);
                }
            }

            foreach(punkt p in punkty)
            {
                p.napisz();
            }

            lisc kozen = buduj(punkty, 0);
            //kozen.napisz();

            int x1;
            int x2;
            int y1;
            int y2;
            Console.WriteLine("Podaj dolną granicę zakresu na osi X");
            x1 = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Podaj górną granicę zakresu na osi X");
            x2 = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Podaj dolną granicę zakresu na osi Y");
            y1 = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Podaj górną granicę zakresu na osi Y");
            y2 = Convert.ToInt32(Console.ReadLine());

            zapytanie(kozen, x1, x2, y1, y2);

            Console.ReadKey();
        }

        static lisc buduj(List<punkt> punkty, int d)
        {
            if (punkty.Count == 1)
            {
                lisc tmp = new lisc(d, 1, punkty.ElementAt(0));
                return tmp;
            }
            else
            {
                if(d%2 == 1)
                {   //nieparzyste
                    List<punkt> pol1 = new List<punkt>();
                    List<punkt> pol2 = new List<punkt>();
                    punkty.Sort((a, b) => (a.porownajY(b)));
                    int ile = punkty.Count / 2;
                    int licznik = 0;
                    int poziom;
                    foreach(punkt p in punkty)
                    {
                        if (licznik < ile) pol1.Add(p);
                        else pol2.Add(p);
                        licznik++;
                    }
                    poziom =  pol1.Last().dajY();

                    /*
                    Console.WriteLine("Pierwsza polowa");
                    foreach (punkt p in pol1)
                    {
                        p.napisz();
                    }
                    Console.WriteLine("Druga polowa");
                    foreach (punkt p in pol2)
                    {
                        p.napisz();
                    }
                    Console.WriteLine("Pozioma linia na " + poziom);
                    */

                    lisc tmp = new lisc(d, 3, poziom);
                    tmp.podepnijNaLewo(buduj(pol1, d + 1));
                    tmp.podepnijNaPrawo(buduj(pol2, d + 1));
                    return tmp;
                }
                else
                {   //parzyste
                    List<punkt> pol1 = new List<punkt>();
                    List<punkt> pol2 = new List<punkt>();
                    punkty.Sort((a, b) => (a.porownajX(b)));
                    int ile = punkty.Count / 2;
                    int licznik = 0;
                    int pion;
                    foreach (punkt p in punkty)
                    {
                        if (licznik < ile) pol1.Add(p);
                        else pol2.Add(p);
                        licznik++;
                    }
                    pion = pol1.Last().dajX();
                    /*
                    Console.WriteLine("Pierwsza polowa");
                    foreach (punkt p in pol1)
                    {
                        p.napisz();
                    }
                    Console.WriteLine("Druga polowa");
                    foreach (punkt p in pol2)
                    {
                        p.napisz();
                    }
                    Console.WriteLine("Pionowa linia na " + pion);
                    */

                    lisc tmp = new lisc(d, 2, pion);
                    tmp.podepnijNaLewo(buduj(pol1, d + 1));
                    tmp.podepnijNaPrawo(buduj(pol2, d + 1));
                    return tmp;
                }
            }
        }

        static void zapytanie(lisc kozen, int x1, int x2, int y1, int y2)
        {
            int typ = kozen.dajTyp();
            switch (typ)
            {
                case 1:
                    int x = kozen.dajPunkt().dajX();
                    int y = kozen.dajPunkt().dajY();
                    if (x >= x1 && x <= x2 && y >= y1 && y <= y2) Console.WriteLine("Punkt (" + x + "," + y + ") leży w obszarze zapytania.");
                    break;
                case 2:
                    int pion = kozen.dajPoziom();
                    if (pion >= x1) zapytanie(kozen.dajLewego(), x1, x2, y1, y2);
                    if (pion <= x2) zapytanie(kozen.dajPrawego(), x1, x2, y1, y2);
                    break;
                case 3:                   
                    int poziom = kozen.dajPoziom();
                    if (poziom >= y1) zapytanie(kozen.dajLewego(), x1, x2, y1, y2);
                    if (poziom <= y2) zapytanie(kozen.dajPrawego(), x1, x2, y1, y2);
                    break;
            }
        }
    }
}
