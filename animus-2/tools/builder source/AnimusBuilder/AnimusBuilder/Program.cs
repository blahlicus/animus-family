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
        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            MdGlobal.init();
            MdGlobal.mainForm = new FmMain();
            List<string> largs = args.ToList();
            if (largs.Count == 1)
            {
                if (System.IO.File.Exists(largs[0]))
                {

                    ClBuildList.BuildFromList(MdCore.Deserialize<ClBuildList>(largs[0]));
                }
                Application.Exit();
            }
            else
            {

                Application.Run(MdGlobal.mainForm);
            }
        }
    }
}
