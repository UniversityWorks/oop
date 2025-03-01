using System;

class Program
{
    static void Main(string[] args)
    {
        

            double[,] array1 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
            double[,] array2 = { { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } };

            MyMatrix matrix1 = new MyMatrix(array1);
            MyMatrix matrix2 = new MyMatrix(array2);

            Console.WriteLine("Matrix 1:");
            Console.WriteLine(matrix1);

            Console.WriteLine("Matrix 2:");
            Console.WriteLine(matrix2);

            Console.WriteLine("Adding matrices:");
            MyMatrix sum = matrix1 + matrix2;
            Console.WriteLine(sum);

            Console.WriteLine("Multiplying matrices:");
            MyMatrix product = matrix1 * matrix2;
            Console.WriteLine(product);

            Console.WriteLine("Transposing Matrix 1:");
            MyMatrix transposed = matrix1.GetTransponedCopy();
            Console.WriteLine(transposed);

            Console.WriteLine("Transposing Matrix 1 in-place:");
            matrix1.TransponeMe();
            Console.WriteLine(matrix1);

            Console.WriteLine("Calculating determinant of Matrix 2:");
            double determinant = matrix2.CalcDeterminant();
            Console.WriteLine($"Determinant: {determinant}");

            Console.WriteLine("Testing with invalid data:");
            double[,] invalidArray = { { 1, 2 }, { 3, 4 }, { 5, 6 } }; 
            MyMatrix invalidMatrix = new MyMatrix(invalidArray);
            Console.WriteLine(invalidMatrix.CalcDeterminant());
        
        
    }
}
