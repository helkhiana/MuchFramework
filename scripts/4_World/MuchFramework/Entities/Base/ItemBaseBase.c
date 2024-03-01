class Msp_ItemBase : Container_Base
{
	protected ref array<string> m_AllowedMSPCargo = { };
	protected string m_MSPCargoTagName = "isMedicalItem";
	protected vector m_MSPAdjustedPlacingPosition = "0 0 0";
	protected vector m_MSPAdjustedPlacingOrientation = "0 0 0";

	override void EEInit()
	{
		super.EEInit();		
					
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
		
		return true;
	}

	override bool CanReceiveItemIntoCargo (EntityAI item)
	{
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
};