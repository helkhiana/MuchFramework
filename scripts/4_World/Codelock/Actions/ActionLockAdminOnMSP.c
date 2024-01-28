#ifdef CodeLock
class ActionLockAdminOnMSP : ActionInteractBase
{
    protected string lockState;

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNone;
    }

    override string GetText()
    {
        return lockState;
    }

    override bool IsInstant()
    {
        return true;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        ItemBase itemBase = ItemBase.Cast(target.GetObject());
        CodeLock codelock;

        if (itemBase && !itemBase.IsOpen())
        {
            codelock = CodeLock.Cast(itemBase.GetCodeLock());

            if (codelock)
            {
                if (codelock.GetLockState())
                {
                    if (GetCLPermissionManager().UserIsAdmin(player.GetIdentity().GetPlainId()))
                    {
                        lockState = "Admin Lock";
                        return true;
                    }
                }
            }
        }
        return false;
    }

    override void OnStartClient(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
        ItemBase itemBase = ItemBase.Cast(action_data.m_Target.GetObject());
        CodeLock codelock;

        if (itemBase)
        {
            codelock = CodeLock.Cast(itemBase.GetCodeLock());

            if (codelock)
            {
                if (codelock.GetLockState())
                {
                    if (GetCLPermissionManager().UserIsAdmin())
                    {
                        GetCLUIManager().ShowMenu(CLMENU.ADMIN_CODE_MENU, itemBase);
                    }
                }
            }
        }
    }
};
#endif