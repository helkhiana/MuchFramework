class Msp_OpenableContainer : Msp_ItemBase
{
	protected bool m_IsOpened;
	protected bool m_IsOpenedLocal;
	protected float m_LastCloseUnixTime = 0;
	protected string m_MF_OpenSoundSet = "";
	protected string m_MF_CloseSoundSet = "";
	protected vector m_MF_OpenCloseSoundPosition = "0 0 0";

	void Msp_OpenableContainer()
	{		
		RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
		RegisterNetSyncVariableBool("m_IsOpened");
	}

	override void Open()
	{
		m_IsOpened = true;
		ResetAutoMFTimer();
		UpdateVisualState();
		GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
		super.Open();
		SetSynchDirty();
	}

	override void Close()
	{
		super.Close();
		m_IsOpened = false;
		ResetAutoMFTimer();
		UpdateVisualState();
		GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
		SetSynchDirty();
	}

	override bool IsOpen()
	{
		return m_IsOpened;
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if ( m_IsOpened != m_IsOpenedLocal )
		{		
			if ( IsOpen() && !IsBeingPlaced() )
			{
				SoundOpenPlay();
			}
			
			if ( !IsOpen() && !IsBeingPlaced() )
			{
				SoundClosePlay();
			}	
			m_IsOpenedLocal = m_IsOpened;
		}
		
		ShowHideMspProxies();
		UpdateVisualState();
	}
	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );		
		ctx.Write( m_IsOpened );
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;
		
		if (!ctx.Read( m_IsOpened ) )
			return false;
		
		if ( m_IsOpened )
			Open();
		else
			Close();
		
		return true;
	}

	override void LoadMFStoreVariables()
	{
		super.LoadMFStoreVariables();
		MF_VirtualStorage_Settings vsSettings = MFSettings.GetSettings().VirtualStorage;
		if(vsSettings)
		{
			m_HasAutoStoreOnCloseEnabled = vsSettings.EnableAutoStoreOnClose;
		}	
		MF_Openable_Settings openSettings = MFSettings.GetSettings().Openables;
		if(openSettings)
		{
			m_HasAutoCloseEnabled =  openSettings.EnableAutoClose;
			m_AutoCloseTimerInSeconds = openSettings.AutoCloseTimerInSeconds;
		}
		SetSynchDirty();
	}

	override void ResetAutoMFTimer()
	{		
		super.ResetAutoMFTimer();
		m_LastCloseUnixTime = 0;
	}
	
	override void OnCEUpdate()
	{
		super.OnCEUpdate();
		AutoCloseMF();
	}
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		Close();
	}

	void AutoCloseMF()
	{
		if(!IsMFAutoCloseTimerEnabled())
		{
			return;
		}
		if(!IsOpen())
		{
			return;
		}
		m_LastCloseUnixTime += m_ElapsedSinceLastUpdate;
		if(m_LastCloseUnixTime >= m_AutoCloseTimerInSeconds)
		{
			ResetAutoMFTimer();
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Close, 0.02, false);
		}
	}	

	void UpdateVisualState()
    {
        if ( IsOpen() )
        {
            SetAnimationPhase("Doors1",1);
            SetAnimationPhase("Doors2",1);
            SetAnimationPhase("Doors3",1);
            SetAnimationPhase("Doors4",1);
        }
        else
        {
            SetAnimationPhase("Doors1",0);
            SetAnimationPhase("Doors2",0);
            SetAnimationPhase("Doors3",0);
            SetAnimationPhase("Doors4",0);
        }
    }
	
	void SoundOpenPlay()
	{
		if(m_MF_OpenSoundSet != "")
		{
			vector soundPos = GetPosition();
			if(m_MF_OpenCloseSoundPosition != "0 0 0")
			{
				soundPos = m_MF_OpenCloseSoundPosition;
			}
			EffectSound sound = SEffectManager.PlaySound( m_MF_OpenSoundSet , soundPos );
			sound.SetSoundAutodestroy( true );
		}
	}
	
	void SoundClosePlay()
	{
		if(m_MF_CloseSoundSet != "")
		{
			vector soundPos = GetPosition();
			if(m_MF_OpenCloseSoundPosition != "0 0 0")
			{
				soundPos = m_MF_OpenCloseSoundPosition;
			}
			EffectSound sound = SEffectManager.PlaySound( m_MF_CloseSoundSet , soundPos );
			sound.SetSoundAutodestroy( true );
		}
	}
	
	override bool IsContainer()
	{
		return true;
	}
	
	override bool CanReleaseCargo(EntityAI attachment)
	{
		return IsOpen() && !GetInventory().IsInventoryLockedForLockType( HIDE_INV_FROM_SCRIPT );
	}

	override bool CanDisplayAttachmentCategory( string category_name )
	{	
		if(category_name == "CodeLock")
		{			
			#ifdef RA_BASEBUILDING		
				return GetMuchCodelockConfig() && GetMuchCodelockConfig().CanAttach();
        	#else
				#ifdef CodeLock		
				return GetMuchCodelockConfig() && GetMuchCodelockConfig().CanAttach();
				#endif
			#endif
			return false;
		}
		return super.CanDisplayAttachmentCategory(category_name);
	}


    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
   	 	#ifdef RA_BASEBUILDING
        RA_CodeLock c_Lock;
        if (Class.CastTo(c_Lock, attachment))
		{
			return GetMuchCodelockConfig() && GetMuchCodelockConfig().CanAttach();
		}
		#else
			#ifdef CodeLock		
       		CodeLock c_Lock;
			if (Class.CastTo(c_Lock, attachment))
			{
				return GetMuchCodelockConfig() && GetMuchCodelockConfig().CanAttach();
			}			
    		#endif
    	#endif

        return super.CanReceiveAttachment(attachment, slotId);
    }

	override void SetActions()
	{
		super.SetActions();
        AddAction(ActionCustomOpen);
        AddAction(ActionCustomClose);
		
        #ifdef RA_BASEBUILDING
        AddAction(ActionRACodeLockAuthenticateOnMF);
        AddAction(ActionRACodeLockSetCodeOnMF);
        AddAction(ActionRaidRACodeLockOnMF);
        #else
			#ifdef CodeLock
			AddAction(ActionInteractLockOnMSP);
			AddAction(ActionManageLockOnMSP);
			AddAction(ActionLockAdminOnMSP);
			#endif
		#endif
	}
};

class Msp_Openable_Base : Msp_OpenableContainer
{
    override bool CanPutInCargo( EntityAI parent )
    {
        return false;
    }
    override bool CanPutIntoHands( EntityAI parent )
    {
        return false;
    }
};

class Msp_Openable_Placeable_Base: Msp_OpenableContainer 
{   
	override bool CanPutInCargo( EntityAI parent )
    {
		if( !super.CanPutInCargo(parent) ) {return false;}
        return IsMspInvEmpty() && !IsOpen();
    }
    
    override bool CanPutIntoHands(EntityAI parent)
	{
		if( !super.CanPutIntoHands(parent) ) {return false;}
		return IsMspInvEmpty() && !IsOpen();
    }

    override bool IsDeployable() 
    {
        return true;
    } 
    
    override void OnInventoryEnter(Man player)
    {
        super.OnInventoryEnter(player);
        GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);        
    }
    
    override void OnInventoryExit(Man player)
    {
        super.OnInventoryExit(player);
        if(IsOpen())
            GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);        
    }

    override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
	}
};