using NUnit.Framework;
using MathLib;

namespace MathLib.Tests
{
    public class ArithmeticProgressionTests
    {
        [Test]
        public void TestProgressionElement()
        {
            var progression = new ArithmeticProgression(1, 2);
            Assert.AreEqual(1, progression[1]);
            Assert.AreEqual(3, progression[2]);
            Assert.AreEqual(5, progression[3]);
        }

        [Test]
        public void TestProgressionSum()
        {
            var progression = new ArithmeticProgression(1, 2);
            Assert.AreEqual(25, progression.Sum(5));    
        }
    }
}
