#ifdef SERVER
modded class DayZGame 
{    
    private static const string m_MF_ModPath = "$CurrentDir:@MuchFramework [EXPERIMENTAL]\\meta.cpp";
    private static const string m_MF_ModID = "3167524573";
    //private static const string m_MF_ModPath = "$CurrentDir:@MuchFramework\\meta.cpp";
    //private static const string m_MF_ModID = "";
    private bool m_InvalidUsage = false;

	void DayZGame() 
	{
        #ifndef DIAG_DEVELOPER
		MFReadMetaFile(m_MF_ModPath, m_MF_ModID);
        #endif
	}
    
    //Credit: wardog for writing this initially and sharing it
    void MFReadMetaFile(string meta, string modId)
    {
        if (!FileExist(meta))
        {
            Print("Couldn't find: " + meta);
            m_InvalidUsage = true;
            RequestExit(0);
            return;
        }

        FileHandle file = OpenFile(meta, FileMode.READ);

        string line;
        bool found = false;
        while (FGets(file,  line) > 0)
        {
            line.TrimInPlace();
            int equalIndex = line.IndexOf("=");
            int semiColonIndex = line.IndexOf(";");

            if (equalIndex != -1 && semiColonIndex != -1)
            {
                string key = line.Substring(0, equalIndex).Trim();
                key.ToLower();

                string value = line.Substring(equalIndex + 1, semiColonIndex - equalIndex - 1).Trim();
                if(value == modId)
                {
                    found = true;
                    break;
                }                
            }
        }
        if(!found)
        {
            Print("Couldn't find: " + modId);
            m_InvalidUsage = true;
            RequestExit(0);
        }
        CloseFile(file);
    }
}
#endif
