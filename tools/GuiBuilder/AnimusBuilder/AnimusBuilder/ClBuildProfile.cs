using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace AnimusBuilder
{
    public class ClBuildProfile
    {
        public List<string> mods { get; set; }
        public List<string> vpins { get; set; }
        public List<string> hpins { get; set; }
        public string name { get; set; }
        public string variant { get; set; }
        public string driver_build { get; set; }
        public string refresh { get; set; }

        public ClBuildProfile()
        {
            mods = new List<string>();
            vpins = new List<string>();
            hpins = new List<string>();
            name = "Unknown Keyboard";
            variant = "Unknown Variant";
            driver_build = "Unknown Build";
            refresh = "10";
        }

        public bool CheckStrings()
        {
            bool output = true;
            if (name.Contains("\"") || name.Contains("\\") || 
                driver_build.Contains("\"") || driver_build.Contains("\\") || 
                variant.Contains("\"") || variant.Contains("\\"))
            {
                output = false;
            }
            return output;
        }

        public bool CheckPins()
        {
            bool output = true;
            if (hpins.Count < 1 || vpins.Count < 1)
            {
                output = false;
            }
            return output;

        }

        public bool CheckMods(string modPath)
        {
            bool output = true;
            if (!Directory.Exists(modPath))
            {
                output = false;
                return output;
            }

            List<string> usedPins = new List<string>();
            List<string> usedFeatures = new List<string>();
            int startEEPROM = -1;
            int endEEPROM = -1;


            List<string> modpool = new List<string>();
            modpool = Directory.GetDirectories(MdSetting.setting.modPath).Select(str => Path.GetFileNameWithoutExtension(str)).ToList();
            foreach (string mod in mods)
            {
                if (modpool.Contains(mod))
                {
                    string mfName = "mod_" + mod + ".ino";
                    string modDir = modPath;
                    if (modDir.EndsWith(MdConstant.pseparator.ToString()))
                    {
                        // do nothing
                    }
                    else
                    {
                        modDir = modDir + MdConstant.pseparator;
                    }

                    string mfPath = modDir + mfName;

                    if (!File.Exists(mfPath))
                    {
                        output = false;
                        return output;
                    }

                    List<string> mfContent = File.ReadAllLines(mfPath).ToList();

                    // checks if #define mod_modname is correctly made
                    if (mfContent.Find(str => str.StartsWith("#define mod_modname")) == "#define mod_modname " + mod)
                    {
                        // do nothing
                    }
                    else
                    {
                        output = false;
                        return output;
                    }

                    // gets list of requirements
                    List<string> mfRequirements = new List<string>();
                    bool addToReq = false;
                    foreach(string str in mfContent)
                    {

                        if (str == "BUILDER_REQUIREMENT_END")
                        {
                            addToReq = false;
                        }

                        if (addToReq)
                        {
                            mfRequirements.Add(str);
                        }

                        if (str == "BUILDER_REQUIREMENT_START")
                        {
                            addToReq = true;
                        }

                        // break omitted for readability
                    }

                    if (mfRequirements.Count > 0)
                    {
                        foreach (string str in mfContent)
                        {

                            // gets pin ownership
                            if (str.StartsWith("Pin("))
                            {
                                string temp = str.Substring(str.IndexOf('(')+1);
                                temp = temp.Substring(0, temp.IndexOf(')'));

                                temp = temp.Replace(" ", string.Empty);

                            }
                            // reserves EEPROM addresses

                            // adds additional features
                        }
                    }

                    
                }
                else
                {
                    output = false;
                    return output;
                }
            }

            return output;
        }
    }
}
