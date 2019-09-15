class GameMenues
{
	private ref BetDiceMenue betDiceMenue;
	private CasinoConfig casinoConfig;
	
	void GameMenues(CasinoConfig casinoConfigExt) {
		casinoConfig = casinoConfigExt;
		DebugMessageCasino("Load GameMenues");
		DebugMessageCasino("check config dice menue" + casinoConfig.positionDice);
	}
		
	BaseMenu GetGameMenue(DayZPlayer player) {		
		vector posPlayer = player.GetPosition();
		
		if (!betDiceMenue) {
			DebugMessageCasino("No selectedMenue");
			betDiceMenue = new BetDiceMenue(casinoConfig.positionDice);
		}
		
		betDiceMenue.Init();
		
		vector posPlay = betDiceMenue.GetPosition();
		
		if (!posPlayer) {
			DebugMessageCasino("No player");
		}
		if (!posPlay) {
			DebugMessageCasino("No gameposition");
		}
		
		float playerDistanceToGamePosition = vector.Distance(posPlayer, posPlay);

		if (playerDistanceToGamePosition <= DAYZ_CASINO_DISTANCE_TO_GAME || DAYZ_CASINO_DEBUG)
		{
			DebugMessageCasino("in near of a game return position");
			
			return betDiceMenue;
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