using System;

public partial class MyMatrix
{
    public static MyMatrix operator +(MyMatrix a, MyMatrix b)
    {
        if (a.Height != b.Height || a.Width != b.Width)
            throw new ArgumentException("Matrices must have the same dimensions for addition.");

        double[,] result = new double[a.Height, a.Width];
        for (int i = 0; i < a.Height; i++)
            for (int j = 0; j < a.Width; j++)
                result[i, j] = a[i, j] + b[i, j];

        return new MyMatrix(result);
    }

    public static MyMatrix operator *(MyMatrix a, MyMatrix b)
    {
        if (a.Width != b.Height)
            throw new ArgumentException("Number of columns in the first matrix must equal the number of rows in the second matrix.");

        double[,] result = new double[a.Height, b.Width];
        for (int i = 0; i < a.Height; i++)
        {
            for (int j = 0; j < b.Width; j++)
            {
                result[i, j] = 0;
                for (int k = 0; k < a.Width; k++)
                {
                    result[i, j] += a[i, k] * b[k, j];
                }
            }
        }

        return new MyMatrix(result);
    }

    private double[,] GetTransponedArray()
    {
        double[,] transposed = new double[Width, Height];
        for (int i = 0; i < Height; i++)
            for (int j = 0; j < Width; j++)
                transposed[j, i] = _matrix[i, j];

        return transposed;
    }

    public MyMatrix GetTransponedCopy()
    {
        return new MyMatrix(GetTransponedArray());
    }

    public void TransponeMe()
    {
        if (Height != Width)
        {
            _matrix = GetTransponedArray();
            return;
        }

        for (int i = 0; i < Height; i++)
        {
            for (int j = i + 1; j < Width; j++)
            {
                double temp = _matrix[i, j];
                _matrix[i, j] = _matrix[j, i];
                _matrix[j, i] = temp;
            }
        }
    }

    private double? cachedDeterminant = null;

    public double CalcDeterminant()
    {
        if (Height != Width)
            throw new InvalidOperationException("Determinant can only be calculated for square matrices.");

        if (cachedDeterminant.HasValue)
            return cachedDeterminant.Value;

        double[,] matrixCopy = (double[,])_matrix.Clone();
        cachedDeterminant = CalculateDeterminantRecursive(matrixCopy);
        return cachedDeterminant.Value;
    }

    private double CalculateDeterminantRecursive(double[,] matrix)
    {
        int n = matrix.GetLength(0);
        if (n == 1) return matrix[0, 0];
        if (n == 2) return matrix[0, 0] * matrix[1, 1] - matrix[0, 1] * matrix[1, 0];

        double determinant = 0;
        for (int col = 0; col < n; col++)
        {
            double[,] subMatrix = GetSubMatrix(matrix, 0, col);
            determinant += Math.Pow(-1, col) * matrix[0, col] * CalculateDeterminantRecursive(subMatrix);
        }
        return determinant;
    }

    private double[,] GetSubMatrix(double[,] matrix, int excludedRow, int excludedCol)
    {
        int n = matrix.GetLength(0);
        double[,] subMatrix = new double[n - 1, n - 1];
        int r = 0;

        for (int i = 0; i < n; i++)
        {
            if (i == excludedRow) continue;
            int c = 0;
            for (int j = 0; j < n; j++)
            {
                if (j == excludedCol) continue;
                subMatrix[r, c] = matrix[i, j];
                c++;
            }
            r++;
        }
        return subMatrix;
    }

    public void InvalidateDeterminantCache()
    {
        cachedDeterminant = null;
    }
}
