#nullable enable
using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Media;

namespace GuiInheritancePolymorphismAvalonia
{
    public partial class MainWindow : Window
    {
        private Figure? currentFigure;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void OnCircleClick(object? sender, RoutedEventArgs e)
        {
            currentFigure = new Circle(100, 100, 50);
            Redraw();
        }

        private void OnSquareClick(object? sender, RoutedEventArgs e)
        {
            currentFigure = new Square(100, 100, 80);
            Redraw();
        }

        private void OnRhombClick(object? sender, RoutedEventArgs e)
        {
            currentFigure = new Rhomb(100, 100, 100, 60);
            Redraw();
        }

        private void OnMoveRightClick(object? sender, RoutedEventArgs e)
        {
            if (currentFigure != null)
            {
                currentFigure.MoveRight(DrawingCanvas);
                Redraw();
            }
        }

        private void Redraw()
        {
            DrawingCanvas.Children.Clear();
            currentFigure?.Draw(DrawingCanvas);
        }
    }
}
