using System;

namespace Lab
{
    public delegate double Func(int x);
    public static class Program
    {
        public static void Main()
        {
            Func[] funcs = new Func[3];

            funcs[0] = x => Math.Sqrt(Math.Abs(x));
            funcs[1] = x => x * x * x;
            funcs[2] = x => x + 3.5;

            while (true)
            {
                try
                {
                    string[] read = Console.ReadLine().Trim().Split();
                    int choise = int.Parse(read[0]);
                    int val = int.Parse(read[1]);

                    Func pickedFunc = funcs[choise];

                    Console.WriteLine(pickedFunc(val));
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Up From the Skies.");
                    break;
                }
            }
        }
    }
}
