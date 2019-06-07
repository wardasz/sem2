using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace projekt
{
    public class loger
    {
        private static loger instancja;

        private loger() { }

        public static loger dajInstancje()
        {       
            if (instancja == null)
            {
                instancja = new loger();
            }
            return instancja;
        }

        public void loguj(string a)
        {
            var s = new FileInfo(Directory.GetCurrentDirectory());
            var s2 = s.Directory.Parent.Parent;
            String sciezka = s2.ToString() + "\\rejestr.txt";

            using (StreamWriter writer = new StreamWriter(sciezka, true))
            {
                writer.WriteLine(a);
            }
        }
    }
}
