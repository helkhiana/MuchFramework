class MF_ItemDropWarningMenu : WarningMenuBase
{
	override string GetText()
	{
		//return "#mf_item_drop_notification";
        return "One or multiple items have been dropped on the ground because they couldn't be restored in the inventory.";
	}
};