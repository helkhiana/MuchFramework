class ActionMFVSStoreContents: ActionInteractBase
{
	void ActionMFVSStoreContents()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
	}

    override typename GetInputType()
    {
        return ContinuousInteractActionInput;
    }

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !target ) return false;
	
		Msp_ItemBase mspitembase = Msp_ItemBase.Cast(target.GetObject());
		if(mspitembase)
		{
			if(!mspitembase.CanDoVSStoreAction())
			{
				return false;
			}
			if(mspitembase.CanStoreCargo())
			{
				m_Text = "Store contents";
				return true;
			}			
		}
		return false;
	}
	
	override void OnStartServer( ActionData action_data )
	{
		Msp_ItemBase mspitembase = Msp_ItemBase.Cast(action_data.m_Target.GetObject());
		if(mspitembase)
		{				
			PlayerBase player = PlayerBase.Cast(action_data.m_Player);
			mspitembase.StoreMFInventory(player);
		}
	}
};