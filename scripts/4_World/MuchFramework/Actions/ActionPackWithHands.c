class ActionPackWithHandsCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime( UATimeSpent.DEFAULT_DECONSTRUCT  / 2 );
	}
};

class ActionPackWithHands: ActionContinuousBase
{
	private ref array<typename> AllowedTypes = {Msp_Item, Msp_Openable_Base};
	void ActionPackWithHands()
	{
		m_CallbackClass = ActionPackWithHandsCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
		m_Text = "#pack_tent";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINotPresent;
	}

	override typename GetInputType()
	{
		return ContinuousInteractActionInput;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if (target && target.GetObject())
		{			
			Msp_ItemBase myItem = Msp_ItemBase.Cast( target.GetObject() );
			if(myItem)
			{
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
		Msp_ItemBase myItem = Msp_ItemBase.Cast( action_data.m_Target.GetObject() );
		if(myItem)
		{
			name = myItem.Get_KitName();
			myItem.Delete();
			ItemBase.Cast( GetGame().CreateObject(name, pos) );
		}		
	}	
}