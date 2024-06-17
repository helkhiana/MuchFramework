modded class PlayerBase
{
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);

        switch (rpc_type)
        {
        case MUCH_RPC.RPC_CLIENT_SETPROXIESCONFIG:
            PluginMuchProxiesConfig msp_config = PluginMuchProxiesConfig.Cast(GetPlugin(PluginMuchProxiesConfig));
            if(msp_config)
            {
                msp_config.OnRPC(sender, this, rpc_type, ctx);
            }
            break;
        case MUCH_RPC.RPC_CLIENT_CODELOCK_SETCONFIG:
            PluginMuchCodelockConfig codelock_config = GetMuchCodelockConfig();
            if(codelock_config)
            {
                codelock_config.OnRPC(sender, this, rpc_type, ctx);
            }
            break;
        case MUCH_RPC.RPC_CLIENT_SETSETTINGSCONFIG:
            PluginMFSettingsConfig settings_config = PluginMFSettingsConfig.Cast(GetPlugin(PluginMFSettingsConfig));
            if(settings_config)
            {
                settings_config.OnRPC(sender, this, rpc_type, ctx);
            }
            break;
        case MUCH_RPC.RPC_SERVER_CYCLEPLACINGOPTIONS:
            if(GetGame().IsServer())
            {
                Msp_ItemBase itemBaseParent = Msp_ItemBase.Cast(GetItemInHands());
                if(itemBaseParent)
                {
                    itemBaseParent.CyclePlacingOptions();
                }               
            }

            break;
        } 
	}
    
	// override void PlacingStartServer(ItemBase item)
	// {
	// 	super.PlacingStartServer(item);
    //     if(m_HologramServer)
    //     {
    //         m_HologramServer.SetPlacingOptions(item);
    //     }
	// }

	// override void PlacingStartLocal(ItemBase item)
	// {
	// 	super.PlacingStartLocal(item);
	// 	if (GetGame().IsMultiplayer() && GetGame().IsServer())
	// 		return;
		
    //     if(m_HologramLocal)
    //     {
    //         m_HologramLocal.RefreshVisual();
    //     }
	// }

    override void SetActions(out TInputActionMap InputActionMap)
    {
        super.SetActions(InputActionMap);
        #ifdef CodeLock
        AddAction(ActionRaidCodelockOnMSP, InputActionMap);       
        #endif 
        #ifdef RA_BASEBUILDING
        AddAction(ActionRaidRACodeLockOnMF, InputActionMap);       
        #endif 
    }
};