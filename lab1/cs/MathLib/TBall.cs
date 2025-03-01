using System;

namespace MathLib
{
    public class TBall : TDisk
    {
        public double Z { get; set; }

        public TBall(double radius, double x, double y, double z) : base(radius, x, y)
        {
            Z = z;
        }

        public double Volume()
        {
            return 4.0 / 3.0 * Math.PI * Math.Pow(Radius, 3);
        }

        public override string ToString()
        {
            return $"Sphere with center at ({Center.x}, {Center.y}, {Z}) and radius {Radius}";
        }
    }
}
