using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AnimusBuilder
{
    public class MdSetting
    {
        public string animusPath { get; set; }
        public string modPath { get; set; }
        public string outputPath { get; set; }

        public static MdSetting setting { get; set; }

        public MdSetting()
        {

        }

        public static void LoadSettings()
        {
            setting = MdCore.Deserialize<MdSetting>(MdConstant.settings);
        }

        public static void SaveSettings()
        {
            MdCore.Serialize<MdSetting>(setting, MdConstant.settings);
        }
    }
}
