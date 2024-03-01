class Msp_OpenableContainer : Msp_ItemBase
{
	protected bool m_IsOpened;
	protected bool m_IsOpenedLocal;
	
	void Msp_OpenableContainer()
	{		
		RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
		RegisterNetSyncVariableBool("m_IsOpened");
	}
	
	override void EEInit()
	{
		super.EEInit();		
        if(IsOpen())
			Open();
		else
			Close();
	}

	override void Open()
	{
		m_IsOpened = true;
		SoundSynchRemote();
		UpdateVisualState();
		GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
		super.Open();
	}

	override void Close()
	{
		super.Close();
		m_IsOpened = false;
		SoundSynchRemote();
		UpdateVisualState();
		GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
	}

#ifdef EXPANSIONMODBASEBUILDING
	override bool IsNonExpansionOpenable()
	{
		return true;
	}
#endif	

	override bool IsOpen()
	{
		return m_IsOpened;
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if ( m_IsOpened != m_IsOpenedLocal )
		{		
			if ( IsOpen() && IsSoundSynchRemote() && !IsBeingPlaced() )
			{
				SoundOpenPlay();
			}
			
			if ( !IsOpen() && IsSoundSynchRemote() && !IsBeingPlaced() )
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
	}
	
	void SoundClosePlay()
	{
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
			#ifdef CodeLock				
				return GetMuchCodelockConfig() && GetMuchCodelockConfig().CanAttach();
			#else
				return false;
			#endif
		}
		return super.CanDisplayAttachmentCategory(category_name);
	}

	//investigation needed
    #ifdef CodeLock
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        CodeLock c_Lock;
        if (Class.CastTo(c_Lock, attachment))
		{
			return GetMuchCodelockConfig() && GetMuchCodelockConfig().CanAttach();
		}

        return super.CanReceiveAttachment(attachment, slotId);
    }
    #endif

	override void SetActions()
	{
		super.SetActions();
        AddAction(ActionCustomOpen);
        AddAction(ActionCustomClose);
		#ifdef CodeLock
        AddAction(ActionInteractLockOnMSP);
        AddAction(ActionManageLockOnMSP);
        AddAction(ActionLockAdminOnMSP);
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