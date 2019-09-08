modded class MissionGameplay 
{
	ref GameMenues m_gameMenues;
	
	void MissionGameplay() {
		DebugMessageCasino("init Mission MissionGameplay");
		GetDayZGame().Event_OnRPC.Insert(OnRPC);
		m_gameMenues = new GameMenues;
	}
	
	void ~MissionGameplay() {
		GetDayZGame().Event_OnRPC.Remove(OnRPC);
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		autoptr DayZPlayer player = GetGame().GetPlayer();
		
		UAInput localInput = GetUApi().GetInputByName("UAInputPlayCasinoGame");	
		
		if(player && player.IsAlive() && localInput.LocalClick()) {
			BaseMenu currentGameMenu = m_gameMenues.GetGameMenue(player);
			DebugMessageCasino("key press");
			if (GetGame().GetUIManager().GetMenu() == null && currentGameMenu && !currentGameMenu.isMenuOpen) {
				DebugMessageCasino("key press open");
				currentGameMenu.OnShow();
			} else if (currentGameMenu && currentGameMenu.isMenuOpen) {
				DebugMessageCasino("key pres close");
				currentGameMenu.CloseMenu();
			}
		}			
	}
	
	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		m_gameMenues.HandleEvents(sender, target, rpc_type, ctx);
	}
	
}