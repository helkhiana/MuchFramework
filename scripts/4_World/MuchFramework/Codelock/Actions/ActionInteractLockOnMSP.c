#ifdef CodeLock
class ActionInteractLockOnMSP : ActionInteractBase
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
                bool isOwner = codelock.IsOwner(player.GetIdentity().GetId());
                bool isGuest = codelock.IsGuest(player.GetIdentity().GetId());

                if (player && !GetDayZGame().CLIsActionRateLimited())
                {
                    auto params = new Param1<CodeLock>(codelock);
                    GetGame().RPCSingleParam(player, CLRPC.RPC_SERVER_SYNCHLOCK, params, true);
                    GetDayZGame().SetCLActionRateLimit();
                }
                if (codelock.GetLockState())
                {
                    if (isOwner || isGuest)
                    {
                        lockState = "Open Locked Door";
                    }
                    else if (!codelock.HasNoOwner())
                    {
                        lockState = "Enter Passcode";
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    lockState = "Set Passcode";
                }
                return true;
            }
        }
        return false;
    }

    override void OnStartClient(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
        EntityAI targetObject = EntityAI.Cast(action_data.m_Target.GetObject());
        ItemBase itemBase = ItemBase.Cast(targetObject);
        CodeLock codelock;

        if (itemBase)
        {
            codelock = CodeLock.Cast(itemBase.GetCodeLock());

            if (codelock)
            {
                if (codelock.GetLockState())
                {
                    if (!codelock.IsOwner(identity.GetId()) && !codelock.IsGuest(identity.GetId()))
                    {
                        GetCLUIManager().ShowMenu(CLMENU.GUEST_CODE_MENU, itemBase);
                    }
                }
                else
                {
                    GetCLUIManager().ShowMenu(CLMENU.SET_CODE_MENU, itemBase);
                }
            }
        }
    }

    override void OnStartServer(ActionData action_data)
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
                    if (codelock.IsOwner(identity.GetId()) || codelock.IsGuest(identity.GetId()))
                    {
                        GetCodeLockLogger().WriteLog("acceSS", action_data.m_Player.GetIdentity(), codelock.GetPosition());
                        itemBase.Open();
                    }
                }
            }
        }
    }
};
#endif