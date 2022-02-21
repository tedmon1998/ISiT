using System;

namespace Lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            RubleAccount rubleAccount = new RubleAccount();
            rubleAccount.Put = 200;
            double rub = rubleAccount.Rate;
            (string _valuta, int _balance) = rubleAccount.CheckBalace;
            Console.WriteLine($"rub {rub.ToString()}");
            Console.WriteLine($"balance {_valuta} {_balance.ToString()}");
            Console.WriteLine($"Rate {rubleAccount.Rate}");
            rubleAccount.ShowLink += Definition;
            Console.WriteLine(value: $"Info {rubleAccount.Info()}");
            RealMoney(rubleAccount);
            VirtualMoney(rubleAccount);
            WriteLineExplicitly(rubleAccount);
            VirtualMoneyExplicitly(rubleAccount);

            ForeignAccount foreignAccount = new();
            foreignAccount.ShowLink += Definition;
            
            foreignAccount.PrintRate();

            ExceptionHandling exceptionHandling = new();
            (_valuta, _balance) = exceptionHandling.CheckBalace(rubleAccount);
            Console.WriteLine($"balance {_valuta} {_balance.ToString()}");

            MyGenericClass<double> myGenericClass = new();
            myGenericClass.Add(rubleAccount.Put);
            myGenericClass.Add(rubleAccount.Put + 1);

            for (int i = 0; i < myGenericClass.Count; i++)
                Console.WriteLine($"myGeneric {i} = {myGenericClass[i]}");
        }

        public static void Definition(object s, TextEventArgs text)
        {
            Console.WriteLine(text.Text);
        }

        static void RealMoney(IRealMoneyInterface money)
        {
            Console.WriteLine("\nRealMoney");
            money.PrintMoney();
        }
        static void VirtualMoney(IVirtualMoneyInterface money)
        {
            Console.WriteLine("\nVirtualMoney");
            money.PrintMoney();
        }
        static void WriteLineExplicitly(IRealMoneyInterfaceExplicitly money)
        {
            Console.WriteLine("\nRealMoneyExplicitly");
            money.PrintMoneyExplicitly();
        }
        static void VirtualMoneyExplicitly(IVirtualMoneyInterfaceExplicitly money)
        {
            Console.WriteLine("\nVirtualMoneyExplicitly");
            money.PrintMoneyExplicitly();
        }

    }

    interface IRealMoneyInterface
    {
        void PrintMoney();
    }

    interface IVirtualMoneyInterface
    {
        void PrintMoney();
    }

    interface IRealMoneyInterfaceExplicitly
    {
        void PrintMoneyExplicitly();
    }

    interface IVirtualMoneyInterfaceExplicitly
    {
        void PrintMoneyExplicitly();
    }


    public abstract class Check
    {
        // Счет базовый, абстрактный класс (родительский)
        private int _money;
        private static string _valuta;

        public Check()
        {
            _money = 0;
            _valuta = "RUB";
        }

        public int Put
        {
            // Получить, положить на счет
            get => this._money;

            set
            {
                this._money += value;
            }
        }


        public string ChangeValuta
        {
            // Изменить валюту, получить текущую валюту
            get => _valuta;

            set => _valuta = value;
        }

        public virtual (string Valuta, int Balance) CheckBalace
        {
            // Проверить баланс
            get => ("", this._money);
        }

        public virtual string CheckValuta
        {
            // Проверить валюту (узнать)
            get => _valuta;
        }


        // Курс валюты
        public abstract double Rate { get; }

        public delegate void Link(object sender, TextEventArgs e);
        public event Link ShowLink;
        // public event EventHandler ShowLink;

        protected virtual void OnShowLink(TextEventArgs args)
        {
            if (this.ShowLink != null)
                ShowLink(this, args);
        }

        ~Check()
        {
            Console.WriteLine("Instance of class Check destroyed");
        }
    }

    public class RubleAccount : Check, IRealMoneyInterface, IVirtualMoneyInterface, IRealMoneyInterfaceExplicitly, IVirtualMoneyInterfaceExplicitly
    {
        // Дочерний класс, рублевый счет (наследник)

        public RubleAccount() : base()
        {
            Console.WriteLine("Object RubleAccount");
        }

        void IRealMoneyInterfaceExplicitly.PrintMoneyExplicitly()
        {
            Console.WriteLine("Валюта");
            Console.WriteLine(Put);
        }

        void IVirtualMoneyInterfaceExplicitly.PrintMoneyExplicitly()
        {
            Console.WriteLine("Виртуальная валюта");
            Console.WriteLine(Put);
        }

        public void PrintMoney()
        {
            Console.WriteLine("Валюта");
            Console.WriteLine(Put);
        }
        
        
        public override (string Valuta, int Balance) CheckBalace
        {
            // Проверка валюты
            get
            {
                return ("RU", Put);
            }
        }

        public override double Rate
        {
            // Получить курс валюты
            get => Put * 0.013;
        }

        public static void LinkConsultant(EventArgs text)
        {
            Console.WriteLine(text);
            Console.WriteLine("Link: http://www.consultant.ru/document/cons_doc_LAW_2201/4b6b5df9fd5c11e890228a3c0fb76e0097d341a6/");
        }

        public string Info()
        {
            string text = "Специальные (рублёвые) счета – это счета, которые были открыты в уполномоченных офисах Сбербанка путём приёма от клиентов чеков всесоюзного объединения «Внешпосылторг» или путём зачисления рублёвого покрытия, поступившего с валютных счетов во Внешэкономбанке СССР.";
            TextEventArgs args = new TextEventArgs();
            args.Text = text;
            OnShowLink(args);
            return text;
        }

        ~RubleAccount()
        {
            Console.WriteLine("Thank you for your work in RubleAccount goodbye");
        }
    }

    public class TextEventArgs : EventArgs
    {
        public string Text { get; set; }
    }

    public class ForeignAccount : Check, IRealMoneyInterface, IVirtualMoneyInterface
    {
        // Дочерний класс, валютный счет (наследник)
        public ForeignAccount() : base()
        {
            Console.WriteLine("Object ForeignAccount");
        }

        public void PrintMoney()
        {
            Console.WriteLine("Виртуальная валюта");
            Console.WriteLine(Put);
        }

        public string Info()
        {
            string text = "Валютный счет - это счет в иностранном банке в валюте страны нахождения банка.";
            TextEventArgs args = new TextEventArgs();
            args.Text = text;
            OnShowLink(args);
            return text;
        }



        public override (string Valuta, int Balance) CheckBalace
        {
            get => ("ALL", Put);
        }

        public override double Rate
        {
            get => Put * 0.15;
        }


        ~ForeignAccount()
        {
            Console.WriteLine("Thank you for your work in ForeignAccount goodbye");
        }
    }

    class ExceptionHandling
    {
        public ExceptionHandling()
        {
            Console.WriteLine("\n----------------\n");
        }

        public (string Valuta, int Balance) CheckBalace(Check obj)
        {
            (string _valuta, int _balance) = obj.CheckBalace;
            try
            {
                if (_balance <= 0)
                    throw new Exception("Balance is either empty or negative");
                else
                    return (_valuta, _balance);
            }
            catch(Exception error)
            {
                Console.WriteLine($"CheckBalace {error}");
            }
            return (_valuta, 0);
        }
    }

    class MyGenericClass<T>
    {
        public MyGenericClass()
        {
            Console.WriteLine("\n--------------\n");
        }
        private T[] _array = Array.Empty<T>();

        public T this[int index]
        {
            get => _array[index];
            set => _array[index] = value;
        }

        public int Count { get => _array.Length; }

        public void Add(T value)
        {
            var newValueArray = new T[_array.Length + 1];

            for(int i = 0; i < _array.Length; i++)
            {
                newValueArray[i] = _array[i];
            }

            newValueArray[_array.Length] = value;
            _array = newValueArray;
        }
    }

    static class ForeignAccountExtension
    {
        public static void PrintRate(this ForeignAccount rate)
        {
            Console.WriteLine($"Текущий курс валюты {rate.Rate}");
        }
    }
}
