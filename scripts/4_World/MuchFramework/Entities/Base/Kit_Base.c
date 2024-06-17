class Msp_Item : Msp_ItemBase
{	
	override bool CanPutInCargo(EntityAI parent)
	{
		return false;
	}

	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
	}
};

class Msp_Kit : Msp_ItemBase
{
	void Msp_Kit()
	{
		RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
	}
	
	override bool IsBasebuildingKit()
	{
		return true;
	}

	override bool IsDeployable()
	{
		return true;
	}

	override string GetPlaceSoundset()
	{
		return "putDown_FenceKit_SoundSet";
	}

	override bool CanStoreCargo()
	{
		return false;
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
		RemoveAction(ActionMFVSRestoreContents);
		RemoveAction(ActionMFVSStoreContents);
	}
	
	#ifdef RA_BASEBUILDING
    override float GetCostToUpkeep()
	{
		return 0;
	}
	#endif
};