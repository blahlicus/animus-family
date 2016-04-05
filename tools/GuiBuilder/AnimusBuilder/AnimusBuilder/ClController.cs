using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AnimusBuilder
{
    public class ClController
    {
        public string name { get; set; }
        public int startEEPROM { get; set; }
        public int endEEPROM { get; set; }
        public List<string> pins { get; set; }
        public List<ClReservedPin> reservedPins { get; set; }
        public List<string> features { get; set; }

        public ClController()
        {
            name = "Unknown Controller";
            startEEPROM = 0;
            endEEPROM = 0;
            pins = new List<string>();
            reservedPins = new List<ClReservedPin>();
            features = new List<string>();
        }

    }
}
