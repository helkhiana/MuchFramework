#ifdef CodeLock
modded class CodeLockServerRPC : PluginBase
{
    override void OpenTarget(ItemBase target)
    {
        TentBase tent = TentBase.Cast(target);
        if ((target.IsKindOf("Msp_Openable_Base") || target.IsKindOf("Msp_Openable_Placeable_Base") || target.IsKindOf("Msp_Greenhouse_Base")) && !target.IsOpen())
            target.Open();
        super.OpenTarget(target);
    }
};
#endif