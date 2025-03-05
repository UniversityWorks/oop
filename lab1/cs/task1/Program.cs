using System;
using System.Threading;


namespace Lab
{
    public delegate void MyTimer();
    public class Timer
    {
        private readonly MyTimer myTimer;
        private readonly int interval;

        public Timer(MyTimer timer, int interval)
        {
            this.myTimer = timer;
            this.interval = interval;
        }   

        public void Launch(int counter=5)
        {
            for (int i=0; i<counter; i++)
            {
                myTimer.Invoke();
                Thread.Sleep(interval* 1000);
            }
        }

        public void LaunchBoth(int counter=5)
        {
            Thread thread = new Thread(() => Launch(counter)); // лямбда
            thread.Start();
        }
    }

    class Program
    {
        static void FirstTimer()
        {
            Console.WriteLine("#1 Pink Floyd - Jugband Blues.");
        }
        static void SecondTimer()
        {
            Console.WriteLine("#2 Beatles - Strawberry Fields Forever.");
        }
        static void Main(string[] args)
        {
            Console.WriteLine("Statring playlist..");
            Thread.Sleep(1000);
            Timer timer1 = new Timer(FirstTimer, 2);
            Timer timer2 = new Timer(SecondTimer, 4);

            timer1.LaunchBoth();
            timer2.LaunchBoth();

            Thread.Sleep(20000);
            Console.WriteLine("The Doors - The end.");
        }
    }
    
}