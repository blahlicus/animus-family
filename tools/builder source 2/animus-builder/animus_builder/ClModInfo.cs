using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace animus_builder
{
    public class ClModInfo
    {
        public List<string> Pins { get; set; }
        public List<ClEEPROMSet> EEPROM { get; set; }

        public ClModInfo(List<string> pins, List<ClEEPROMSet> EEPROM)
        {
            this.Pins = new List<string>(pins);
            this.EEPROM = EEPROM.Select(eep => new ClEEPROMSet(eep)).ToList();
        }

        public ClModInfo () : this (new List<string>(), new List<ClEEPROMSet>())
        {
            
        }

        public ClModInfo(ClModInfo input) : this(input.Pins, input.EEPROM)
        {

        }

        public List<int> GetEEPROMs()
        {
            var output = new List<int>();
            foreach(var ele in EEPROM)
            {
                for(int i = ele.StartAddr; i < ele.EndAddr; i++)
                {
                    output.Add(i);
                }
            }

            return output;
        }
    }
}
