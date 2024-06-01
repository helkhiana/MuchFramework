class PluginReadJson : PluginBase
{
	[NonSerialized()]
	protected float wantedVersion = 1.0;
    protected float version = -1;
    
    [NonSerialized()]
	private static const string m_profileFolder = "$profile:/";
    [NonSerialized()]
	protected string m_ConfigFolder		        = "WillowGlade";
    [NonSerialized()]
	protected string m_ConfigName 		        = "YourConfigName";
    [NonSerialized()]
	protected string m_PrintName 		        = "YourConfigName";
    [NonSerialized()]
    protected string FULLPATH                     = "";

#ifdef SERVER
	override void OnInit()
	{     
        if(!GetGame().IsServer())
        {
            return;
        }
		Print("Initializing plugin: " + m_PrintName);
		FULLPATH = m_profileFolder + m_ConfigFolder;
		if (!FileExist(FULLPATH))
        {            
            Print("[" +m_PrintName + "] '" + FULLPATH + "' does NOT exist, creating directory!");
			MakeDirectory(FULLPATH);	
        }
        
		FULLPATH = FULLPATH + "/" + m_ConfigName + ".json";
	
		if (!FileExist(FULLPATH))
        {
            Print("[" + m_PrintName + "] '" + FULLPATH + "' does NOT exist, creating default config!");
            Default();
            return;
        }        
        Load();
    }

	protected void Load()
    {
		//JsonFileLoader<PluginReadJson>.JsonLoadFile(FULLPATH, this);
    }

	protected void Save()
    {
        //JsonFileLoader<PluginReadJson>.JsonSaveFile(FULLPATH, this);
    }

	protected void Default()
    {
		Save();
	}

    void Server_SendConfigToClient(PlayerBase player, PlayerIdentity identity)
    { 
        if(!GetGame().IsServer())
            return;
    }
#endif

    void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{

    }
};