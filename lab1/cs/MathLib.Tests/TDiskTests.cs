using NUnit.Framework;
using MathLib;

namespace MathLib.Tests
{
    public class TDiskTests
    {
        [Test]
        public void TestArea()
        {
            var disk = new TDisk(5, 0, 0);
            Assert.AreEqual(Math.PI * 25, disk.Area());
        }

        [Test]
        public void TestIsPointInside()
        {
            var disk = new TDisk(5, 0, 0);
            Assert.IsTrue(disk.IsPointInside(3, 4));  
            Assert.IsFalse(disk.IsPointInside(6, 0));  
        }

        [Test]
        public void TestVolumeForBall()
        {
            var ball = new TBall(3, 0, 0, 0);
            Assert.AreEqual(4.0 / 3.0 * Math.PI * 27, ball.Volume());
        }
    }
}
