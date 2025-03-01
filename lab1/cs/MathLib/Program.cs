using System;

namespace MathLib
{
    class Program
    {
        static void Main(string[] args)
        {
            var progression = new ArithmeticProgression(1, -2);
            Console.WriteLine("5th member of the progression: " + progression[-1]);
            Console.WriteLine("first 5 elements sum: " + progression.Sum(5));

            var disk = new TDisk(5, 0, 0);
            Console.WriteLine(disk.ToString());
            Console.WriteLine("Disk area:" + disk.Area());
            Console.WriteLine("is point (3,4) depends circle: " + disk.IsPointInside(3, 4));

            var ball = new TBall(3, 0, 0, 0);
            Console.WriteLine(ball.ToString());
            Console.WriteLine("Ball`s Volume: " + ball.Volume());
        }
    }
}
