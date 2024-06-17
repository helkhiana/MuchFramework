// enum MSP_HoloAdjustMode
// {
//     Raise = 1,
//     Lower,
//     Left,
//     Right,
//     Backwards,
//     Forward
// };

// modded class MissionGameplay 
// {
//     override void OnUpdate(float timeslice) 
//     {
//         super.OnUpdate(timeslice);

//         Input input = GetGame().GetInput();
//         if (input.LocalPress("MF_RaiseHolo", false)) 
//         {
//             MspAdjustHolo(MSP_HoloAdjustMode.Raise);
//             return;
//         }
//         if (input.LocalPress("MF_LowerHolo", false)) 
//         {
//             MspAdjustHolo(MSP_HoloAdjustMode.Lower);
//             return;
//         }
//         if (input.LocalPress("MF_LeftHolo", false)) 
//         {
//             MspAdjustHolo(MSP_HoloAdjustMode.Left);
//             return;
//         }
//         if (input.LocalPress("MF_RightHolo", false)) 
//         {
//             MspAdjustHolo(MSP_HoloAdjustMode.Right);
//             return;
//         }
//         if (input.LocalPress("MF_BackHolo", false)) 
//         {
//             MspAdjustHolo(MSP_HoloAdjustMode.Backwards);
//             return;
//         }
//         if (input.LocalPress("MF_ForwardHolo", false)) 
//         {
//             MspAdjustHolo(MSP_HoloAdjustMode.Forward);
//             return;
//         }
//     }

//     void MspAdjustHolo(int mode)
//     {
//         PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
//         if(player)
//         {
//             if (player.IsPlacingLocal())
//             {				
//                 Msp_ItemBase projection = Msp_ItemBase.Cast(player.GetHologramLocal().GetProjectionEntity());
//                 if(projection)
//                 {
//                     vector currentAdjustPos = projection.Get_ItemAdjustedPlacingPos();
//                     switch (mode)
//                     {
//                     case MSP_HoloAdjustMode.Raise:                        
//                         currentAdjustPos[1] = currentAdjustPos[1] + 0.1;
//                         break;
//                     case MSP_HoloAdjustMode.Lower:                        
//                         currentAdjustPos[1] = currentAdjustPos[1] - 0.1;
//                         break;
//                     case MSP_HoloAdjustMode.Left:                        
//                         currentAdjustPos[0] = currentAdjustPos[0] + 0.1;
//                         break;
//                     case MSP_HoloAdjustMode.Right:                        
//                         currentAdjustPos[0] = currentAdjustPos[0] - 0.1;
//                         break;
//                     case MSP_HoloAdjustMode.Backwards:                        
//                         currentAdjustPos[2] = currentAdjustPos[2] + 0.1;
//                         break;
//                     case MSP_HoloAdjustMode.Forward:                        
//                         currentAdjustPos[2] = currentAdjustPos[2] - 0.1;
//                         break;
//                     default:
//                         break;
//                     }
//                     projection.Set_ItemAdjustedPlacingPos(currentAdjustPos);
//                 }
//             }
//         }
//     }
// };

modded class MissionGameplay 
{	
    private static const float m_MF_CycleInputDelay = 1.5;
    private float m_MF_CycleInputDelay_Timer = 0.0;

	bool IsInputKeyNameReleased(string inputName)
	{
		Input input = GetGame().GetInput();
		if (input && !IsChatMenuOpen()) 
		{
			return input.LocalRelease( inputName );
		}
		return false;
	}

	bool IsChatMenuOpen()
	{
		return GetGame().GetUIManager().IsMenuOpen( MENU_CHAT_INPUT );
	}

	override void OnUpdate( float timeslice ) 
	{
		super.OnUpdate( timeslice );
		PlayerBase playerPB = PlayerBase.Cast(GetGame().GetPlayer());
		if (playerPB) 
		{
            m_MF_CycleInputDelay_Timer += timeslice;
            if(m_MF_CycleInputDelay_Timer > m_MF_CycleInputDelay)
            {
                m_MF_CycleInputDelay_Timer = 0;
                
		        UIScriptedMenu menuOpened = m_UIManager.GetMenu();
                if (menuOpened == NULL && playerPB.IsPlacingLocal())
                {
                    if(KeyState( KeyCode.KC_T ) > 0 )
                    {
						GetGame().RPCSingleParam(playerPB, MUCH_RPC.RPC_SERVER_CYCLEPLACINGOPTIONS, null, true, playerPB.GetIdentity());
                        playerPB.GetHologramLocal().CyclePlacingOptionsClient();
                    }
                }
            }
		}
	}
};