class MSP_StorageRestrictions
{
    static ref array<string> MedicalCargoItems = 
    {
		"BandageDressing" , "PurificationTablets", "CharcoalTablets", "PainkillerTablets", "VitaminBottle", 
		"IodineTincture", "TetracyclineAntibiotics", "Epinephrine", "Morphine", "AntiChemInjector", 
		"InjectionVial", "SalineBag", "StartKitIV", "SalineBagIV", "BloodBagEmpty", "BloodBagFull", "BloodBagIV",
		"BloodTestKit", "Splint", "Thermometer", "Defibrillator", "DisinfectantSpray", "DisinfectantAlcohol", 
        "SewingKit", "Rag", "WG_Medkit_Base", "WG_EmergencyBandage", "WG_Surgicalkit_Base", "GasMask_Filter",
        "GasMask_Filter_Improvised", "SurgicalGloves_ColorBase" 
    };
    static ref array<string> FishCargoItems = 
    {        
        "CarpFilletMeat",
        "Carp",
        "MackerelFilletMeat",
        "Mackerel",
        "Sardines",
        "zeroy_shell",
        "zeroy_chub",
        "CodFilletMeat",
        "zeroy_cod",
        "PikeFilletMeat",
        "zeroy_pike",
        "SalmonFilletMeat",
        "zeroy_salmon",
        "Bitterlings"
    };
};

enum MUCH_RPC 
{
    DIRPC_START = 71666666,
    // Client RPC's
    RPC_CLIENT_SETCONFIG,    
    RPC_CLIENT_CODELOCK_SETCONFIG
};