#ifdef SERVER
static void Much_Print(string message)
{
    PluginWriteLog m_Logger = PluginWriteLog.Cast(GetPlugin(PluginWriteLog));
    if(m_Logger)
    {
        m_Logger.Log(message);
    }
};
#endif

static ref array<string> MakeACopyOfArray(array<string> OtherArray)
{
    ref array<string> NewArray = new array<string>;
    foreach( string item : OtherArray )
    {
        NewArray.Insert(item);
    }
    return NewArray;
};

static ref array<EntityAI> MakeACopyOfEntityAIArray(array<EntityAI> OtherArray)
{
    array<EntityAI> NewArray = new array<EntityAI>;
    foreach( EntityAI item : OtherArray )
    {
        NewArray.Insert(item);
    }
    return NewArray;
};

class MF_Helper
{    
	static bool IsFridgeOn(EntityAI parent)
	{
		bool isFridge = false;
		EntityAI fridge;
		if(parent.IsInherited(Msp_Fridge_Base))
		{
			isFridge = true;
			fridge = parent;
		}

		if(!fridge)
		{
			array<string> OtherFridges = GetMFSettingsConfig().Fridge_Settings.OtherFridgeClasses;
			foreach (string fridgeClassName : OtherFridges)
			{
				if (parent.IsKindOf(fridgeClassName))
				{
					isFridge = true;
					fridge = parent;
					break;
				}
			}
		}
		if(isFridge && fridge.HasEnergyManager())
		{
			return fridge.GetCompEM().IsWorking();
		}
		return false;
	}

    string GetDisplayNameByClassName(string classname)
	{
		TStringArray itemInfos = new TStringArray;
		
		string cfg = "CfgVehicles " + classname + " displayName";
		string displayName = "";
		GetGame().ConfigGetText(cfg, displayName);
	
		if (displayName == "")
		{
			cfg = "CfgAmmo " + classname + " displayName";
			GetGame().ConfigGetText(cfg, displayName);
		}
		
		if (displayName == "")
		{
			cfg = "CfgMagazines " + classname + " displayName";
			GetGame().ConfigGetText(cfg, displayName);
		}
		
		if (displayName == "")
		{
			cfg = "cfgWeapons " + classname + " displayName";
			GetGame().ConfigGetText(cfg, displayName);
		}
	
		if (displayName == "")
		{
			cfg = "CfgNonAIVehicles " + classname + " displayName";
			GetGame().ConfigGetText(cfg, displayName);
		}
		
		
		return displayName;
	}
	
	static void SendMessageToClient(Object receiver, string message ) //sends given string to client, don't use if not nescessary
	{
		PlayerBase man;
        protected ref Param1<string> m_MessageParam = new Param1<string>(message);
		if (GetGame().IsServer() && Class.CastTo(man, receiver) && m_MessageParam && receiver.IsAlive() && message != "")
		{
			GetGame().RPCSingleParam(man, ERPCs.RPC_USER_ACTION_MESSAGE, m_MessageParam, true, man.GetIdentity());
		}
	}

