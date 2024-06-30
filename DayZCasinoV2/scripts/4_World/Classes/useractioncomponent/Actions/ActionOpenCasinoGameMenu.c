class ActionOpenCasinoGameMenu: ActionInteractBase {

    override string GetText() {
        return "#openGame";
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTObject(UAMaxDistances.REPAIR);
    }

    override void OnStartClient(ActionData action_data) {
        super.OnStartClient(action_data);

        if(g_Game.GetUIManager().GetMenu() != NULL) return;

        BaseMenu currentGameMenu = GameMenu.Get().GetGameMenu(action_data.m_Target.GetObject().GetPosition());
        if(GetGame().GetUIManager().GetMenu() == null && currentGameMenu && !currentGameMenu.isMenuOpen) {
            currentGameMenu.Init();
            GetGame().GetUIManager().ShowScriptedMenu(currentGameMenu, NULL);
        }
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!target) return false;
        if(!GetGame().IsServer() && g_Game.GetUIManager().GetMenu() != NULL) return false;

        CasinoConfig config = CasinoConfig.Get();
        if(!config.luckyWheelSettings) return false;

        if(!config.HasType(target.GetObject().GetType())) return false;


        return config.HasPosition(target.GetObject().GetPosition());
    }
}
