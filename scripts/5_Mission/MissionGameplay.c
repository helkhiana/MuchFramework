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