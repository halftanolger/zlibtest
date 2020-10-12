using System;
using System.IO;
using System.Text;

class Program
{
    static void Main(string[] args)
    {

        /*
         *        
         *  Orginalprogram - start
         * 

        // Read the file into <bits>
        var fs = new FileStream(@"/home/sensor/src/myzlibtest/zlibtest/data/Swap_compress.swap", FileMode.Open);
        var len = (int)fs.Length;
        var bits = new byte[len];
        fs.Read(bits, 0, len);

        // Dump 16 bytes per line
        for (int ix = 0; ix < len; ix += 16)
        {
            var cnt = Math.Min(16, len - ix);
            var line = new byte[cnt];
            Array.Copy(bits, ix, line, 0, cnt);
            // Write address + hex + ascii
            Console.Write("{0:X6}  ", ix);
            Console.Write(BitConverter.ToString(line));
            Console.Write("  ");
            // Convert non-ascii characters to .
            for (int jx = 0; jx < cnt; ++jx)
                if (line[jx] < 0x20 || line[jx] > 0x7f) line[jx] = (byte)'.';
            Console.WriteLine(Encoding.ASCII.GetString(line));
        }

        *
        * Orginalprogram - stopp
        *
        */


        /*
         * Testprogram - start -------------------------------------------------
         */

        // Åpne fila og legg den i lokal variable 'databuff'

        var fs = new FileStream(@"/home/sensor/src/myzlibtest/zlibtest/data/Swap_compress.swap", FileMode.Open);
        var sz = (int)fs.Length;
        var databuff = new byte[sz];
        fs.Read(databuff, 0, sz);

        Console.WriteLine("Size: {0:D} bytes", sz);

        // Finn posisjonen til ':'

        int p = 0;
        for (int i=0; i<10; i++) {

            var line = new byte[1];
            Array.Copy(databuff, i, line, 0, 1);

            byte[] charByte = Encoding.ASCII.GetBytes);

            Console.Write("{0:D} ", i);
            Console.Write("  ");
            Console.Write(BitConverter.ToString(line));
            Console.Write("  ");
            Console.Write(charByte);



            Console.WriteLine(" ");

        }





        Console.ReadLine();

    }

}


