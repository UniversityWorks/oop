using System;
using System.Linq;

namespace Lab
{
    public class Program
    {
        public delegate bool Filter(int number);

        public static int[] EnumerableMethodRealization(int[] array, Filter condition)
        {
            return array.Where(condition).ToArray();
        }

        public static int[] OwnRealization(int[] array, Filter condition)
        {
            int counter = 0;
            for(int i = 0; i < array.Length; i++)
            {
                if(condition(array[i])) counter++;
            }


            int[] res = new int[counter];
          
            int index =0;

            for (int i = 0; i < array.Length; i++)
            {
                if (condition(array[i])) res[index++] = array[i];
            }

            return res;
        }
        public static void Main(string[] args)          
        {
            Console.Write("k: ");
            int k = int.Parse(Console.ReadLine());

            Console.Write("Number List: ");
            int[] array = int.Parse(Console.ReadLine());

            Filter condition = (num) => num % k == 0;

            int[] OwnFiltered = OwnRealization(array, condition);
            int[] EnumerableFiltered = EnumerableMethodRealization(array, condition);

            Console.WriteLine("With method 'Where': " + string.Join(", ", EnumerableFiltered));
            Console.WriteLine("Own Realization: " + string.Join(", ", OwnFiltered));

        }
    }
}