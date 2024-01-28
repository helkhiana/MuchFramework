#ifdef CodeLock
class ActionManageLockOnMSP : ActionInteractBase
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
                    if (isOwner)
                    {
                        lockState = "Manage Lock";
                        return true;
                    }
                    else if (codelock.HasNoOwner())
                    {
                        lockState = "Claim Ownership";
                        return true;
                    }
                }
            }
        }
        return false;
    }

    override bool CanContinue(ActionData action_data)
    {
        return true;
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
                    if (codelock.IsOwner(identity.GetId()))
                    {
                        GetCLUIManager().ShowMenu(CLMENU.ENTER_CODE_MENU, itemBase);
                    }
                    else if (codelock.HasNoOwner())
                    {
                        GetCLUIManager().ShowMenu(CLMENU.CLAIM_CODE_MENU, itemBase);
                    }
                }
            }
        }
    }

    override void CreateAndSetupActionCallback(ActionData action_data)
    {
        super.CreateAndSetupActionCallback(action_data);
    }
};
#endif