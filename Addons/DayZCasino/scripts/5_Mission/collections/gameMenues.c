class GameMenues
{
	private ref BetDiceMenue betDiceMenue;
	private ref BlackJackMenu blackJackMenu;
	private CasinoConfig casinoConfig;
	
	void GameMenues(CasinoConfig casinoConfigExt) {
		DebugMessageCasino("Load GameMenues");
		casinoConfig = casinoConfigExt;
		DebugMessageCasino("check config dice menue" + casinoConfig.positionDice);
	}
		
	BaseMenu GetGameMenue(DayZPlayer player) {		
		vector posPlayer = player.GetPosition();
		
		if (!betDiceMenue) {
			DebugMessageCasino("No selectedMenue");
			betDiceMenue = new BetDiceMenue(casinoConfig.positionDice);
		}
		if (!blackJackMenu) {
			DebugMessageCasino("No selectedMenue");
			blackJackMenu = new BlackJackMenu(casinoConfig.positionBlackJack);
		}
		
		betDiceMenue.Init();
		
		vector posPlayBetDice = betDiceMenue.GetPosition();
		
		float playerDistanceToGamePositionBetDice = vector.Distance(posPlayBetDice, posPlayer);

		if (playerDistanceToGamePositionBetDice <= DAYZ_CASINO_DISTANCE_TO_GAME)
		{
			DebugMessageCasino("in near of bet dice");
			
			return betDiceMenue;
		}
		
		vector posPlayBlackJack = blackJackMenu.GetPosition();
		float playerDistanceToGamePositionBlackJack = vector.Distance(posPlayBlackJack, posPlayer);
		
		if (playerDistanceToGamePositionBlackJack <= DAYZ_CASINO_DISTANCE_TO_GAME || DAYZ_CASINO_DEBUG)
		{
			DebugMessageCasino("in near of black jack");
			
			return blackJackMenu;
		}
	
		DebugMessageCasino("not in near of a game.");
		return null;
	}
	
	void CloseAllMenue(){
		if (betDiceMenue) {
			DebugMessageCasino("No selectedMenue");
			betDiceMenue.Close();
		}
	}
	
	void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (!betDiceMenue) {
			DebugMessageCasino("No selectedMenue");
			betDiceMenue = new BetDiceMenue(casinoConfig.positionDice);
		}
		
		betDiceMenue.HandleEvents(sender, target, rpc_type, ctx);
	}
}