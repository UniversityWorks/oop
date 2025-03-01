using Avalonia.Controls;
using Avalonia.Media;
using Avalonia.Controls.Shapes;


namespace GuiInheritancePolymorphismAvalonia
{
    public class Square : Figure
    {
        public double SideLength { get; }

        public Square(double x, double y, double sideLength) : base(x, y)
        {
            SideLength = sideLength;
        }

        public override void Draw(Canvas canvas)
        {
            var rect = new Rectangle
            {
                Width = SideLength,
                Height = SideLength,
                Fill = Brushes.Black
            };
            Canvas.SetLeft(rect, X - SideLength / 2);
            Canvas.SetTop(rect, Y - SideLength / 2);
            canvas.Children.Add(rect);
        }
    }
}
