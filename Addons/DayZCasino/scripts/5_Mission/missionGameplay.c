modded class MissionGameplay 
{
	ref GameMenues m_gameMenues;
	
	void MissionGameplay() {
		DebugMessageCasino("init Mission MissionGameplay");
		m_gameMenues = new GameMenues;
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
			} else if (currentGameMenu && currentGameMenu.isMenuOpen && DAYZ_CASINO_DEBUG) {
				DebugMessageCasino("key pres close");
				currentGameMenu.CloseMenu();
			}
		}			
	}
}