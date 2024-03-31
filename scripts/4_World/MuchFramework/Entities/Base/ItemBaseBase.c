class Msp_ItemBase : Container_Base
{
	protected ref array<string> m_AllowedMSPCargo = { };
	protected string m_MSPCargoTagName = "isMedicalItem";
	protected vector m_MSPAdjustedPlacingPosition = "0 0 0";
	protected vector m_MSPAdjustedPlacingOrientation = "0 0 0";

	
	ref MF_Inventory inventory;
	protected bool m_StoreIsDirty = false;
	protected bool m_HasStoredCargo = false;
	protected bool m_PrevHasStoredCargo = false;

	void Msp_ItemBase()
	{		
		RegisterNetSyncVariableBool("m_HasStoredCargo");
		RegisterNetSyncVariableBool("m_PrevHasStoredCargo");
	}

	override void EEInit()
	{
		super.EEInit();		
		InitializeMFInventory();
		if(ConfigIsExisting("hasProxiesToHide") && ConfigGetBool("hasProxiesToHide"))
		{
			if(GetGame().IsClient())
			{
				if(GetMuchProxiesConfig())
				{
					ShowHideMspProxies();
				}
				else
				{
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.ShowHideMspProxies, 3000, true);	
				}
			}
			else
			{
				ShowHideMspProxies();
			}	
		}
	}

	override bool CanPutInCargo(EntityAI parent)
	{
		if (!super.CanPutInCargo(parent))
			return false;

		if (parent && (parent == this || (this.GetType() == parent.GetType())))
			return false;

		if(HasStoredCargo())
			return false;
		
		return true;
	}

	override bool CanReceiveItemIntoCargo (EntityAI item)
	{
		if(HasStoredCargo())
			return false;

		if(IsOpen() && !GetInventory().IsInventoryLockedForLockType( HIDE_INV_FROM_SCRIPT ))
		{
			if(ConfigIsExisting("hasCargoRestrictions") && ConfigGetBool("hasCargoRestrictions"))
			{
				return IsAllowedMSPCargo(item) && super.CanReceiveItemIntoCargo(item);
			}
			return super.CanReceiveItemIntoCargo(item);
		}

		return false;
	}
	
	override bool CanSwapItemInCargo(EntityAI child_entity, EntityAI new_entity)
	{
		if(HasStoredCargo())
			return false;

		if(ConfigIsExisting("hasCargoRestrictions") && ConfigGetBool("hasCargoRestrictions"))
		{
			if(IsAllowedMSPCargo(child_entity) && IsAllowedMSPCargo(new_entity))	
			{
				return true;
			}		
			return false;	
		}
		return super.CanSwapItemInCargo(child_entity,new_entity);
	}

	bool IsAllowedMSPCargo(EntityAI item)
	{
		if(item.ConfigIsExisting(m_MSPCargoTagName) && item.ConfigGetBool(m_MSPCargoTagName))
		{
			return true;
		}
		foreach( string allowedCargo : m_AllowedMSPCargo )
		{
			if(item.IsKindOf(allowedCargo))
				return true;
		}
		return false;
	}
	
    bool IsMspFacingPlayer( PlayerBase player)
	{
		vector fence_pos = GetPosition();
		vector player_pos = player.GetPosition();
		vector ref_dir = GetDirection();
		
		//vector fence_player_dir = player_pos - fence_pos;
		vector fence_player_dir = player.GetDirection();
		fence_player_dir.Normalize();
		fence_player_dir[1] = 0; 	//ignore height
		
		ref_dir.Normalize();
		ref_dir[1] = 0;			//ignore height
		
		if ( ref_dir.Length() != 0 )
		{
			float angle = Math.Acos( fence_player_dir * ref_dir );
			
			if ( angle >= 1.3 )
			{
				return true;
			}
		}
		
		return false;
	}
		
	void ShowHideMspProxies()
	{		
		//Print("ShowHideMspProxies: called " + this);
		if(GetMuchProxiesConfig())
		{
			//Simple hidden selection state; 0 == hidden -> false == hidden		
			if(GetMuchProxiesConfig().HideAllProxiesWhenClosed && !IsOpen())
			{
				SetSimpleHiddenSelectionState(0, false);
				SetSimpleHiddenSelectionState(1, false);
				SetSimpleHiddenSelectionState(2, false);
			}
			else
			{
				SetSimpleHiddenSelectionState(0, ShouldHideWeaponsProxies());
				SetSimpleHiddenSelectionState(1, ShouldHideClothesProxies());
				SetSimpleHiddenSelectionState(2, ShouldHideOtherProxies());
			}
			
			//Print("ShowHideMspProxies: Config good " + this);
			if(GetGame().IsClient())
			{
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(this.ShowHideMspProxies);
			}
		}
		else
		{						
			//Print("ShowHideMspProxies: Config bad " + this);
			SetSimpleHiddenSelectionState(0, false);
			SetSimpleHiddenSelectionState(1, false);
			SetSimpleHiddenSelectionState(2, false);
		}
	}

	bool ShouldHideWeaponsProxies()
	{
		return !GetMuchProxiesConfig().HideWeaponProxies;
	}
	bool ShouldHideClothesProxies()
	{
		return !GetMuchProxiesConfig().HideClothingProxies;		
	}
	bool ShouldHideOtherProxies()
	{		
		return !GetMuchProxiesConfig().HideOtherProxies;
	}

	bool MspSnapToCeiling()
	{
		return false;
	}

	float GetMspCeilingSnapPos()
	{
		return 0.0;
	}

	bool MspSnapToWall()
	{
		return false;
	}

	vector Get_ItemAdjustedPlacingPos()
	{	
		return m_MSPAdjustedPlacingPosition;
	}
	
	void Set_ItemAdjustedPlacingPos(vector adjustedVector)
	{	
		m_MSPAdjustedPlacingPosition = adjustedVector;
	}

	vector Get_ItemAdjustedPlacingOrientation()
	{
		return m_MSPAdjustedPlacingOrientation;
	}

	void Set_ItemAdjustedPlacingOrientation(vector adjustedVector)
	{
		m_MSPAdjustedPlacingOrientation = adjustedVector;
	}

	#ifdef RA_BASEBUILDING
    override float GetCostToUpkeep()
	{
		return 0.00001;
	}
	#endif

	override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
		//call store inventory
		if(m_StoreIsDirty && m_PrevHasStoredCargo != m_HasStoredCargo)
		{
			m_StoreIsDirty = false;
			if(m_PrevHasStoredCargo == true)
			{				
				if(inventory && inventory.Restore(this))
				{			
					m_HasStoredCargo = false;
					m_PrevHasStoredCargo = false;
					DeleteMFInventory();
					if(IsOpen())
					{
						MF_UnlockInventory();
					}
					delete inventory;
					SetSynchDirty();
					return;
				}
				MF_Helper.RemoveItemsInCargo(this);
			}
			if(m_PrevHasStoredCargo == false)
			{
				SaveMFInventory();				
				m_HasStoredCargo = true;
				m_PrevHasStoredCargo = true;
			}
			delete inventory;
			SetSynchDirty();
		}
    }

	void MF_LockInventory()
	{
		if(!MF_IsLocked())
		{
			GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
		}
	}

	void MF_UnlockInventory()
	{
		if(MF_IsLocked())
		{
			GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
		}
	}

	bool MF_IsLocked()
	{
		return GetInventory().IsInventoryLockedForLockType( HIDE_INV_FROM_SCRIPT );
	}

	//Virtual Storage
	bool HasStoredCargo()
	{
		return m_HasStoredCargo || m_PrevHasStoredCargo;
	}

	bool CanStoreCargo()
	{
		return !HasStoredCargo() && !IsMspInvEmpty();
	}

	bool CanDoVSAction()
	{
		return m_HasStoredCargo == m_PrevHasStoredCargo;
	}

	override bool IsMspDismantleAllowed()
	{   
		if(super.IsMspDismantleAllowed())
		{
			return !HasStoredCargo();
		}
		return false;
	}	

	void StoreMFInventory() 
	{		
		inventory = new MF_Inventory();
		if(inventory.Store(this))
		{
			//SaveMFInventory();
			m_PrevHasStoredCargo = m_HasStoredCargo;
			m_HasStoredCargo = true;
			m_StoreIsDirty = true;
			if(IsOpen())
			{
				Close();
			}
			MF_LockInventory();
			SetSynchDirty();
		}
	}

	void RestoreMFInventory() 
	{		
		LoadMFInventory();
		if(inventory)
		{			
			m_PrevHasStoredCargo = m_HasStoredCargo;
			m_HasStoredCargo = false;
			m_StoreIsDirty = true;
			SetSynchDirty();
			return;
		}
		delete inventory;
	}

	void InitializeMFInventory()
	{
		LoadMFInventory();
		if(inventory)
		{	
			m_PrevHasStoredCargo = true;
			m_HasStoredCargo = true;
		}
	}

	protected string GetFileName() 
	{
		int b1;
		int b2;
		int b3;
		int b4;
		string filename;
		GetPersistentID(b1, b2, b3, b4);
		filename = GetType()+ "_"+b1+"_"+b2+"_"+b3+"_"+b4;
		string folder = MSP_Constants.ProfileFolder + MSP_Constants.VSFolder + MSP_Constants.VSEntityFolder;
		if (!FileExist(MSP_Constants.ProfileFolder + MSP_Constants.VSFolder))
			MakeDirectory(MSP_Constants.ProfileFolder + MSP_Constants.VSFolder);
		if (!FileExist(folder))
			MakeDirectory(folder);
		return folder + "/" + filename + ".json";
	}

	void LoadMFInventory() 
	{
		inventory = new MF_Inventory();
		JsonFileLoader<MF_Inventory>.JsonLoadFile(GetFileName(), inventory);
	}

	void SaveMFInventory() 
	{
		MF_Helper.RemoveItemsInCargo(this);
		JsonFileLoader<MF_Inventory>.JsonSaveFile(GetFileName(), inventory);
	}

	void DeleteMFInventory()
	{
		string fileName = GetFileName();
		if (FileExist(fileName))
		{
			DeleteFile(fileName);
		}
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionMFVSHandle);
	}
};