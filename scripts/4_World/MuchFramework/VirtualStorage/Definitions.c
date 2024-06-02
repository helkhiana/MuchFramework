enum MF_Item_Type
{
    Regular,
    Magazine, // Magazine_Base do we separate in diff types
    Ammo, // Ammunition_Base
    Weapon, // special Pistol_Base Rifle_Base Launcher_Base
	Energy, //items with energy manager
    Vehicle, //CarScript special spawn with parts
    Food, //Edible_Base
    Bottle, //Bottle_Base
    Special, //
    Unknown //we don't know the type so it should be skipped? 
};

class MF_Food_State
{
	FoodStageType StageType;
	FoodStageType LastStageType;
	float DecayTimer;
};

class MF_Energy_State
{
	float EnergyAmount;
};

class MF_Cartridge_Info
{
	int infoIndex;
	string className;
	float damage;
};

class MF_Cartridge_Info_List
{
	ref array<ref MF_Cartridge_Info> list = new array<ref MF_Cartridge_Info>;
};

class MF_Weapon_State
{
	bool chamberIsFull = false;
	int current_muzzle = -1;
	int mode_count = -1;
	ref array<int> muzzle = new array<int>;
	bool isJammed = false;
	ref map<int, ref MF_Cartridge_Info> chamberCartridgeInfo = new map<int, ref MF_Cartridge_Info>;
	ref map<int, ref MF_Cartridge_Info_List> intMagCrtrdgInfo = new map<int, ref MF_Cartridge_Info_List>;
};

class MF_Magazine_State
{
	int ammoCount = -1;
	ref array<ref MF_Cartridge_Info> magCrtrdgInfo = new array<ref MF_Cartridge_Info>;
};

class MF_Item_CustomVariables
{
	ref map<string, float> itemFloatVariables = new map<string, float>;
	ref map<string, int> itemIntVariables = new map<string, int>;
	ref map<string, bool> itemBoolVariables = new map<string, bool>;
	ref map<string, vector> itemVectorVariables = new map<string, vector>;
	ref map<string, string> itemStringVariables = new map<string, string>;
};


class MF_Inventory
{
	[NonSerialized()]
	protected EntityAI m_Entity;
	[NonSerialized()]
	protected bool m_StoreCargo;

	string typeName;
	int index;
	float health;
	int row;
	int col;
	bool flipped;
	int agents = 0;
	MF_Item_Type itemType = MF_Item_Type.Regular;
	ref MF_Weapon_State wpnState;
	ref MF_Magazine_State magState;
	ref MF_Energy_State energyState;
	ref MF_Food_State foodState;

	ref array<ref MF_Inventory> attachments = new array<ref MF_Inventory>;
	ref array<ref MF_Inventory> cargo = new array<ref MF_Inventory>;
	ref map<string, float> damageZones = new map<string, float>;

	ref array<float> itemBaseVariables = new array<float>;
	ref MF_Item_CustomVariables customVariables;
	InventoryLocationType locationType = -1;

	void MF_Inventory(bool storeCargo = true)
	{
		m_StoreCargo = storeCargo;
	}

	bool Store(EntityAI entity) 
	{
		if (!entity)
			return false;
		m_Entity = entity;
		typeName = m_Entity.GetType();

		if (!StoreCargo())
		{
			return false;
		}

		if (!StoreAttachments())
		{
			return false;
		}
		return true;
	}

