#ifdef RA_BASEBUILDING
class ActionRaidRACodeLockOnMFCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        float raidTime = 15;
        if(GetMuchCodelockConfig())
        {
            raidTime = GetMuchCodelockConfig().Get_RaidTimeInSeconds() / 5; // config value to minutes
        }
        
        
        m_ActionData.m_ActionComponent = new CAContinuousRepeat(raidTime);
    }
}

class ActionRaidRACodeLockOnMF : ActionContinuousBase
{

    void ActionRaidRACodeLockOnMF()
    {
        m_CallbackClass = ActionRaidRACodeLockOnMFCB;
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

    override string GetText() 
    {
        return "Destroy Codelock";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
		ItemBase itemBase = ItemBase.Cast(target.GetObject());
        RA_CodeLock code_lock;

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
            if(raidTools && raidTools.Find(itemInHands.GetType()) == -1)
                return false;

            Class.CastTo(code_lock, itemBase.FindCodeLock());

            if (code_lock && GetMuchCodelockConfig().CanRaid()) 
            {
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

        if (itemBase)
        {
            RA_CodeLock code_lock = RA_CodeLock.Cast(itemBase.FindCodeLock());

            if (code_lock) 
            {
		        float maxHealth = code_lock.GetMaxHealth("", "Health");
		        float raidIncrementAmount = maxHealth / 5;
                code_lock.AddHealth("", "Health", -raidIncrementAmount);

                float lockHealth = code_lock.GetHealth();
                if (lockHealth > 0) 
                {
                    //GetCodeLockLogger().WriteLog("RAID", action_data.m_Player.GetIdentity(), code_lock.GetPosition(), "", false, false, raidIncrementAmount, lockHealth);
                } 
                else 
                {
                    code_lock.SetState(CodeLockState.PENDING);
                    
                    #ifdef SERVER
                    Msp_ItemBase mspitembase = Msp_ItemBase.Cast(action_data.m_Target.GetObject());
                    if(mspitembase && mspitembase.IsMFVirtualStorageEnabled())
                    {
                        mspitembase.RestoreMFInventory(action_data.m_Player);
                    }
                    #endif
                    itemBase.Open();
                    if (GetMuchCodelockConfig().ShouldDeleteLockOnRaid())
                    {    
                        action_data.m_Player.ServerDropEntity(code_lock);
                        code_lock.Delete();
                    }
					
        			int toolDamage = GetMuchCodelockConfig().Get_ToolDamageOnRaid(); 
                    if (toolDamage > 0)
                    {   		
						action_data.m_MainItem.DecreaseHealth(toolDamage, false);
					}
                    //GetCodeLockLogger().WriteLog("RAID", action_data.m_Player.GetIdentity(), codelock.GetPosition(), "", false, true);
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