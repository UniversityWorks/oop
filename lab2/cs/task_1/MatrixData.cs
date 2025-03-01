using System;
using System.Linq;
using System.Text;

public partial class MyMatrix
{
    private double[,] _matrix;

    public MyMatrix(double[,] array)
    {
        _matrix = (double[,])array.Clone();
    }

    public MyMatrix(double[][] jaggedArray)
    {
        if (!jaggedArray.All(row => row.Length == jaggedArray[0].Length)) // All() - перевірка, чи всі елементи задовільняють умову
            throw new ArgumentException("Jagged array must form a rectangular matrix.");

        int height = jaggedArray.Length;
        int width = jaggedArray[0].Length;
        _matrix = new double[height, width];

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                _matrix[i, j] = jaggedArray[i][j];
    }

    public MyMatrix(string[] rows)
    {
        var parsedRows = rows.Select(row => row.Split(new[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries)
                                               .Select(double.Parse).ToArray()).ToArray();

        if (!parsedRows.All(row => row.Length == parsedRows[0].Length))
            throw new ArgumentException("String array must form a rectangular matrix.");

        int height = parsedRows.Length;
        int width = parsedRows[0].Length;
        _matrix = new double[height, width];

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                _matrix[i, j] = parsedRows[i][j];
    }

    public MyMatrix(string matrixString)
    {
        var rows = matrixString.Split(new[] { '\n' }, StringSplitOptions.RemoveEmptyEntries)
                               .Select(row => row.Split(new[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries)
                                                 .Select(double.Parse).ToArray()).ToArray();

        if (!rows.All(row => row.Length == rows[0].Length))
            throw new ArgumentException("Input string must form a rectangular matrix.");

        int height = rows.Length;
        int width = rows[0].Length;
        _matrix = new double[height, width];

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                _matrix[i, j] = rows[i][j];
    }

    public int Height => _matrix.GetLength(0);
    public int Width => _matrix.GetLength(1);

    public int getHeight() => Height;
    public int getWidth() => Width;

    public double this[int row, int col]
    {
        get => _matrix[row, col];
        set => _matrix[row, col] = value;
    }

    public double getElement(int row, int col) => _matrix[row, col];
    public void setElement(int row, int col, double value) => _matrix[row, col] = value;

    public override string ToString()
    {
        var sb = new StringBuilder();
        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
                sb.Append(_matrix[i, j].ToString("F2")).Append("\t");

            sb.AppendLine();
        }
        return sb.ToString();
    }
}