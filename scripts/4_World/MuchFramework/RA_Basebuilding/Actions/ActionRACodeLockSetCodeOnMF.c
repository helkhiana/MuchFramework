#ifdef RA_BASEBUILDING
class ActionRACodeLockSetCodeOnMF : ActionInteractBase
{
    protected string lockState;

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNone;
		m_Text = "Set Code";
		m_Sound = "BeepSound";
    }

    override typename GetInputType()
    {
        return ContinuousInteractActionInput;
    }

    override bool HasProgress()
    {
        return false;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
        ItemBase itemBase = ItemBase.Cast(target.GetObject());
        RA_CodeLock code_lock;

        if (itemBase && !itemBase.IsOpen())
        {
            code_lock = RA_CodeLock.Cast(itemBase.FindCodeLock());

            if (code_lock)
            {                
                return code_lock.GetState() == CodeLockState.PENDING;
            }
        }
        return false;
	}
	
	override void OnExecuteClient(ActionData action_data)
	{
		super.OnExecuteClient(action_data);
		
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
            code_lock.TrySetCode(code);
            code_lock.CloseMenu();
		}		
	}
};
#endif