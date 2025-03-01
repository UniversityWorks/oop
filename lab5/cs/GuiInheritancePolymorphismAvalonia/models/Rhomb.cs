using Avalonia.Controls;
using Avalonia.Media;
using Avalonia;
using Avalonia.Controls.Shapes;

namespace GuiInheritancePolymorphismAvalonia
{
    public class Rhomb : Figure
    {
        public double HorDiag { get; }
        public double VertDiag { get; }

        public Rhomb(double x, double y, double horDiag, double vertDiag) : base(x, y)
        {
            HorDiag = horDiag;
            VertDiag = vertDiag;
        }

        public override void Draw(Canvas canvas)
        {
            var points = new[]
            {
                new Point(X, Y - VertDiag / 2),
                new Point(X + HorDiag / 2, Y),
                new Point(X, Y + VertDiag / 2),
                new Point(X - HorDiag / 2, Y)
            };

            var polygon = new Polygon
            {
                Points = new Points(points),
                Fill = Brushes.Black
            };
            canvas.Children.Add(polygon);
        }
    }
}
