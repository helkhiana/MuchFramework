class ActionChangeType: ActionInteractBase
{
	void ActionChangeType()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
		m_Text = "Change";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		if(!targetObject)
		{
			return false;
		}
		
		Msp_ItemBase itemMF = Msp_ItemBase.Cast( targetObject );
		if (itemMF && player)
		{
			string newItemName = itemMF.GetNextInterchangeableItem();
			if(newItemName == "")
			{
				return false;
			}
			return true;
		}

		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		Msp_ItemBase item = Msp_ItemBase.Cast( targetObject );
		if(item)
		{
			string newItemName = item.GetNextInterchangeableItem();
			if(newItemName == "")
			{
				return;
			}
			vector itemPos = item.GetPosition();
			vector itemOrientation = item.GetOrientation();
				
			Msp_ItemBase newItem = Msp_ItemBase.Cast(GetGame().CreateObject(newItemName, itemPos));
			newItem.SetPosition(itemPos);
			newItem.SetOrientation(itemOrientation);
			MoveItems(item, newItem);
			if(newItem)
			{
				item.Delete();
			}
		}
	}

	//we currently only do slots
	//todo: expand to cargo too
	//TransferInventory misc func doesn't seem to work
	void MoveItems(Msp_ItemBase oldItem, Msp_ItemBase newItem)
	{		
		for (int i = 0; i < oldItem.GetInventory().GetAttachmentSlotsCount(); i++)
		{
			int slot = oldItem.GetInventory().GetAttachmentSlotId(i);
			EntityAI attachment = oldItem.GetInventory().FindAttachment(slot);

			if (attachment)
			{
				if (newItem.GetInventory().CanAddAttachment(attachment))
				{
					oldItem.ServerTakeEntityToTargetInventory(newItem, FindInventoryLocationType.ATTACHMENT, attachment);
				}
				else
				{
					oldItem.GetInventory().DropEntity(InventoryMode.SERVER, oldItem, attachment);
				}
			}
		}
	}
};