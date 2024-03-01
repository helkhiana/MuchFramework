modded class PluginManager
{
    override void Init()
    {
        super.Init();
        RegisterPlugin("PluginMuchProxiesConfig", true, true);
        #ifdef CodeLock
        RegisterPlugin("PluginMuchCodelockConfig", true, true);
        #endif
    }
};