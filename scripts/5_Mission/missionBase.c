modded class MissionBase 
{
    override UIScriptedMenu CreateScriptedMenu(int id) 
    {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (!menu && id == MSP_Constants.MF_NOTICE_UI) 
        {
            menu = new MF_ItemDropWarningMenu;
            if (menu) 
            {
                menu.SetID(id);
            }
        }
        return menu;
    }
};