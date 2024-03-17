class ActionDismantleItemCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime( UATimeSpent.DEFAULT_DECONSTRUCT / 2 );
	}
};

class ActionDismantleItem: ActionContinuousBase
{
	private ref array<typename> AllowedTypes = {Msp_Item, Msp_Openable_Base};
	void ActionDismantleItem()
	{
		m_CallbackClass = ActionDismantleItemCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.BASEBUILDING );
	}

	override string GetText()
	{
		return "Dismantle";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		Object targetObject = target.GetObject();
		if ( targetObject )
		{				
			ItemBase myItem = ItemBase.Cast( targetObject );
			if(myItem)
			{
				#ifdef CodeLock
					if(myItem.IsCodeLocked())
						return false;
				#endif
				#ifdef RA_BASEBUILDING
					if(myItem.IsCodeLocked(player.GetIdentity()))
						return false;
				#endif

				if(!myItem.IsMspDismantleAllowed()) 
				{
					return false;
				}
				
				if (myItem.IsAnyInherited(AllowedTypes) && !myItem.IsInherited(Msp_Openable_Placeable_Base))								
					return true;
			}
		}
		return false;
	}
		
	override void OnFinishProgressServer( ActionData action_data ) 
	{
		vector pos = action_data.m_Player.GetPosition();
		string name = "";
		ItemBase myItem = ItemBase.Cast( action_data.m_Target.GetObject() );
		if(myItem)
		{
			name = myItem.Get_KitName();
			myItem.Delete();
			action_data.m_MainItem.DecreaseHealth( 5, false );
			ItemBase.Cast( GetGame().CreateObject(name, pos) );
		}
	}	
}