class ActionTrashItemsCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime( 5 );
	}
};

class ActionTrashItems: ActionContinuousBase
{
	void ActionTrashItems()
	{
        m_CallbackClass = ActionTrashItemsCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_CRAFTING;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
	}

	override string GetText()
	{
        return "Throw away trash";
	}
    
    override typename GetInputType()
	{
		return ContinuousInteractActionInput;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		Object targetObject = target.GetObject();
        Msp_TrashCan myItem = Msp_TrashCan.Cast( targetObject );
        if (myItem && !myItem.IsMspInvEmpty())
            return true; 
		return false;
	}
		
	override void OnFinishProgressServer( ActionData action_data )
	{
		Msp_TrashCan myItem = Msp_TrashCan.Cast( action_data.m_Target.GetObject() );
		if (myItem)
		{		
			MF_Helper.RemoveItemsInCargo(myItem);
		}	
	}
};