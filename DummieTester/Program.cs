using System;
using System.Threading;

namespace DummieTester
{
    class Program
    {
        private static int value_priv = 123456;
        private static IntPtr addr_priv;

        static void Main(string[] args)
        {
            Console.SetWindowSize(35, 7);
            int value = 123456;
            IntPtr addr;
            IntPtr addr_priv;

            unsafe
            {
                addr = (IntPtr)(&value);
                fixed (int* ptr = &value_priv)
                {
                    addr_priv = (IntPtr)ptr;
                }
                
            }

            while (true) {
                Console.Clear();
                Console.WriteLine("int");
                Console.WriteLine("address:" + addr.ToString("x"));
                Console.WriteLine("value  :" + value.ToString());
                Console.WriteLine("private static int");
                Console.WriteLine("address:" + addr_priv.ToString("x"));
                Console.WriteLine("value  :" + value_priv.ToString());
                Thread.Sleep(100);
            }
        }
    }
}
