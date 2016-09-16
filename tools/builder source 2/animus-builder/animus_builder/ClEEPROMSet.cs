using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace animus_builder
{
    public class ClEEPROMSet
    {
        public int StartAddr { get; set; }
        public int EndAddr { get; set; }

        public ClEEPROMSet(int start, int end)
        {
            this.StartAddr = start;
            this.EndAddr = end;
        }

        public ClEEPROMSet() : this(-1, -1)
        {

        }

        public ClEEPROMSet(ClEEPROMSet input) : this(input.StartAddr, input.EndAddr)
        {

        }
    }
}
