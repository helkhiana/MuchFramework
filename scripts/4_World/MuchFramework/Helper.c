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
			int count = children.Count();
			for (int i = 0; i < count; ++i)
			{
				EntityAI child = children.Get(i);
				if ( child )
				{
					//If you copy this code again, youre a pos and karma will catch up
					item.GetInventory().DropEntity(InventoryMode.SERVER, item, child);
					GetGame().ObjectDelete(child);
				}
			}
		}
	}
};