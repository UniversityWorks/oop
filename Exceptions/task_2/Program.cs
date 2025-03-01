using System;
using System.IO;
using System.Text.RegularExpressions;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.Processing;
using SixLabors.ImageSharp.Formats.Gif;

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Processing images in the current folder with vertical mirroring.\n");

        string currentDirectory = Directory.GetCurrentDirectory();
        string[] files = Directory.GetFiles(currentDirectory);
        Regex regexExtForImage = new Regex(@"\.(bmp|gif|tiff?|jpe?g|png|jpg)$", RegexOptions.IgnoreCase);

        foreach (string file in files)
        {
            try
            {
                if (!regexExtForImage.IsMatch(Path.GetExtension(file)))
                    continue;

                Console.WriteLine($"Processing file: {Path.GetFileName(file)}");

                try
                {
                    using (Image image = Image.Load(file))
                    {
                        image.Mutate(x => x.Flip(FlipMode.Vertical));

                        string newFileName = Path.Combine(currentDirectory, $"{Path.GetFileNameWithoutExtension(file)}-mirrored.gif");

                        image.Save(newFileName, new GifEncoder());
                        Console.WriteLine($"Saved as: {newFileName}");
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error reading or processing image: {ex.Message}");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Unexpected error: {ex.Message}");
            }
        }

        Console.WriteLine("\nProcessing complete.");
    }
}