	bool StoreEntity(EntityAI entity) 
	{
		if (!entity)
			return false;
		m_Entity = entity;
		typeName = m_Entity.GetType();
		health = m_Entity.GetHealth();

		ItemBase item;
		if (Class.CastTo(item, m_Entity)) 
		{
			/// WARNING: THE VANILLA CODE IS CURSED. IF THIS BREAKS, IT'S BOHEMIA'S FAULT.
			item.SerializeNumericalVars(itemBaseVariables);
			agents = item.GetAgents();
		}
		if(m_Entity.IsMagazine())
		{
			itemType = MF_Item_Type.Magazine;
			Magazine_Base mag = Magazine_Base.Cast(m_Entity);
			if(mag)
			{
				magState = new MF_Magazine_State();
				magState.ammoCount = mag.GetAmmoCount();
				for (int ammoIndex = 0; ammoIndex < mag.GetAmmoCount(); ammoIndex++)
				{
					float damage;
					string className;
					mag.GetCartridgeAtIndex(ammoIndex, damage, className);
					ref MF_Cartridge_Info chamberinfo = new MF_Cartridge_Info();
					chamberinfo.infoIndex = ammoIndex;
					chamberinfo.damage = damage;
					chamberinfo.className = className;
					magState.magCrtrdgInfo.Insert(chamberinfo);
				}
			}
		}

		if(m_Entity.IsWeapon())
		{
			itemType = MF_Item_Type.Weapon;
			StoreWeapon();
		}

        if(m_Entity.IsAmmoPile())
        {
            itemType = MF_Item_Type.Ammo;			
			Magazine_Base ammo = Magazine_Base.Cast(m_Entity);
			if(ammo)
			{
				magState = new MF_Magazine_State();
				magState.ammoCount = ammo.GetAmmoCount();
			}
        }

		if(m_Entity.HasEnergyManager())
		{
            itemType = MF_Item_Type.Energy;	
			energyState = new MF_Energy_State();
			energyState.EnergyAmount = m_Entity.GetCompEM().GetEnergy();
		}

        if(m_Entity.IsKindOf("Edible_Base"))
        {
            itemType = MF_Item_Type.Food;
			foodState = new MF_Food_State();
			Edible_Base edible = Edible_Base.Cast(m_Entity);
			if(edible)
			{
				if (edible.GetFoodStage())
				{
					foodState.StageType = edible.GetFoodStageType();
				}
				foodState.LastStageType = edible.GetLastDecayStage();
				foodState.DecayTimer = edible.GetDecayTimer();
			}			
        }

        if(m_Entity.IsKindOf("Bottle_Base"))
        {
            itemType = MF_Item_Type.Bottle;
        }


		StoreCustomVariables();

		// Get damage zone values. foreach is broken, don't use.
		auto components = m_Entity.GetEntityDamageZoneMap().GetValueArray();
		for (int i = 0; i < components.Count(); ++i) 
		{
			for (int j = 0; j < components[i].Count(); j++) 
			{
				string zone = m_Entity.GetEntityDamageZoneMap().GetKey(i);
				damageZones.Insert(zone, m_Entity.GetHealth(zone, "Health"));
			}
		}

		InventoryLocation il = new InventoryLocation();
		m_Entity.GetInventory().GetCurrentInventoryLocation(il);
		if (il.IsValid()) 
		{
			locationType = il.GetType();
			switch (locationType) 
			{
			case InventoryLocationType.ATTACHMENT:
				index = il.GetSlot();
				break;
			}
		}

		if(m_StoreCargo)
		{
			if (!StoreCargo())
			{
				return false;
			}
		}

		if (!StoreAttachments())
		{
			return false;
		}
		return true;
	}

	EntityAI CreateSubEntity(notnull EntityAI parent)
	{
		if (!parent)
		{
			return NULL;
		}
		if(itemType == MF_Item_Type.Magazine)
		{
			Weapon_Base wpn = Weapon_Base.Cast(parent);
			if(wpn)
			{
				EntityAI magAtt = EntityAI.Cast(wpn.MF_SpawnAttachedMagazine(typeName, false));
				if(magAtt)
				{
					wpn.ForceSyncSelectionState();
					return magAtt;
				}
				return NULL;
			}
		}
		switch (locationType) 
		{
			case InventoryLocationType.ATTACHMENT:
				EntityAI attachment = parent.GetInventory().CreateAttachmentEx(typeName, index);
				if(attachment)
				{
					return attachment;
				}
				return NULL;
			break;
			case InventoryLocationType.CARGO:
				EntityAI cargoItem = parent.GetInventory().CreateEntityInCargoEx(typeName, index, row, col, flipped);
				if(cargoItem)
				{
					return cargoItem;
				}
				return NULL;
		}
		return NULL;
	}
	
