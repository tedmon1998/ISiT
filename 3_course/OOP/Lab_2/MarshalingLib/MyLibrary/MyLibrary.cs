using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NMyLibrary
{
    public interface IRealMoneyInterface
    {
        void PrintMoney();
    }

    public interface IVirtualMoneyInterface
    {
        void PrintMoney();
    }

    public interface IRealMoneyInterfaceExplicitly
    {
        void PrintMoneyExplicitly();
    }

    public interface IVirtualMoneyInterfaceExplicitly
    {
        void PrintMoneyExplicitly();
    }

    public static class MyLibrary
    {
        public static void Hi()
        {
            Console.WriteLine("Hi I'm ready to go");
        }

        private static double Computing(double N)
        {
            return N + 3 / 2;
        }

        public static double ComputingStart(double N)
        {
            return Computing(N);
        }
    }
}
