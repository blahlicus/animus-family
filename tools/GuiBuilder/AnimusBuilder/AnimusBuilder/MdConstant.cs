using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AnimusBuilder
{
    class MdConstant
    {
        public static char pseparator = System.IO.Path.DirectorySeparatorChar;
        public static string root = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetEntryAssembly().Location);
        public static string controllers = root + pseparator + @"controllers";
        public static string profiles = root + pseparator + @"profiles";
        public static string settings = root + pseparator + @"settings" + pseparator + @"setting.ukbst";


        public static string eControllers = @"*.ukbct";
        public static string eProfiles = @"*.ukbpr";
        public static string eSettings = @"*.ukbst";
    }
}
