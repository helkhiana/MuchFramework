modded class Edible_Base
{	
	float m_PreservationMultiplier = 1.0;
	bool m_EnableFridgePreservation = false;
	#ifdef SERVER
	override void EEInit()
	{
		super.EEInit();
		m_PreservationMultiplier = GetMFSettingsConfig().Fridge_Settings.PreservationMultiplier;
		m_EnableFridgePreservation = GetMFSettingsConfig().Fridge_Settings.EnableFridgePreservation;
	}
	#endif

#ifndef WG_PerishableFood
	override void ProcessDecay( float delta, bool hasRootAsPlayer )
	{
		if(m_EnableFridgePreservation)
		{
			InventoryLocation invLocation = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation(invLocation);
			EntityAI parent = GetHierarchyRoot();
			float m_ConservationMultiplier = 1.0;
			if (parent && invLocation.GetType() == InventoryLocationType.CARGO)
			{				
				if(MF_Helper.IsFridgeOn(parent) && m_PreservationMultiplier > 0)
				{
					m_ConservationMultiplier = m_PreservationMultiplier;
					delta = delta / m_ConservationMultiplier;
				}
			}
			// if(this.IsKindOf("DeerSteakMeat"))
			// {	
			// 	Print( "-------------------------" );
			// 	Print( this );
			// 	Print( m_ConservationMultiplier );
			// 	Print( delta );	
			// 	Print( m_DecayTimer );
			// 	Print( m_DecayDelta );
			// 	Print( m_LastDecayStage );
			// }
		}
		super.ProcessDecay(delta,hasRootAsPlayer);
	}
#endif
    void MF_SetDecayTimer(float newTimer)
    {
        m_DecayTimer = newTimer;
    }

    void MF_SetLastDecayStage(FoodStageType newStage)
    {
        m_LastDecayStage = newStage;
    }
};