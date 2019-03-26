using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace singletonTesty
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void dwojeDzieci()
        {
            var log1 = singleton.logerMlody1.dajLogera;
            var log2 = singleton.logerMlody2.dajLogera;

            Assert.AreSame(log1, log2);
        }

        [TestMethod]
        public void synZOjcem()
        {
            var log1 = singleton.logerMlody1.dajLogera;
            var log2 = singleton.logerStary1.dajLogera;

            Assert.AreSame(log1, log2);
        }

        [TestMethod]
        public void synZWujem()
        {
            var log1 = singleton.logerMlody1.dajLogera;
            var log2 = singleton.logerStary2.dajLogera;

            Assert.AreNotSame(log1, log2);
        }

        [TestMethod]
        public void starzyBracia()
        {
            var log1 = singleton.logerStary1.dajLogera;
            var log2 = singleton.logerStary2.dajLogera;

            Assert.AreNotSame(log1, log2);
        }
    }
}
