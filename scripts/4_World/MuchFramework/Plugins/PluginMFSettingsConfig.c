class MF_VirtualStorage_Settings
{
    bool EnableVirtualStorage = false;
    bool EnableAutoStoreOnClose = false;
    bool EnableAutoStoreTimer = false;
    int AutoStoreTimerInSeconds = 600;
	ref array<string> ItemsBlacklist = new array<string>;
	ref array<string> ContainerBlacklist = new array<string>;
};

class MF_Openable_Settings
{
    bool EnableAutoClose = false;
    int AutoCloseTimerInSeconds = 600;
};

class MF_Fridge_Settings
{
    bool EnableFridgePreservation = false;
	ref array<string> OtherFridgeClasses = new array<string>;
    //TODO: Test ref array<typname> OtherFridgeClasses = new array<typname>;
    float PreservationMultiplier = 2.0;
};

class MF_Settings
{    
    ref MF_VirtualStorage_Settings VirtualStorage = new MF_VirtualStorage_Settings;
    ref MF_Openable_Settings Openables = new MF_Openable_Settings;
    ref MF_Fridge_Settings Fridge_Settings = new MF_Fridge_Settings;
};

class PluginMFSettingsConfig : PluginReadJson
{		
    private ref MF_Settings m_Settings;

    static float PreservationMultiplier = 1.0;

	void PluginMFSettingsConfig()
	{
        m_ConfigFolder = "MuchFramework";
		m_ConfigName = "Settings";
        m_PrintName = "MuchFramework General Settings Config";
        wantedVersion =  1.1;
	}

#ifdef SERVER
	override void Load()
    {
		if (FileExist(FULLPATH))
        {
            Print("[" + m_PrintName+ "] '" + FULLPATH + "' found, loading existing config!");
            PluginMFSettingsConfig settingsConfig = PluginMFSettingsConfig.Cast(GetPlugin(PluginMFSettingsConfig));
            JsonFileLoader<PluginMFSettingsConfig>.JsonLoadFile(FULLPATH, settingsConfig);
            VersionCheck();
        }
        if(m_Settings && m_Settings.Fridge_Settings)
        {
           PreservationMultiplier = m_Settings.Fridge_Settings.PreservationMultiplier;
        }
    }

	override void Save()
    {
        PluginMFSettingsConfig settingsConfig = PluginMFSettingsConfig.Cast(GetPlugin(PluginMFSettingsConfig));
        JsonFileLoader<PluginMFSettingsConfig>.JsonSaveFile(FULLPATH, settingsConfig);
    }

	override void Default()
    {        
        if(!m_Settings)
        {
            m_Settings = new MF_Settings();
        }
        version = wantedVersion;
		Save();
	}

    protected void VersionCheck()
    {
        if(version != wantedVersion)
        {
            //TODO: Change here when we change the version
            Default();
            return; 
        }
    }    

    override void Server_SendConfigToClient(PlayerBase player, PlayerIdentity identity)
    { 
        if(!GetGame().IsServer())
            return;
        auto settingsConfigParams = new Param1<MF_Settings>(m_Settings);
        GetGame().RPCSingleParam(player, MUCH_RPC.RPC_CLIENT_SETSETTINGSCONFIG, settingsConfigParams, true, identity);
    }
#endif

	MF_Settings GetSettings()
	{
		return m_Settings;
	}

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		switch (rpc_type)
		{
			case MUCH_RPC.RPC_CLIENT_SETSETTINGSCONFIG: 
            {
                if(!GetGame().IsClient())
                    return;
				Param1<MF_Settings> settingsConfig;
                if(!ctx.Read(settingsConfig))
                    return;
                m_Settings = settingsConfig.param1;
                Print("[" + m_PrintName+ "] Received instance of config " + m_Settings);
				break;
			}           
		}
	}
};


static MF_Settings GetMFSettingsConfig()
{
    PluginMFSettingsConfig config = PluginMFSettingsConfig.Cast(GetPlugin(PluginMFSettingsConfig));
    if(config)
    {
        return config.GetSettings();
    }
    return null;
}