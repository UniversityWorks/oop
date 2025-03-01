using Avalonia.Controls;
using Avalonia.Media;
using Avalonia.Controls.Shapes;

namespace GuiInheritancePolymorphismAvalonia
{
    public class Circle : Figure
    {
        public double Radius { get; }

        public Circle(double x, double y, double radius) : base(x, y)
        {
            Radius = radius;
        }

        public override void Draw(Canvas canvas)
        {
            var ellipse = new Ellipse
            {
                Width = Radius * 2,
                Height = Radius * 2,
                Fill = Brushes.Black
            };
            Canvas.SetLeft(ellipse, X - Radius);
            Canvas.SetTop(ellipse, Y - Radius);
            canvas.Children.Add(ellipse);
        }
    }
}
