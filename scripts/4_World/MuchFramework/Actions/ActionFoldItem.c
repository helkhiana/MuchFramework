class ActionFoldItemCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(3);
	}
}

class ActionFoldItem : ActionContinuousBase
{
	void ActionFoldItem()
	{
		m_CallbackClass = ActionFoldItemCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}

	override void CreateConditionComponents()
	{
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINotPresent;
	}

	override string GetText()
	{
		return "#fold";
	}

	override typename GetInputType()
	{
		return ContinuousInteractActionInput;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (target && target.GetObject())
		{
			Msp_Foldable_Item foldable_item = Msp_Foldable_Item.Cast(target.GetObject());
			if (foldable_item && !foldable_item.IsFolded())
				return true;
		}
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		Msp_Foldable_Item foldable_item = Msp_Foldable_Item.Cast(action_data.m_Target.GetObject());
		if (foldable_item)
			foldable_item.Fold();
	}

	override string GetAdminLogMessage(ActionData action_data)
	{
		return " folded " + action_data.m_Target.GetObject().GetDisplayName();
	}
};