#ifdef SERVER
class PluginWriteLog extends PluginBase
{
	private FileHandle m_LogFile;
	private bool m_LogEnabled                   = false;
	private static const string m_profileFolder = "$profile:";
	protected string m_LogName       = "YourLogName_";
	protected string m_LogFullFileName  = "TM_Trades_";
	
	int year, month, day, hour, minute, second;
	string sYear, sMonth, sDay, sHour, sMinute, sSecond, currentDateTime, currentTime;
	
	void ~PluginWriteLog()
	{
		Print(this.ToString() + " Closed");
		if (GetGame().IsServer())
		{
			// Close Log File
			CloseFile(m_LogFile);
		}
	}

	override void OnInit()
	{     
		Print("Initializing plugin: " + this.ToString());
		
		if (!FileExist(m_profileFolder))
			MakeDirectory(m_profileFolder);	
        
		//setting currentDateTime
		SetCurrentTime();
		m_LogFullFileName = m_profileFolder + "/" + m_LogName + currentDateTime + ".log";
    }
	
	bool CreateNewLogFile(string logFilePath)
	{
		if (GetGame().IsServer())
		{
			SetCurrentTime();		
			m_LogFile = OpenFile(logFilePath, FileMode.WRITE);
			if (m_LogFile != 0)
			{
				FPrintln(m_LogFile, "Log Created: " + currentDateTime);
				return true;
			}
			Print("Unable to create" + logFilePath + " file in Profile.");
			return false;
		}
		return false;
	}

	void Log(string text)
	{
		if(!m_LogEnabled)
		{				
			// Create New Log
			if (CreateNewLogFile(m_LogFullFileName))
			{				
				m_LogEnabled = true;
			}

		}
		if (m_LogEnabled)
		{
			SetCurrentTime();			
			FPrintln(m_LogFile, currentTime + text);
		}
	}

	protected void SetCurrentTime()
	{
		// Setting Time Variables for new file name
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
		
		// Setting String for Time Variables for new file name
		sYear = year.ToString();
		
		sMonth = month.ToString();
		if (sMonth.Length() == 1)
		{
			sMonth = "0" + sMonth;
		}
		
		sDay = day.ToString();
		if (sDay.Length() == 1)
		{
			sDay = "0" + sDay;
		}
		
		sHour = hour.ToString();
		if (sHour.Length() == 1)
		{
			sHour = "0" + sHour;
		}
		
		sMinute = minute.ToString();
		if (sMinute.Length() == 1)
		{
			sMinute = "0" + sMinute;
		}
		
		sSecond = second.ToString();
		if (sSecond.Length() == 1)
		{
			sSecond = "0" + sSecond;
		}
		
		currentDateTime = "_" + sYear + "-" + sMonth + "-" + sDay + "_" + sHour + "-" + sMinute + "-" + sSecond;
		currentTime = sHour + ":" + sMinute + ":" + sSecond + " | ";
	}
};
#endif