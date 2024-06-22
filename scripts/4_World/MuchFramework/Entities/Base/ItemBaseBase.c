class Msp_ItemBase : Container_Base
{
	protected ref array<string> m_AllowedMSPCargo = { };
	protected string m_MSPCargoTagName = "isMedicalItem";
	protected vector m_MSPAdjustedPlacingPosition = "0 0 0";
	protected vector m_MSPAdjustedPlacingOrientation = "0 0 0";

	
	ref MF_Inventory m_MFInventory;
	protected bool m_StoreIsDirty = false;
	protected bool m_HasStoredCargo = false;
	protected bool m_PrevHasStoredCargo = false;
	protected float m_LastCargoStoreUnixTime = 0;
	protected bool m_HasAutoStoreEnabled = false;
	protected bool m_HasAutoStoreOnCloseEnabled = false;
    protected int m_AutoStoreTimerInSeconds = -1;
	protected bool m_HasAutoCloseEnabled = false;
    protected int m_AutoCloseTimerInSeconds = -1;
	protected PluginMFSettingsConfig MFSettings;

	void Msp_ItemBase()
	{		
		RegisterNetSyncVariableBool("m_HasStoredCargo");
		RegisterNetSyncVariableBool("m_PrevHasStoredCargo");
		RegisterNetSyncVariableBool("m_HasAutoStoreEnabled");
		RegisterNetSyncVariableBool("m_HasAutoStoreOnCloseEnabled");
	}

	override void EEInit()
	{
		super.EEInit();
		
		MFSettings = PluginMFSettingsConfig.Cast(GetPlugin(PluginMFSettingsConfig));
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
		#ifdef SERVER
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.LoadMFStoreVariables, 3000, false);
		#endif
	}

	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		DeleteMFInventoryFile();
	}

	void LoadMFStoreData()
	{
		if(IsMFVirtualStorageEnabled())
		{
			InitializeMFInventory();
		}
	}

	void LoadMFStoreVariables()
	{
		if(IsMFVirtualStorageEnabled())
		{
			MF_VirtualStorage_Settings vsSettings = MFSettings.GetSettings().VirtualStorage;
			if(vsSettings)
			{
				m_HasAutoStoreEnabled =  vsSettings.EnableAutoStoreTimer;
				m_AutoStoreTimerInSeconds = vsSettings.AutoStoreTimerInSeconds;
				SetSynchDirty();
			}			
		}
	}
	
    override bool CanPutIntoHands(EntityAI parent)
	{
		if (!super.CanPutIntoHands(parent))
		{
			return false;
		}
		if(HasStoredCargo())
		{
			return false;
		}

		return true;
    }
	
	override bool NameOverride(out string output)
	{
		if(HasStoredCargo())
		{
			string DisplayName;
			GetGame().ObjectGetDisplayName(this, DisplayName);	
			output = DisplayName + " [Stored]";
			return true;
		}
		return super.NameOverride(output);
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
		if (!super.CanReceiveItemIntoCargo(item))
			return false;

		if(HasStoredCargo())
			return false;

		if(IsOpen() && !GetInventory().IsInventoryLockedForLockType( HIDE_INV_FROM_SCRIPT ))
		{
			if(ConfigIsExisting("hasCargoRestrictions") && ConfigGetBool("hasCargoRestrictions"))
			{
				return IsAllowedMSPCargo(item) && super.CanReceiveItemIntoCargo(item);
			}
			return true;
		}

		return false;
	}
	
	override bool CanSwapItemInCargo(EntityAI child_entity, EntityAI new_entity)
	{
		if (!super.CanSwapItemInCargo(child_entity,new_entity))
			return false;

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
		return true;
	}

	bool IsAllowedMSPCargo(EntityAI item)
	{
		if(item.ConfigIsExisting(m_MSPCargoTagName) && item.ConfigGetBool(m_MSPCargoTagName))
		{
			return true;
		}
		
		return MF_Helper.IsAnyKindOf(item, m_AllowedMSPCargo);
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

    string GetNextInterchangeableItem()
    {
        return "";
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
		//call store m_MFInventory
		if(m_StoreIsDirty && m_PrevHasStoredCargo != m_HasStoredCargo)
		{
			m_StoreIsDirty = false;
			//if prev we had cargo means we restored 
			if(m_PrevHasStoredCargo == true)
			{				
				DeleteMFInventoryFile();
				m_HasStoredCargo = false;
				m_PrevHasStoredCargo = false;
				m_LastCargoStoreUnixTime = 0;
				delete m_MFInventory;
				SetSynchDirty();
				return;
			}
			// if prev is false means we stored
			if(m_PrevHasStoredCargo == false)
			{
				SaveMFInventoryFile();
				m_HasStoredCargo = true;
				m_PrevHasStoredCargo = true;				
				m_LastCargoStoreUnixTime = 0;
			}
			delete m_MFInventory;
			SetSynchDirty();
		}
    }
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		LoadMFStoreData();
	}

	override void OnCEUpdate()
	{
		super.OnCEUpdate();
		AutoStoreMFCargo();
	}

	void ResetAutoMFTimer()
	{		
		m_LastCargoStoreUnixTime = 0;
	}

	void AutoStoreMFCargo()
	{
		if(IsMFAutoStoreOnCloseEnabled() && IsMFAutoCloseTimerEnabled())
		{
			return;
		}
		if(m_HasAutoStoreEnabled && CanStoreCargo())
		{
			m_LastCargoStoreUnixTime += m_ElapsedSinceLastUpdate;
			if(m_LastCargoStoreUnixTime >= m_AutoStoreTimerInSeconds)
			{
				ResetAutoMFTimer();
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(StoreMFInventory, 0.02, false);
			}
		} 
		else
		{
			m_LastCargoStoreUnixTime = 0;
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
	bool IsMFVirtualStorageEnabled()
	{
		if(MFSettings && MFSettings.GetSettings())
		{
			MF_VirtualStorage_Settings settings = MFSettings.GetSettings().VirtualStorage;
			if(settings)
			{
				return settings.EnableVirtualStorage;
			}
		}
		return false;
	}

	bool IsMFAutoStoreOnCloseEnabled()
	{
		if(!IsMFVirtualStorageEnabled())
		{
			return false;
		}
		return m_HasAutoStoreOnCloseEnabled;
	}

	bool IsMFAutoCloseTimerEnabled()
	{
		return m_HasAutoCloseEnabled && !m_HasAutoStoreEnabled;
	}

	bool HasStoredCargo()
	{
		return m_HasStoredCargo;
	}

	bool CanStoreCargo()
	{
		if(GetInventory().IsInCargo())
		{
			return false;
		}
		if(IsVSBlackListed())
		{
			return false;
		}
		
		return !HasStoredCargo() && !IsMspInvEmpty();
	}

	protected bool IsVSBlackListed()
	{
		if(MFSettings && MFSettings.GetSettings())
		{
			MF_VirtualStorage_Settings settings = MFSettings.GetSettings().VirtualStorage;
			if(settings)
			{
				array<string> ContainerBlacklist = settings.ContainerBlacklist;
				return MF_Helper.IsAnyKindOf(this, ContainerBlacklist);
			}
		}
		return false;
	}

	bool CanDoVSStoreAction()
	{
		if(IsMFVirtualStorageEnabled())
		{
			if(HasStoredCargo())
			{
				return false;
			}
			if(m_HasAutoStoreOnCloseEnabled)
			{
				return false;
			}
			return true;
		}
		return false;
	}

	bool CanDoVSRestoreAction()
	{
		if(IsMFVirtualStorageEnabled())
		{
			if(HasStoredCargo() && IsOpen())
			{
				return true;
			}
		}
		return false;
	}

	override bool IsMspDismantleAllowed()
	{   
		if(super.IsMspDismantleAllowed())
		{
			return !HasStoredCargo();
		}
		return false;
	}	

	void StoreMFInventory(PlayerBase player = null) 
	{	
		if(HasStoredCargo())
		{
			return;
		}
		ref array<string> blacklist;
		MF_VirtualStorage_Settings vsSettings = MFSettings.GetSettings().VirtualStorage;
		if(vsSettings)
		{
			blacklist = vsSettings.ItemsBlacklist;
		}
		string item = "";
		if(!MF_Helper.CheckItemInventory(this, blacklist, item))
		{
			string reason = MF_Helper.GetDate() + ": The item has the following blacklisted item in inventory." + " " + item;
			if(player)
			{
				MF_Helper.SendMessageToClient(player, reason);
			}
			else
			{
				reason = MF_Helper.GetDate() + ": The item " + this + " has the following blacklisted item in inventory." + " " + item;
				//Print(reason);
			}
			
			return;
		}

		m_MFInventory = new MF_Inventory();
		if(m_MFInventory.Store(this))
		{
			m_StoreIsDirty = true;
			MF_Helper.RemoveItemsInCargo(this);
			m_PrevHasStoredCargo = false;
			m_HasStoredCargo = true;
			if(IsOpen())
			{
				Close();
			}
			MF_LockInventory();
			SetSynchDirty();
		}
	}

	void SetContainerAsStored()
	{
		m_PrevHasStoredCargo = true;
		m_HasStoredCargo = true;
		if(IsOpen())
		{
			Close();
		}
		MF_LockInventory();
		SetSynchDirty();
	}

	void RestoreMFInventory()
	{	
		if(!HasStoredCargo())
		{
			return;
		}
		LoadMFInventoryFile();
		if(m_MFInventory)
		{
			MF_UnlockInventory();
			if(m_MFInventory && m_MFInventory.Restore(this))
			{			
				m_PrevHasStoredCargo = true;
				m_HasStoredCargo = false;
				m_StoreIsDirty = true;
				if(IsOpen())
				{
					MF_UnlockInventory();
				}
				else
				{
					MF_LockInventory();
				}
				SetSynchDirty();
				return;
			}
			MF_Helper.RemoveItemsInCargo(this);
			SetSynchDirty();
			return;
		}
		delete m_MFInventory;
	}

	void InitializeMFInventory()
	{
		if(LoadMFInventoryFile())
		{				
			if(!m_HasStoredCargo)
			{
				m_PrevHasStoredCargo = true;
				m_HasStoredCargo = true;
				if(IsOpen())
				{
					Close();
				}
				MF_LockInventory();

				if(GetInventory().IsInCargo() || IsVSBlackListed())
				{
					RestoreMFInventory();
					return;
				}
				SetSynchDirty();
			}
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

	bool LoadMFInventoryFile() 
	{
		string filename = GetFileName();
		if(!FileExist(filename))
		{
			return false;
		}
		m_MFInventory = new MF_Inventory();
		JsonFileLoader<MF_Inventory>.JsonLoadFile(filename, m_MFInventory);
		return true;
	}

	void SaveMFInventoryFile() 
	{
		MF_Helper.RemoveItemsInCargo(this);
		JsonFileLoader<MF_Inventory>.JsonSaveFile(GetFileName(), m_MFInventory);
	}

	void DeleteMFInventoryFile()
	{
		string fileName = GetFileName();
		if (FileExist(fileName))
		{
			DeleteFile(fileName);
		}
	}

	override void EEItemAttached(EntityAI item, string slot_name)	
	{
		super.EEItemAttached(item, slot_name);
		ResetAutoMFTimer();
	}	
	
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
		ResetAutoMFTimer();
	}	

	override void EECargoIn(EntityAI item)
	{
		super.EECargoIn(item);
		ResetAutoMFTimer();
	}

	override void EECargoOut(EntityAI item)
	{
		super.EECargoOut(item);
		ResetAutoMFTimer();
	}

	override void EECargoMove(EntityAI item)
	{
		super.EECargoMove(item);
		ResetAutoMFTimer();
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionMFVSStoreContents);
		AddAction(ActionMFVSRestoreContents);
	}
};