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
        case MUCH_RPC.RPC_CLIENT_SHOWWARNINGUI:
            if (GetGame().IsClient() && GetGame().GetUIManager())
            {
                GetGame().GetUIManager().EnterScriptedMenu(MSP_Constants.MF_NOTICE_UI,null);                
                //GetGame().GetUIManager().ShowScriptedMenu(noticeUI, NULL);
                GetGame().GetMission().AddActiveInputExcludes({"menu"});
            }
            break;
        } 
        
	}

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