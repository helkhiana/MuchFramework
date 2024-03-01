#ifdef CodeLock
modded class CodeLock : ItemBase
{    
    override void NewUnlockServer(EntityAI player, EntityAI parent)
    {
        if (!GetGame().IsServer() || !GetGame().IsMultiplayer())
            return;
        ItemBase itemBase = ItemBase.Cast(parent);
        if (itemBase && itemBase.IsKindOf("Msp_Openable_Base") || itemBase.IsKindOf("Msp_Openable_Placeable_Base") || itemBase.IsKindOf("Msp_Greenhouse_Base"))
        {
            itemBase.Open();
            
            player.ServerDropEntity( this );
            SetPosition(player.GetPosition());
        }

        super.NewUnlockServer(player, parent);
    }

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionAttachCodeLockToMSP);
    }
};
#endif