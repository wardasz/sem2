using System;

namespace projekt
{
    class Program
    {
        static void Main(string[] args)
        {
            loger l = loger.dajInstancje();
            l.loguj("jeden");
            loger j = loger.dajInstancje();
            j.loguj("dwa");
            bool czy = l.GetHashCode() == j.GetHashCode();
            l.loguj(czy.ToString());
        }
    }
}
