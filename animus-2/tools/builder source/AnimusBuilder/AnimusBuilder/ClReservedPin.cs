using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AnimusBuilder
{

    public class ClReservedPin
    {
        public string name { get; set; }
        public string use { get; set; }
        public ClReservedPin()
        {

        }
        public ClReservedPin(string name, string use)
        {
            this.name = name;
            this.use = use;
        }
    }
}
