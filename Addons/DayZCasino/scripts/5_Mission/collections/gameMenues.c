class GameMenues
{
	private ref BetDiceMenue betDiceMenue;
	private ref CasinoConfig casinoConfig;
	
	
	void GameMenues() {
		DebugMessageCasino("Load GameMenues");
		
		casinoConfig = new CasinoConfig;
		
		JsonFileLoader<ref CasinoConfig>.JsonFileLoader("$profile:DayZCasion/config.json", casinoConfig);
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
	
	
	
	void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (!betDiceMenue) {
			DebugMessageCasino("No selectedMenue");
			betDiceMenue = new BetDiceMenue();
		}
		
		betDiceMenue.HandleEvents(sender, target, rpc_type, ctx);
	}
	
}