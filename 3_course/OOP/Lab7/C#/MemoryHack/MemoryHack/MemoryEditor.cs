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
        public MemoryEditor(string process)
        {
            _pNmae = process;
        }


        // my cod
        public void WriteMemory(IntPtr address, byte[] value, int pId) 
        {
            IntPtr _hProcess = OpenProcess((uint)ProcessAccessFlags.All, false, pId);
            IntPtr bytesWritten = IntPtr.Zero;

            // WriteProcessMemory(куда пишем_дескримтоор, адрес памяти, массив записываемых байт, кол. байт, переменная получающая кол байт)
            WriteProcessMemory(_hProcess, address, value, (int)value.Length, out bytesWritten);
            CloseHandle(_hProcess);
        }

        public int ReadMemory(IntPtr address, int size, int pId)
        {
            byte[] buffer = new byte[size];

            // OpenProcess(флаг доступа, параметр дискриптора наследования, ид процесса)
            IntPtr _hProcess = OpenProcess((uint)ProcessAccessFlags.All, false, pId);

            // WriteProcessMemory(куда пишем_дескримтоор, адрес памяти, указатель на буффер получающий процесс, кол. байт, переменная получающая кол байт)
            ReadProcessMemory(_hProcess, address, buffer, size, out nint bytesread);
            CloseHandle(_hProcess);
            return BitConverter.ToInt32(buffer, 0);
        }

        //public int GetParentProcess()
        //{
        //    _pId = 0;
        //    IntPtr handleToSnapshot = IntPtr.Zero;
        //    try
        //    {
        //        PROCESSENTRY32 procEntry = new PROCESSENTRY32();
        //        procEntry.dwSize = (UInt32)Marshal.SizeOf(typeof(PROCESSENTRY32));
        //        handleToSnapshot = CreateToolhelp32Snapshot((uint)SnapshotFlags.Process, 0);
        //        if (Process32First(handleToSnapshot, ref procEntry))
        //        {
        //            do
        //            {
        //                if (_pNmae == procEntry.szExeFile)
        //                {
        //                    _pId = (int)procEntry.th32ProcessID;
        //                    break;
        //                }
        //            } while (Process32Next(handleToSnapshot, ref procEntry));
        //        }
        //        else
        //        {
        //            throw new ApplicationException(string.Format("Failed with win32 error code {0}", Marshal.GetLastWin32Error()));
        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        throw new ApplicationException("Can't get the process.", ex);
        //    }
        //    finally
        //    {
        //        // Must clean up the snapshot object!
        //        CloseHandle(handleToSnapshot);
        //    }
        //    return _pId;
        //}

        private string _pNmae;
        //public int _pId;

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

        [DllImport("kernel32", SetLastError = true, CharSet = System.Runtime.InteropServices.CharSet.Auto)]
        static extern bool Process32Next([In] IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

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

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool ReadProcessMemory(
        IntPtr hProcess,
        IntPtr lpBaseAddress,
        IntPtr lpBuffer,
        int dwSize,
        out IntPtr lpNumberOfBytesRead);

    }
}
