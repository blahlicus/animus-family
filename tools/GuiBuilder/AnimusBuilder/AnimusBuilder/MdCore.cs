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
    }
}
