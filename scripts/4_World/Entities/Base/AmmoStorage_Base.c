class Msp_AmmoStorage_Base : Msp_Storage_Base 
{	
	void Msp_AmmoStorage_Base()
	{
		m_AllowedMSPCargo = {"Box_Base","Ammunition_Base"};
		m_MSPCargoTagName = "isAmmunitionCargo";
	}
};