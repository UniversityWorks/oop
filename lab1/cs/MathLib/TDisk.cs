using System;

namespace MathLib
{
    public class TDisk
    {
        public double Radius { get; set; }
        public (double x, double y) Center { get; set; }

        public TDisk(double radius, double x, double y)
        {
            Radius = radius;
            Center = (x, y);
        }

        public TDisk(TDisk disk)
        {
            Radius = disk.Radius;
        }

        public double Area()
        {
            return Math.PI * Math.Pow(Radius, 2);
        }

        public bool IsPointInside(double x, double y)
        {
            double distance = Math.Sqrt(Math.Pow(x - Center.x, 2) + Math.Pow(y - Center.y, 2));
            return distance <= Radius;
        }

        public override string ToString()
        {
            return $"Circle with center at ({Center.x}, {Center.y}) and radius {Radius}";
        }

        public static TDisk operator *(TDisk disk, double factor)
        {
            return new TDisk(disk.Radius * factor, disk.Center.x, disk.Center.y);
        }

        public static TDisk operator *(double factor, TDisk disk)
        {
            return disk * factor;
        }
    }
}
