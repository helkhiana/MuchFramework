#ifdef RA_BASEBUILDING
class ActionRACodeLockAuthenticateOnMF : ActionInteractBase
{
    protected string lockState;

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNone;
		m_Text = "Enter Code";
		m_Sound = "BeepSound";
    }

    override bool IsInstant()
    {
        return true;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        ItemBase itemBase = ItemBase.Cast(target.GetObject());
        RA_CodeLock codelock;

        if (itemBase && !itemBase.IsOpen())
        {
            codelock = RA_CodeLock.Cast(itemBase.FindCodeLock());

            if (codelock)
            {               
                bool notauthorized = !codelock.IsAuthorized(player.GetIdentity());
                bool locked = codelock.IsLocked();
                return  notauthorized && locked;
            }
        }
        return false;
    }

    override void OnStartClient(ActionData action_data)
    {
        ItemBase itemBase = ItemBase.Cast(action_data.m_Target.GetObject());
        if (itemBase)
        {
            RA_CodeLock code_lock = RA_CodeLock.Cast(itemBase.FindCodeLock());
            if (code_lock) 
            {
                code_lock.OpenMenu(ScriptCaller.Create(OnCodeComplete));
            }            
        }
    }
	
	protected void OnCodeComplete(RA_CodeLock code_lock, string code)
	{
		if (code_lock) 
        {
		    code_lock.TryAuthorize(code, ScriptCaller.Create(OnAuthorizationAttempt));
		}		
	}
	
	protected void OnAuthorizationAttempt(RA_CodeLock code_lock, bool success)
	{
		if (!code_lock) 
        {
			return;
		}
		
		if (!success) 
        {
			CodeLockViewMenu code_lock_menu = code_lock.GetMenu();
			if (code_lock_menu) 
            {
				code_lock_menu.OnAuthenticationFailed();
			}
			
			return;
		}
		
		// close if succesful
		code_lock.CloseMenu();
	}
};
#endif