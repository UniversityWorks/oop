using Avalonia;
using Avalonia.ReactiveUI;

internal class Program
{
    public static void Main(string[] args) => BuildAvaloniaApp().StartWithClassicDesktopLifetime(args);

    public static AppBuilder BuildAvaloniaApp() => AppBuilder.Configure<GuiInheritancePolymorphismAvalonia.App>().UsePlatformDetect().LogToTrace().UseReactiveUI();
}
