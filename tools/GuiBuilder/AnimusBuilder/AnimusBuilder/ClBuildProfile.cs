using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace AnimusBuilder
{
    public class ClBuildProfile
    {
        public enum CheckModResponse
        {
            DirectoryDoesNotExist,
            ModNamingError,
            ModDoesNotExist,
            PinDoesNotExist,
            PinConflictError,
            AllClear

        }
        

        public List<string> mods { get; set; }
        public List<string> vpins { get; set; }
        public List<string> hpins { get; set; }
        public string name { get; set; }
        public string bp_name { get; set; }
        public string variant { get; set; }
        public string driver_build { get; set; }
        public string refresh { get; set; }

        public ClBuildProfile()
        {
            mods = new List<string>();
            vpins = new List<string>();
            hpins = new List<string>();
            name = "Unknown Keyboard";
            bp_name = "unknown-keyboard";
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

        public CheckModResponse CheckMods(ClController controller, string modPath)
        {
            CheckModResponse output = CheckModResponse.AllClear;
            if (!Directory.Exists(modPath))
            {
                output = CheckModResponse.DirectoryDoesNotExist;
                return output;
            }

            List<string> usedPins = new List<string>();
            List<string> usedEEPROM = new List<string>();
            List<string> usedFeatures = new List<string>();

            usedPins.AddRange(hpins);
            usedPins.AddRange(vpins);


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
                        output = CheckModResponse.ModDoesNotExist;
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
                        output = CheckModResponse.ModNamingError;
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
                                usedPins = temp.Split(',').ToList();
                                if (usedPins.All(pstr => controller.pins.Contains(pstr)))
                                {
                                    // do nothing
                                }
                                else
                                {
                                    output = CheckModResponse.PinDoesNotExist;
                                    return output;
                                }

                            }
                            else if (str.StartsWith("EEPROM("))// reserves EEPROM addresses
                            {
                                string temp = str.Substring(str.IndexOf('(') + 1);
                                temp = temp.Substring(0, temp.IndexOf(')'));

                                temp = temp.Replace(" ", string.Empty);
                                usedEEPROM = temp.Split(',').ToList();
                            }
                            else // adds additional features
                            {
                                // fuck LINQ, i love you LINQ but i am having a brain fart right now
                                if (controller.features.Contains(str))
                                {
                                    usedFeatures.Add(str);
                                    foreach(ClReservedPin rp in controller.reservedPins)
                                    {
                                        if (rp.use == str)
                                        {
                                            if (usedPins.Contains(rp.name))
                                            {
                                                output = CheckModResponse.PinConflictError;
                                                return output;
                                            }
                                            else
                                            {
                                                usedPins.Add(rp.name);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    
                }
                else
                {
                    output = CheckModResponse.ModDoesNotExist;
                    return output;
                }
            }

            output = CheckModResponse.AllClear;
            return output;
        }
    }
}
