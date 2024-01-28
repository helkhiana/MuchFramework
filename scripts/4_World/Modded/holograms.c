modded class Hologram
{
	protected ref array<typename> m_MSPItemsCollision = { Msp_Kit, Msp_Storage_Base, Msp_Openable_Placeable_Base, Msp_InventoryStorage_Base, Msp_Floaties, Msp_Foldable_Item };
	protected ref array<string> m_MSPItemsHologram = { "Msp_Item", "Msp_Storage_Base", "Msp_InventoryStorage_Base", "Msp_Openable_Placeable_Base", "Msp_Floaties", "Msp_Foldable_Item" };
	
	override void UpdateHologram( float timeslice )
	{
		super.UpdateHologram(timeslice);

		Msp_ItemBase container = Msp_ItemBase.Cast(m_Parent);
		if(container)
		{
			vector containerPos = GetProjectionEntityPosition( m_Player ) + container.Get_ItemPlacingPos();
			vector containerOrientation = AlignProjectionOnTerrain( timeslice ) + container.Get_ItemPlacingOrientation();
			SetProjectionPosition( containerPos );
			SetProjectionOrientation( containerOrientation );		
			m_Projection.OnHologramBeingPlaced( m_Player );
			return;
		}
	}

	override string GetProjectionName(ItemBase item)
	{
		Msp_Kit item_in_hands = Msp_Kit.Cast( item );
		if ( item_in_hands )
			return item_in_hands.Get_ItemName();
		
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

		
	override void RefreshVisual()
	{
		if(m_Projection && m_MSPItemsHologram)
		{			
			foreach( string MSPItem : m_MSPItemsHologram )
			{
				if(m_Projection.IsKindOf(MSPItem))
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
						m_Projection.SetObjectTexture( hidden_selection, textureName );
						m_Projection.SetObjectMaterial( hidden_selection, hologram_material_path );
					}
					return;
				}
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
		foreach( string MSPItem : m_MSPItemsHologram )
		{
			if(m_Projection.IsKindOf(MSPItem))
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
		}
		return super.GetProjectionEntityPosition(player);
	}

 	// override bool IsFloating() 
	// {
	// 	if (m_Parent.IsInherited(Msp_Kit) || m_Parent.IsInherited(Msp_Storage_Base) || m_Parent.IsInherited(Msp_Openable_Placeable_Base))
	// 	{
	// 		return true;
	// 	}
		
	// 	return super.IsFloating();
	// }

	// override void SetProjectionPosition( vector position )
	// {	
	// 	if (m_Parent.IsInherited(Msp_Kit) || m_Parent.IsInherited(Msp_Storage_Base) || m_Parent.IsInherited(Msp_Openable_Placeable_Base) && IsFloating())
	// 	{ 
	// 		vector itemPos = SetOnGroundOld( position ) + m_Parent.Get_ItemPlacingPos();
	// 		m_Projection.SetPosition( itemPos );
	// 		return;
	// 	}

	// 	super.SetProjectionPosition(position);
	// }

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