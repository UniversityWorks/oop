using System.Numerics;

namespace Lab
{
  public class MyFrac : IMyNumber<MyFrac>, IComparable<MyFrac>
  {
    public BigInteger Numerator { get; }
    public BigInteger Denominator { get; }

    public MyFrac(BigInteger numerator, BigInteger denominator)
    {
      if (denominator == 0) throw new DivideByZeroException("Denominator cannot be zero.");
      (Numerator, Denominator) = Simplify(numerator, denominator);
    }

    public MyFrac(string fraction)
    {
      var parts = fraction.Split('/');
      if (parts.Length != 2) throw new ArgumentException("Invalid fraction format.");
      var numerator = BigInteger.Parse(parts[0]);
      var denominator = BigInteger.Parse(parts[1]);
      if (denominator == 0) throw new DivideByZeroException("Denominator cannot be zero.");
      (Numerator, Denominator) = Simplify(numerator, denominator);
    }

    public MyFrac Add(MyFrac that) =>
        new MyFrac(Numerator * that.Denominator + that.Numerator * Denominator,
                   Denominator * that.Denominator);

    public MyFrac Subtract(MyFrac that) =>
        new MyFrac(Numerator * that.Denominator - that.Numerator * Denominator,
                   Denominator * that.Denominator);

    public MyFrac Multiply(MyFrac that) =>
        new MyFrac(Numerator * that.Numerator, Denominator * that.Denominator);

    public MyFrac Divide(MyFrac that)
    {
      if (that.Numerator == 0) throw new DivideByZeroException("Cannot divide by zero.");
      return new MyFrac(Numerator * that.Denominator, Denominator * that.Numerator);
    }

    public int CompareTo(MyFrac? that)
    {
      if (that == null)
        throw new ArgumentNullException(nameof(that), "Cannot compare with null.");

      return (Numerator * that.Denominator).CompareTo(Denominator * that.Numerator);
    }


    public override string ToString() => $"{Numerator}/{Denominator}";

    private static (BigInteger, BigInteger) Simplify(BigInteger numerator, BigInteger denominator)
    {
      var gcd = BigInteger.GreatestCommonDivisor(numerator, denominator);
      numerator /= gcd;
      denominator /= gcd;

      if (denominator < 0)
      {
        numerator = -numerator;
        denominator = -denominator;
      }

      return (numerator, denominator);
    }
  }

}