	bool Restore(notnull EntityAI entity)
	{	
		m_Entity = entity;

		if (!RestoreCargo(m_Entity))
		{
			return false;
		}

		if (!RestoreAttachments(m_Entity))
		{
			return false;
		}

		m_Entity.AfterStoreLoad();
		m_Entity.SetSynchDirty();
		
		return true;
	}

	bool RestoreSubEntity(notnull EntityAI parent, bool heal = false) 
	{
		return RestoreEntity(parent, null, heal);
	}

	bool RestoreParentEntity(notnull EntityAI entity, bool heal = false)
	{
		return RestoreEntity(null, entity, heal);
	}

	//heal is for MCP feature
	bool RestoreEntity(EntityAI parent = null, EntityAI entity = null, bool heal = false) 
	{	
		if(entity)
		{
			m_Entity = entity;
		}
		if (!entity)
		{			
			m_Entity = CreateSubEntity(parent);
			
			if (!m_Entity)
			{
				return false;
			}
		}
		
		bool shouldHeal = false;
		if(heal && health != 0.0)
		{
			if(parent && parent.IsInherited(CarScript))
			{
				//only heal if the parent is CarScript...so we don't propagate down
				shouldHeal = true;
			}
			if(m_Entity.IsInherited(CarScript))
			{
				shouldHeal = true;
			}
		}
		if(!shouldHeal)
		{
			m_Entity.SetHealth(health);
			auto zoneNames = damageZones.GetKeyArray();
			auto zoneValues = damageZones.GetValueArray();
			for (int i = 0; i < zoneNames.Count(); ++i) 
			{		
				m_Entity.SetHealth(zoneNames[i], "Health", zoneValues[i]);
			}
		}

		ItemBase item;
		if (Class.CastTo(item, m_Entity)) 
		{
			/// WARNING: THE VANILLA CODE IS CURSED. IF THIS BREAKS, IT'S BOHEMIA'S FAULT.
			item.DeSerializeNumericalVars(itemBaseVariables);
			item.TransferAgents(agents);
		}

		RestoreCustomVariables();

		if(itemType == MF_Item_Type.Ammo)
		{				
			Magazine_Base ammo = Magazine_Base.Cast(m_Entity);
			if(ammo)
			{
				ammo.ServerSetAmmoCount(magState.ammoCount);
			}
		}
		
		if(itemType == MF_Item_Type.Magazine)
		{				
			Magazine_Base mag = Magazine_Base.Cast(m_Entity);
			if(mag)
			{
				mag.ServerSetAmmoCount(0);
				foreach (ref MF_Cartridge_Info mag_info : magState.magCrtrdgInfo)
				{						
					if(!mag.ServerStoreCartridge(mag_info.damage, mag_info.className))
					{
						return false;
					}
				}
			}
		}
		if(itemType == MF_Item_Type.Weapon)
		{
			RestoreWeapon();
		}

		if(itemType == MF_Item_Type.Energy)
		{
			m_Entity.GetCompEM().SetEnergy(energyState.EnergyAmount);
		}

		if(itemType == MF_Item_Type.Food)
		{
			Edible_Base edible = Edible_Base.Cast(m_Entity);
			if(edible)
			{
				if (edible.GetFoodStage())
				{
					edible.GetFoodStage().ChangeFoodStage(foodState.StageType);
				}
				edible.MF_SetLastDecayStage(foodState.LastStageType);
				edible.MF_SetDecayTimer(foodState.DecayTimer);
			}
		}

		if (!RestoreCargo(m_Entity))
		{
			return false;
		}

		if (!RestoreAttachments(m_Entity, heal))
		{
			return false;
		}

		m_Entity.AfterStoreLoad();
		m_Entity.SetSynchDirty();
		
		return true;
	}

