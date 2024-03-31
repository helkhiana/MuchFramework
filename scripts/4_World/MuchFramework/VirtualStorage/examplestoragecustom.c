// #ifdef MuchFramework
// moddded class MF_Inventory 
// {
// 	override void StoreCustomVariables()
// 	{		
//         super.StoreCustomVariables();
// 		YOURITEM carkey = YOURITEM.Cast(m_Entity);
// 		if(carkey)
// 		{
//             InitializeCustomVariables();
// 			customVariables.itemIntVariables.Insert("YOURITEM.m_MCKId", carkey.GetMCKId());
// 		}
// 	}
	
// 	override void RestoreCustomVariables()
// 	{	
//         super.RestoreCustomVariables();
// 		YOURITEM carkey = YOURITEM.Cast(m_Entity);
// 		if(carkey)
// 		{
// 			int mckId = -1;
// 			if(customVariables.itemIntVariables.Find("YOURITEM.m_MCKId", mckId))
// 			{
// 				carkey.SetNewMCKId(mckId);
// 			}
// 		}
// 	}
// }
// #endif