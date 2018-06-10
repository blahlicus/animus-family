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

        public static string bRow = "builder_row";
        public static string bCol = "builder_col";
        public static string bName = "builder_kbname";
        public static string bVariant = "builder_kbvariant";
        public static string bDriver = "builder_kbdriver";
        public static string bBuild = "builder_kbdriver_build";
        public static string bVPins = "builder_vpins";
        public static string bHPins = "builder_hpins";
        public static string bRefresh = "builder_refresh";

        public static string bMStart = "builder_mstartup";
        public static string bMLoop = "builder_mloop";
        public static string bMPreCoord = "builder_mpresscoord";
        public static string bMPrePress = "builder_mprepress";
        public static string bMKDown = "builder_mkeydown";
        public static string bMKUp = "builder_mkeyup";
        public static string bMSerial = "builder_mserial";

        public static string bMEStartup = "Startup();";
        public static string bMELoop = "Loop();";
        public static string bMEPreCoord = "PressCoord(x, y);";
        public static string bMEPrePress = "PrePress(val, type);";
        public static string bMEKDown = "KeyDown(val, type);";
        public static string bMEKUp = "KeyUp(val, type);";
        public static string bMESerial = "Serial(input);";

        public static string bMFPreCoord = "void modMethod(PressCoord)(byte x, byte y)";
        public static string bMFPrePress = "void modMethod(PrePress)(char val, byte type)";
    }
}
