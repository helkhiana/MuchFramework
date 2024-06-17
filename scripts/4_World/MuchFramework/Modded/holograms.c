modded class Hologram
{
	protected ref array<typename> m_MSPItemsCollision = { Msp_Kit, Msp_Storage_Base, Msp_Openable_Placeable_Base, Msp_InventoryStorage_Base, Msp_Foldable_Item };
	protected ref array<string> m_MSPItemsHologram = { "Msp_Item", "Msp_Storage_Base", "Msp_InventoryStorage_Base", "Msp_Openable_Placeable_Base", "Msp_Floaties", "Msp_Foldable_Item" };
	
    int m_PlacingOptionIndex = 0;

	override void UpdateHologram( float timeslice )
	{
		super.UpdateHologram(timeslice);

		Msp_ItemBase container = Msp_ItemBase.Cast(m_Parent);
		if(container)
		{
			vector containerPos;
			vector adjustedContainerPos;
			//vector adjustedContainerOri;
			bool not_snapped = true;
			Msp_ItemBase itemBaseProjection = Msp_ItemBase.Cast(m_Projection);
			if(itemBaseProjection)
			{
				vector pos;
				if(itemBaseProjection.MspSnapToCeiling() && GetMspCeilingPosition(itemBaseProjection, 5.0, pos))
				{
					containerPos = pos;
					not_snapped = false;
				}
				adjustedContainerPos = itemBaseProjection.Get_ItemAdjustedPlacingPos();
				//adjustedContainerOri = itemBaseProjection.Get_ItemAdjustedPlacingOrientation();
			}
			if(not_snapped)
			{
				containerPos = GetProjectionEntityPosition( m_Player ) + container.Get_ItemPlacingPos() + adjustedContainerPos;
			}
			vector containerOrientation = AlignProjectionOnTerrain( timeslice ) + container.Get_ItemPlacingOrientation();
			SetProjectionPosition( containerPos );
			SetProjectionOrientation( containerOrientation );		
			m_Projection.OnHologramBeingPlaced( m_Player );
			return;
		}
	}

	override string GetProjectionName(ItemBase item)
	{
		Msp_ItemBase mspItemBase = Msp_ItemBase.Cast( item );
		if(mspItemBase && mspItemBase.m_PlacingOptionIndex > -1)
		{	
			int index = mspItemBase.m_PlacingOptionIndex;
			if(GetGame().IsServer())	
			{
				SetPlacingOptionIndex(mspItemBase.m_PlacingOptionIndex);
			}
			else
			{
				index = m_PlacingOptionIndex;
			}
			
			array<string> placingOptions = new array<string>;			
			if(item && item.ConfigIsExisting("placingOptions"))			
			{
				item.ConfigGetTextArray("placingOptions", placingOptions);
			}
			if(placingOptions && placingOptions.Count() > index)
			{
				return placingOptions[index];
			}
		}

		Msp_Kit item_in_hands = Msp_Kit.Cast( item );
		if ( item_in_hands )
		{
			return item_in_hands.Get_ItemName();
		}
		
		return super.GetProjectionName(item);
	}

	override void EvaluateCollision(ItemBase action_item = null)
	{			
		ItemBase item_in_hands = m_Parent;

		if(item_in_hands.IsAnyInherited(m_MSPItemsCollision))
		{
			SetIsColliding(false);
			return;
		}
		super.EvaluateCollision();
	}

	//Client
	void CyclePlacingOptionsClient()
	{	
		Msp_ItemBase mspItemBase = Msp_ItemBase.Cast( m_Parent );
		if(mspItemBase)
		{			
			array<string> placingOptions = new array<string>;			
			if(mspItemBase && mspItemBase.ConfigIsExisting("placingOptions"))			
			{
				mspItemBase.ConfigGetTextArray("placingOptions", placingOptions);
			}
			if(placingOptions && placingOptions.Count() > 0)
			{
				int newIndex = m_PlacingOptionIndex + 1;
				if(newIndex == placingOptions.Count())
				{
					newIndex = 0;
				}
				SetPlacingOptionIndex(newIndex);		
				RedoHologramEntity();
			}
		}	
	}

	void SetPlacingOptionIndex(int newIndex)
	{
		m_PlacingOptionIndex = newIndex;
	}

	void RedoHologramEntity()
	{
		vector pos = "0 0 0";
		if (GetGame())
		{
			if (m_Projection)
			{
				pos = m_Projection.GetPosition();
				GetGame().ObjectDelete(m_Projection);
			}
	
			if (m_ProjectionTrigger)
			{
				GetGame().ObjectDelete(m_ProjectionTrigger);
			}
		}

		EntityAI projectionEntity;
		if (GetGame().IsMultiplayer() && GetGame().IsServer())
		{	
			projectionEntity = EntityAI.Cast(GetGame().CreateObjectEx(ProjectionBasedOnParent(), pos, ECE_PLACE_ON_SURFACE));
			if(projectionEntity)
			{
				projectionEntity.SetAllowDamage(false);
			}
			SetProjectionEntity(projectionEntity);
			SetAnimations();
		}
		else
		{
			projectionEntity = EntityAI.Cast(GetGame().CreateObjectEx(ProjectionBasedOnParent(), pos, ECE_TRACE|ECE_LOCAL));
			if (projectionEntity == null)
			{
				ErrorEx(string.Format("Cannot create hologram entity from config class %1", ProjectionBasedOnParent()), ErrorExSeverity.WARNING);
				return;
			}

			SetProjectionEntity(projectionEntity);
			SetAnimations();
			CreateTrigger();
			RefreshTrigger();
		}
		
		if (ItemBase.Cast(projectionEntity))
		{
			ItemBase.Cast(GetProjectionEntity()).SetIsHologram(true);
		}
		
		string configPathSlope = string.Format("CfgVehicles %1 slopeTolerance", GetProjectionEntity().GetType());
		if (GetGame().ConfigIsExisting(configPathSlope))
		{
			m_SlopeTolerance = GetGame().ConfigGetFloat(configPathSlope);
		}
		
		string configPathAlign = string.Format("CfgVehicles %1 alignHologramToTerain", GetProjectionEntity().GetType());
		if (GetGame().ConfigIsExisting(configPathAlign))
		{
			m_AlignToTerrain = GetGame().ConfigGetInt(configPathAlign);
		}
		
		string configPathOrientationLimit = string.Format("CfgVehicles %1 yawPitchRollLimit", GetProjectionEntity().GetType());
		if (GetGame().ConfigIsExisting(configPathOrientationLimit))
		{
			m_YawPitchRollLimit = GetGame().ConfigGetVector(configPathOrientationLimit);
		}
	}
		
	override void RefreshVisual()
	{
		if(m_Projection && m_MSPItemsHologram)
		{			
			if(MF_Helper.IsAnyKindOf(m_Projection, m_MSPItemsHologram))
			{
				string config_material = "CfgVehicles" + " " + m_Projection.GetType() + " " + "hologramMaterial";
				string hologram_material = GetGame().ConfigGetTextOut( config_material );
				string config_model = "CfgVehicles" + " " + m_Projection.GetType() + " " + "hologramMaterialPath";
				string hologram_material_path = GetGame().ConfigGetTextOut( config_model ) + "\\" + hologram_material;
				string selection_to_refresh;
				int hidden_selection = 0;
				static const string textureName = "#(argb,8,8,3)color(0.5,0.5,0.5,0.75,ca)";
				
				string config_path = "CfgVehicles" + " " + m_Projection.GetType() + " " + "hiddenSelections";
				array<string> hidden_selection_array = new array<string>;

				GetGame().ConfigGetTextArray( config_path, hidden_selection_array );	
				hologram_material_path += CorrectMaterialPathName();
					
				for (int i = 0; i < hidden_selection_array.Count(); ++i)
				{
					selection_to_refresh = hidden_selection_array.Get(i);
					hidden_selection = GetHiddenSelection( selection_to_refresh );
					// m_Projection.SetObjectTexture( hidden_selection, textureName );
					// m_Projection.SetObjectMaterial( hidden_selection, hologram_material_path );
				}
				return;
			}
		}
		else
		{
			super.RefreshVisual();
		}
		
	}
	
	//doing this so items don't snap to middle of other items
	//removed the part where it checks for the BBox
	override protected vector GetProjectionEntityPosition( PlayerBase player )
	{		
		if(MF_Helper.IsAnyKindOf(m_Projection, m_MSPItemsHologram))
		{
			float minProjectionDistance;
			float maxProjectionDistance; 
			m_ContactDir = vector.Zero;
			vector minMax[2];
			float projectionRadius = GetProjectionRadius();
			float cameraToPlayerDistance = vector.Distance(GetGame().GetCurrentCameraPosition(), player.GetPosition());

			if (projectionRadius < SMALL_PROJECTION_RADIUS) // objects with radius smaller than 1m
			{
				minProjectionDistance = SMALL_PROJECTION_RADIUS;
				maxProjectionDistance = SMALL_PROJECTION_RADIUS * 2;
			}
			else
			{
				minProjectionDistance = projectionRadius;
				maxProjectionDistance = projectionRadius * 2;
				maxProjectionDistance = Math.Clamp(maxProjectionDistance, SMALL_PROJECTION_RADIUS, LARGE_PROJECTION_DISTANCE_LIMIT);
			}
			
			vector from = GetGame().GetCurrentCameraPosition();
			//adjusts raycast origin to player head approx. level (limits results behind the character)
			if ( DayZPlayerCamera3rdPerson.Cast(player.GetCurrentCamera()) )
			{
				vector head_pos;
				MiscGameplayFunctions.GetHeadBonePos(player,head_pos);
				float dist = vector.Distance(head_pos,from);
				from = from + GetGame().GetCurrentCameraDirection() * dist;
			}
			
			vector to = from + (GetGame().GetCurrentCameraDirection() * (maxProjectionDistance + cameraToPlayerDistance));
			vector contactPosition;
			set<Object> hitObjects = new set<Object>();

			DayZPhysics.RaycastRV(from, to, contactPosition, m_ContactDir, m_ContactComponent, hitObjects, player, m_Projection, false, false, ObjIntersectFire);
			
			static const float raycastOriginOffsetOnFail = 0.25;
			static const float minDistFromStart = 0.01;
			// Camera isn't correctly positioned in some cases, leading to raycasts hitting the object directly behind the camera
			if ((hitObjects.Count() > 0) && (vector.DistanceSq(from, contactPosition) < minDistFromStart))
			{
				from = contactPosition + GetGame().GetCurrentCameraDirection() * raycastOriginOffsetOnFail;
				DayZPhysics.RaycastRV(from, to, contactPosition, m_ContactDir, m_ContactComponent, hitObjects, player, m_Projection, false, false, ObjIntersectFire);
			}

			bool isFloating = SetHologramPosition(player.GetPosition(), minProjectionDistance, maxProjectionDistance, contactPosition);
			SetIsFloating(isFloating);	
			
			m_FromAdjusted = from;

			return contactPosition;
		}
		return super.GetProjectionEntityPosition(player);
	}
	
	bool GetMspCeilingPosition(Msp_ItemBase entity, float height, out vector contact_pos ) 
	{
		vector from = entity.GetPosition();
		vector to = "0 0 0";
		vector ceiling = "0 0 0";
		ceiling[1] = height;
		to = from + ceiling;

		vector contact_dir;
		int geometry = ObjIntersectFire;
		int contact_component;
		//Print("got from " + from);
		bool boo = DayZPhysics.RaycastRV( from, to, contact_pos, contact_dir, contact_component, /*hit_object*/NULL, NULL, entity, false, false, geometry );
		//Print("got contact_pos " + contact_pos);
		
		if (boo)
		{
			Debug.DrawSphere(contact_pos , 0.05, Colors.GREEN, ShapeFlags.ONCE);
			contact_pos[1] = contact_pos[1] - entity.GetMspCeilingSnapPos();
			Debug.DrawSphere(contact_pos , 0.05, Colors.BLUE, ShapeFlags.ONCE);
			//Print("adjusted contact_pos " + contact_pos);
		}
		else
		{
			Debug.DrawSphere(from , 0.05, Colors.RED, ShapeFlags.ONCE);
		}
		
		return boo;
	}
	
	bool GetMspWallPosition(Msp_ItemBase entity, float backchecksize, out vector contact_pos ) 
	{
		vector from = entity.GetPosition();
		vector to = "0 0 0";
		vector ceiling = "0 0 0";
		ceiling[2] = backchecksize;
		to = from + ceiling;

		vector contact_dir;
		int geometry = ObjIntersectFire;
		int contact_component;
		//Print("got from " + from);
		bool boo = DayZPhysics.RaycastRV( from, to, contact_pos, contact_dir, contact_component, /*hit_object*/NULL, NULL, entity, false, false, geometry );
		//Print("got contact_pos " + contact_pos);
		
		if (boo)
		{
			Debug.DrawSphere(contact_pos , 0.05, Colors.GREEN, ShapeFlags.ONCE);
			contact_pos[2] = contact_pos[2] + 0.1;
			Debug.DrawSphere(contact_pos , 0.05, Colors.BLUE, ShapeFlags.ONCE);
			//Print("adjusted contact_pos " + contact_pos);
		}
		else
		{
			Debug.DrawSphere(from , 0.05, Colors.RED, ShapeFlags.ONCE);
		}
		
		return boo;
	}

 	// override bool IsFloating() 
	// {
	// 	if (m_Parent.IsInherited(Msp_Kit) || m_Parent.IsInherited(Msp_Storage_Base) || m_Parent.IsInherited(Msp_Openable_Placeable_Base))
	// 	{
	// 		return true;
	// 	}
		
	// 	return super.IsFloating();
	// }

	override void SetProjectionPosition( vector position )
	{	
		//if (m_Parent.IsInherited(Msp_Kit) || m_Parent.IsInherited(Msp_Storage_Base) || m_Parent.IsInherited(Msp_Openable_Placeable_Base) && IsFloating())
		Msp_ItemBase itemBaseProjection = Msp_ItemBase.Cast(m_Projection);
		if(itemBaseProjection && itemBaseProjection.MspSnapToCeiling())
		{
			m_Projection.SetPosition( position );
			return;
		}

		super.SetProjectionPosition(position);
	}

	// vector SetOnGroundOld( vector position )
	// {
	// 	vector from = position;
	// 	vector ground;
	// 	vector player_to_projection_vector;
	// 	float projection_diameter = GetProjectionDiameter();
			
	// 	ground = Vector(0, - Math.Max( projection_diameter, SMALL_PROJECTION_GROUND ), 0);	
	// 	vector to = from + ground;
	// 	vector contact_pos;
	// 	int contact_component;
		
	// 	DayZPhysics.RaycastRV( from, to, contact_pos, m_ContactDir, contact_component, NULL, NULL, m_Projection, false, false );

	// 	HideWhenClose( contact_pos );

	// 	return contact_pos;
	// }
};