	protected bool StoreAttachments() 
	{
		int attCount = m_Entity.GetInventory().AttachmentCount();

		EntityAI codelock = NULL;
		ItemBase itemBase = ItemBase.Cast(m_Entity);
		if(itemBase)
		{
			#ifdef RA_BASEBUILDING			
			codelock = itemBase.FindCodeLock();
			#endif
			#ifdef Codelock
			codelock = itemBase.GetCodeLock();
			#endif		
		}
		for (int i = 0; i < attCount; ++i) 
		{
			EntityAI att = m_Entity.GetInventory().GetAttachmentFromIndex(i);
			if (!att)
				continue;
			if(codelock && codelock == att)
			{
				continue;
			}
			MF_Inventory attInv = new MF_Inventory(m_StoreCargo);
			if (!attInv.StoreEntity(att))
				return false;

			attachments.Insert(attInv);
		}

		return true;
	}

	protected bool StoreCargo() 
	{
		if(m_Entity.GetInventory() && m_Entity.GetInventory().GetCargo())
		{
			int attCount = m_Entity.GetInventory().GetCargo().GetItemCount();
			for (int i = 0; i < attCount; ++i) 
			{
				EntityAI att = m_Entity.GetInventory().GetCargo().GetItem(i);
				if (!att)
					continue;
					
				MF_Inventory attInv = new MF_Inventory();
				bool lFlipped = att.GetInventory().GetFlipCargo();
				int lRow = -1;
				int lCol = -1;
				m_Entity.GetInventory().GetCargo().GetItemRowCol(i, lRow, lCol);
				attInv.row = lRow;
				attInv.col = lCol;
				attInv.flipped = lFlipped;
				if (!attInv.StoreEntity(att))
					return false;
	
				cargo.Insert(attInv);
			}
		}		

		return true;
	}

	protected bool RestoreAttachments(EntityAI parent, bool heal = false) 
	{
		for (int i = 0; i < attachments.Count(); ++i)
		{
			if (!attachments[i].RestoreSubEntity(parent, heal))
			{
				return false;
			}
		}

		return true;
	}

	protected bool RestoreCargo(EntityAI parent) 
	{
		for (int i = 0; i < cargo.Count(); ++i)
		{
			if (!cargo[i].RestoreSubEntity(parent))
			{
				return false;
			}
		}

		return true;
	}

	protected void StoreWeapon()
	{
		Weapon_Base wpn = Weapon_Base.Cast(m_Entity);			
		if(wpn)
		{
			int mi = wpn.GetCurrentMuzzle();
			wpnState = new MF_Weapon_State();
			wpnState.chamberIsFull = wpn.IsChamberFull(mi);
			wpnState.current_muzzle = wpn.GetCurrentMuzzle();
			wpnState.mode_count = wpn.GetMuzzleCount();
			wpnState.isJammed = wpn.IsJammed();
			if(wpnState.mode_count == 0)
			{
				return;
			}
			for (int muzzleIndex = 0; muzzleIndex < wpnState.mode_count; ++muzzleIndex)
			{
				float damage = -1;
				string ammoTypeName = "";
				wpnState.muzzle.Insert(wpn.GetCurrentMode(muzzleIndex));
				if (!wpn.IsChamberEmpty(muzzleIndex))
				{
					if (wpn.GetCartridgeInfo(muzzleIndex, damage, ammoTypeName))
					{						
						MF_Cartridge_Info chamberinfo = new MF_Cartridge_Info();
						chamberinfo.infoIndex = muzzleIndex;
						chamberinfo.className = ammoTypeName;
						chamberinfo.damage = damage;
						wpnState.chamberCartridgeInfo.Insert(muzzleIndex, chamberinfo);
					}
				}
				if(wpn.HasInternalMagazine(muzzleIndex) && wpn.GetInternalMagazineCartridgeCount(muzzleIndex) > 0)
				{
					MF_Cartridge_Info_List info_list = new MF_Cartridge_Info_List();
					for (int cartridgeIndex = 0; cartridgeIndex < wpn.GetInternalMagazineCartridgeCount(muzzleIndex); ++cartridgeIndex)
					{
						if (wpn.GetInternalMagazineCartridgeInfo(muzzleIndex, cartridgeIndex, damage, ammoTypeName))
						{
							MF_Cartridge_Info info = new MF_Cartridge_Info;
							info.infoIndex = cartridgeIndex;
							info.className = ammoTypeName;
							info.damage = damage;
							info_list.list.Insert(info);
						}
					}
					wpnState.intMagCrtrdgInfo.Insert(muzzleIndex, info_list);
				}
			}				
		}
	}

