using System;
class Triangle
{
    private double a, b, c;
    private bool isTriangle,isPos;

    public Triangle(double t_a, double t_b, double t_c)
    {
        a = t_a;
        b = t_b;
        c = t_c;

        isTriangle = (a + b > c && a + c > b && b + c > a);
        isPos = a > 0 && b > 0 && c > 0;


        if (!isTriangle || !isPos)
            throw new ArgumentException("невірні вхідні дані.");
    }
    public double GetP()
    {
        return a + b + c;
    }

    public double GetS()
    {
        double p = GetP() / 2.0;
        return Math.Sqrt(p * (p - a) * (p - b) * (p - c));
    }

    public void Print(double value)
    {
        Console.WriteLine(value);
    }
}

class Program
{
    static void Main()
    {
        Console.WriteLine("Введіть сторони трикутника: ");
        double a = double.Parse(Console.ReadLine());
        double b = double.Parse(Console.ReadLine());
        double c = double.Parse(Console.ReadLine());

        try
        {
            Triangle triangle = new Triangle(a, b, c);

            triangle.Print(triangle.GetP());
            triangle.Print(triangle.GetS());
        }
        catch (ArgumentException ex)
        {
            Console.WriteLine(ex.Message);
        }
        
    }
}
