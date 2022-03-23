using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Lab2
{
    class Program
    {
        static void Main(string[] args)
        {
            WorkingBaseClasses working = new();
            //working.Consol();
            //working.Files();
            //working.Maths();
            //working.Arrays();
            //working.Lists();
            //working.Dictionary();
        }
    }

    class WorkingBaseClasses
    {
        public void Consol()
        {
            Console.Write("Working with class ");
            Console.WriteLine("Console");
            Console.Title = "Title Console";
            Console.ReadKey();
            Console.BackgroundColor = ConsoleColor.Gray;
            Console.Clear();
            Console.ForegroundColor = ConsoleColor.Black;
            Console.WriteLine("Please input text in console");
            string _text = Console.ReadLine();
            Console.WriteLine($"You wrote {_text}");
            Console.WriteLine($"Window width {Console.WindowWidth}");
            Console.WriteLine($"Window height {Console.WindowHeight}");
            Console.WriteLine($"Buffer width {Console.BufferWidth}");
            Console.WriteLine($"Buffer height {Console.BufferHeight}");
            Console.ReadKey();
        }

        public void Files()
        {
            string path = string.Empty;
            for (int i = 0; i < 4; i++)
                path += "../";

            string _textFileName = "test.txt";
            string _folderName = "test";

            if (File.Exists(path + _textFileName))
            {
                Console.WriteLine("File exists");
                File.Delete(path + _textFileName);
            }
            var _myFile = File.Create(path + _textFileName);
            _myFile.Close();
            File.AppendAllText(path + _textFileName, "Test Lab2");

            if (File.Exists(path + _folderName))
            {
                Console.WriteLine("Folder exists");
                File.Delete(path + _folderName);
            }
            _myFile = File.Create(path + _folderName);
            _myFile.Close();
            File.Move(path + _textFileName, path + _folderName + _textFileName);
            Console.WriteLine("File moved");
            Console.WriteLine("Please CLICK ANY BUTTON for continue");
            Console.ReadKey();
            File.Copy(path + _folderName + _textFileName, path + _textFileName);
            Console.WriteLine("Fule copied");
            File.AppendAllText(path + _textFileName, "Lab 2 finished");

            Console.WriteLine(File.ReadAllText(path + _textFileName));
        }

        public void Maths()
        {
            int a = -5;
            int b = 10;
            double c = 2.4;
            Console.WriteLine($"|{a}| = {Math.Abs(a)}");
            Console.WriteLine($"Cos({a}) = {Math.Cos(a)}");
            Console.WriteLine($"Sin({a}) = {Math.Sin(a)}");
            Console.WriteLine($"Tangens({a}) = {Math.Tan(a)}");
            Console.WriteLine($"{c} округлить в большую сторону = {Math.Ceiling(c)}");
            Console.WriteLine($"{c} округлить в меньшую сторону = {Math.Floor(c)}");
            int res = new();
            Console.WriteLine($"{b}/{3} = {Math.DivRem(b, 3, out res)}; {b}%{3} = {res}");
            Console.WriteLine($"{b}%{2.3} = {Math.IEEERemainder(b, 2.3)}");
            Console.WriteLine($"{2.333333} примерно = {Math.Round(2.333333, 2)}");
            Console.WriteLine($"{a} > 0 ? 1 : -1 = {Math.Sign(a)}");
            Console.WriteLine($"{b} > 0 ? 1 : -1 = {Math.Sign(b)}");
            Console.WriteLine($"√{b} = {Math.Sqrt(b)}");
            Console.WriteLine($"{c} отбрость все, что после ',' = {Math.Truncate(c)}");
            Console.WriteLine($"{c} * {c} = {Math.Pow(c, 2)}");
        }

        public void Arrays()
        {
            string[] testArray = { "item1", "item2", "item3" };
            int[] myNumbers = { 5, 1, 8, 9 };


            void printArrayString(string text = "")
            {
                Console.WriteLine("\n-----------------------\n");
                if (String.IsNullOrEmpty(text)) Console.WriteLine(text);
                for (int i = 0; i < testArray.Length; i++)
                    Console.WriteLine($"{i}:\t {testArray[i]}");
            }
            void printArrayInt(string text = "")
            {
                Console.WriteLine("\n-----------------------\n");
                if (String.IsNullOrEmpty(text)) Console.WriteLine(text);
                for (int i = 0; i < myNumbers.Length; i++)
                    Console.WriteLine($"{i}:\t {myNumbers[i]}");
            }


            printArrayString("Test1");
            testArray[1] = "item22";
            printArrayString("Test2");

            printArrayInt("Test3");
            Array.Sort(myNumbers);
            printArrayInt("Test4");
            myNumbers[0] = myNumbers.Max();
            myNumbers[myNumbers.Length - 1] = myNumbers.Min();
            printArrayInt("Test5");
            Console.WriteLine($"Sum:\t {myNumbers.Sum()}");
        }

        public void Lists()
        {
            List <string> firstList = new List<string>();
            firstList.Add("item1");
            firstList.Add("item2");
            firstList.Add("item4");
            firstList.Add("item3");

            Console.WriteLine($"Count: \t{firstList.Count}");
            Console.WriteLine($"Capacity: \t{firstList.Capacity}");
            firstList.Add("item5");
            Console.WriteLine("\n-----------------------\n");
            Console.WriteLine($"Count: \t{firstList.Count}");
            Console.WriteLine($"Capacity: \t{firstList.Capacity}");
            Console.WriteLine("\n-----------------------\n");
            firstList.ForEach(Console.WriteLine);
            Console.WriteLine("\n-----------------------\n");
            firstList.Sort();
            Console.WriteLine("\n-----------------------\n");
            firstList.ForEach(Console.WriteLine);
            Console.WriteLine("\n-----------------------\n");
            firstList.ForEach(Console.WriteLine);
            Console.WriteLine($"FindIndex: \t{firstList.FindIndex("item2".StartsWith)}");
            firstList.Clear();
            Console.WriteLine("\n-----------------------\n");
            Console.WriteLine($"Count: \t{firstList.Count}");
        }

        public void Dictionary()
        {
            Dictionary<string, string> dict = new Dictionary<string, string>();
            dict.Add("key1", "val1");
            dict.Add("key2", "val2");
            dict.Add("key3", "val3");
            dict.Add("key4", "val4");
            dict.Add("key5", "val5");
            Console.WriteLine("\n-----------------------\n");
            Console.WriteLine($"dict: \t{dict["key3"]}");
            Console.WriteLine("\n-----------------------\n");

            foreach (KeyValuePair<string, string> dictItem in dict) Console.WriteLine("Key = {0}, Value = {1}", dictItem.Key, dictItem.Value);

            Console.WriteLine("\n-----------------------\n");
            Console.WriteLine($"Count: \t{dict.Count}");
            Console.WriteLine("\n-----------------------\n");
            foreach(string s in dict.Keys)  Console.WriteLine($"Keys: \t{s}");
            Console.WriteLine("\n-----------------------\n");
            foreach (string s in dict.Values) Console.WriteLine($"Values: \t{s}");
            dict.Clear();
            Console.WriteLine("\n-----------------------\n");
            Console.WriteLine($"Count: \t{dict.Count}");
        }
    }
}
