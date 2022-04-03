using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace MemoryHack
{
    class MemoryEditor
    {
        public MemoryEditor(Process allProcess)
        {
            // OpenProcess(флаг доступа, параметр дискриптора наследования, ид процесса)
            _id = allProcess.Id;
            _process = OpenProcess((uint)ProcessAccessFlags.All, false, _id);
            IntPtr _baseAddress = allProcess.MainModule.BaseAddress;
            FindDMAAddy((IntPtr)(_baseAddress + 0x0012E0D8), new int[] { 0x31C });
        }

        // my cod
        public void WriteMemory(byte[] value) 
        {
            IntPtr bytesWritten = IntPtr.Zero;

            // WriteProcessMemory(куда пишем_дескримтоор, адрес памяти, массив записываемых байт, кол. байт, переменная получающая кол байт)
            WriteProcessMemory(_process, _address, value, (int)value.Length, out bytesWritten);
        }

        public int ReadMemory()
        {
            
            byte[] buffer = new byte[_size];

            // WriteProcessMemory(куда пишем_дескримтоор, адрес памяти, указатель на буффер получающий процесс, кол. байт, переменная получающая кол байт)
            ReadProcessMemory(_process, _address, buffer, _size, out nint bytesread);
            
            return BitConverter.ToInt32(buffer, 0);
        }

        public void FindDMAAddy(IntPtr ptr, int[] offsets)
        {
            var buffer = new byte[_size];

            foreach (int i in offsets)
            {
                ReadProcessMemory(_process, ptr, buffer, buffer.Length, out
                var read);
                ptr = (_size == 4) ? IntPtr.Add(new IntPtr(BitConverter.ToInt32(buffer, 0)), i) : ptr = IntPtr.Add(new IntPtr(BitConverter.ToInt64(buffer, 0)), i);
            }
            // можно то, что выше переписать ptr = IntPtr.Add(new IntPtr(BitConverter.ToInt64(buffer, 0)), 0x31C);
            Console.WriteLine("Memory address: " + "0x" + ptr.ToString("X"));
            _address = ptr;
        }

        
        // global var
        private int _size = IntPtr.Size;
        private IntPtr _process;
        private IntPtr _address;
        private int _id;

        ~MemoryEditor()
        {
            CloseHandle(_process);
        }

        // import library
        // CreateToolhelp32Snapshot
        [Flags]
        private enum SnapshotFlags : uint
        {
            HeapList = 0x00000001,
            Process = 0x00000002,
            Thread = 0x00000004,
            Module = 0x00000008,
            Module32 = 0x00000010,
            Inherit = 0x80000000,
            All = 0x0000001F,
            NoHeaps = 0x40000000
        }
        //inner struct used only internally
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        private struct PROCESSENTRY32
        {
            const int MAX_PATH = 260;
            internal UInt32 dwSize;
            internal UInt32 cntUsage;
            internal UInt32 th32ProcessID;
            internal IntPtr th32DefaultHeapID;
            internal UInt32 th32ModuleID;
            internal UInt32 cntThreads;
            internal UInt32 th32ParentProcessID;
            internal Int32 pcPriClassBase;
            internal UInt32 dwFlags;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = MAX_PATH)]
            internal string szExeFile;
        }

        [DllImport("kernel32", SetLastError = true, CharSet = System.Runtime.InteropServices.CharSet.Auto)]
        static extern IntPtr CreateToolhelp32Snapshot([In] UInt32 dwFlags, [In] UInt32 th32ProcessID);

        [DllImport("kernel32", SetLastError = true, CharSet = System.Runtime.InteropServices.CharSet.Auto)]
        static extern bool Process32First([In] IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

        [DllImport("kernel32", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool CloseHandle([In] IntPtr hObject);

        // WriteProcessMemory
        [DllImport("kernel32.dll")]
        static extern bool WriteProcessMemory(
        IntPtr hProcess,
        IntPtr lpBaseAddress,
        byte[] lpBuffer,
        Int32 nSize,
        out IntPtr lpNumberOfBytesWritten
        );

        // OpenProcess
        [Flags]
        public enum ProcessAccessFlags : uint
        {
            All = 0x001F0FFF,
            Terminate = 0x00000001,
            CreateThread = 0x00000002,
            VirtualMemoryOperation = 0x00000008,
            VirtualMemoryRead = 0x00000010,
            VirtualMemoryWrite = 0x00000020,
            DuplicateHandle = 0x00000040,
            CreateProcess = 0x000000080,
            SetQuota = 0x00000100,
            SetInformation = 0x00000200,
            QueryInformation = 0x00000400,
            QueryLimitedInformation = 0x00001000,
            Synchronize = 0x00100000
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern IntPtr OpenProcess(
        uint processAccess,
        bool bInheritHandle,
        int processId
        );

        // ReadProcessMemory
        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool ReadProcessMemory(
        IntPtr hProcess,
        IntPtr lpBaseAddress,
        [Out] byte[] lpBuffer,
        int dwSize,
        out IntPtr lpNumberOfBytesRead);
    }
}
