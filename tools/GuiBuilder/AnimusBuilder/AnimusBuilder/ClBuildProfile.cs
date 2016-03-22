using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

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
    }
}
