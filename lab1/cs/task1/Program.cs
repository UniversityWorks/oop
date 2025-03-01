using System;
using System.Threading;

namespace Lab
{
    public delegate void MyTimer();
    public class Timer
    {
        private readonly MyTimer myTimer;
        private readonly int interval;

        public Timer(MyTimer myTimer, int interval=0)
        {
            this.myTimer = myTimer;
            this.interval = interval;
        }

        public void Launch(int counter = 5)
        {
            for(int i = 0; i < counter; i++)
            {
                myTimer.Invoke();
                Thread.Sleep(interval * 1000);
            }
        }
    }
    class Program
    {

        static void FristTimer()
        {
            Console.WriteLine("Виконується перший метод.");
        }
         static void SecondTimer()
        {
            Console.WriteLine("Виконується другий метод.");
        }
        static void Main(string[] args)
        {

            Timer timer = new Timer(FristTimer, 2);
            timer.Launch();
        }
    }
}