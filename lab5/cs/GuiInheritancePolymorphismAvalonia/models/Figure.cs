using Avalonia.Controls;
using Avalonia.Media;

namespace GuiInheritancePolymorphismAvalonia
{
    public abstract class Figure
    {
        public double X { get; protected set; }
        public double Y { get; protected set; }

        protected Figure(double x, double y)
        {
            X = x;
            Y = y;
        }

        public abstract void Draw(Canvas canvas);
        public virtual void MoveRight(Canvas canvas) => X += 10;
    }
}
