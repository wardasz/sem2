using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace singleton
{
    public class logerStary1 : logerBaza<logerStary1>
    {
        new public void loguj()
        {
            Console.WriteLine("ociec jeden pisze");
        }
    }
}
