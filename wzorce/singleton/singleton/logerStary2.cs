using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace singleton
{
    public class logerStary2 : logerBaza<logerStary2>
    {
        new public void loguj()
        {
            Console.WriteLine("ociec dwa pisze");
        }
    }
}
