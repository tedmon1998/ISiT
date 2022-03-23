using System;
using System.Diagnostics;


namespace MemoryHack
{
    class Program
    {
        static void Main(string[] args)
        {
            char finish = new();
            int newValue = new();
            MemoryEditor memoryEditor = new MemoryEditor("starter.exe");

            //Process.GetProcessesByName("starter.exe");
            var pList = Process.GetProcessesByName("starter")[0];
            int pId = pList.Id;

            Console.WriteLine($"Name \t{pList.ProcessName}\n");
            Console.WriteLine($"ID \t{pId}\n");

            Console.WriteLine("Please enter address ");
            IntPtr address = (IntPtr)0x8d949ffd5c;
            int sizeVar = sizeof(Int32);

            //Console.WriteLine($"\nResult {memoryEditor.ReadMemory(address, sizeVar, pId)}");

            do
            {
                Console.WriteLine($"\nResult {memoryEditor.ReadMemory(address, sizeVar, pId).ToString()}\n");
                newValue = int.Parse(Console.ReadLine());
                memoryEditor.WriteMemory(address, BitConverter.GetBytes(newValue), pId);
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

            Console.WriteLine($"\nResult {memoryEditor.ReadMemory(address, sizeVar, pId)}");
        }
    }
}
