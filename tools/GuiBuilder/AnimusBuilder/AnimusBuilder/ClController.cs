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

        public static ClController ProMicro()
        {
            ClController output = new ClController();
            output.name = "Pro Micro - Atmega32u4";
            output.startEEPROM = 600;
            output.endEEPROM = 1000;
            output.pins = new List<string> { "2", "3", "4", "5", "6", "7", "8", "9", "10", "14", "15", "!6", "A0", "A1", "A2", "A3" };
            output.reservedPins = new List<ClReservedPin>();
            output.reservedPins.Add(new ClReservedPin("2", "I2C"));
            output.reservedPins.Add(new ClReservedPin("3", "I2C"));
            output.reservedPins.Add(new ClReservedPin("14", "SPI"));
            output.reservedPins.Add(new ClReservedPin("15", "SPI"));
            output.reservedPins.Add(new ClReservedPin("16", "SPI"));
            output.features = new List<string> { "I2C", "SPI" };
            return output;
        }

    }
}
