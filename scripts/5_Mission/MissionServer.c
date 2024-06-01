modded class MissionServer 
{    
    
#ifdef SERVER
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);		
		PluginMuchProxiesConfig proxies_config = PluginMuchProxiesConfig.Cast(GetPlugin(PluginMuchProxiesConfig));
        if(proxies_config)
        {
            proxies_config.Server_SendConfigToClient(player, identity);
        }
		PluginMuchCodelockConfig codelock_config = PluginMuchCodelockConfig.Cast(GetPlugin(PluginMuchCodelockConfig));
        if(codelock_config)
        {
            codelock_config.Server_SendConfigToClient(player, identity);
        }
		PluginMFSettingsConfig settings_config = PluginMFSettingsConfig.Cast(GetPlugin(PluginMFSettingsConfig));
        if(settings_config)
        {
            settings_config.Server_SendConfigToClient(player, identity);
        }
	}
#endif
};