using System;
using Eto;
using Eto.Forms;

namespace animus_builder.Gtk3
{
    public class Program
    {
        [STAThread]
        public static void Main(string[] args)
        {
            new Application(Platforms.Gtk3).Run(new MainForm());
        }
    }
}
