modded class Weapon_Base extends Weapon
{
    Magazine MF_SpawnAttachedMagazine(string magazineType = "", bool fullAmmo = true, int ammoCount = 0, bool fillChamber = false)
	{
		// Check if the gun has any magazines registered in config
		if ( GetMagazineTypeCount(0) == 0 )
		{
			ErrorEx(string.Format("No 'magazines' config entry for %1.", this));
			return null;
		}
		
		// Randomize when no specific one is given
		if ( magazineType == "" )
		{
			return null;
		}
		
		EntityAI magAI = GetInventory().CreateAttachment(magazineType);
		if (!magAI)
		{
			ErrorEx(string.Format("Failed to create and attach %1 to %2", GetDebugName(magAI), this));
			return null;
		}
		
		Magazine mag;
		if (!CastTo(mag, magAI))
		{
			ErrorEx(string.Format("Expected magazine, created: %1", GetDebugName(magAI)));
			return null;
		}
		
		if(fullAmmo)
		{
			mag.ServerSetAmmoCount(mag.GetAmmoMax());
		}
		else
		{			
			mag.ServerSetAmmoCount(ammoCount);
		}

		if(fillChamber)
		{
			FillChamber(magazineType);
		}

		// FSM cares about magazine state
		RandomizeFSMState();
		Synchronize();

		return mag;
	}
};