	protected void RestoreWeapon()
	{
		Weapon_Base wpn = Weapon_Base.Cast(m_Entity);			
		if(wpn)
		{
			int mi = wpn.GetCurrentMuzzle();
			wpn.SetJammed(wpnState.isJammed);
			wpn.SetCurrentMuzzle(wpnState.current_muzzle);
			for (int muzzleIndex = 0; muzzleIndex < wpnState.mode_count; ++muzzleIndex)
			{
				ref MF_Cartridge_Info chamberinfo = new MF_Cartridge_Info();
				if(wpnState.chamberCartridgeInfo.Find(muzzleIndex, chamberinfo) != -1)
				{
					if(chamberinfo)
					{
						wpn.PushCartridgeToChamber(muzzleIndex, chamberinfo.damage, chamberinfo.className);
					}
				}
				wpn.SetMuzzleMode(muzzleIndex, wpnState.muzzle[muzzleIndex]);
			}	
			wpn.SetCurrentMode(wpnState.current_muzzle, wpnState.muzzle[wpnState.current_muzzle]);
			
			array<int> crtrdgIndexes = wpnState.intMagCrtrdgInfo.GetKeyArray();
			foreach (int crtIndex : crtrdgIndexes)
			{
				ref MF_Cartridge_Info_List info_list = new MF_Cartridge_Info_List();
				if(wpnState.intMagCrtrdgInfo.Find(crtIndex, info_list) != -1)
				{
					if(info_list && info_list.list)
					{
						foreach(MF_Cartridge_Info intMagInfo : info_list.list)
						{
							wpn.PushCartridgeToInternalMagazine(crtIndex, intMagInfo.damage, intMagInfo.className);
						}
					}
				}
			}
			wpn.RandomizeFSMState();						
			wpn.Synchronize();
		}
	}

	void StoreCustomVariables()
	{		
		#ifdef MuchCarKey
		MCK_CarKey_Base carkey = MCK_CarKey_Base.Cast(m_Entity);
		if(carkey)
		{
			InitializeCustomVariables();
			customVariables.itemIntVariables.Insert("MCK_CarKey_Base.m_MCKId", carkey.GetMCKId());
		}
		#endif
	}

	void RestoreCustomVariables()
	{		
		#ifdef MuchCarKey
		MCK_CarKey_Base carkey = MCK_CarKey_Base.Cast(m_Entity);
		if(carkey)
		{
			int mckId = -1;
			if(customVariables.itemIntVariables.Find("MCK_CarKey_Base.m_MCKId", mckId))
			{
				carkey.SetNewMCKId(mckId);
			}
		}
		#endif
	}

	protected void InitializeCustomVariables()
	{
		if(!customVariables)
		{	
			customVariables = new MF_Item_CustomVariables();
		}
	}

	protected MF_Weapon_State GetWeaponState()
	{
		if(wpnState)
		{
			return wpnState;
		}

		wpnState = new MF_Weapon_State();
		return wpnState;
	}

};
