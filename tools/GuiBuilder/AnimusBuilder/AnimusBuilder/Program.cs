using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace AnimusBuilder
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            MdGlobal.init();
            MdGlobal.mainForm = new FmMain();
            Application.Run(MdGlobal.mainForm);
        }
    }
}
