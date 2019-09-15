modded class MissionGameplay 
{
	ref GameMenues m_gameMenues;
	ref CasinoConfig casinoConfig;
	
	
	void MissionGameplay() {
		DebugMessageCasino("init Mission MissionGameplay");
		
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
		
		Param1<PlayerBase> paramGetConfig = new Param1<PlayerBase>(GetGame().GetPlayer());
	    GetGame().RPCSingleParam(paramGetConfig.param1, DAYZ_CASINO_GET_CASINO_CONFIG, paramGetConfig, true);
	}
	
	void ~MissionGameplay() {
		GetDayZGame().Event_OnRPC.Remove(HandleEvents);
	}
	
	void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (rpc_type == DAYZ_CASINO_GET_CASINO_CONFIG_RESPONSE) {
			DebugMessageCasino("player recive config");
			Param1 <ref CasinoConfig> casinoConfigParam;
			if (ctx.Read(casinoConfigParam)){
				casinoConfig = casinoConfigParam.param1;
				DebugMessageCasino("player load config" + casinoConfig.positionDice);
				m_gameMenues = new GameMenues(casinoConfig);
			}
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		autoptr DayZPlayer player = GetGame().GetPlayer();
		
		UAInput localInput = GetUApi().GetInputByName("UAInputPlayCasinoGame");	
		
		if(player) {
			if (localInput.LocalClick()){
				BaseMenu currentGameMenu = m_gameMenues.GetGameMenue(player);
				if (GetGame().GetUIManager().GetMenu() == null && currentGameMenu && !currentGameMenu.isMenuOpen && player.IsAlive()) {
					DebugMessageCasino("key press open");
					currentGameMenu.OnShow();
				} else if (currentGameMenu && currentGameMenu.isMenuOpen) {
					DebugMessageCasino("key pres close");
					currentGameMenu.CloseMenu();
				}
			}
			if (!player.IsAlive() && m_gameMenues){
				m_gameMenues.CloseAllMenue();
			}
		}			
	}
}