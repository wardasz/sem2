using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace wyznaczaniePrzeciec
{
    class Program
    {
        static void Main(string[] args)
        {
            List<zdarzenie> zdazenia = new List<zdarzenie>();
            int ax;
            int ay;
            int bx;
            int by;
            //var s = new FileInfo(Directory.GetCurrentDirectory());
            //var s2 = s.Directory.Parent.Parent;
            //String sciezka = s2.ToString() + "\\dane.csv";

            String sciezka = "C:\\Users\\wardasz\\source\\repos\\wyznaczaniePrzecięć\\wyznaczaniePrzecięć\\dane.csv";
            using (var reader = new StreamReader(sciezka))
            {
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var values = line.Split(',');

                    ax = Convert.ToInt32(values[0]);
                    ay = Convert.ToInt32(values[1]);
                    bx = Convert.ToInt32(values[2]);
                    by = Convert.ToInt32(values[3]);

                    zdarzenie tmp;
                    if(ax == bx)
                    {
                        if (ay > by)
                        {
                            tmp = new zdarzenie(2, ax, ay, by);
                            zdazenia.Add(tmp);
                        }
                        else
                        {
                            tmp = new zdarzenie(2, ax, by, ay);
                            zdazenia.Add(tmp);
                        }
                    }
                    else
                    {
                        if (ax > bx)
                        {
                            tmp = new zdarzenie(3, ax, ay);
                            zdazenia.Add(tmp);
                            tmp = new zdarzenie(1, bx, by);
                            zdazenia.Add(tmp);
                        }
                        else
                        {
                            tmp = new zdarzenie(1, ax, ay);
                            zdazenia.Add(tmp);
                            tmp = new zdarzenie(3, bx, by);
                            zdazenia.Add(tmp);
                        }
                    }
                }
            }

            //napiszListe(zdazenia);
            zdazenia.Sort((a, b) => (a.porownaj(b)));
            //napiszListe(zdazenia);

            zamiataj(zdazenia);





            Console.ReadKey();
        }

        static void napiszListe(List<zdarzenie> lista)
        {
            foreach(zdarzenie z in lista)
            {
                int typ = z.dajTyp();
                int x = z.dajX();
                int y = z.dajY();
                int y2 = z.dajY2();
                switch (typ)
                {
                    case 1:
                        Console.WriteLine("Zdarzenie na X=" + x + " Początek odcinka na wysokosci " + y);
                        break;
                    case 2:
                        Console.WriteLine("Zdarzenie na X=" + x + " Pion na wysokosci " + y + "-" + y2);
                        break;
                    case 3:
                        Console.WriteLine("Zdarzenie na X=" + x + " Koniec odcinka na wysokosci " + y);
                        break;
                }
            }
            Console.WriteLine();
        }

        static void zamiataj(List<zdarzenie> lista)
        {
            List<int> poziomy = new List<int>();
            foreach (zdarzenie z in lista)
            {
                int typ = z.dajTyp();
                int x = z.dajX();
                int y = z.dajY();
                int y2 = z.dajY2();
                switch (typ)
                {
                    case 1:
                        bool dodano = false;
                        for (int i = 0; i < poziomy.Count(); i++)
                        {
                            if (y < poziomy.ElementAt(i))
                            {
                                poziomy.Insert(i, y);
                                dodano = true;
                                break;
                            }
                        }
                        if (dodano == false)
                        {
                            poziomy.Add(y);
                        }
                        break;
                    case 2:
                        foreach (int p in poziomy)
                        {
                            if(p<= y && p >= y2)
                            {
                                Console.WriteLine("Wykryto przecięcie w punkcie (" + x + "," + p + ").");
                            }
                        }
                        break;
                    case 3:
                        foreach (int p in poziomy)
                        {
                            if (p == y)
                            {
                                poziomy.Remove(p);
                                break;
                            }
                        }
                        break;
                }
            }
        }
    }
}
