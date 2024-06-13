//This was created by Helkhiana to solve the CreateInInventory issues
//All rights reserved
//Redistribution of this code cannot be done without explicit permission from Helkhiana
class MF_InventoryTransactions
{
    static EntityAI CreateItem(string classname, notnull EntityAI target, out InventoryLocationType locationType, bool createOnGroundOnFailure = true)
    {
        #ifdef SERVER
        EntityAI newItemLocal = EntityAI.Cast(GetGame().CreateObjectEx(classname,  target.GetPosition(), ECE_PLACE_ON_SURFACE|ECE_LOCAL));
        if(!newItemLocal)
        {
            locationType = InventoryLocationType.UNKNOWN;
            return null;
        }
        EntityAI newItem = EntityAI.Cast(TryMoveLocalItem(newItemLocal, target, locationType));        
        if(newItem)
        {
            return newItem;
        }

        if(createOnGroundOnFailure)
        {
            locationType = InventoryLocationType.GROUND;
            GetGame().RemoteObjectTreeCreate(newItemLocal);
            return newItemLocal;
        }

        locationType = InventoryLocationType.UNKNOWN;
        GetGame().ObjectDelete(newItemLocal);
        #endif

		return null;
    }

    protected static EntityAI TryMoveLocalItem(EntityAI newItemLocal, notnull EntityAI target, out InventoryLocationType locationType)
    {
        #ifdef SERVER        
        InventoryLocation sourceInvLoc = new InventoryLocation();
        newItemLocal.GetInventory().GetCurrentInventoryLocation(sourceInvLoc);
        InventoryLocation targetInvLoc = new InventoryLocation();
		if (target.GetInventory().FindFreeLocationFor(newItemLocal, FindInventoryLocationType.CARGO | FindInventoryLocationType.ATTACHMENT, targetInvLoc))
		{
            //Print(string.Format("TryMoveLocalItem: Item %1 | Target %2", Object.GetDebugName(newItemLocal), Object.GetDebugName(target)));
            //Print(targetInvLoc.DumpToString());
            if(GameInventory.LocationCanMoveEntity(sourceInvLoc, targetInvLoc))
            {
                switch (targetInvLoc.GetType())
                {
                    case InventoryLocationType.ATTACHMENT:
                        if(targetInvLoc.GetParent().CanReceiveAttachment(newItemLocal, targetInvLoc.GetSlot()))
                        {
                            if(target.GetInventory().TakeToDst(InventoryMode.LOCAL, sourceInvLoc, targetInvLoc))
                            {
                                locationType = InventoryLocationType.ATTACHMENT;
                                GetGame().RemoteObjectTreeCreate(newItemLocal);
                                return newItemLocal;
                            }
                        }
                        break;
                    case InventoryLocationType.CARGO:
                        if(targetInvLoc.GetParent().CanReceiveItemIntoCargo(newItemLocal))
                        {                            
                            if(target.GetInventory().TakeToDst(InventoryMode.LOCAL, sourceInvLoc, targetInvLoc))
                            {
                                GetGame().RemoteObjectTreeCreate(newItemLocal);
                                locationType = InventoryLocationType.CARGO;
                                return newItemLocal;
                            }
                        }
                        break;
                    case InventoryLocationType.HANDS:
                        break;
                    default:
                        break;
                }
            }
		}
        locationType = InventoryLocationType.UNKNOWN;
        #endif

		return null;
    }

    //1. Create item local on server
    //2. Try to move item in inventory of player directly
    //3. Try to move in attachments if #2 failed
    //4. Create on ground if allowed to and #3 failed
    static EntityAI CreateItemInPlayerInventory(string classname, notnull PlayerBase target, out InventoryLocationType locationType, bool createOnGroundOnFailure = true)
    {        
        #ifdef SERVER
        //create item and
        //initial check to make sure we can create this class name
        EntityAI newItemLocal = EntityAI.Cast(GetGame().CreateObjectEx(classname,  target.GetPosition(), ECE_PLACE_ON_SURFACE|ECE_LOCAL));
        if(!newItemLocal)
        {
            locationType = InventoryLocationType.UNKNOWN;
            return null;
        }

        EntityAI newItem = EntityAI.Cast(TM_InventoryTransactions.TryMoveLocalItem(newItemLocal, target, locationType));
        if (newItem)
        {
            return newItem;
        }
        else
        {
            for (int i = 0; i < target.GetInventory().GetAttachmentSlotsCount(); i++)
		    {
                int slot = target.GetInventory().GetAttachmentSlotId(i);
                EntityAI attachment = target.GetInventory().FindAttachment(slot);
                if (attachment)
                {
                    if(!attachment.GetInventory().GetCargo() && attachment.GetInventory().GetAttachmentSlotsCount() <= 0)
                    {
                        continue;
                    }
                    newItem = EntityAI.Cast(TM_InventoryTransactions.TryMoveLocalItem(newItemLocal, attachment, locationType));
                    if (newItem)
                    {
                        return newItem;
                    }
                }
            }
        }

        if(createOnGroundOnFailure && !newItem)
        {
            locationType = InventoryLocationType.GROUND;
            GetGame().RemoteObjectTreeCreate(newItemLocal);
            return newItemLocal;
        }

        GetGame().ObjectDelete(newItemLocal);
        locationType = InventoryLocationType.UNKNOWN;
        #endif

        return null;
    }
};