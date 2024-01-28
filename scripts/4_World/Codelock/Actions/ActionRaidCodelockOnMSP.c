#ifdef CodeLock
class ActionRaidCodelockOnMSPCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        float raidTime = 15;
        if(GetMuchCodelockConfig())
        {
            raidTime = GetMuchCodelockConfig().Get_RaidTimeInSeconds() / GetDayZGame().GetCodeLockConfig().GetIncrementAmount(); // config value to minutes
        }
        
        
        m_ActionData.m_ActionComponent = new CAContinuousRepeat(raidTime);
    }
}

class ActionRaidCodelockOnMSP : ActionContinuousBase
{
    protected float m_LockHealth;
    protected float m_MaxHealth;

    void ActionRaidCodelockOnMSP()
    {
        m_CallbackClass = ActionRaidCodelockOnMSPCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
        m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_MEDIUM;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINonRuined;
        m_ConditionTarget = new CCTNone;
    }

    override string GetText() {
        int healthPercentage = (m_LockHealth / m_MaxHealth) * 100;
        return "Destroy Codelock | HP: " + healthPercentage + "%";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
		ItemBase itemBase = ItemBase.Cast(target.GetObject());
        CodeLock codelock;
        m_LockHealth = 0;
        m_MaxHealth = 0;

        if (itemBase && (itemBase.IsKindOf("Msp_Openable_Placeable_Base")|| itemBase.IsKindOf("Msp_Openable_Base") || itemBase.IsKindOf("Msp_Greenhouse_Base")))
        {
            if(!GetMuchCodelockConfig())
            {
                return false;
            }
            
            ItemBase itemInHands = ItemBase.Cast(item);
            if(!itemInHands)
                itemInHands = player.GetItemInHands();
            array<string> raidTools = GetMuchCodelockConfig().Get_RaidTools();
            if(raidTools.Find(itemInHands.GetType()) == -1)
                return false;

            Class.CastTo(codelock, itemBase.GetCodeLock());

            if (codelock && GetMuchCodelockConfig().CanRaid()) 
            {
                m_LockHealth = codelock.GetSynchronizedHealth();
                m_MaxHealth = codelock.GetMaxHealth("", "Health");
                return true;
            }
        }       

        return false;
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        if(!GetMuchCodelockConfig())
        {
            return;
        }
        if (!GetMuchCodelockConfig().CanRaid())
        {
            return;
        }

        ItemBase itemBase = ItemBase.Cast(action_data.m_Target.GetObject());
        float raidIncrementAmount = m_MaxHealth / GetDayZGame().GetCodeLockConfig().GetIncrementAmount();
        int toolDamage = GetMuchCodelockConfig().Get_ToolDamageOnRaid();

        if (itemBase)
        {
            CodeLock codelock = itemBase.GetCodeLock();

            if (codelock) 
            {
                codelock.AddHealth("", "Health", -raidIncrementAmount);

                m_LockHealth = codelock.GetHealth();

                codelock.SetSynchronizedHealth(m_LockHealth);

                if (m_LockHealth > 0) 
                {
                    GetCodeLockLogger().WriteLog("RAID", action_data.m_Player.GetIdentity(), codelock.GetPosition(), "", false, false, raidIncrementAmount, m_LockHealth);
                } 
                else 
                {
                    codelock.UnlockServer(action_data.m_Player, itemBase);

                    if (GetMuchCodelockConfig().ShouldDeleteLockOnRaid())
                        codelock.Delete();                        
                    if (toolDamage > 0)
                        action_data.m_MainItem.DecreaseHealth(toolDamage, false);
                    GetCodeLockLogger().WriteLog("RAID", action_data.m_Player.GetIdentity(), codelock.GetPosition(), "", false, true);
                }
            }
        }
    }

    override string GetAdminLogMessage(ActionData action_data)
    {
        return " destroyed CodeLock on " + action_data.m_Target.GetObject().GetDisplayName() + " at " + action_data.m_Player.GetPosition();
    }
};
#endif