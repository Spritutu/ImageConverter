using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO.Ports;

namespace StandaloneMCUTester
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("This is Standalone MCU Tester");
            try
            {
                SerialPort port = new SerialPort();
                port.PortName = "COM4";
                port.BaudRate = 115200;
                port.Parity = Parity.None;
                port.DataBits = 8;
                port.StopBits = StopBits.Two;
                port.Handshake = Handshake.None;
                port.DataReceived += Port_DataReceived;
                port.ErrorReceived += Port_ErrorReceived;
                port.Disposed += Port_Disposed;
                port.Open();

                ThreadPool.QueueUserWorkItem(SendMessage, (object)port);    

                // Wait for data or user input to continue.
                Console.Write("Enter a key to close port");
                Console.ReadLine();

                port.Close();
                port.Dispose();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Caught Exception ", ex);
            }
        }

        private static void SendMessage(object commandPort)
        {
            SerialPort port = (SerialPort)commandPort;

            byte[] bytes = Encoding.ASCII.GetBytes("resetCounter");
            int length = bytes.Length + 2;
            byte[] buf = new byte[length];
            Buffer.BlockCopy(bytes, 0, buf, 0, bytes.Length);
            buf[bytes.Length] = 13;
            buf[bytes.Length + 1] = 10;
            for (int i=0; i<length; i++)
                port.Write(buf, i, 1);

            Console.WriteLine("\n Command Sent");
        }

        private static void Port_Disposed(object sender, EventArgs e)
        {
            Console.WriteLine("Port Disposed!");
        }

        private static void Port_ErrorReceived(object sender, SerialErrorReceivedEventArgs e)
        {
            Console.WriteLine("Error Received!");
        }

        private static void Port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            Console.WriteLine("Data Received!");
            SerialPort port = (SerialPort)sender;
            if (e.EventType == SerialData.Chars)
            {
                int nread = port.BytesToRead;
                Console.WriteLine("Number of Bytes that available to read = {0}", nread);
                int bufSize = nread + 1;
                Byte[] buf = new Byte[bufSize];
                nread = port.Read(buf, 0, bufSize - 1);
                Console.WriteLine("Number of Bytes that have been to read = {0}", nread);
                buf[bufSize - 1] = 0;
                string message = Encoding.ASCII.GetString(buf);
                Console.WriteLine("Message received = {0}", message);
            }
            else
            {
                Console.WriteLine("EOF Received!");
            }
        }
    }
}
