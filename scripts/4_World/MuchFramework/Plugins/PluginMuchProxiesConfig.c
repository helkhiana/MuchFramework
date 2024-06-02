class MF_Proxies_Settings
{    
    bool HideAllProxiesWhenClosed;
    bool HideWeaponProxies;
    bool HideClothingProxies;
    bool HideOtherProxies;
};

class PluginMuchProxiesConfig : PluginReadJson
{		
    private ref MF_Proxies_Settings proxies_settings;

	void PluginMuchProxiesConfig()
	{
        m_ConfigFolder = "MuchFramework";
		m_ConfigName = "Proxies_Config";
        m_PrintName = "MuchFramework Proxies Config";
	}	    

#ifdef SERVER
	override void Load()
    {
		if (FileExist(FULLPATH))
        {
            Print("[" + m_PrintName+ "] '" + FULLPATH + "' found, loading existing config!");
            PluginMuchProxiesConfig msp_config = PluginMuchProxiesConfig.Cast(GetPlugin(PluginMuchProxiesConfig));
            JsonFileLoader<PluginMuchProxiesConfig>.JsonLoadFile(FULLPATH, msp_config);
            VersionCheck();
        }
    }

	override void Save()
    {
        PluginMuchProxiesConfig msp_config = PluginMuchProxiesConfig.Cast(GetPlugin(PluginMuchProxiesConfig));
        JsonFileLoader<PluginMuchProxiesConfig>.JsonSaveFile(FULLPATH, msp_config);
    }

	override void Default()
    {
        proxies_settings = new MF_Proxies_Settings();
        proxies_settings.HideAllProxiesWhenClosed = true;
        proxies_settings.HideWeaponProxies = false;
        proxies_settings.HideClothingProxies = false;
        proxies_settings.HideOtherProxies = false;	
        version = 1.0;
		Save();
	}

    protected void VersionCheck()
    {
        if(version != 1)
        {
            Default();
            return; 
        }
    }    

    override void Server_SendConfigToClient(PlayerBase player, PlayerIdentity identity)
    { 
        if(!GetGame().IsServer())
            return;
        auto proxiesConfigParams = new Param1<MF_Proxies_Settings>(proxies_settings);
        GetGame().RPCSingleParam(player, MUCH_RPC.RPC_CLIENT_SETPROXIESCONFIG, proxiesConfigParams, true, identity);
    }
#endif

	MF_Proxies_Settings GetProxiesSettings()
	{
		return proxies_settings;
	}

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		switch (rpc_type)
		{
			case MUCH_RPC.RPC_CLIENT_SETPROXIESCONFIG: 
            {
                if(!GetGame().IsClient())
                    return;
				Param1<MF_Proxies_Settings> proxiesConfig;
                if(!ctx.Read(proxiesConfig))
                    return;
                proxies_settings = proxiesConfig.param1;
                Print("[" + m_PrintName+ "] Received instance of config " + proxies_settings);
				break;
			}           
		}
	}
};


static MF_Proxies_Settings GetMuchProxiesConfig()
{
    PluginMuchProxiesConfig proxies_config = PluginMuchProxiesConfig.Cast(GetPlugin(PluginMuchProxiesConfig));
    if(proxies_config)
    {
        return proxies_config.GetProxiesSettings();
    }
    return null;
}