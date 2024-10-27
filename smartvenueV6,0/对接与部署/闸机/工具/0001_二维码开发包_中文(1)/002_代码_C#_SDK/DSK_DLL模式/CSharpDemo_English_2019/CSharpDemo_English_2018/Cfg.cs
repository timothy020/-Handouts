using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace CSharpDemo
{
    class Cfg
    {

        [DllImport("kernel32")]
        private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);

        [DllImport("kernel32")]
        private static extern long GetPrivateProfileString(string section, string key, string def, StringBuilder retVal, int size, string filePath);

        public static string Section = "";

        public static string FilePath = "";

        public static string GetConfig(string key, string defaultVal)
        {
            try
            {
                StringBuilder sb = new StringBuilder();

                GetPrivateProfileString(Section, key, defaultVal, sb, 200, FilePath);

                return sb.ToString();
            }
            catch
            {
                return defaultVal;
            }
        }

        public static int GetConfig(string key, int defaultVal)
        {
            try
            {
                StringBuilder sb = new StringBuilder();

                GetPrivateProfileString(Section, key, defaultVal.ToString(), sb, 50, FilePath);

                return int.Parse(sb.ToString());
            }
            catch
            {
                return defaultVal;
            }
        }

        public static bool GetConfig(string key, bool defaultVal)
        {
            try
            {
                StringBuilder sb = new StringBuilder();

                GetPrivateProfileString(Section, key, defaultVal.ToString(), sb, 50, FilePath);

                return bool.Parse(sb.ToString());
            }
            catch
            {
                return defaultVal;
            }
        }

        public static void SetConfig(string key, string val)
        {
            WritePrivateProfileString(Section, key, val, FilePath);
        }

        public static void SetConfig(string key, int val)
        {
            WritePrivateProfileString(Section, key, val.ToString(), FilePath);
        }

        public static void SetConfig(string key, bool val)
        {
            WritePrivateProfileString(Section, key, val.ToString(), FilePath);
        }

    }
}
