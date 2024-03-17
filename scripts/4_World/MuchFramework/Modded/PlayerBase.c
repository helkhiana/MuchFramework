modded class PlayerBase
{
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);

		if(rpc_type == MUCH_RPC.RPC_CLIENT_SETCONFIG)
        {
            PluginMuchProxiesConfig msp_config = PluginMuchProxiesConfig.Cast(GetPlugin(PluginMuchProxiesConfig));
            if(msp_config)
            {
                msp_config.OnRPC(sender, this, rpc_type, ctx);
            }
        }      
            
		if(rpc_type == MUCH_RPC.RPC_CLIENT_CODELOCK_SETCONFIG)
        {
            PluginMuchCodelockConfig codelock_config = GetMuchCodelockConfig();
            if(codelock_config)
            {
                codelock_config.OnRPC(sender, this, rpc_type, ctx);
            }
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