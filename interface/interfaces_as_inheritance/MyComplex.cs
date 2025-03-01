namespace Lab
{
  public class MyComplex : IMyNumber<MyComplex>
  {
    public double Real { get; }
    public double Imaginary { get; }

    public MyComplex(double real, double imaginary)
    {
      Real = real;
      Imaginary = imaginary;
    }

    public MyComplex(string complex)
    {
      var parts = complex.Split('+');
      if (parts.Length != 2 || !parts[1].EndsWith("i"))
        throw new ArgumentException("Invalid complex number format.");
      Real = double.Parse(parts[0]);
      Imaginary = double.Parse(parts[1].TrimEnd('i'));
    }

    public MyComplex Add(MyComplex that) =>
        new MyComplex(Real + that.Real, Imaginary + that.Imaginary);

    public MyComplex Subtract(MyComplex that) =>
        new MyComplex(Real - that.Real, Imaginary - that.Imaginary);

    public MyComplex Multiply(MyComplex that) =>
        new MyComplex(Real * that.Real - Imaginary * that.Imaginary,
                      Real * that.Imaginary + Imaginary * that.Real);

    public MyComplex Divide(MyComplex that)
    {
      var divisor = that.Real * that.Real + that.Imaginary * that.Imaginary;
      if (divisor == 0) throw new DivideByZeroException("Cannot divide by zero.");
      return new MyComplex((Real * that.Real + Imaginary * that.Imaginary) / divisor,
                           (Imaginary * that.Real - Real * that.Imaginary) / divisor);
    }

    public override string ToString() => $"{Real}+{Imaginary}i";


    public override bool Equals(object obj)
    {
      if (obj == null || GetType() != obj.GetType())
        return false;

      var other = (MyComplex)obj;
      return Math.Abs(Real - other.Real) < 0.0001 && Math.Abs(Imaginary - other.Imaginary) < 0.0001;
    }

    public override int GetHashCode()
    {
      return HashCode.Combine(Real, Imaginary);
    }
  }

}
