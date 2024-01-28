modded class MissionServer 
{    
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);		
		PluginMuchProxiesConfig msp_config = PluginMuchProxiesConfig.Cast(GetPlugin(PluginMuchProxiesConfig));
        if(msp_config)
        {
            msp_config.Server_SendConfigToClient(player, identity);
        }
	}
};