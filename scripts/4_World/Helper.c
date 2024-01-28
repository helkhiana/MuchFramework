static void Much_Print(string message)
{
    PluginWriteLog m_Logger = PluginWriteLog.Cast(GetPlugin(PluginWriteLog));
    if(m_Logger)
    {
        m_Logger.Log(message);
    }
}

static ref array<EntityAI> MakeACopyOfEntityAIArray(array<EntityAI> OtherArray)
{
    array<EntityAI> NewArray = new array<EntityAI>;
    foreach( EntityAI item : OtherArray )
    {
        NewArray.Insert(item);
    }
    return NewArray;
}

