class Msp_Lamp_Light extends PointLightBase
{
	static float m_TorchRadius = 10;
	static float m_TorchBrightness = 3.0;
	
	void Msp_Lamp_Light()
	{
		SetVisibleDuringDaylight(false);
		SetRadiusTo( m_TorchRadius );
		SetBrightnessTo(m_TorchBrightness);
		SetCastShadow(true);
        SetFlareVisible(false);
		FadeIn(0.5);
		SetFadeOutTime(0.1);
		SetDiffuseColor(1.0, 0.7, 0.5);
		SetAmbientColor(1.0, 0.7, 0.5);
		SetFlickerAmplitude(0.3);
		SetFlickerSpeed(0.75);
		SetDancingShadowsMovementSpeed(0.005);
		SetDancingShadowsAmplitude(0.003);
	}
};

class Msp_Lamp_Base : Msp_Item 
{    
    protected PointLightBase m_Light;
	protected string LIGHT_MEMORY_POS = "light";
	
	protected string MATERIAL_ON 	= "PATH\\TO\\YOUR\\RVMAT_ON.rvmat";
	protected string MATERIAL_OFF = "PATH\\TO\\YOUR\\RVMAT_OFF.rvmat";

	//sound
	protected string SOUND_TURN_ON		= "spotlight_turn_on_SoundSet";
	protected string SOUND_TURN_OFF		= "spotlight_turn_off_SoundSet";
	
	protected EffectSound m_SoundTurnOn;
	protected EffectSound m_SoundTurnOff;
	
	//--- POWER EVENTS
	override void OnSwitchOn()
	{
		super.OnSwitchOn();
		
		//sound (client only)
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if(player && player.IsPlacingLocal())
		{
			return;
		}
		SoundTurnOn();
	}

	override void OnSwitchOff()
	{
		super.OnSwitchOff();
		
		//sound (client only)
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if(player && player.IsPlacingLocal())
		{
			return;
		}
		SoundTurnOff();
	}
	
	override void OnWorkStart()
	{
		CreateLight();
		//refresh visual
		SetObjectMaterial( 1, MATERIAL_ON );
	}

	override void OnWorkStop()
	{
		if (m_Light)
			m_Light.FadeOut();
		
		//refresh visual
		SetObjectMaterial( 1, MATERIAL_OFF );		
	}

	void CreateLight()
    {
		#ifndef SERVER
        m_Light = PointLightBase.Cast(ScriptedLightBase.CreateLight(Msp_Lamp_Light, GetPosition()));
        m_Light.AttachOnMemoryPoint(this, LIGHT_MEMORY_POS);
        #endif
    }
	//================================================================
	// SOUNDS
	//================================================================

	protected void SoundTurnOn()
	{
		PlaySoundSet( m_SoundTurnOn, SOUND_TURN_ON, 0.01, 0.01 );
	}
	
	protected void SoundTurnOff()
	{
		PlaySoundSet( m_SoundTurnOff, SOUND_TURN_OFF, 0.01, 0.01 );
	}	
	
	override void SetActions()
	{
		super.SetActions();		
		AddAction(ActionTurnOnWhileOnGround);
		AddAction(ActionTurnOffWhileOnGround);
	}
};