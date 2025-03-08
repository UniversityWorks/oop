using System;
using System.Linq;

namespace Lab
{
    public class Program
    {
        public static int[] EnumerableMethodRealization(int[] array, Func<int, bool> condition)
        {
            return array.Where(condition).ToArray();
        }   

        public static int[] OwnRealization(int[] array, Func<int, bool> condition)
        {
            int counter = 0;
            for(int i = 0; i < array.Length; i++)
            {
                if(condition(array[i])) counter++;
            }

            int[] res = new int[counter];
            counter = 0;
            for (int i = 0; i < array.Length; i++)
            {
                if (condition(array[i])) res[counter++] = array[i];
            }

            return res;
        }

        public static void Main()          
        {
            Console.Write("k: ");
            int k = int.Parse(Console.ReadLine());

            Console.Write("Number List: ");
            int[] array = Console.ReadLine().Split().Select(int.Parse).ToArray();

            Func<int, bool> condition = (num) => num % k == 0;

            int[] OwnFiltered = OwnRealization(array, condition);
            int[] EnumerableFiltered = EnumerableMethodRealization(array, condition);

            Console.WriteLine("With method 'Where': " + string.Join(", ", EnumerableFiltered));
            Console.WriteLine("Own Realization: " + string.Join(", ", OwnFiltered));
        }
    }
}
