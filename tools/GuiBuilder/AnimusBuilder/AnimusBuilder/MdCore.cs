using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml.Serialization;

namespace AnimusBuilder
{
    class MdCore
    {
        public static void Serialize<T>(T obj, string path)
        {

            StreamWriter sw = new StreamWriter(path, false);
            XmlSerializer ser = new XmlSerializer(typeof(T));
            ser.Serialize(sw, obj);
            sw.Close();
        }

        public static T Deserialize<T>(string path)
        {
            StreamReader sr = new StreamReader(path);
            XmlSerializer ser = new XmlSerializer(typeof(T));
            T output = (T)ser.Deserialize(sr);

            sr.Close();
            return output;

        }

        public static string BuildAnimus(ClBuildProfile bp, string animusPath, string modPath, string outputPath)
        {
            string output = "";

            if (bp.name.Contains("\"") || bp.name.Contains("\\") ||
                bp.driver_build.Contains("\"") || bp.driver_build.Contains("\\") ||
                bp.variant.Contains("\"") || bp.variant.Contains("\\"))
            {
                output = "Error: name, build, or variant contains illegal characters.";
                return output;
            }

            if (bp.hpins.Count < 1 || bp.vpins.Count < 1)
            {
                output = "Error: you need at least 1 pin per column and row.";
                return output;
            }

            if (!File.Exists(animusPath + MdConstant.pseparator + "animus.ino"))
            {
                output = "Error: animus.ino missing, animus path is invalid";
                return output;
            }

            if (!Directory.Exists(modPath))
            {
                output = "Error: mod folder missing, mod path is invalid.";
                return output;
            }

            List<string> modpool = new List<string>();
            modpool = Directory.GetDirectories(MdSetting.setting.modPath).Select(str => Path.GetFileNameWithoutExtension(str)).ToList();
            foreach (string mod in bp.mods)
            {
                if (modpool.Contains(mod))
                {
                    
                }
                else
                {
                    output = "Error: mod " + mod + " missing from the mod path.";
                    return output;
                }
            }

            

            return output;
        }
    }
}
