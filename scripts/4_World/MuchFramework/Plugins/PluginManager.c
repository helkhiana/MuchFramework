modded class PluginManager
{
    override void Init()
    {
        super.Init();
        RegisterPlugin("PluginMuchProxiesConfig", true, true);
        RegisterPlugin("PluginMuchCodelockConfig", true, true);
        RegisterPlugin("PluginMFSettingsConfig", true, true);
    }
};