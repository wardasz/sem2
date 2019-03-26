using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace paraPunktow2
{
    class Program
    {
        static void Main(string[] args)
        {
            var s = new FileInfo(Directory.GetCurrentDirectory());
            var s2 = s.Directory.Parent.Parent;
            String s3 = s2.ToString() + "\\dane.csv";


            listy S = new listy();
            punkt dodawany;
            
            using (var reader = new StreamReader(s3))
            {
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var values = line.Split(',');

                    dodawany = new punkt(Convert.ToInt32(values[0]), Convert.ToInt32(values[1]));
                    S.dodaj(dodawany);
                }
            }

            S.sortuj();
            List<punkt> wynik = policz(S);
            punkt a = wynik.ElementAt(0);
            punkt b = wynik.ElementAt(1);
            double dystans = a.dystans(b);
            Console.WriteLine("Najbliższa para: ");
            a.napisz();
            b.napisz();
            Console.WriteLine("Dystan pomiędzy nimi równy jest " + Math.Sqrt(dystans));

            Console.ReadKey();
        }


        public static List<punkt> policz(listy S)
        {
            List<punkt> Sx = S.dajSx();
            List<punkt> Sy = S.dajSy();
            int ile = Sx.Count();
            if (ile < 5)
            {
                punkt a = Sx.ElementAt(0);
                punkt b = Sx.ElementAt(1);
                double min = a.dystans(b);
                for(int x = 0; x<Sx.Count(); x++)
                {
                    for(int y = x+1; y < Sx.Count(); y++)
                    {
                        double dys = Sx.ElementAt(x).dystans(Sx.ElementAt(y));
                        if (dys < min)
                        {
                            min = dys;
                            a = Sx.ElementAt(x);
                            b = Sx.ElementAt(y);
                        }
                    }
                }
                List<punkt> wynik = new List<punkt>();
                wynik.Add(a);
                wynik.Add(b);
                return wynik;
            }
            else
            {
                listy S1 = new listy();
                listy S2 = new listy();

                int l;
                for (int x = 0; x < ile; x++)
                {
                    punkt p = Sx.ElementAt(x);
                    if (x < ile / 2)
                    {
                        S1.dodajX(p);
                        p.ustawPrzed(true);
                    }
                    else
                    {
                        S2.dodajX(p);
                        p.ustawPrzed(false);
                    }
                }
                for (int x = 0; x < ile; x++)
                {
                    punkt p = Sy.ElementAt(x);
                    if (p.czyPrzed()==true)
                    {
                        S1.dodajY(p);
                    }
                    else
                    {
                        S2.dodajY(p);
                    }
                }
                Sx = S1.dajSx();
                ile = Sx.Count();
                ile -= 1;
                punkt ostatni = Sx.ElementAt(ile);
                l = ostatni.dajX();

                List<punkt> wynik1 = policz(S1);   //najbliższe pary w podzbiorach
                List<punkt> wynik2 = policz(S2);
                double dystans1 = wynik1.ElementAt(0).dystans(wynik1.ElementAt(1));
                double dystans2 = wynik2.ElementAt(0).dystans(wynik2.ElementAt(1));
                double minDystans;   //dystans między mniejszą parą
                List<punkt> minPara;   //mniejsza para
                if (dystans1 < dystans2)
                {
                    minDystans = dystans1;
                    minPara = wynik1;
                }
                else
                {
                    minDystans = dystans2;
                    minPara = wynik2;
                }

                //tworzenie list punktów w pasie przy prostej            
                listy S1znaczek = new listy();
                listy S2znaczek = new listy();
                List<punkt> tmp = S1.dajSy();
                foreach(punkt p in tmp)
                {
                    double odleglosc = p.dajX() - l;
                    if (odleglosc < 0) odleglosc *= -1;
                    if(odleglosc<= minDystans)
                    {
                        S1znaczek.dodaj(p);
                    }
                }
                tmp = S2.dajSy();
                foreach (punkt p in tmp)
                {
                    double odleglosc = p.dajX() - l;
                    if (odleglosc < 0) odleglosc *= -1;
                    if (odleglosc <= minDystans)
                    {
                        S2znaczek.dodaj(p);
                    }
                }

                List<punkt> tmp1 = S1znaczek.dajSy();
                List<punkt> tmp2 = S2znaczek.dajSy();
                foreach (punkt p in tmp1)
                {
                    int licznik = 0;
                    foreach(punkt P in tmp2)
                    {
                        if (P.dajY() >= p.dajY())
                        {
                            licznik += 1;
                            if (p.dystans(P) < minDystans)
                            {
                                minDystans = p.dystans(P);
                                minPara = new List<punkt>();
                                minPara.Add(p);
                                minPara.Add(P);
                            }
                            if (licznik >= 4)
                            {
                                break;
                            }
                        }
                    }
                }
                foreach (punkt p in tmp2)
                {
                    int licznik = 0;
                    foreach (punkt P in tmp1)
                    {
                        if (P.dajY() >= p.dajY())
                        {
                            licznik += 1;
                            if (p.dystans(P) < minDystans)
                            {
                                minDystans = p.dystans(P);
                                minPara = new List<punkt>();
                                minPara.Add(p);
                                minPara.Add(P);
                            }
                            if (licznik >= 4)
                            {
                                break;
                            }
                        }
                    }
                }
                return minPara;
            }
        }
    }
}
