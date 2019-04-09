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

            List<punkt> punktyX = new List<punkt>();
            List<punkt> punktyY = new List<punkt>();
            punkt dodawany;

            using (var reader = new StreamReader(s3))
            {
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var values = line.Split(',');

                    dodawany = new punkt(Convert.ToInt32(values[0]), Convert.ToInt32(values[1]));
                    punktyX.Add(dodawany);
                    punktyY.Add(dodawany);
                }
            }

            foreach(punkt p in punktyX)
            {
                p.napisz();
            }

            punktyX.Sort((a, b) => (a.porownajX(b)));
            punktyY.Sort((a, b) => (a.porownajY(b)));
            lisc kozen = buduj(punktyX, punktyY, 0);
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

        static lisc buduj(List<punkt> punktyX, List<punkt> punktyY, int d)
        {
            if (punktyX.Count == 1)
            {
                lisc tmp = new lisc(d, 1, punktyX.ElementAt(0));
                return tmp;
            }
            else
            {
                if(d%2 == 1)
                {   //nieparzyste
                    List<punkt> pol1X = new List<punkt>();
                    List<punkt> pol1Y = new List<punkt>();
                    List<punkt> pol2X = new List<punkt>();
                    List<punkt> pol2Y = new List<punkt>();
                    int ile = punktyY.Count / 2;
                    int licznik = 0;
                    int poziom;
                    foreach(punkt p in punktyY)
                    {
                        if (licznik < ile)
                        {
                            pol1Y.Add(p);
                            p.czyPierwsza(true);
                        }
                        else
                        {
                            pol2Y.Add(p);
                            p.czyPierwsza(false);
                        }
                        licznik++;
                    }
                    foreach(punkt p in punktyX)
                    {
                        if (p.czyPierwsza() == true)
                        {
                            pol1X.Add(p);
                        }
                        else
                        {
                            pol2X.Add(p);
                        }
                    }
                    poziom = pol1Y.Last().dajY();

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
                    tmp.podepnijNaLewo(buduj(pol1X, pol1Y, d + 1));
                    tmp.podepnijNaPrawo(buduj(pol2X, pol2Y, d + 1));
                    return tmp;
                }
                else
                {   //parzyste
                    List<punkt> pol1X = new List<punkt>();
                    List<punkt> pol1Y = new List<punkt>();
                    List<punkt> pol2X = new List<punkt>();
                    List<punkt> pol2Y = new List<punkt>();
                    int ile = punktyX.Count / 2;
                    int licznik = 0;
                    int pion;
                    foreach (punkt p in punktyX)
                    {
                        if (licznik < ile)
                        {
                            pol1X.Add(p);
                            p.czyPierwsza(true);
                        }
                        else
                        {
                            pol2X.Add(p);
                            p.czyPierwsza(false);
                        }
                        licznik++;
                    }
                    foreach (punkt p in punktyY)
                    {
                        if (p.czyPierwsza() == true)
                        {
                            pol1Y.Add(p);
                        }
                        else
                        {
                            pol2Y.Add(p);
                        }
                    }
                    pion = pol1X.Last().dajX();
                    
                    /*
                    Console.WriteLine("Pierwsza polowa");
                    foreach (punkt p in pol1X)
                    {
                        p.napisz();
                    }
                    Console.WriteLine("Druga polowa");
                    foreach (punkt p in pol2X)
                    {
                        p.napisz();
                    }
                    Console.WriteLine("Pionowa linia na " + pion);
                    */

                    lisc tmp = new lisc(d, 2, pion);
                    tmp.podepnijNaLewo(buduj(pol1X, pol1Y, d + 1));
                    tmp.podepnijNaPrawo(buduj(pol2X, pol2Y, d + 1));
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
