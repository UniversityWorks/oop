namespace Lab
{
  internal class Program
  {
    static void TestAPlusBSquare<T>(T a, T b) where T : IMyNumber<T>
    {
      Console.WriteLine("=== Starting testing (a+b)^2=a^2+2ab+b^2 with a = " + a + ", b = " + b + " ===");
      T aPlusB = a.Add(b);
      Console.WriteLine("a = " + a);
      Console.WriteLine("b = " + b);
      Console.WriteLine("(a + b) = " + aPlusB);
      Console.WriteLine("(a+b)^2 = " + aPlusB.Multiply(aPlusB));
      Console.WriteLine(" = = = ");
      T curr = a.Multiply(a);
      Console.WriteLine("a^2 = " + curr);
      T wholeRightPart = curr;
      curr = a.Multiply(b); // ab
      curr = curr.Add(curr); // ab + ab = 2ab

      Console.WriteLine("2*a*b = " + curr);
      wholeRightPart = wholeRightPart.Add(curr);
      curr = b.Multiply(b);
      Console.WriteLine("b^2 = " + curr);
      wholeRightPart = wholeRightPart.Add(curr);
      Console.WriteLine("a^2+2ab+b^2 = " + wholeRightPart);
      Console.WriteLine("=== Finishing testing (a+b)^2=a^2+2ab+b^2 with a = " + a + ", b = " + b + " ===");
    }

    static void TestSquareDifference<T>(T a, T b) where T : IMyNumber<T>
    {
      Console.WriteLine("=== Starting testing (a-b)=(a^2-b^2)/(a+b) with a = " + a + ", b = " + b + " ===");
      T aSubtractB = a.Subtract(b);
      Console.WriteLine("a = " + a);
      Console.WriteLine("b = " + b);
      Console.WriteLine("(a - b) = " + aSubtractB);
      Console.WriteLine(" = = = ");
      T curr = a.Multiply(a);
      Console.WriteLine("a^2 = " + curr);
      T wholePart = curr;
      curr = b.Multiply(b); // b^2
      Console.WriteLine("b^2 = " + curr);
      wholePart = wholePart.Subtract(curr);
      Console.WriteLine("(a^2-b^2) = " + wholePart); // a^2-b^2

      curr = a.Add(b); // a + b
      Console.WriteLine("(a+b) = " + curr);
      curr = wholePart.Divide(curr);
      Console.WriteLine("(a^2-b^2)/(a+b) = " + curr);
      T difference = aSubtractB.Subtract(curr);
      Console.WriteLine("(a-b) - (a^2-b^2)/(a+b) = " + difference);
      Console.WriteLine("=== Finishing testing (a+b)^2=a^2+2ab+b^2 with a = " + a + ", b = " + b + " ===");
    }
    static void Main(string[] args)
    {
      TestAPlusBSquare(new MyFrac(1, 3), new MyFrac(1, 6));
      TestAPlusBSquare(new MyComplex(1, 3), new MyComplex(1, 6));
      TestSquareDifference(new MyFrac(1, 3), new MyFrac(1, 6));
      TestSquareDifference(new MyComplex(1, 3), new MyComplex(1, 6));

      var fractions = new MyFrac[] { new MyFrac(1, 3), new MyFrac(50, 60), new MyFrac(1, 2), new MyFrac(1, 4), new MyFrac(1, 8) };
      Console.WriteLine("\nUnsorted fractions:");
      foreach (var frac in fractions)
      {
        Console.WriteLine(frac);
      }

      Array.Sort(fractions, (frac1, frac2) => frac1.CompareTo(frac2));

      Console.WriteLine("\nSorted fractions:");
      foreach (var frac in fractions)
      {
        Console.WriteLine(frac);
      }
    }

  }
}