    static string SecondsToDays(int seconds)
    {
        string Date = "";
        int days = seconds / (24 * 3600);
        Date += days.ToString() + "d ";
        seconds = seconds % (24 * 3600);
        int hours = seconds / 3600;
        Date += hours.ToString() + "h ";
        seconds = seconds % 3600;
        int minutes = seconds / 60;
        seconds = seconds % 60;
        Date += minutes.ToString() + "m ";
        Date += seconds.ToString() + "s ";
        return Date;
    };
	/**
	 * Returns the current date and time as a formatted string.
	 * The format of the string is "YYYY-MM-DD HH:MM:SS".
	 *
	 * @return The current date and time as a formatted string.
	 */
	static string GetDate() 
	{
		int year, month, day, hour, minute, second;
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
		return year.ToStringLen(4) + "-" + month.ToStringLen(2) + "-" + day.ToStringLen(2) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);
	}

	/**
	 * Calculates the Unix time based on the current date and time.
	 *
	 * @return The Unix time as an integer.
	 */
	static int GetUnixTime() 
	{
		int year, month, day, hour, minute, second, i, unixTime = 0;
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);

		for (i = 1970; i < year; i++) {
			if (IsLeapYear(i)) {
				unixTime += 31622400;
			} else {
				unixTime += 31536000;
			}
		}

		int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (IsLeapYear(year)) {
			daysInMonth[1] = 29;
		}

		for (i = 0; i < month - 1; i++) {
			unixTime += daysInMonth[i] * 86400;
		}

		unixTime += (day - 1) * 86400 + hour * 3600 + minute * 60 + second;
		return unixTime;
	}

	/**
	 * Determines whether a given year is a leap year.
	 *
	 * @param year The year to check.
	 * @return True if the year is a leap year, false otherwise.
	 */
	static bool IsLeapYear(int year) 
	{
		if (year % 4 != 0) {
			return false;
		} else if (year % 100 != 0) {
			return true;
		} else if (year % 400 != 0) {
			return false;
		} else {
			return true;
		}
	}

	static void RemoveItemsInCargo(ItemBase item)
	{
		if (item)
		{		
			array<EntityAI> children = new array<EntityAI>;
			item.GetInventory().EnumerateInventory(InventoryTraversalType.LEVELORDER, children);		
			EntityAI codelock = NULL;
			#ifdef RA_BASEBUILDING			
			codelock = item.FindCodeLock();
			#endif
			#ifdef Codelock
			codelock = item.GetCodeLock();
			#endif
			foreach( EntityAI child : children )
			{
				if ( child )
				{
					if(codelock && codelock == child)
					{
						continue;
					}
					//If you copy this code again, youre a pos and karma will catch up
					item.GetInventory().DropEntity(InventoryMode.SERVER, item, child);
					GetGame().ObjectDelete(child);
				}
			}
		}
	}

	static bool CheckItemInventory(EntityAI entity, array<string> itemsBlacklist,  out string reasonItem)
	{		
		if(!entity.GetInventory())
		{
			return true;
		}		

		if(!CheckEntityCargo(entity, itemsBlacklist, reasonItem))
		{
			return false;
		}
		
		if(!CheckEntityAtt(entity, itemsBlacklist, reasonItem))
		{
			return false;
		}

		return true;
	}

	static bool CheckEntityAtt(EntityAI entity, array<string> itemsBlacklist, out string reasonItem)
	{		
		int attCount = entity.GetInventory().AttachmentCount();
		for (int i = 0; i < attCount; ++i) 
		{
			EntityAI att = entity.GetInventory().GetAttachmentFromIndex(i);
			if (!att)
				continue;

			if(!CheckBlacklistedItem(att, itemsBlacklist, reasonItem))
			{
				return false;
			}

			if(!CheckItemInventory(att, itemsBlacklist, reasonItem))
			{
				return false;
			}
		}
		return true;
	}

	static bool CheckEntityCargo(EntityAI entity, array<string> itemsBlacklist, out string reasonItem)
	{
		if(!entity.GetInventory().GetCargo())
		{
			return true;
		}

		int cargoCount = entity.GetInventory().GetCargo().GetItemCount();
		for (int i = 0; i < cargoCount; ++i) 
		{
			EntityAI cargoItem = entity.GetInventory().GetCargo().GetItem(i);
			if (!cargoItem)
				continue;
				
			if(!CheckBlacklistedItem(cargoItem, itemsBlacklist, reasonItem))
			{
				return false;
			}
			if(!CheckItemInventory(cargoItem, itemsBlacklist, reasonItem))
			{
				return false;
			}
		}
		return true;
	}

	static bool CheckBlacklistedItem(EntityAI item, array<string> itemsBlacklist, out string itemReason)
	{
		foreach(string blacklisted : itemsBlacklist)
		{
			//can we do this faster with typename?
			if(item.IsKindOf(blacklisted))
			{
				itemReason = item.GetDisplayName();
				return false;
			}
		}
		return true;
	}
};