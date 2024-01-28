class Msp_Fridge_Base : Msp_Openable_Base 
{
	//sound
	const string SOUND_HUMMING 		= "MSP_RefrigeratorHumming_SoundSet";
	const string SOUND_TURN_ON		= "spotlight_turn_on_SoundSet";
	const string SOUND_TURN_OFF		= "spotlight_turn_off_SoundSet";
	
	protected EffectSound m_SoundHummingLoop;
	protected EffectSound m_SoundTurnOn;
	protected EffectSound m_SoundTurnOff;

	void Msp_Fridge_Base()
	{
		m_AllowedMSPCargo = {"SodaCan_ColorBase", "Bottle_Base", "Edible_Base"};
		m_MSPCargoTagName = "isEdibleCargo";
	}

	//--- POWER EVENTS
	override void OnSwitchOn()
	{
		super.OnSwitchOn();
		
		//sound (client only)
		SoundTurnOn();
	}

	override void OnSwitchOff()
	{
		super.OnSwitchOff();
		
		//sound (client only)
		SoundTurnOff();
	}
	
	override void OnWorkStart()
	{	
		//sound (client only)
		SoundHummingStart();
	}

	override void OnWorkStop()
	{		
		//sound (client only)
		SoundHummingStop();
	}

	override bool IsElectricAppliance()
	{
		return true;
	}
	
	//================================================================
	// SOUNDS
	//================================================================
	protected void SoundHummingStart()
	{
		PlaySoundSetLoop( m_SoundHummingLoop, SOUND_HUMMING, 0.1, 0.3 );
	}
	
	protected void SoundHummingStop()
	{
		StopSoundSet( m_SoundHummingLoop );
	}	

	protected void SoundTurnOn()
	{
		PlaySoundSet( m_SoundTurnOn, SOUND_TURN_ON, 0, 0);
	}
	
	protected void SoundTurnOff()
	{
		PlaySoundSet( m_SoundTurnOff, SOUND_TURN_OFF, 0, 0);
	}

	override void SoundOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "MSP_RefrigeratorOpen_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	
	override void SoundClosePlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "MSP_RefrigeratorClose_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}

	override void SetActions()
	{
		super.SetActions();		
		AddAction(ActionUnplugThisByCord);
		AddAction(ActionTurnOnWhileOnGround);
		AddAction(ActionTurnOffWhileOnGround);
	}
};