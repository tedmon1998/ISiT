using System;



namespace MemoryHack
{
    class Program
    {
        static void Main(string[] args)
        {
            char finish = new();
            int newValue = new();
            MemoryEditor memoryEditor = new MemoryEditor("starter.exe");

            Console.WriteLine($"ID \t{memoryEditor.GetParentProcess()}\n");

            Console.WriteLine("Please enter address ");
            IntPtr address = (IntPtr)0x6ee0dffb6c;
            int sizeVar = sizeof(Int32);

            //Console.WriteLine($"\nResult {memoryEditor.ReadMemory(address)}");

            do
            {
                Console.WriteLine($"\nResult {memoryEditor.ReadMemory(address, sizeVar).ToString()}\n");
                newValue = int.Parse(Console.ReadLine());
                memoryEditor.WriteMemory(address, BitConverter.GetBytes(newValue));
                
                finish = char.Parse(Console.ReadLine());
            } while(finish.Equals('g'));

            Console.WriteLine($"\nResult {memoryEditor.ReadMemory(address, sizeVar)}");
        }
    }
}
