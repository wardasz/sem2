using System;
using System.Collections.Generic;
using System.IO;

namespace grafy1
{
    class Program
    {

        static void Main(string[] args)
        {
            List<int> x = new List<int>();
            List<int> y = new List<int>();
          
            var s = new FileInfo(Directory.GetCurrentDirectory());
            var s2 = s.Directory.Parent.Parent;
            String sciezka = s2.ToString() + "\\dane.csv";
            
            using (var reader = new StreamReader(sciezka))
            {            
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var values = line.Split(',');

                    x.Add(Convert.ToInt32(values[0]));
                    y.Add(Convert.ToInt32(values[1]));
                }
            }
            int ile = x.Count;

            if (ile < 3)
            {
                Console.WriteLine("Za mało wieszchołków by stworzyć wielokąt.");
                Console.ReadKey();
                return;
            }

            int dol=y[0];
            int gora=y[0];
            for(int i = 1; i<ile; i++)
            {
                if (y[i] > gora) { gora = y[i]; }
                if (y[i] < dol) { dol = y[i]; }
            }

            for (int i = 0; i < ile; i++)
            {
                int poprzedni = i - 1;
                if (poprzedni == -1) { poprzedni = ile - 1; }
                int nastepny = i + 1;
                if (nastepny == ile) { nastepny = 0; }
                
                if (y[i] == y[poprzedni]) { poprzedni--; }
                if (y[i] == y[nastepny]) { nastepny++; }
                if (poprzedni == -1) { poprzedni = ile - 1; }
                if (nastepny == ile) { nastepny = 0; }
 
                int det = x[poprzedni] * y[i] + y[poprzedni] * x[nastepny] + x[i] * y[nastepny] - x[poprzedni] * y[nastepny] - y[poprzedni] * x[i] - y[i] * x[nastepny];

                if (det < 0)
                {
                    if (y[i] < y[nastepny] && y[i] < y[poprzedni] && y[i] < gora) { gora = y[i]; }
                    if (y[i] > y[nastepny] && y[i] > y[poprzedni] && y[i] > dol) { dol = y[i]; }
                }
            }

            if (gora > dol)
            {
                Console.WriteLine("Jądro istnieje, jego górna granica to " + gora + " a dolna wynosi " + dol);
            }
            else
            {
                if (gora == dol)
                {
                    Console.WriteLine("Jądro istnieje, ale zawiera się w pasie o zerowej grubości. Znajduje się on na wysokości " + gora);
                }
                else
                {
                    Console.WriteLine("Jądro nie istnieje");
                }
            }

            Console.ReadKey();
        }

    }
}
