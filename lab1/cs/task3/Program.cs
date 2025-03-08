using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;




namespace Lab {
    public class Program 
    {
        public delegate double FractionTask(int x);

        public static void Main() 
        {
            int precision = int.Parse(Console.ReadLine());

            FractionTask sum_to_square = n => 1.0 / Math.Pow(2,n);

            FractionTask factorial_sum = n => 1.0 / factorial(n);
            
            FractionTask negative_sum = n => Math.Pow(-1, n + 1) / Math.Pow(2,n);

            Console.WriteLine(TotalSum(precision,sum_to_square));
            Console.WriteLine(TotalSum(precision,factorial_sum));
            Console.WriteLine(TotalSum(precision,negative_sum));
        }

        static double TotalSum(int precision, FractionTask frac) 
        {
            double res = 0.0;
            for (int i = 0; i <= precision; ++i) res += frac(i);
            
            return res;
        }

        static double factorial(int n) 
        {
            double res = 1.0;
            for (int i = 1; i <= n; ++i) res *= i;
            return res;
        }
    }
}