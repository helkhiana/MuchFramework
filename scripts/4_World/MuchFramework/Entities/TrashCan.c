class Msp_TrashCan : Msp_Openable_Placeable_Base 
{
	override vector Get_ItemPlacingOrientation()
	{
		return "90 0 0";
	}

	override void SetActions()
	{
		super.SetActions();
        AddAction(ActionTrashItems);
	}
};