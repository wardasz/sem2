﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace singleton
{
    public class logerMlody2 : logerStary1
    {
        new public void loguj()
        {
            Console.WriteLine("syn dwa pisze");
        }
    }
}
