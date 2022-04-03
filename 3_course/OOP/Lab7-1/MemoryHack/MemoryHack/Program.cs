using System;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;

namespace MemoryHack
{
    class Program
    {
        static void Main(string[] args)
        {
            char finish = new();
            int newValue = new();


            Process pList = Process.GetProcessesByName("starter").FirstOrDefault();
            //Process pList = Process.GetProcessesByName("starter")[0];

            MemoryEditor memoryEditor = new MemoryEditor(pList);


            Console.WriteLine($"Name \t{pList.ProcessName}\n");
            Console.WriteLine($"ID \t{pList.Id}\n");
            Console.WriteLine($"Handler \t{pList.Handle}\n");
            Console.WriteLine($"BaseAddress \t{pList.MainModule.BaseAddress.ToString()}\n");

            do
            {
                Console.WriteLine($"\nResult {memoryEditor.ReadMemory().ToString()}\n");
                Console.Write("Please enter a new value: ");
                newValue = int.Parse(Console.ReadLine());
                memoryEditor.WriteMemory(BitConverter.GetBytes(newValue));
                try
                {
                    finish = char.Parse(Console.ReadLine());
                }
                catch
                {
                    Console.WriteLine("Error: please enter one symbol");
                    finish = 'g';
                }
            } while (finish.Equals('g'));
        }

    }


}
