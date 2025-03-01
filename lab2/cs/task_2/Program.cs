using System;

public class MyTime
{
    public int Hour { get; private set; }
    public int Minute { get; private set; }
    public int Second { get; private set; }

    public MyTime(int h, int m, int s)
    {
        Hour = (h % 24 + 24) % 24;
        Minute = (m % 60 + 60) % 60; 
        Second = (s % 60 + 60) % 60;
    }

    public override string ToString()
    {
        return $"{Hour}:{Minute:D2}:{Second:D2}";
    }

    public static int TimeSinceMidnight(MyTime t)
    {
        return t.Hour * 3600 + t.Minute * 60 + t.Second;
    }

    public static MyTime TimeSinceMidnight(int seconds)
    {
        int secPerDay = 60 * 60 * 24;
        seconds = ((seconds % secPerDay) + secPerDay) % secPerDay; 
        int h = seconds / 3600;
        int m = (seconds / 60) % 60;
        int s = seconds % 60;
        return new MyTime(h, m, s);
    }

    public static MyTime AddOneSecond(MyTime t)
    {
        return TimeSinceMidnight(TimeSinceMidnight(t) + 1);
    }

    public static MyTime AddOneMinute(MyTime t)
    {
        return TimeSinceMidnight(TimeSinceMidnight(t) + 60);
    }

    public static MyTime AddOneHour(MyTime t)
    {
        return TimeSinceMidnight(TimeSinceMidnight(t) + 3600);
    }

    public static MyTime AddSeconds(MyTime t, int seconds)
    {
        return TimeSinceMidnight(TimeSinceMidnight(t) + seconds);
    }

    public static int Difference(MyTime mt1, MyTime mt2)
    {
        return TimeSinceMidnight(mt1) - TimeSinceMidnight(mt2);
    }

    public static string WhatLesson(MyTime mt)
    {
        int seconds = TimeSinceMidnight(mt);
        if (seconds < 8 * 3600) return "Пари ще не почалися";
        if (seconds < 9 * 3600 + 20 * 60) return "1-а пара";
        if (seconds < 9 * 3600 + 30 * 60) return "Перерва між 1-ю та 2-ю парами";
        if (seconds < 11 * 3600) return "2-а пара";
        if (seconds < 11 * 3600 + 20 * 60) return "Перерва між 2-ю та 3-ю парами";
        if (seconds < 12 * 3600 + 40 * 60) return "3-я пара";
        if (seconds < 13 * 3600) return "Перерва між 3-ю та 4-ю парами";
        if (seconds < 14 * 3600 + 20 * 60) return "4-а пара";
        if (seconds < 14 * 3600 + 30 * 60) return "Перерва між 4-ю та 5-ю парами";
        if (seconds < 16 * 3600) return "5-а пара";
        if (seconds < 16 * 3600 + 10 * 60) return "Перерва між 5-ю та 6-ю парами";
        if (seconds < 17 * 3600 + 30 * 60) return "6-а пара";
        return "Пари вже скінчилися";
    }
}

class Program
{
    static void Main(string[] args)
    {
        MyTime time = new MyTime(9, 30, 0);
        Console.WriteLine($"Current time: {time}");

        Console.WriteLine($"Seconds since midnight: {MyTime.TimeSinceMidnight(time)}");

        MyTime newTime = MyTime.TimeSinceMidnight(36000);
        Console.WriteLine($"Time from 36000 seconds: {newTime}");

        Console.WriteLine($"Adding one second: {MyTime.AddOneSecond(time)}");
        Console.WriteLine($"Adding one minute: {MyTime.AddOneMinute(time)}");
        Console.WriteLine($"Adding one hour: {MyTime.AddOneHour(time)}");

        Console.WriteLine($"Adding 5000 seconds: {MyTime.AddSeconds(time, 5000)}");

        MyTime time2 = new MyTime(8, 0, 0);
        Console.WriteLine($"Difference: {MyTime.Difference(time, time2)} seconds");

        Console.WriteLine($"What lesson: {MyTime.WhatLesson(time)}");
    }
}
