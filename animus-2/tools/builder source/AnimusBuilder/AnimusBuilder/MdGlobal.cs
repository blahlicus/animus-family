using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AnimusBuilder
{
    class MdGlobal
    {
        private static ClController _selectedController;
        public static FmMain mainForm { get; set; }

        public static ClController selectedController
        {
            get { return _selectedController; }
            set
            {
                _selectedController = value;
                mainForm.SetPins(selectedController.pins);
                mainForm.SetControllerName("uC: " + selectedController.name);
            }
        }

        public static ClBuildProfile profile { get; set; }
        
        public static void init()
        {
            _selectedController = new ClController();
            profile = new ClBuildProfile();
        }

    }
}
