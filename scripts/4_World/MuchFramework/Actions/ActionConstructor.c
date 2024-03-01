modded class ActionConstructor 
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);
        actions.Insert(ActionDismantleItem);
        actions.Insert(ActionCustomClose);
        actions.Insert(ActionCustomOpen);
        actions.Insert(ActionFoldItem);
        actions.Insert(ActionPackWithHands);
        actions.Insert(ActionTrashItems);
        
        #ifdef CodeLock
        actions.Insert(ActionRaidCodelockOnMSP);
        actions.Insert(ActionInteractLockOnMSP);
        actions.Insert(ActionAttachCodeLockToMSP);
        actions.Insert(ActionManageLockOnMSP);
        actions.Insert(ActionLockAdminOnMSP);
        #endif
    }
};