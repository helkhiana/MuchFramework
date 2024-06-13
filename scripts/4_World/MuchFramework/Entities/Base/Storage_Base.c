class Msp_Storage_Base: Msp_ItemBase 
{   
    override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		ShowHideMspProxies();
	}
    
	override bool CanPutInCargo( EntityAI parent )
    {
		if( !super.CanPutInCargo(parent) ) {return false;}
        return IsMspInvEmpty();
    }
    
    override bool CanPutIntoHands(EntityAI parent)
	{
		if( !super.CanPutIntoHands(parent) ) {return false;}
		return IsMspInvEmpty();		
    } 

	override bool IsContainer()
	{
		return true;
	}
    
    override bool IsDeployable() 
    {
        return true;
    }   
    
    override void OnInventoryEnter(Man player)
    {
        super.OnInventoryEnter(player);
        GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);        
    }
    
    override void OnInventoryExit(Man player)
    {
        super.OnInventoryExit(player);
        GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);        
    }

    override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
	}
};

class Msp_InventoryStorage_Base: Msp_ItemBase 
{
	//uncomment this later?
	// override bool CanStoreCargo()
	// {
	// 	return false;
	// }

	override bool AreChildrenAccessible()
	{
		return true;
	}

    override bool IsDeployable() 
    {
        return true;
    }  

    override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
	}
};